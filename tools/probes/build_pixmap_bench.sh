#!/bin/bash
# usage: build_pixmap_bench.sh [pixmap_bench | pixmap_bench2]
# Cross-compile pixmap_bench (spike S1) against the Dreambox vendor EGL headers/libs from the build tree, like build_gl_bench.sh.
# Sources and headers: this directory (include/ion_dream.h = enigma2 interfaces/ion.h, include/EGL/dreameglplatform.h = Dream Property, MIT). The build
# copies them to the scratchpad pmb/ dir first (WSL cannot see U:): mkdir -p $SP/EGL; cp pixmap_bench*.c include/ion_dream.h $SP; cp include/EGL/*.h $SP/EGL
set -uo pipefail
SP=/mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad/pmb
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
CC=$T/sysroots-components/x86_64/gcc-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-gcc
SHIM=/home/alpha/wpe-test/tcshim
X=/home/alpha/wpe-test/xsys
V=$(ls -d $T/sysroots-components/dm900/libvc5dream $T/sysroots-components/cortexa15hf-neon-vfpv4/libvc5dream 2>/dev/null | head -1)
NAME=${1:-pixmap_bench}
OUT=/home/alpha/wpe-test/deploy/bin/$NAME
"$CC" -B"$SHIM/" --sysroot="$X" -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a15 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -O2 -Wall \
  "$SP/$NAME.c" -o "$OUT" -I"$SP" -I"$T/sysroots-components/cortexa15hf-neon-vfpv4/libvc5driver/usr/include" -I"$V/usr/include" -L"$V/usr/lib" -lEGL -lGLESv2 \
  -Wl,--allow-shlib-undefined -Wl,-rpath-link,"$V/usr/lib" 2>&1 | head -40
echo "compile exit: ${PIPESTATUS[0]}"
ls -la "$OUT" 2>&1 | awk '{print $5, $NF}'
