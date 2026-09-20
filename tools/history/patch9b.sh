#!/bin/bash
set -euo pipefail
cd /home/alpha/wpe-src/wpewebkit-2.54.0
G=Source/WebCore/platform/gstreamer
M=Source/WebCore/platform/graphics/gstreamer/MediaPlayerPrivateGStreamer.cpp
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-browser/wpewebkit/files
python3 - <<'PY'
p = "Source/WebCore/platform/gstreamer/GStreamerQuirkDreambox.cpp"
s = open(p).read()
old = '''    auto typeName = StringView::fromLatin1(G_OBJECT_TYPE_NAME(G_OBJECT(element)));
    if (typeName != "GstDVBVideoSink"_s && typeName != "GstDVBAudioSink"_s)
        return;
    if (gstObjectHasProperty(element, "e2-async"_s))
        g_object_set(element, "e2-async", TRUE, nullptr);
'''
new = '''    // Only the dvb sinks have this property.
    if (gstObjectHasProperty(element, "e2-async"_s))
        g_object_set(element, "e2-async", TRUE, nullptr);
'''
assert s.count(old) == 1
open(p, "w").write(s.replace(old, new))
PY
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
grep -c "^+" $LAYER/0009-GStreamer-Dreambox-e2-async-and-decoder-position.patch
