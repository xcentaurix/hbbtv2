#!/bin/bash
# Cross-build the ORB host pieces for the DM900: libORBHost.so, libORBPlatformImpl.so (WPE flavour), libORBWebExt.so, wpe_fb.
set -uo pipefail
ORB=/home/alpha/orb
L=$ORB/rdk/ORB/library
M=$ORB/rdk/ORB/platform-mock
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv
F=$LAYER/orb/files
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
C=$T/sysroots-components/cortexa15hf-neon-vfpv4
GCCB=$T/sysroots-components/x86_64/gcc-cross-arm/usr/bin/arm-oe-linux-gnueabi
CXX=$GCCB/arm-oe-linux-gnueabi-g++
CC=$GCCB/arm-oe-linux-gnueabi-gcc
SHIM=/home/alpha/wpe-test/tcshim
X=/home/alpha/wpe-test/xsys
RT=/home/alpha/wpe-test/pkg/rt
DEV=/home/alpha/wpe-test/pkg/dev
OUT=/home/alpha/wpe-test/orb-out
mkdir -p "$OUT/obj-host" "$OUT/deploy/ext"

ARCH=(-B"$SHIM/" --sysroot="$X" -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a15 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -Os -fPIC -Wno-psabi)
CORE_INC=(-I"$L/src" -I"$L/src/core" -I"$L/src/core/api" -I"$L/src/core/dataTypes" -I"$L/src/core/requestHandlers" -I"$L/src/core/utilities"
          -I"$L/src/platform" -I"$L/src/platform/dataTypes" -I"$L/src/thirdparty" -I"$L/src/thirdparty/nlohmann" -I"$C/libxml2/usr/include/libxml2"
          -I"$C/curl/usr/include" -I"$ORB/components/application_manager")
DEFS=(-std=c++14 -Wno-deprecated-declarations -DRDK -DANDROID_DEBUG -DORB_HBBTV_VERSION=203 -include cstdint)
GLIB=(-I"$X/usr/include/glib-2.0" -I"$X/usr/lib/glib-2.0/include")
WPEINC=(-I"$DEV/usr/include/wpe-webkit-2.0" -I"$DEV/usr/include/wpe-webkit-2.0/wpe-platform" -I"$X/usr/include/libsoup-3.0")
fail=0

echo "== libORBHost.so"
"$CXX" "${ARCH[@]}" "${DEFS[@]}" "${CORE_INC[@]}" -I"$F" -c "$F/orb_host.cpp" -o "$OUT/obj-host/orb_host.o" 2>&1 | grep -E "error|Error" | head;
"$CXX" "${ARCH[@]}" -shared -o "$OUT/libORBHost.so" "$OUT/obj-host/orb_host.o" -L"$OUT" -lORBCore -lpthread \
  -Wl,--allow-shlib-undefined -Wl,-rpath-link,"$OUT" -Wl,-rpath-link,"$C/libxml2/usr/lib" -Wl,-rpath-link,"$C/curl/usr/lib" 2>&1 | head -5
ls -la "$OUT/libORBHost.so" | awk '{print $5, $NF}'

echo "== libORBPlatformImpl.so (WPE platform: mock + overrides)"
"$CXX" "${ARCH[@]}" "${DEFS[@]}" -I"$L/src/platform" -I"$L/src/platform/dataTypes" -I"$M/src" -I"$L/src/thirdparty" -I"$L/src/thirdparty/nlohmann" -I"$F" \
  -c "$F/orb_platform_wpe.cpp" -o "$OUT/obj-host/orb_platform_wpe.o" 2>&1 | grep -E "error" | head
"$CXX" "${ARCH[@]}" -shared -o "$OUT/deploy/libORBPlatformImpl.so" "$OUT/obj-host/orb_platform_wpe.o" "$OUT"/obj-mock/*.o \
  -Wl,--allow-multiple-definition -Wl,--allow-shlib-undefined 2>&1 | head -5
ls -la "$OUT/deploy/libORBPlatformImpl.so" | awk '{print $5, $NF}'

echo "== libORBWebExt.so (web process extension)"
"$CC" "${ARCH[@]}" -Wall -std=gnu11 "${GLIB[@]}" "${WPEINC[@]}" -c "$F/orb_ext.c" -o "$OUT/obj-host/orb_ext.o" 2>&1 | head -20
"$CC" "${ARCH[@]}" -shared -o "$OUT/deploy/ext/libORBWebExt.so" "$OUT/obj-host/orb_ext.o" -L"$X/usr/lib" -L"$X/lib" \
  "$RT/usr/lib/libWPEWebKit-2.0.so.1.11.3" -lgobject-2.0 -lglib-2.0 -lgmodule-2.0 -Wl,--allow-shlib-undefined -Wl,-rpath-link,"$RT/usr/lib" -Wl,-rpath-link,"$X/usr/lib" 2>&1 | head -8
ls -la "$OUT/deploy/ext/libORBWebExt.so" | awk '{print $5, $NF}'

echo "== wpe_fb (with --orb)"
"$CC" "${ARCH[@]}" -Wall "$LAYER/wpe-shot/files/wpe_fb.c" -o "$OUT/deploy/wpe_fb" -I"$F" \
  "${WPEINC[@]}" "${GLIB[@]}" -L"$RT/usr/lib" -L"$X/usr/lib" -L"$X/lib" -L"$OUT" \
  "$RT/usr/lib/libWPEWebKit-2.0.so.1.11.3" -lORBHost -lORBCore -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lm \
  -Wl,--allow-shlib-undefined -Wl,-rpath-link,"$RT/usr/lib" -Wl,-rpath-link,"$X/usr/lib" -Wl,-rpath-link,"$OUT" -Wl,-rpath-link,"$C/libxml2/usr/lib" -Wl,-rpath-link,"$C/curl/usr/lib" 2>&1 | head -30
ls -la "$OUT/deploy/wpe_fb" | awk '{print $5, $NF}'
cp -f "$OUT/libORBHost.so" "$OUT/deploy/"
cp -f "$ORB/out/resources/assets/polyfill/hbbtv.js" "$OUT/deploy/hbbtv.js"
echo "== deploy dir"; ls -la "$OUT/deploy" | awk '{print $5, $NF}'
