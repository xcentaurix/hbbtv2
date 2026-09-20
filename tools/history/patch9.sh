#!/bin/bash
set -euo pipefail
cd /home/alpha/wpe-src/wpewebkit-2.54.0
G=Source/WebCore/platform/gstreamer
M=Source/WebCore/platform/graphics/gstreamer/MediaPlayerPrivateGStreamer.cpp
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-browser/wpewebkit/files
# make patches 0007 and 0008 part of the local baseline, so the diff below is 0009 alone
git add -A && git -c user.name=hbbtv2 -c user.email=noreply@localhost commit -q -m "apply patches 0007 and 0008" || true
python3 - <<'PY'
import re

def edit(path, old, new, count=1):
    s = open(path).read()
    assert s.count(old) == count, (path, old[:60], s.count(old))
    open(path, "w").write(s.replace(old, new))

G = "Source/WebCore/platform/gstreamer/"

# 1) quirk interface: an optional decoder position supplied by the platform's sinks
edit(G + "GStreamerQuirks.h",
     "    virtual std::optional<GstState> eosMediaPlayerState() const { return { }; }\n",
     "    virtual std::optional<GstState> eosMediaPlayerState() const { return { }; }\n\n"
     "    // Position of the platform's decoder(s), for sinks that do not answer position queries with what is on screen.\n"
     "    virtual std::optional<GstClockTime> decoderPositionFromSinks(GstElement*, GstElement*) const { return std::nullopt; }\n")
edit(G + "GStreamerQuirks.h",
     "    GstState eosMediaPlayerState() const;\n",
     "    GstState eosMediaPlayerState() const;\n\n"
     "    std::optional<GstClockTime> decoderPositionFromSinks(GstElement* audioSink, GstElement* videoSink) const;\n")

# 2) manager
edit(G + "GStreamerQuirks.cpp",
     "bool GStreamerQuirksManager::needsCustomInstantRateChange() const\n",
     "std::optional<GstClockTime> GStreamerQuirksManager::decoderPositionFromSinks(GstElement* audioSink, GstElement* videoSink) const\n"
     "{\n"
     "    for (const auto& quirk : m_quirks) {\n"
     "        if (auto position = quirk->decoderPositionFromSinks(audioSink, videoSink))\n"
     "            return position;\n"
     "    }\n"
     "    return std::nullopt;\n"
     "}\n\n"
     "bool GStreamerQuirksManager::needsCustomInstantRateChange() const\n")

# 3) media player: ask the quirks first
edit("Source/WebCore/platform/graphics/gstreamer/MediaPlayerPrivateGStreamer.cpp",
     "    gint64 gstreamerPosition = GST_CLOCK_TIME_NONE;\n    // Asking directly to the sinks and choosing the highest value is faster than asking to the pipeline.\n",
     "    if (auto decoderPosition = GStreamerQuirksManager::singleton().decoderPositionFromSinks(m_audioSink.get(), m_videoSink.get()))\n"
     "        return *decoderPosition;\n\n"
     "    gint64 gstreamerPosition = GST_CLOCK_TIME_NONE;\n    // Asking directly to the sinks and choosing the highest value is faster than asking to the pipeline.\n")

# 4) Dreambox quirk: e2-async on the dvb sinks + decoder position
edit(G + "GStreamerQuirkDreambox.h",
     "    GstElement* createAudioSink() final;\n",
     "    GstElement* createAudioSink() final;\n"
     "    void configureElement(GstElement*, const OptionSet<ElementRuntimeCharacteristics>&) final;\n"
     "    std::optional<GstClockTime> decoderPositionFromSinks(GstElement*, GstElement*) const final;\n")
edit(G + "GStreamerQuirkDreambox.cpp",
     "std::optional<bool> GStreamerQuirkDreambox::isHardwareAccelerated(",
     '''// The dvb sinks ignore changes of their "async" and "sync" properties made by anybody but enigma2's own player, which
// uses the dedicated e2-async / e2-sync properties. With async left off they never post GST_MESSAGE_ASYNC_DONE, and a
// flushing seek in WebKit only completes on that message: the seek stayed "in progress" until the end of the stream.
void GStreamerQuirkDreambox::configureElement(GstElement* element, const OptionSet<ElementRuntimeCharacteristics>&)
{
    auto typeName = StringView::fromLatin1(G_OBJECT_TYPE_NAME(G_OBJECT(element)));
    if (typeName != "GstDVBVideoSink"_s && typeName != "GstDVBAudioSink"_s)
        return;
    if (gstObjectHasProperty(element, "e2-async"_s))
        g_object_set(element, "e2-async", TRUE, nullptr);
}

// What the sinks report to position queries is what has been pushed into the driver, which for a small clip is the whole
// stream a second after it started. The real position of the decoder is available as an action signal, and enigma2's
// own player (eServiceMP3::getPlayPosition) takes it from the audio sink when there is one, from the video sink otherwise.
std::optional<GstClockTime> GStreamerQuirkDreambox::decoderPositionFromSinks(GstElement* audioSink, GstElement* videoSink) const
{
    for (GstElement* sink : { audioSink, videoSink }) {
        if (!sink || !g_signal_lookup("get-decoder-time", G_OBJECT_TYPE(sink)))
            continue;
        if (GST_STATE(sink) != GST_STATE_PLAYING) // paused: the decoder time is not meaningful, use the regular query
            continue;
        gint64 position = GST_CLOCK_TIME_NONE;
        g_signal_emit_by_name(sink, "get-decoder-time", &position);
        if (GST_CLOCK_TIME_IS_VALID(position))
            return static_cast<GstClockTime>(position);
    }
    return std::nullopt;
}

std::optional<bool> GStreamerQuirkDreambox::isHardwareAccelerated(''')
PY

git diff --stat | tail -12
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] GStreamer: quirk hook for the decoder position; Dreambox sinks: e2-async and get-decoder-time"
  echo
  echo "The Dreambox dvb sinks (a) ignore changes of async/sync unless made through e2-async/e2-sync, so a flushing seek never"
  echo "sees GST_MESSAGE_ASYNC_DONE and stays in progress until EOS, and (b) answer position queries with the data pushed into"
  echo "the driver instead of the decoder's position. Enable async through e2-async and take the position from the sinks'"
  echo "get-decoder-time signal, through a new GStreamerQuirk::decoderPositionFromSinks() hook."
  echo
  echo "---"
  git diff --no-color -- $G $M Source/WebCore/platform/SourcesGStreamer.txt
} > $LAYER/0009-GStreamer-Dreambox-e2-async-and-decoder-position.patch
wc -l $LAYER/0009-GStreamer-Dreambox-e2-async-and-decoder-position.patch
