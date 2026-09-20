#!/bin/bash
# Cross-compile gl_bench against the Dreambox vendor EGL (libvc5dream) headers/libs from the build tree.
set -uo pipefail
SP=/mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
CC=$T/sysroots-components/x86_64/gcc-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-gcc
SHIM=/home/alpha/wpe-test/tcshim
X=/home/alpha/wpe-test/xsys
V=$(ls -d $T/sysroots-components/dm900/libvc5dream $T/sysroots-components/cortexa15hf-neon-vfpv4/libvc5dream 2>/dev/null | head -1)
echo "vendor EGL component: $V"
ls "$V/usr/lib" 2>/dev/null | head; ls "$V/usr/include" 2>/dev/null | head -5
OUT=/home/alpha/wpe-test/deploy/bin/gl_bench
"$CC" -B"$SHIM/" --sysroot="$X" -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a15 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -Os -Wall \
  "$SP/gl_bench.c" -o "$OUT" -I"$T/sysroots-components/cortexa15hf-neon-vfpv4/libvc5driver/usr/include" -I"$V/usr/include" -L"$V/usr/lib" -lEGL -lGLESv2 \
  -Wl,--allow-shlib-undefined -Wl,-rpath-link,"$V/usr/lib" 2>&1 | head -30
echo "compile exit: ${PIPESTATUS[0]}"
ls -la "$OUT" 2>&1 | awk '{print $5, $NF}'
readelf -d "$OUT" 2>/dev/null | grep NEEDED | sed 's/.*Shared library: //' | tr '\n' ' '; echo
