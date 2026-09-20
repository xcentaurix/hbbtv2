#!/bin/bash
# Hand cross-compile wpe_fb against the build-7 WPE runtime + headers (no bitbake needed).
set -uo pipefail
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
COMP=$T/sysroots-components/cortexa15hf-neon-vfpv4
CC=$T/sysroots-components/x86_64/gcc-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-gcc
# use the matching cross binutils (as/ld) that OE builds with; the system ones do not know armv7ve+simd
for d in binutils-cross-arm gcc-cross-arm; do
  b=$(find $T/sysroots-components/x86_64/$d/usr/bin -maxdepth 2 -type d -name 'arm-oe-linux-gnueabi' 2>/dev/null | head -1)
  [ -n "$b" ] && PATH="$b:$PATH"
done
export PATH
# gcc calls plain `as`/`ld`: shim them to the ARM cross binutils so it never picks the host x86 ones
SHIM=/home/alpha/wpe-test/tcshim
BU=$(dirname "$(find $T/sysroots-components/x86_64/binutils-cross-arm -name 'arm-oe-linux-gnueabi-as' | head -1)")
mkdir -p "$SHIM"
for t in as ld; do
  if   [ -e "$BU/arm-oe-linux-gnueabi-$t.bfd" ]; then ln -sf "$BU/arm-oe-linux-gnueabi-$t.bfd" "$SHIM/$t"
  else ln -sf "$BU/arm-oe-linux-gnueabi-$t" "$SHIM/$t"; fi
done
ls -la "$SHIM" | awk '{print $9, $10, $11}' | tail -2
X=/home/alpha/wpe-test/xsys
RT=/home/alpha/wpe-test/pkg/rt
DEV=/home/alpha/wpe-test/pkg/dev
SRC=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-shot/files/wpe_fb.c
OUT=/home/alpha/wpe-test/deploy/bin/wpe_fb

if [ ! -d "$X/usr/include/glib-2.0" ]; then
  rm -rf "$X"; mkdir -p "$X"
  for c in glibc linux-libc-headers libgcc gcc-runtime glib-2.0 libffi libpcre2 zlib libsoup util-linux util-linux-libuuid libxkbcommon; do
    [ -d "$COMP/$c" ] && cp -a "$COMP/$c/." "$X/" || echo "note: component $c not present"
  done
fi

ls "$X/usr/include/libsoup-3.0" >/dev/null 2>&1 || echo "WARN: libsoup-3.0 headers not found in sysroot"

"$CC" -B"$SHIM/" --sysroot="$X" -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a15 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -Os -Wall \
  "$SRC" -o "$OUT" \
  -I"$DEV/usr/include/wpe-webkit-2.0" -I"$DEV/usr/include/wpe-webkit-2.0/wpe-platform" -I"$X/usr/include/libsoup-3.0" \
  -I"$X/usr/include/glib-2.0" -I"$X/usr/lib/glib-2.0/include" \
  -L"$RT/usr/lib" -L"$X/usr/lib" -L"$X/lib" \
  "$RT/usr/lib/libWPEWebKit-2.0.so.1.11.3" -lgio-2.0 -lgobject-2.0 -lglib-2.0 \
  -Wl,--allow-shlib-undefined -Wl,-rpath-link,"$RT/usr/lib" -Wl,-rpath-link,"$X/usr/lib" 2>&1 | head -40
echo "compile exit: ${PIPESTATUS[0]}"
ls -la "$OUT" 2>&1 | awk '{print $5, $NF}'
file "$OUT" 2>&1 | cut -c1-140
readelf -d "$OUT" 2>/dev/null | grep NEEDED | sed 's/.*Shared library: //' | tr '\n' ' '; echo
