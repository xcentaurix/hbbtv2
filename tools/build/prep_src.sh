#!/bin/bash
# Prepare a persistent, patched WPE WebKit source tree for OE's externalsrc (incremental rebuilds).
set -euo pipefail
B=/home/alpha/openvix/build-enviroment
TARBALL=$(ls $B/sources/wpewebkit-2.54.0.tar.xz)
LAYER=$B/meta-hbbtv2/recipes-browser/wpewebkit/files
WKF=$B/meta-webkit/recipes-browser/wpewebkit/files
W=/home/alpha/wpe-src
SRC=$W/wpewebkit-2.54.0

rm -rf "$W"; mkdir -p "$W"
echo "extracting $TARBALL"
tar -xf "$TARBALL" -C "$W"
cd "$SRC"

# 0003: make the default-EGL-display fallback available for WPE (it is compiled for WPE already, only guarded out)
mkdir -p /tmp/p3/a /tmp/p3/b; rm -rf /tmp/p3/a/* /tmp/p3/b/*
FILES="Source/WebCore/platform/graphics/egl/PlatformDisplayDefault.h Source/WebCore/platform/graphics/egl/PlatformDisplayDefault.cpp Source/WebKit/WebProcess/glib/WebProcessGLib.cpp"
for f in $FILES; do
  mkdir -p "/tmp/p3/a/$(dirname $f)" "/tmp/p3/b/$(dirname $f)"
  cp "$f" "/tmp/p3/a/$f"; cp "$f" "/tmp/p3/b/$f"
done
python3 - $FILES <<'EOF'
import sys
old = "PLATFORM(GTK) || OS(ANDROID)"
new = "PLATFORM(GTK) || PLATFORM(WPE) || OS(ANDROID)"
for f in sys.argv[1:]:
    p = "/tmp/p3/b/" + f
    s = open(p).read()
    n = s.count(old)
    assert n == 2, "%s: expected 2 occurrences, found %d" % (f, n)
    open(p, "w").write(s.replace(old, new))
print("edited 3 files, 2 guard occurrences each")
EOF
P3="$LAYER/0003-Enable-default-EGL-display-fallback-for-WPE.patch"
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] Enable the default EGL display fallback for WPE"
  echo
  echo "WebProcess::initializePlatformDisplayIfNeeded() tries GBM, then the Mesa"
  echo "surfaceless platform, then (GTK/Android only) PlatformDisplayDefault, and"
  echo "otherwise aborts with 'no supported platform available'. WPE already compiles"
  echo "PlatformDisplayDefault.cpp (SourcesWPE.txt) but its guards exclude WPE."
  echo "On EGL stacks without EGL_MESA_platform_surfaceless or GBM (vendor set-top"
  echo "box drivers such as Broadcom V3D) plain eglGetDisplay(EGL_DEFAULT_DISPLAY) is"
  echo "the only working way to get a display, and it supports surfaceless contexts."
  echo
  echo "---"
  (cd /tmp/p3 && diff -u a/Source/WebCore/platform/graphics/egl/PlatformDisplayDefault.h b/Source/WebCore/platform/graphics/egl/PlatformDisplayDefault.h) || true
  (cd /tmp/p3 && diff -u a/Source/WebCore/platform/graphics/egl/PlatformDisplayDefault.cpp b/Source/WebCore/platform/graphics/egl/PlatformDisplayDefault.cpp) || true
  (cd /tmp/p3 && diff -u a/Source/WebKit/WebProcess/glib/WebProcessGLib.cpp b/Source/WebKit/WebProcess/glib/WebProcessGLib.cpp) || true
} > "$P3"

echo "--- applying patches in order"
for p in "$WKF/0001-bmalloc-libpas-avoid-C-stdatomic-in-C-build.patch" \
         "$WKF/0002-WebDriver-Fix-build-when-logging-is-disabled.patch" \
         "$LAYER/0001-GStreamerChecks-only-require-gl-and-mpegts-when-enabled.patch" \
         "$LAYER/0002-AcceleratedBackingStore-guard-DRM_FORMAT-with-USE-LIBDRM.patch" \
         "$P3"; do
  echo "* $(basename $p)"
  patch -p1 --no-backup-if-mismatch < "$p" | sed 's/^/    /'
done

echo "--- git baseline for future patch generation"
git init -q
git -c user.name=hbbtv2 -c user.email=noreply@localhost add -A >/dev/null 2>&1
git -c user.name=hbbtv2 -c user.email=noreply@localhost commit -q -m "WPE WebKit 2.54.0 + patches 0001-0003 (baseline)" && echo committed
du -sh "$SRC" | cut -f1
