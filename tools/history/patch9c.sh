#!/bin/bash
set -euo pipefail
cd /home/alpha/wpe-src/wpewebkit-2.54.0
G=Source/WebCore/platform/gstreamer
M=Source/WebCore/platform/graphics/gstreamer/MediaPlayerPrivateGStreamer.cpp
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-browser/wpewebkit/files
python3 - <<'PY'
def edit(path, old, new, count=1):
    s = open(path).read()
    assert s.count(old) == count, (path, old[:70], s.count(old))
    open(path, "w").write(s.replace(old, new))

G = "Source/WebCore/platform/gstreamer/"
M = "Source/WebCore/platform/graphics/gstreamer/MediaPlayerPrivateGStreamer.cpp"

# --- quirk interface + manager: seek flags and seek completion
edit(G + "GStreamerQuirks.h",
     "    virtual std::optional<GstClockTime> decoderPositionFromSinks(GstElement*, GstElement*) const { return std::nullopt; }\n",
     "    virtual std::optional<GstClockTime> decoderPositionFromSinks(GstElement*, GstElement*) const { return std::nullopt; }\n\n"
     "    // Sinks that never post GST_MESSAGE_ASYNC_DONE after a flushing seek, which is what WebKit waits for to complete it.\n"
     "    virtual bool seekCompletesWithoutAsyncDone() const { return false; }\n"
     "    // Platforms whose decoders cannot cope with some seek flags (e.g. hardware decoders and GST_SEEK_FLAG_ACCURATE).\n"
     "    virtual GstSeekFlags adjustSeekFlags(GstSeekFlags flags) const { return flags; }\n")
edit(G + "GStreamerQuirks.h",
     "    std::optional<GstClockTime> decoderPositionFromSinks(GstElement* audioSink, GstElement* videoSink) const;\n",
     "    std::optional<GstClockTime> decoderPositionFromSinks(GstElement* audioSink, GstElement* videoSink) const;\n"
     "    bool seekCompletesWithoutAsyncDone() const;\n"
     "    GstSeekFlags adjustSeekFlags(GstSeekFlags) const;\n")
edit(G + "GStreamerQuirks.cpp",
     "std::optional<GstClockTime> GStreamerQuirksManager::decoderPositionFromSinks(",
     "bool GStreamerQuirksManager::seekCompletesWithoutAsyncDone() const\n"
     "{\n"
     "    for (const auto& quirk : m_quirks) {\n"
     "        if (quirk->seekCompletesWithoutAsyncDone())\n"
     "            return true;\n"
     "    }\n"
     "    return false;\n"
     "}\n\n"
     "GstSeekFlags GStreamerQuirksManager::adjustSeekFlags(GstSeekFlags flags) const\n"
     "{\n"
     "    for (const auto& quirk : m_quirks)\n"
     "        flags = quirk->adjustSeekFlags(flags);\n"
     "    return flags;\n"
     "}\n\n"
     "std::optional<GstClockTime> GStreamerQuirksManager::decoderPositionFromSinks(")

# --- media player: flags + completion of the seek
edit(M,
     "    auto seekFlags = static_cast<GstSeekFlags>(flag | GST_SEEK_FLAG_ACCURATE);\n",
     "    auto seekFlags = GStreamerQuirksManager::singleton().adjustSeekFlags(static_cast<GstSeekFlags>(flag | GST_SEEK_FLAG_ACCURATE));\n\n"
     "    // With sinks that never post ASYNC_DONE, nothing tells us that the flush is over (and updateStates() does not run for a\n"
     "    // seek in PLAYING): once the seek event has been sent the seek is as complete as it will get, so complete it.\n"
     "    auto completeSeekWithoutAsyncDone = [this, time = target.time] {\n"
     "        if (!GStreamerQuirksManager::singleton().seekCompletesWithoutAsyncDone())\n"
     "            return;\n"
     "        RunLoop::mainSingleton().dispatchAfter(100_ms, [weakThis = ThreadSafeWeakPtr { *this }, time] {\n"
     "            RefPtr protectedThis = weakThis.get();\n"
     "            if (protectedThis && protectedThis->m_isSeeking && !protectedThis->m_isSeekPending && protectedThis->m_seekTarget.time == time)\n"
     "                protectedThis->finishSeek();\n"
     "        });\n"
     "    };\n")
