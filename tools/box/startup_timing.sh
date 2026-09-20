#!/bin/sh
# startup_timing.sh <app-url> : how long each phase of "start wpe_fb + ORB + load an application" takes (headless, no decoder)
cd /media/hdd/wpe-test || exit 1
. ./env.sh
export ORB_PLATFORM_LIB=/media/hdd/wpe-test/orb/wpe/libORBPlatformImpl.so
URL="${1:-http://hbbtv.zdf.de/zdfstart/index.php}"
now() { awk '{print $1}' /proc/uptime; }
rm -f /tmp/timing.ctl /tmp/timing.log
T0=$(now)
./bin/wpe_fb --orb /media/hdd/wpe-test/orb --transparent --fine-damage --ctl /tmp/timing.ctl --secs 0 >/tmp/timing.log 2>&1 &
FP=$!
mark() { echo "$(awk -v a=$(now) -v b=$T0 'BEGIN{printf "%5.2f", a-b}') s  $1"; }
# poll the log for the milestones
seen_engine=0; seen_fifo=0; sent=0; seen_created=0; loads=0; done=0
i=0
while [ $i -lt 400 ] && [ $done -eq 0 ]; do
  L=$(cat /tmp/timing.log 2>/dev/null)
  [ $seen_engine -eq 0 ] && echo "$L" | grep -q "engine started" && { seen_engine=1; mark "ORB engine started (process+libs+platform)"; }
  if [ $seen_fifo -eq 0 ] && [ -p /tmp/timing.ctl ]; then seen_fifo=1; mark "control FIFO ready"; echo "app $URL" > /tmp/timing.ctl; mark "app command sent"; fi
  [ $seen_created -eq 0 ] && echo "$L" | grep -q "CreateApplication(.*ok" && { seen_created=1; mark "ORB CreateApplication done (URL fetched + classified)"; }
  n=$(echo "$L" | grep -c "load-changed: FINISHED"); [ "$n" -ge 2 ] && { mark "application page loaded (load-changed FINISHED)"; done=1; }
  sleep 0.1; i=$((i+1))
done
sleep 2
mark "first-frame check: $(grep -a 'page reports\|== sink' /tmp/timing.log | tail -1)"
echo quit > /tmp/timing.ctl; wait $FP
