#!/bin/bash
# Build vu_egl_probe for an ARMv7 hard-float box with the cross compiler of an OpenEmbedded build tree (no vendor headers needed: the GPU libraries
# are loaded at run time). The DM900 build tree of this project is used as an example; any arm-*-gcc with a glibc sysroot does it.
# usage: build_vu_probe.sh [output file]     (WSL)
# Not built with _TIME_BITS=64: the binary then also runs on an image with an older glibc than the one it was built against.
set -uo pipefail
HERE=$(cd "$(dirname "$0")" && pwd)
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
CC=$T/sysroots-components/x86_64/gcc-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-gcc
SHIM=/home/alpha/wpe-test/tcshim   # as/ld shims of the hand cross builds of this project
X=/home/alpha/wpe-test/xsys        # merged sysroot
OUT=${1:-$HERE/vu_egl_probe}
"$CC" -B"$SHIM/" --sysroot="$X" -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a15 -Os -Wall "$HERE/vu_egl_probe.c" -o "$OUT" -ldl -lm
echo "compile exit: $?"
ls -l "$OUT" | awk '{print $5, $NF}'
readelf -d "$OUT" | grep NEEDED | sed 's/.*Shared library: //' | tr '\n' ' '; echo
readelf -V "$OUT" | grep -o 'GLIBC_[0-9.]*' | sort -u | tr '\n' ' '; echo   # the newest glibc symbol version it needs
