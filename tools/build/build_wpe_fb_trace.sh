#!/bin/bash
# Hand-build only wpe_fb (with --orb) for the DM900 as deploy/wpe_fb.trace (same command line as the last step of orb_host_build.sh).
set -uo pipefail
ORB=/home/alpha/orb
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv
F=$LAYER/orb/files
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
C=$T/sysroots-components/cortexa15hf-neon-vfpv4
CC=$T/sysroots-components/x86_64/gcc-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-gcc
SHIM=/home/alpha/wpe-test/tcshim
X=/home/alpha/wpe-test/xsys
RT=/home/alpha/wpe-test/pkg/rt
DEV=/home/alpha/wpe-test/pkg/dev
OUT=/home/alpha/wpe-test/orb-out
ARCH=(-B"$SHIM/" --sysroot="$X" -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a15 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -Os -fPIC -Wno-psabi)
GLIB=(-I"$X/usr/include/glib-2.0" -I"$X/usr/lib/glib-2.0/include")
WPEINC=(-I"$DEV/usr/include/wpe-webkit-2.0" -I"$DEV/usr/include/wpe-webkit-2.0/wpe-platform" -I"$X/usr/include/libsoup-3.0")
"$CC" "${ARCH[@]}" -Wall "$LAYER/wpe-shot/files/wpe_fb.c" -o "$OUT/deploy/wpe_fb.trace" -I"$F" \
  "${WPEINC[@]}" "${GLIB[@]}" -L"$RT/usr/lib" -L"$X/usr/lib" -L"$X/lib" -L"$OUT" \
  "$RT/usr/lib/libWPEWebKit-2.0.so.1.11.3" -lORBHost -lORBCore -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lm \
  -Wl,--allow-shlib-undefined -Wl,-rpath-link,"$RT/usr/lib" -Wl,-rpath-link,"$X/usr/lib" -Wl,-rpath-link,"$OUT" -Wl,-rpath-link,"$C/libxml2/usr/lib" -Wl,-rpath-link,"$C/curl/usr/lib" 2>&1 | head -30
ls -la "$OUT/deploy/wpe_fb.trace" | awk '{print $5, $NF}'
strings -a "$OUT/deploy/wpe_fb.trace" | grep -c -E '^--trace$|^--autoplay$|key-in %s'
