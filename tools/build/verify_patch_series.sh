#!/bin/bash
# Prove that pristine wpewebkit-2.54.0 + layer patches 0001..0012 (in order) == the externalsrc tree the builds came from.
set -uo pipefail
B=/home/alpha/openvix/build-enviroment
TARBALL=$B/sources/wpewebkit-2.54.0.tar.xz
P=$B/meta-hbbtv2/recipes-browser/wpewebkit/files
DEV=/home/alpha/wpe-src/wpewebkit-2.54.0
W=$(mktemp -d /tmp/wkverify.XXXXXX)
trap 'rm -rf "$W"' EXIT
ls -la "$TARBALL" | awk '{print "tarball:", $5, $NF}'
tar -xf "$TARBALL" -C "$W" || exit 1
cd "$W/wpewebkit-2.54.0" || exit 1
WKF=$B/meta-webkit/recipes-browser/wpewebkit/files
for p in "$WKF"/0001-bmalloc-libpas-avoid-C-stdatomic-in-C-build.patch "$WKF"/0002-WebDriver-Fix-build-when-logging-is-disabled.patch $(ls "$P"/00*.patch | sort); do
  if patch -p1 --no-backup-if-mismatch -s < "$p" >/tmp/wkverify.out 2>&1; then echo "applied  $(basename $p)"; else echo "FAILED   $(basename $p)"; head -8 /tmp/wkverify.out; exit 2; fi
done
echo "== compare with the dev tree (git dir excluded)"
diff -rq --exclude=.git --exclude="*.pyc" --exclude=oe-logs --exclude=oe-workdir "$W/wpewebkit-2.54.0" "$DEV" | head -40
echo "diff exit: ${PIPESTATUS[0]} (0 = identical)"
