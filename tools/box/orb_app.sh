#!/bin/sh
# headless run of an HbbTV app URL through the ORB engine: orb_app.sh <url> <settle-secs> [key ...]
cd /media/hdd/wpe-test || exit 1
. ./env.sh
export ORB_PLATFORM_LIB=/media/hdd/wpe-test/orb/wpe/libORBPlatformImpl.so
URL="$1"; WAIT="${2:-15}"; shift; shift
rm -f /tmp/orb_app.ctl
./bin/wpe_fb --orb /media/hdd/wpe-test/orb --transparent --fine-damage --ctl /tmp/orb_app.ctl --secs 0 --dump /tmp/orb_app.ppm >/tmp/orb_app.log 2>&1 &
FP=$!
sleep 4
echo "app $URL" > /tmp/orb_app.ctl
sleep "$WAIT"
for k in "$@"; do echo "key $k" > /tmp/orb_app.ctl; sleep 3; done
echo quit > /tmp/orb_app.ctl
wait $FP
cp /tmp/orb_app.ppm /media/hdd/wpe-test/orb_app.ppm
echo finished
