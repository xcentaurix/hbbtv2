#!/bin/bash
# Which shared libs does libWPEWebKit need that the DM900 does not already provide?
# Box filesystem is mounted read-only-in-practice at /mnt/u (we only stat files).
BOX=${BOX:-/mnt/u}
X=/home/alpha/wpe-test/pkg
lib=$(find "$X/rt" -name 'libWPEWebKit-2.0.so.1.*' -type f | head -1)
[ -d "$BOX/usr/lib" ] || { echo "box mount not visible at $BOX"; ls /mnt | head; exit 1; }

need=$(readelf -d "$lib" | grep NEEDED | sed 's/.*Shared library: \[//; s/\]//')
echo "NEEDED total: $(echo "$need" | wc -l)"
missing=""; present=""
for n in $need; do
  if ls "$BOX"/usr/lib/"$n" "$BOX"/lib/"$n" >/dev/null 2>&1; then present="$present $n"; else missing="$missing $n"; fi
done
echo "== present on box:$present"
echo "== MISSING on box:$missing"

# sizes of the missing ones as built by this tree (from the deploy ipks' sysroot components)
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
echo "== where the missing ones come from (sysroots-components)"
for n in $missing; do
  f=$(find $T/sysroots-components/cortexa15hf-neon-vfpv4 -name "$n" 2>/dev/null | head -1)
  [ -n "$f" ] && echo "$(stat -c %s "$(readlink -f "$f")") $n <- $(echo "$f" | sed "s#$T/sysroots-components/cortexa15hf-neon-vfpv4/##" | cut -d/ -f1)" || echo "?? $n (not found in sysroots-components)"
done
echo "== box libc / gstreamer / soup versions"
ls "$BOX"/lib/libc-* "$BOX"/lib/libc.so* "$BOX"/lib/ld-linux* 2>/dev/null | head -4
ls "$BOX"/usr/lib | grep -E "^libgstreamer-1.0|^libsoup|^libicuuc|^libglib-2.0" | head -8
