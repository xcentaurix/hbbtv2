#!/bin/sh
# video_probe.sh <page> <secs> : headless run of a video test page, CPU sample midway, prints the page's status lines
cd /media/hdd/wpe-test || exit 1
. ./env.sh
PAGE="$1"; SECS="${2:-20}"
./bin/wpe_fb --transparent --fine-damage --secs "$SECS" --dump /tmp/vprobe.ppm "$PAGE" >/tmp/vprobe.log 2>&1 &
sleep $((SECS / 2))
top -b -n 1 | head -14 | tail -9 > /tmp/vprobe.top
wait
cp /tmp/vprobe.ppm /media/hdd/wpe-test/vprobe.ppm
grep -a "page reports vid=" /tmp/vprobe.log | sed 's/page reports vid=//' | awk 'NR%4==1' | tail -12
grep -a "== sink\|WEB PROCESS\|Gst\|GStreamer\|ERROR\|CRITICAL" /tmp/vprobe.log | cut -c1-200 | head
echo "--- top:"; cat /tmp/vprobe.top
