#!/bin/sh
cd /media/hdd/wpe-test || exit 1
. ./env.sh
export ORB_PLATFORM_LIB=/media/hdd/wpe-test/orb/wpe/libORBPlatformImpl.so
pkill -f "http.server 8088" 2>/dev/null
(cd pages && exec python3 -m http.server 8088 --bind 127.0.0.1 >/tmp/http8088.log 2>&1) &
HP=$!
sleep 1
rm -f /tmp/orb_wpe.ctl
./bin/wpe_fb --orb /media/hdd/wpe-test/orb --transparent --fine-damage --ctl /tmp/orb_wpe.ctl --secs 30 --dump /tmp/orb_hello.ppm >/tmp/orb_wpe.log 2>&1 &
FP=$!
sleep 4
echo "app http://127.0.0.1:8088/orb_hello.html" > /tmp/orb_wpe.ctl
sleep 8
for k in red green yellow blue down ok 5; do echo "key $k" > /tmp/orb_wpe.ctl; sleep 1; done
sleep 2
echo quit > /tmp/orb_wpe.ctl
wait $FP
kill $HP 2>/dev/null
echo "exit: done"
