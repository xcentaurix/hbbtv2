#!/bin/sh
# Make a private copy of /usr/lib/orb whose platform library presents another HbbTV user agent token (same or shorter length: patched in place),
# for experiments with what a broadcaster's device service does with it.   usage: sh ua_orbdir.sh <name> "<HbbTV token>"
N=$1; TOKEN=$2; DIR=/media/hdd/wpe-test/orb_$N
rm -rf $DIR; cp -r /usr/lib/orb $DIR
python3 - "$DIR/wpe/libORBPlatformImpl.so" "$TOKEN" <<'PY'
import sys
p, new = sys.argv[1], sys.argv[2].encode()
old = b"HbbTV/1.6.1 (; OBS; WPE; v1.0.0-alpha; ; OBS;)"
data = open(p, "rb").read()
assert data.count(old) == 1 and len(new) <= len(old), (data.count(old), len(new), len(old))
open(p, "wb").write(data.replace(old, new + b"\0" * (len(old) - len(new))))
print("patched:", new.decode())
PY
