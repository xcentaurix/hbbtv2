#!/bin/bash
set -uo pipefail
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
CC=$T/sysroots-components/x86_64/gcc-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-gcc
SHIM=/home/alpha/wpe-test/tcshim; X=/home/alpha/wpe-test/xsys
SRC=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-shot/files/fb_watch.c
OUT=/home/alpha/wpe-test/deploy/bin/fb_watch
"$CC" -B"$SHIM/" --sysroot="$X" -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a15 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -Os -Wall "$SRC" -o "$OUT" 2>&1 | head -20
echo "compile exit: ${PIPESTATUS[0]}"; ls -la "$OUT" | awk '{print $5}'
