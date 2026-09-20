#!/bin/sh
# Test the control channel + key injection without touching the screen (no --fb).
cd /media/hdd/wpe-test
. ./env.sh
rm -f /tmp/wpe_fb.ctl
./bin/wpe_fb --ctl /tmp/wpe_fb.ctl --transparent --fine-damage --secs 40 pages/keys.html > /tmp/keys_test.log 2>&1 &
pid=$!
# wait for the control channel
i=0; while [ $i -lt 20 ] && ! grep -q "control channel ready" /tmp/keys_test.log; do sleep 1; i=$((i+1)); done
sleep 3
for k in ok up down left right red green yellow blue 5 back exit; do
  echo "key $k" > /tmp/wpe_fb.ctl
  sleep 1
done
echo "key bogus" > /tmp/wpe_fb.ctl
sleep 1
echo quit > /tmp/wpe_fb.ctl
wait $pid
echo "exit status: $?"
grep -E "control channel|ctl:|page reports key|sink" /tmp/keys_test.log
ls -la /tmp/wpe_fb.ctl 2>&1 | head -1
