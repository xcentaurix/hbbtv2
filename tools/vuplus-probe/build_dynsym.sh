#!/bin/bash
# build_dynsym.sh - cross-compile dynsym_dump.c for the box (ARMv7 hard-float), matching build_vu_probe.sh's toolchain setup.
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
CC=$T/sysroots-components/x86_64/gcc-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-gcc
SHIM=/home/alpha/wpe-test/tcshim
X=/home/alpha/wpe-test/xsys
HERE="$(cd "$(dirname "$0")" && pwd)"
OUT="$HERE/dynsym_dump"
"$CC" -B"$SHIM/" --sysroot="$X" -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a15 -Os -Wall "$HERE/dynsym_dump.c" -o "$OUT"
echo "COMPILE_EXIT: $?"
ls -l "$OUT"
