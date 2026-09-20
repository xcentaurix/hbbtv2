#!/bin/bash
set -uo pipefail
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
COMP=$T/sysroots-components/cortexa15hf-neon-vfpv4
CC=$T/sysroots-components/x86_64/gcc-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-gcc
SHIM=/home/alpha/wpe-test/tcshim
X=/home/alpha/wpe-test/xsys
SRC=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-shot/files/dvb_probe.c
GST=$COMP/gstreamer1.0
[ -d "$GST" ] || { echo "no gstreamer1.0 component"; ls $COMP | grep -i gst; exit 1; }
find $GST -name "gst.h" | head -2
find $GST -name "gstconfig.h" | head -2
find $GST -name "libgstreamer-1.0.so*" | head -2
INC=$(dirname $(dirname $(find $GST -name gst.h | head -1)))
CONF=$(dirname $(find $GST -name gstconfig.h | head -1))
"$CC" -B"$SHIM/" --sysroot="$X" -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a15 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -Os -Wall "$SRC" -o /home/alpha/wpe-test/orb-out/deploy/dvb_probe \
  -I"$INC" -I"$CONF" -I"$X/usr/include/glib-2.0" -I"$X/usr/lib/glib-2.0/include" \
  -L"$GST/usr/lib" -L"$X/usr/lib" -L"$X/lib" -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 \
  -Wl,--allow-shlib-undefined -Wl,-rpath-link,"$GST/usr/lib" -Wl,-rpath-link,"$X/usr/lib" 2>&1 | head -20
ls -la /home/alpha/wpe-test/orb-out/deploy/dvb_probe 2>&1 | awk '{print $5, $NF}'
