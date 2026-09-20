#!/bin/bash
set -euo pipefail
B=/home/alpha/openvix/build-enviroment
S=$B/builds/openvix/developer/dm900/tmp/work/cortexa15hf-neon-vfpv4-oe-linux-gnueabi/wpewebkit/2.54.0/sources/wpewebkit-2.54.0
F=Source/cmake/GStreamerChecks.cmake
OUT=$B/meta-hbbtv2/recipes-browser/wpewebkit/files
mkdir -p "$OUT"

W=$(mktemp -d)
mkdir -p "$W/a/Source/cmake" "$W/b/Source/cmake"
cp "$S/$F" "$W/a/$F"
cp "$S/$F" "$W/b/$F"

python3 - "$W/b/$F" <<'EOF'
import sys
p = sys.argv[1]
s = open(p).read()
old = """          if (ENABLE_VIDEO)
              list(APPEND GSTREAMER_COMPONENTS video mpegts tag gl)
          endif ()
"""
new = """          if (ENABLE_VIDEO)
              list(APPEND GSTREAMER_COMPONENTS video tag)
              if (USE_GSTREAMER_MPEGTS)
                  list(APPEND GSTREAMER_COMPONENTS mpegts)
              endif ()
              if (USE_GSTREAMER_GL)
                  list(APPEND GSTREAMER_COMPONENTS gl)
              endif ()
          endif ()
"""
assert s.count(old) == 1, "anchor not found exactly once"
open(p, "w").write(s.replace(old, new))
EOF

PATCH="$OUT/0001-GStreamerChecks-only-require-gl-and-mpegts-when-enabled.patch"
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] GStreamerChecks: only require gl and mpegts when enabled"
  echo
  echo "With ENABLE_VIDEO the gl and mpegts GStreamer components were always added"
  echo "to the REQUIRED find_package() list, even with USE_GSTREAMER_GL=OFF and"
  echo "USE_GSTREAMER_MPEGTS=OFF. Only require them when the matching option is on,"
  echo "so a target without gst-gl (no OpenGL distro feature) can build with video."
  echo
  echo "---"
  (cd "$W" && diff -u a/$F b/$F) || true
} > "$PATCH"

rm -rf "$W"
cat "$PATCH"
# sanity: does it apply cleanly to a pristine copy?
cd "$S" && patch -p1 --dry-run < "$PATCH"
