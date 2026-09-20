#!/bin/bash
# Build libsegvtrace.so (ARM32) into the deploy dir and extract the debug symbols of the new libWPEWebKit.
set -uo pipefail
SP=/mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
CC=$T/sysroots-components/x86_64/gcc-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-gcc
SHIM=/home/alpha/wpe-test/tcshim
X=/home/alpha/wpe-test/xsys
D=/home/alpha/wpe-test/deploy
"$CC" -B"$SHIM/" --sysroot="$X" -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a15 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -Os -Wall -fPIC -shared \
  "$SP/segv_trace.c" -o "$D/lib/libsegvtrace.so" 2>&1 | head -20
echo "segv lib: $(ls -la $D/lib/libsegvtrace.so 2>&1 | awk '{print $5}')"

P=$T/deploy/ipk/cortexa15hf-neon-vfpv4
DBG=$(ls $P/libwpewebkit-2.0-dbg_*.ipk 2>/dev/null | head -1)
echo "dbg ipk: $DBG"
if [ -n "$DBG" ]; then
  rm -rf /home/alpha/wpe-test/pkg/dbg; mkdir -p /home/alpha/wpe-test/pkg/dbg
  t=$(mktemp -d); (cd "$t" && ar x "$DBG" && tar -xf data.tar.* -C /home/alpha/wpe-test/pkg/dbg); rm -rf "$t"
  find /home/alpha/wpe-test/pkg/dbg -name '*.debug' | head -3 | xargs -r ls -la | awk '{print $5, $NF}'
fi
# does the debug file match the deployed lib (build-id)?
echo "deployed  build-id: $(readelf -n $D/lib/libWPEWebKit-2.0.so.1 | grep -i 'Build ID' | awk '{print $3}')"
echo "debugfile build-id: $(readelf -n $(find /home/alpha/wpe-test/pkg/dbg -name 'libWPEWebKit-2.0.so.1.11.3.debug' | head -1) 2>/dev/null | grep -i 'Build ID' | awk '{print $3}')"
