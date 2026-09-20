#!/bin/bash
set -euo pipefail
cd /home/alpha/wpe-src/wpewebkit-2.54.0
G=Source/WebCore/platform/gstreamer
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-browser/wpewebkit/files
git add -A && git -c user.name=hbbtv2 -c user.email=noreply@localhost commit -q -m "apply patch 0011" || true
python3 - <<'PY'
def edit(path, old, new, count=1):
    s = open(path).read()
    assert s.count(old) == count, (path, old[:70], s.count(old))
    open(path, "w").write(s.replace(old, new))

c = "Source/WebCore/platform/gstreamer/GStreamerHolePunchQuirkDreambox.cpp"
edit(c, '''    GST_DEBUG("Dreambox video plane: view rect %d,%d %dx%d -> dst %d,%d %dx%d", rect.x(), rect.y(), rect.width(), rect.height(), left, top, right - left, bottom - top);
''', '''    GST_DEBUG("Dreambox video plane: view rect %d,%d %dx%d -> dst %d,%d %dx%d", rect.x(), rect.y(), rect.width(), rect.height(), left, top, right - left, bottom - top);
    if (getenv("WPE_DREAM_VIDEO_DRYRUN")) { // tests: say where the plane would go, without touching it (the live service may be using it)
        fprintf(stderr, "Dreambox video plane (dry run): view rect %d,%d %dx%d -> dst %d,%d %dx%d\\n", rect.x(), rect.y(), rect.width(), rect.height(), left, top, right - left, bottom - top);
        return true;
    }
''')
PY
git diff --stat | tail -3
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] GStreamer: Dreambox hole punch - WPE_DREAM_VIDEO_DRYRUN for tests"
  echo
  echo "Log where the video plane would be put instead of writing /proc/stb/vmpeg/0/dst_*, so that the mapping can be tested while"
  echo "the live service is using the plane."
  echo
  echo "---"
  git diff --no-color -- $G
} > $LAYER/0012-GStreamer-Dreambox-hole-punch-dry-run.patch
