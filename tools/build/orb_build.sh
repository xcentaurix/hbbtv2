#!/bin/bash
# Cross-compile ORBCore (engine + request handlers + application manager) and the mock ORBPlatform for the DM900.
set -uo pipefail
ORB=/home/alpha/orb
L=$ORB/rdk/ORB/library
M=$ORB/rdk/ORB/platform-mock
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
C=$T/sysroots-components/cortexa15hf-neon-vfpv4
CXX=$T/sysroots-components/x86_64/gcc-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-g++
SHIM=/home/alpha/wpe-test/tcshim
X=/home/alpha/wpe-test/xsys
OUT=/home/alpha/wpe-test/orb-out
mkdir -p "$OUT/obj-core" "$OUT/obj-mock"

COMMON=(-B"$SHIM/" --sysroot="$X" -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a15 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -Os -fPIC -std=c++14
        -Wno-deprecated-declarations -Wno-psabi -DRDK -DANDROID_DEBUG -DORB_HBBTV_VERSION=203 -include cstdint)
INC_CORE=(-I"$L/src" -I"$L/src/core" -I"$L/src/core/api" -I"$L/src/core/dataTypes" -I"$L/src/core/requestHandlers" -I"$L/src/core/utilities"
          -I"$L/src/platform" -I"$L/src/platform/dataTypes" -I"$L/src/thirdparty" -I"$C/libxml2/usr/include/libxml2" -I"$C/curl/usr/include"
          -I"$ORB/components/application_manager")

SRC_CORE=$(cd "$L" && ls src/core/*.cpp src/core/dataTypes/*.cpp src/core/requestHandlers/*.cpp src/core/utilities/*.cpp | tr '\n' ' ')
SRC_APP=$(cd "$ORB/components/application_manager" && ls ait.cpp app.cpp application_manager.cpp utils.cpp xml_parser.cpp | tr '\n' ' ')
echo "core sources: $(echo $SRC_CORE | wc -w), application manager: $(echo $SRC_APP | wc -w)"

compile() { # srcfile objdir
  local o="$2/$(echo "$1" | tr '/' '_').o"
  "$CXX" "${COMMON[@]}" "${INC_CORE[@]}" -c "$1" -o "$o" 2>&1 | grep -E "error|Error" | head -5
  [ -f "$o" ] || echo "FAILED: $1"
}
export -f compile; export CXX; export -a COMMON INC_CORE 2>/dev/null

fail=0
( cd "$L" && for s in $SRC_CORE; do compile "$L/$s" "$OUT/obj-core"; done ) &
wait
COMPAT=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/orb/files/orb_compat.h
COMMON+=(-include "$COMPAT")   # only affects the application manager files compiled below
( for s in $SRC_APP; do compile "$ORB/components/application_manager/$s" "$OUT/obj-core"; done )
n=$(ls "$OUT/obj-core"/*.o 2>/dev/null | wc -l)
echo "core objects: $n"

"$CXX" "${COMMON[@]}" -shared -o "$OUT/libORBCore.so" "$OUT"/obj-core/*.o \
  -L"$C/libxml2/usr/lib" -L"$C/curl/usr/lib" -L"$X/usr/lib" -lxml2 -lcurl -luuid -ldl \
  -Wl,--allow-shlib-undefined -Wl,-rpath-link,"$C/libxml2/usr/lib" -Wl,-rpath-link,"$C/curl/usr/lib" 2>&1 | head -12
ls -la "$OUT/libORBCore.so" 2>&1 | awk '{print $5, $NF}'

# mock platform
INC_MOCK=(-I"$L/src/platform" -I"$L/src/platform/dataTypes" -I"$M/src" -I"$L/src/thirdparty")
for s in "$M/src/DVB.cpp" "$M/src/ORBPlatformMockImpl.cpp" /home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/orb/files/mock_fix.cpp; do
  "$CXX" "${COMMON[@]}" "${INC_MOCK[@]}" -c "$s" -o "$OUT/obj-mock/$(basename "$s" .cpp).o" 2>&1 | grep -E "error" | head -5
done
"$CXX" "${COMMON[@]}" -shared -o "$OUT/libORBPlatformImpl.so" "$OUT"/obj-mock/*.o -Wl,--allow-shlib-undefined 2>&1 | head -5
ls -la "$OUT/libORBPlatformImpl.so" 2>&1 | awk '{print $5, $NF}'
echo "== exported entry points of the platform lib"
nm -D --defined-only "$OUT/libORBPlatformImpl.so" 2>/dev/null | grep -iE "orb|platform" | head -5

# test host
TESTSRC=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/orb/files/orb_test.cpp
"$CXX" -B"$SHIM/" --sysroot="$X" -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a15 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -Os -std=c++14 \
  -Wno-psabi -include cstdint -DORB_HBBTV_VERSION=203 "${INC_CORE[@]}" -I"$L/src/thirdparty/nlohmann" "$TESTSRC" -o "$OUT/orb_test" \
  -L"$OUT" -lORBCore -Wl,--allow-shlib-undefined -Wl,-rpath-link,"$OUT" -Wl,-rpath-link,"$C/libxml2/usr/lib" -Wl,-rpath-link,"$C/curl/usr/lib" 2>&1 | grep -E "error" | head -8
ls -la "$OUT/orb_test" 2>&1 | awk '{print $5, $NF}'
