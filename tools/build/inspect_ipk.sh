#!/bin/bash
set -e
P=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp/deploy/ipk/cortexa15hf-neon-vfpv4
X=/home/alpha/wpe-test/pkg
rm -rf "$X"; mkdir -p "$X/rt" "$X/dev" "$X/epoxy"
extract() { # ipk destdir
  local t; t=$(mktemp -d); (cd "$t" && ar x "$1" && tar -xf data.tar.* -C "$2"); rm -rf "$t"
}
extract "$P/libwpewebkit-2.0-1_2.54.0-r0_cortexa15hf-neon-vfpv4.ipk" "$X/rt"
extract "$P/libwpewebkit-2.0-dev_2.54.0-r0_cortexa15hf-neon-vfpv4.ipk" "$X/dev"
extract "$P/libepoxy0_1.5.10-r0_cortexa15hf-neon-vfpv4.ipk" "$X/epoxy"

echo "== runtime package files (size path)"
(cd "$X/rt" && find . -type f -o -type l | sort | while read f; do s=$(stat -c %s "$f" 2>/dev/null || echo l); echo "$s $f"; done) | head -40
echo "== arch"
lib=$(find "$X/rt" -name 'libWPEWebKit-2.0.so*' -type f | head -1)
file "$lib" | cut -c1-160
echo "== DT_NEEDED of libWPEWebKit"
readelf -d "$lib" | grep NEEDED | sed 's/.*Shared library: \[//; s/\]//' | tr '\n' ' '; echo
echo "== process binaries"
find "$X/rt" -name 'WPE*Process' -type f -exec sh -c 'echo {}; readelf -d {} | grep NEEDED | sed "s/.*Shared library: \[//; s/\]//" | tr "\n" " "; echo' \;
echo "== dev package (headers/pc)"
(cd "$X/dev" && find . -type f | sort | head -40)
echo "== headless platform bits in lib"
strings -a "$lib" | grep -iE "wpe_display_headless|WPEDisplayHeadless|headless" | sort -u | head -8
echo "== extracted size"; du -sh "$X/rt"