edit(M,
     "        }), data, reinterpret_cast<GDestroyNotify>(destroyAsyncSeekData));\n\n        return true;\n",
     "        }), data, reinterpret_cast<GDestroyNotify>(destroyAsyncSeekData));\n\n        completeSeekWithoutAsyncDone();\n        return true;\n")
edit(M,
     "    auto result = gst_element_send_event(m_pipeline.get(), event.leakRef());\n    if (isSegment ||",
     "    auto result = gst_element_send_event(m_pipeline.get(), event.leakRef());\n    if (result)\n        completeSeekWithoutAsyncDone();\n    if (isSegment ||")

# --- Dreambox quirk: no e2-async (breaks pause/resume), seek flags, decoder position also while paused
q = G + "GStreamerQuirkDreambox.h"
edit(q,
     "    void configureElement(GstElement*, const OptionSet<ElementRuntimeCharacteristics>&) final;\n",
     "    bool seekCompletesWithoutAsyncDone() const final { return true; }\n"
     "    GstSeekFlags adjustSeekFlags(GstSeekFlags) const final;\n")
c = G + "GStreamerQuirkDreambox.cpp"
s = open(c).read()
start = s.index("// The dvb sinks ignore changes")
end = s.index("// What the sinks report to position queries")
s = s[:start] + '''// The hardware decoders cannot drop the frames that lead from a keyframe to an accurate seek target the way a software
// decoder does: after a FLUSH | ACCURATE seek the output stalled. enigma2's own player (eServiceMP3) seeks to the nearest
// keyframe with FLUSH | KEY_UNIT, which the sinks handle: the decoder restarts at the keyframe and pause/resume work.
GstSeekFlags GStreamerQuirkDreambox::adjustSeekFlags(GstSeekFlags flags) const
{
    return static_cast<GstSeekFlags>((flags & ~GST_SEEK_FLAG_ACCURATE) | GST_SEEK_FLAG_KEY_UNIT);
}

''' + s[end:]
old = '''        if (GST_STATE(sink) != GST_STATE_PLAYING) // paused: the decoder time is not meaningful, use the regular query
            continue;
        gint64 position = GST_CLOCK_TIME_NONE;
        g_signal_emit_by_name(sink, "get-decoder-time", &position);
        if (GST_CLOCK_TIME_IS_VALID(position))
            return static_cast<GstClockTime>(position);
'''
new = '''        // Before the first frame the driver reports garbage (hours); while paused the plain pipeline query is wrong and the
        // decoder time is frozen at the right value.
        if (GST_STATE(sink) < GST_STATE_PAUSED)
            continue;
        gint64 position = GST_CLOCK_TIME_NONE;
        g_signal_emit_by_name(sink, "get-decoder-time", &position);
        if (GST_CLOCK_TIME_IS_VALID(position) && position < static_cast<gint64>(12 * 3600) * GST_SECOND)
            return static_cast<GstClockTime>(position);
'''
assert s.count(old) == 1
s = s.replace(old, new)
open(c, "w").write(s)
PY
git diff --stat | tail -8
OLD=$LAYER/0009-GStreamer-Dreambox-e2-async-and-decoder-position.patch
NEW=$LAYER/0009-GStreamer-Dreambox-decoder-position-and-seeking.patch
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] GStreamer: Dreambox sinks - decoder position, seek flags and seek completion"
  echo
  echo "Measured with a GStreamer-only probe on a DM900 (dvbvideosink/dvbaudiosink through playbin):"
  echo " - position queries on the sinks/pipeline return what has been pushed into the driver (the whole clip a second after"
  echo "   start) or garbage; the decoder's real position is the sinks' get-decoder-time action signal (what enigma2 uses):"
  echo "   new GStreamerQuirk::decoderPositionFromSinks() hook."
  echo " - FLUSH | ACCURATE seeks stall the hardware output; FLUSH | KEY_UNIT (as enigma2 does) works, pause/resume too:"
  echo "   new GStreamerQuirk::adjustSeekFlags() hook."
  echo " - the sinks stay non-async (async=TRUE breaks pause), so a flushing seek never gets GST_MESSAGE_ASYNC_DONE, which is"
  echo "   what WebKit waits for: new GStreamerQuirk::seekCompletesWithoutAsyncDone() hook, the seek is completed shortly after"
  echo "   the seek event has been sent."
  echo
  echo "---"
  git diff --no-color -- $G $M Source/WebCore/platform/SourcesGStreamer.txt
} > $NEW
rm -f $OLD
grep -c '^+' $NEW
