#!/bin/sh
# Peak memory while rendering: sample RSS of all wpe processes and the system's MemAvailable.
. /media/hdd/wpe-test/env.sh
cd /media/hdd/wpe-test
base=$(awk '/MemAvailable/{print $2}' /proc/meminfo)
/media/hdd/wpe-test/bin/wpe_shot - /media/hdd/wpe-test/shot_mem.ppm > /tmp/wpe-mem-out.txt 2>&1 &
pid=$!
max=0; minavail=$base; procs=0
while kill -0 $pid 2>/dev/null; do
  s=0; n=0
  for p in $(pgrep -f "WPEWebProcess|WPENetworkProcess|bin/wpe_shot"); do
    r=$(awk '/VmRSS/{print $2}' /proc/$p/status 2>/dev/null)
    s=$((s + ${r:-0})); n=$((n+1))
  done
  a=$(awk '/MemAvailable/{print $2}' /proc/meminfo)
  [ $s -gt $max ] && { max=$s; procs=$n; }
  [ $a -lt $minavail ] && minavail=$a
  usleep 100000 2>/dev/null || sleep 1
done
wait $pid; echo "wpe_shot exit: $?"
echo "MemAvailable before: ${base} kB, lowest during run: ${minavail} kB  (drop: $((base - minavail)) kB)"
echo "peak summed RSS of $procs wpe processes: ${max} kB (RSS double-counts shared libs, so this over-estimates)"
grep -E "RESULT|snapshot ok" /tmp/wpe-mem-out.txt
