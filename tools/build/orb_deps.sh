#!/bin/bash
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
C=$T/sysroots-components/cortexa15hf-neon-vfpv4
echo "== target components ORBCore needs"
for c in libxml2 curl libcurl util-linux-libuuid libuuid openssl zlib libidn2 nghttp2 libpsl brotli; do
  [ -d "$C/$c" ] && echo "  have: $c ($(find $C/$c -name 'lib*.so*' | head -2 | xargs -n1 basename 2>/dev/null | tr '\n' ' '))" || echo "  MISSING: $c"
done
echo "== libxml2 headers"; find $C/libxml2 -name parser.h 2>/dev/null | head -2
echo "== curl headers"; find $C/curl -name curl.h 2>/dev/null | head -2
echo "== uuid header"; find /home/alpha/wpe-test/xsys -name uuid.h 2>/dev/null | head -2
echo "== does the box already have these libs?"
ls /home/alpha/wpe-test/*.txt 2>/dev/null | head -1
grep -E "^(libxml2\.so|libcurl\.so|libuuid\.so)" /mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad/boxlibs.txt | tr '\n' ' '
echo
echo "== C++ compiler + libstdc++ headers"
ls $T/sysroots-components/x86_64/gcc-cross-arm/usr/bin/arm-oe-linux-gnueabi/ | grep -E "g\+\+|c\+\+" | head -3
ls -d /home/alpha/wpe-test/xsys/usr/include/c++/* 2>/dev/null | head -2
echo "== nlohmann json in repo"; ls /home/alpha/orb/rdk/ORB/library/src/thirdparty/nlohmann | head -3
