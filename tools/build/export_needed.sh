#!/bin/bash
SP=/mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad
lib=$(find /home/alpha/wpe-test/pkg/rt -name 'libWPEWebKit-2.0.so.1.*' -type f | head -1)
echo "lib: $lib"
readelf -d "$lib" | grep NEEDED | sed 's/.*Shared library: \[//; s/\]//' > "$SP/needed.txt"
wc -l < "$SP/needed.txt"
# versions of a few key libs as built here
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
for n in libsoup-3.0.so.0 libicuuc.so.78 libxkbcommon.so.0 libwoff2dec.so.1.0.2 libepoxy.so.0; do
  f=$(find $T/sysroots-components/cortexa15hf-neon-vfpv4 -name "$n*" -type f 2>/dev/null | head -1)
  [ -n "$f" ] && echo "$(stat -c %s "$f") $n" || echo "?? $n"
done
