#!/bin/bash
set -euo pipefail
cd /home/alpha/wpe-src/wpewebkit-2.54.0
G=Source/WebCore/platform/gstreamer
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-browser/wpewebkit/files
git add -A && git -c user.name=hbbtv2 -c user.email=noreply@localhost commit -q -m "apply patch 0010" || true
python3 - <<'PY'
def edit(path, old, new, count=1):
    s = open(path).read()
    assert s.count(old) == count, (path, old[:70], s.count(old))
    open(path, "w").write(s.replace(old, new))

G = "Source/WebCore/platform/gstreamer/"
c = G + "GStreamerHolePunchQuirkDreambox.cpp"
edit(c, "    static int originX = 0, originY = 0, screenW = 1920, screenH = 1080;\n",
        "    static int originX = 0, originY = 0, screenW = 1920, screenH = 1080;\n    static double scale = 1.0;\n")
edit(c, '''        if (const char* screen = getenv("WPE_DREAM_VIDEO_SCREEN"))
            sscanf(screen, "%dx%d", &screenW, &screenH);
''', '''        if (const char* screen = getenv("WPE_DREAM_VIDEO_SCREEN"))
            sscanf(screen, "%dx%d", &screenW, &screenH);
        if (const char* factor = getenv("WPE_DREAM_VIDEO_SCALE")) {
            scale = atof(factor);
            if (scale <= 0)
                scale = 1.0;
        }
''')
edit(c, '''    // view pixels -> screen pixels -> the driver's 720x576 output space (clamped to it)
    int left = (originX + rect.x()) * 720 / screenW;
    int top = (originY + rect.y()) * 576 / screenH;
    int right = (originX + rect.maxX()) * 720 / screenW;
    int bottom = (originY + rect.maxY()) * 576 / screenH;
''', '''    // view pixels -> screen pixels (the embedder may show the view scaled up, e.g. a 1280x720 page on a 1920x1080 screen) -> the
    // driver's 720x576 output space (clamped to it)
    int left = static_cast<int>((originX + rect.x() * scale) * 720 / screenW);
    int top = static_cast<int>((originY + rect.y() * scale) * 576 / screenH);
    int right = static_cast<int>((originX + rect.maxX() * scale) * 720 / screenW);
    int bottom = static_cast<int>((originY + rect.maxY() * scale) * 576 / screenH);
''')
edit(G + "GStreamerHolePunchQuirkDreambox.h",
     " *   WPE_DREAM_VIDEO_SCREEN=WxH     size of the screen/OSD the view is placed on (default 1920x1080)\n",
     " *   WPE_DREAM_VIDEO_SCREEN=WxH     size of the screen/OSD the view is placed on (default 1920x1080)\n"
     " *   WPE_DREAM_VIDEO_SCALE=F        the view is shown F times larger than its size (default 1: a 1280x720 page on a\n"
     " *                                  1920x1080 screen is 1.5)\n")
PY
git diff --stat | tail -4
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] GStreamer: Dreambox hole punch - the embedder may show the view scaled"
  echo
  echo "HbbTV applications are laid out at 1280x720 and shown scaled to the whole screen. The hole-punch rectangle of a <video> is in"
  echo "view pixels, so scale it by WPE_DREAM_VIDEO_SCALE before mapping it to the video plane."
  echo
  echo "---"
  git diff --no-color -- $G
} > $LAYER/0011-GStreamer-Dreambox-hole-punch-scale.patch
grep -c '^+' $LAYER/0011-GStreamer-Dreambox-hole-punch-scale.patch
