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

# the hook gets a bound: the driver reports garbage (hours, different every time) until the first frame is shown, so a fixed
# sanity limit is not enough
edit(G + "GStreamerQuirks.h",
     "    virtual std::optional<GstClockTime> decoderPositionFromSinks(GstElement*, GstElement*) const { return std::nullopt; }\n",
     "    // maxPosition: the position cannot be beyond this (the stream's duration plus some slack); values above are garbage.\n"
     "    virtual std::optional<GstClockTime> decoderPositionFromSinks(GstElement*, GstElement*, GstClockTime maxPosition) const { UNUSED_PARAM(maxPosition); return std::nullopt; }\n")
edit(G + "GStreamerQuirks.h",
     "    std::optional<GstClockTime> decoderPositionFromSinks(GstElement* audioSink, GstElement* videoSink) const;\n",
     "    std::optional<GstClockTime> decoderPositionFromSinks(GstElement* audioSink, GstElement* videoSink, GstClockTime maxPosition) const;\n")
edit(G + "GStreamerQuirks.cpp",
     "std::optional<GstClockTime> GStreamerQuirksManager::decoderPositionFromSinks(GstElement* audioSink, GstElement* videoSink) const\n",
     "std::optional<GstClockTime> GStreamerQuirksManager::decoderPositionFromSinks(GstElement* audioSink, GstElement* videoSink, GstClockTime maxPosition) const\n")
edit(G + "GStreamerQuirks.cpp",
     "        if (auto position = quirk->decoderPositionFromSinks(audioSink, videoSink))\n",
     "        if (auto position = quirk->decoderPositionFromSinks(audioSink, videoSink, maxPosition))\n")
edit(M,
     "    if (auto decoderPosition = GStreamerQuirksManager::singleton().decoderPositionFromSinks(m_audioSink.get(), m_videoSink.get()))\n"
     "        return *decoderPosition;\n",
     "    // Only with a known duration: the decoder time is garbage before the first frame and the duration is what bounds it.\n"
     "    gint64 durationForBound = GST_CLOCK_TIME_NONE;\n"
     "    if (m_pipeline && gst_element_query_duration(m_pipeline.get(), GST_FORMAT_TIME, &durationForBound) && GST_CLOCK_TIME_IS_VALID(durationForBound)) {\n"
     "        if (auto decoderPosition = GStreamerQuirksManager::singleton().decoderPositionFromSinks(m_audioSink.get(), m_videoSink.get(), static_cast<GstClockTime>(durationForBound) + 5 * GST_SECOND))\n"
     "            return *decoderPosition;\n"
     "    }\n")
edit(G + "GStreamerQuirkDreambox.h",
     "    std::optional<GstClockTime> decoderPositionFromSinks(GstElement*, GstElement*) const final;\n",
     "    std::optional<GstClockTime> decoderPositionFromSinks(GstElement*, GstElement*, GstClockTime maxPosition) const final;\n")
edit(G + "GStreamerQuirkDreambox.cpp",
     "std::optional<GstClockTime> GStreamerQuirkDreambox::decoderPositionFromSinks(GstElement* audioSink, GstElement* videoSink) const\n",
     "std::optional<GstClockTime> GStreamerQuirkDreambox::decoderPositionFromSinks(GstElement* audioSink, GstElement* videoSink, GstClockTime maxPosition) const\n")
edit(G + "GStreamerQuirkDreambox.cpp",
     "        if (GST_CLOCK_TIME_IS_VALID(position) && position < static_cast<gint64>(12 * 3600) * GST_SECOND)\n",
     "        if (GST_CLOCK_TIME_IS_VALID(position) && static_cast<GstClockTime>(position) <= maxPosition)\n")
edit(G + "GStreamerQuirkDreambox.cpp",
     "        // Before the first frame the driver reports garbage (hours); while paused the plain pipeline query is wrong and the\n"
     "        // decoder time is frozen at the right value.\n",
     "        // Before the first frame the driver reports garbage (hours, a different value every time: maxPosition, the duration\n"
     "        // plus some slack, tells it from a real position); while paused the plain pipeline query is wrong and the decoder\n"
     "        // time is frozen at the right value.\n")
PY
NEW=$LAYER/0009-GStreamer-Dreambox-decoder-position-and-seeking.patch
{
  sed -n '1,/^---$/p' $NEW
  git diff --no-color -- $G $M Source/WebCore/platform/SourcesGStreamer.txt
} > /tmp/new0009 && mv /tmp/new0009 $NEW
grep -c '^+' $NEW
git diff --stat | tail -6
