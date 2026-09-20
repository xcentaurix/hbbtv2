#!/bin/bash
set -euo pipefail
B=/home/alpha/openvix/build-enviroment
S=$B/builds/openvix/developer/dm900/tmp/work/cortexa15hf-neon-vfpv4-oe-linux-gnueabi/wpewebkit/2.54.0/sources/wpewebkit-2.54.0
F=Source/WebKit/UIProcess/wpe/AcceleratedBackingStore.cpp
OUT=$B/meta-hbbtv2/recipes-browser/wpewebkit/files
SP=/mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad
LOG=/home/alpha/wpe-build7.log
mkdir -p "$OUT"

W=$(mktemp -d)
mkdir -p "$W/a/$(dirname $F)" "$W/b/$(dirname $F)"

if grep -q "UNUSED_PARAM(dmaBuffer)" "$S/$F"; then
  echo "source already fixed in place; regenerating patch from git-less pristine is not possible, skipping patch generation"
else
  cp "$S/$F" "$W/a/$F"
  cp "$S/$F" "$W/b/$F"
  python3 - "$W/b/$F" <<'EOF'
import sys
p = sys.argv[1]
s = open(p).read()
old = """        SkAlphaType alphaType = kPremul_SkAlphaType;
        if (wpe_buffer_dma_buf_get_format(dmaBuffer) == DRM_FORMAT_XRGB8888)
            alphaType = kOpaque_SkAlphaType;
"""
new = """        SkAlphaType alphaType = kPremul_SkAlphaType;
#if USE(LIBDRM)
        if (wpe_buffer_dma_buf_get_format(dmaBuffer) == DRM_FORMAT_XRGB8888)
            alphaType = kOpaque_SkAlphaType;
#else
        UNUSED_PARAM(dmaBuffer);
#endif
"""
assert s.count(old) == 1, "anchor not found exactly once"
open(p, "w").write(s.replace(old, new))
EOF
  PATCH="$OUT/0002-AcceleratedBackingStore-guard-DRM_FORMAT-with-USE-LIBDRM.patch"
  {
    echo "From: HbbTV2 experiment <noreply@localhost>"
    echo "Subject: [PATCH] AcceleratedBackingStore: guard DRM_FORMAT_XRGB8888 with USE(LIBDRM)"
    echo
    echo "drm_fourcc.h is only included when USE(LIBDRM) (or on Android), and the"
    echo "DRM_FORMAT_ARGB8888 use further down is guarded, but the DRM_FORMAT_XRGB8888"
    echo "use in getImageInfoFromBuffer() was not, so a build with -DUSE_LIBDRM=OFF and"
    echo "the WPE Platform API fails to compile."
    echo
    echo "---"
    (cd "$W" && diff -u a/$F b/$F) || true
  } > "$PATCH"
  cat "$PATCH"
  # apply in place (same change the patch describes) and prove the patch matches
  cp "$W/b/$F" "$S/$F"
fi
rm -rf "$W"

cat > "$SP/chain.sh" <<'EOF'
#!/bin/bash
SP=/mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad
# force only do_compile (build dir is kept, so ninja rebuilds just what failed), then finish the recipe
bash "$SP/bb.lf.sh" -f -c compile wpewebkit
bash "$SP/bb.lf.sh" wpewebkit
EOF

echo "launching detached: log $LOG"
setsid nohup nice -n 10 bash "$SP/chain.sh" > "$LOG" 2>&1 < /dev/null &
sleep 2
pgrep -af "bin/bitbake" | head -2 | cut -c1-100
