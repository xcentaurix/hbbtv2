#!/bin/bash
set -euo pipefail
cd /home/alpha/wpe-src/wpewebkit-2.54.0
G=Source/WebCore/platform/gstreamer
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-browser/wpewebkit/files
git checkout -q -- $G/GStreamerQuirks.cpp Source/WebCore/platform/SourcesGStreamer.txt
rm -f $G/GStreamerQuirkDreambox.h $G/GStreamerQuirkDreambox.cpp $G/GStreamerHolePunchQuirkDreambox.h $G/GStreamerHolePunchQuirkDreambox.cpp

cat > $G/GStreamerQuirkDreambox.h <<'EOF'
/*
 * Dreambox (Broadcom, gst-plugin-dvbmediasink) quirk: audio goes to dvbaudiosink, the hardware decoder path is
 * used for video through GStreamerHolePunchQuirkDreambox. Enable with WEBKIT_GST_QUIRKS=dreambox.
 */

#pragma once

#if USE(GSTREAMER)

#include "GStreamerQuirks.h"

namespace WebCore {

class GStreamerQuirkDreambox final : public GStreamerQuirk {
public:
    GStreamerQuirkDreambox() = default;
    const ASCIILiteral identifier() const final { return "Dreambox"_s; }
    bool isPlatformSupported() const final;

    GstElement* createAudioSink() final;
    std::optional<bool> isHardwareAccelerated(GstElementFactory*) final;
    unsigned getAdditionalPlaybinFlags() const final { return getGstPlayFlag("native-video") | getGstPlayFlag("native-audio"); }
};

} // namespace WebCore

#endif // USE(GSTREAMER)
EOF

cat > $G/GStreamerQuirkDreambox.cpp <<'EOF'
#include "config.h"
#include "GStreamerQuirkDreambox.h"

#if USE(GSTREAMER)

#include "GStreamerCommon.h"

namespace WebCore {

bool GStreamerQuirkDreambox::isPlatformSupported() const
{
    GRefPtr videoSink = adoptGRef(gst_element_factory_find("dvbvideosink"));
    GRefPtr audioSink = adoptGRef(gst_element_factory_find("dvbaudiosink"));
    return videoSink && audioSink;
}

GstElement* GStreamerQuirkDreambox::createAudioSink()
{
    return makeGStreamerElement("dvbaudiosink"_s);
}

std::optional<bool> GStreamerQuirkDreambox::isHardwareAccelerated(GstElementFactory* factory)
{
    auto view = StringView::fromLatin1(GST_OBJECT_NAME(factory));
    if (view.startsWith("dvb"_s))
        return true;

    return std::nullopt;
}

} // namespace WebCore

#endif // USE(GSTREAMER)
EOF

cat > $G/GStreamerHolePunchQuirkDreambox.h <<'EOF'
/*
 * Dreambox hole-punch quirk: the video element's area is punched transparent in the page and the decoded video is
 * shown by the hardware video plane (dvbvideosink). The plane is positioned through /proc/stb/vmpeg/0/dst_*, which,
 * like in enigma2's eVideoWidget, take coordinates in a 720x576 space that spans the whole output.
 *
 * The page does not know where it sits on the screen, so the embedder tells it:
 *   WPE_DREAM_VIDEO_ORIGIN=x,y     screen position of the web view's top-left corner (default 0,0)
 *   WPE_DREAM_VIDEO_SCREEN=WxH     size of the screen/OSD the view is placed on (default 1920x1080)
 * Enable with WEBKIT_GST_HOLE_PUNCH_QUIRK=dreambox (plus WEBKIT_GST_QUIRKS=dreambox for the audio sink).
 */

#pragma once

#if USE(GSTREAMER)

#include "GStreamerQuirks.h"

namespace WebCore {

class GStreamerHolePunchQuirkDreambox final : public GStreamerHolePunchQuirk {
public:
    const ASCIILiteral identifier() const final { return "DreamboxHolePunch"_s; }

    GstElement* createHolePunchVideoSink(bool, const MediaPlayer*) final;
    bool setHolePunchVideoRectangle(GstElement*, const IntRect&) final;
    bool requiresClockSynchronization() const final { return false; }
};

} // namespace WebCore

#endif // USE(GSTREAMER)
EOF

cat > $G/GStreamerHolePunchQuirkDreambox.cpp <<'EOF'
#include "config.h"
#include "GStreamerHolePunchQuirkDreambox.h"

#if USE(GSTREAMER)

#include "GStreamerCommon.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>

namespace WebCore {

GstElement* GStreamerHolePunchQuirkDreambox::createHolePunchVideoSink(bool, const MediaPlayer*)
{
    return makeGStreamerElement("dvbvideosink"_s, "DreamboxVideoSink"_s);
}

static void writeVideoProc(const char* name, int value)
{
    char path[64];
    snprintf(path, sizeof(path), "/proc/stb/vmpeg/0/dst_%s", name);
    if (FILE* f = fopen(path, "w")) {
        fprintf(f, "%08x\n", static_cast<unsigned>(value));
        fclose(f);
    }
}

bool GStreamerHolePunchQuirkDreambox::setHolePunchVideoRectangle(GstElement*, const IntRect& rect)
{
    static int originX = 0, originY = 0, screenW = 1920, screenH = 1080;
    static bool configured = false;
    static IntRect lastRect;
    if (!configured) {
        configured = true;
        if (const char* origin = getenv("WPE_DREAM_VIDEO_ORIGIN"))
            sscanf(origin, "%d,%d", &originX, &originY);
        if (const char* screen = getenv("WPE_DREAM_VIDEO_SCREEN"))
            sscanf(screen, "%dx%d", &screenW, &screenH);
        if (screenW <= 0 || screenH <= 0) {
            screenW = 1920;
            screenH = 1080;
        }
    }
    if (rect == lastRect)
        return true;
    lastRect = rect;

    // view pixels -> screen pixels -> the driver's 720x576 output space (clamped to it)
    int left = (originX + rect.x()) * 720 / screenW;
    int top = (originY + rect.y()) * 576 / screenH;
    int right = (originX + rect.maxX()) * 720 / screenW;
    int bottom = (originY + rect.maxY()) * 576 / screenH;
    left = std::clamp(left, 0, 720);
    top = std::clamp(top, 0, 576);
    right = std::clamp(right, left, 720);
    bottom = std::clamp(bottom, top, 576);

    GST_DEBUG("Dreambox video plane: view rect %d,%d %dx%d -> dst %d,%d %dx%d", rect.x(), rect.y(), rect.width(), rect.height(), left, top, right - left, bottom - top);
    writeVideoProc("left", left);
    writeVideoProc("top", top);
    writeVideoProc("width", right - left);
    writeVideoProc("height", bottom - top);
    writeVideoProc("apply", 1);
    return true;
}

} // namespace WebCore

#endif // USE(GSTREAMER)
EOF

# register the sources and the two quirks
S=Source/WebCore/platform/SourcesGStreamer.txt
sed -i 's|^platform/gstreamer/GStreamerHolePunchQuirkWesteros.cpp$|platform/gstreamer/GStreamerHolePunchQuirkDreambox.cpp\nplatform/gstreamer/GStreamerHolePunchQuirkWesteros.cpp|' $S
sed -i 's|^platform/gstreamer/GStreamerQuirkWesteros.cpp$|platform/gstreamer/GStreamerQuirkDreambox.cpp\nplatform/gstreamer/GStreamerQuirkWesteros.cpp|' $S
grep -c Dreambox $S | grep -qx 2

Q=$G/GStreamerQuirks.cpp
grep -q '#include "GStreamerQuirkBroadcom.h"' $Q
sed -i 's|^#include "GStreamerHolePunchQuirkBcmNexus.h"|#include "GStreamerHolePunchQuirkBcmNexus.h"\n#include "GStreamerHolePunchQuirkDreambox.h"|' $Q
sed -i 's|^#include "GStreamerQuirkBroadcom.h"|#include "GStreamerQuirkBroadcom.h"\n#include "GStreamerQuirkDreambox.h"|' $Q
sed -i 's|are: amlogic, broadcom, bcmnexus, openmax|are: amlogic, broadcom, bcmnexus, dreambox, openmax|' $Q
sed -i 's|are: fake, bcmnexus, rialto, westeros|are: fake, bcmnexus, dreambox, rialto, westeros|' $Q
python3 - <<'PY'
p = "Source/WebCore/platform/gstreamer/GStreamerQuirks.cpp"
s = open(p).read()
a = '''            else if (WTF::equalLettersIgnoringASCIICase(identifier, "openmax"_s))
                quirk = WTF::makeUnique<GStreamerQuirkOpenMAX>();'''
assert s.count(a) == 1
s = s.replace(a, '''            else if (WTF::equalLettersIgnoringASCIICase(identifier, "dreambox"_s))
                quirk = WTF::makeUnique<GStreamerQuirkDreambox>();
''' + a)
b = '''    else if (WTF::equalLettersIgnoringASCIICase(identifierString.span(), "rialto"_s))
        m_holePunchQuirk = WTF::makeUnique<GStreamerHolePunchQuirkRialto>();'''
assert s.count(b) == 1
s = s.replace(b, '''    else if (WTF::equalLettersIgnoringASCIICase(identifierString.span(), "dreambox"_s))
        m_holePunchQuirk = WTF::makeUnique<GStreamerHolePunchQuirkDreambox>();
''' + b)
open(p, "w").write(s)
PY

git add -N $G/GStreamerQuirkDreambox.h $G/GStreamerQuirkDreambox.cpp $G/GStreamerHolePunchQuirkDreambox.h $G/GStreamerHolePunchQuirkDreambox.cpp
git diff --stat
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] GStreamer: add Dreambox quirk and hole-punch quirk (dvbvideosink/dvbaudiosink)"
  echo
  echo "Dreambox (Broadcom) boxes decode with gst-plugin-dvbmediasink: dvbvideosink drives the hardware video plane, which"
  echo "sits underneath the OSD. Add a quirk (WEBKIT_GST_QUIRKS=dreambox: dvbaudiosink, native audio/video playbin flags)"
  echo "and a hole-punch quirk (WEBKIT_GST_HOLE_PUNCH_QUIRK=dreambox: dvbvideosink; the video element's rectangle is mapped"
  echo "to /proc/stb/vmpeg/0/dst_* in the driver's 720x576 output space)."
  echo
  echo "---"
  git diff --no-color -- $G $S
} > $LAYER/0008-GStreamer-add-Dreambox-quirk-and-hole-punch-quirk.patch
wc -l $LAYER/0008-GStreamer-add-Dreambox-quirk-and-hole-punch-quirk.patch
