#!/bin/sh
# dvb_test.sh [uri] : GStreamer/dvb-sink ground-truth test (no browser). Stops the live service once, runs dvb_probe twice
# (e2-async off, then on: seek back at 3 s, pause at 5 s, resume at 7 s), zaps back and bounces the video plane.
cd /media/hdd/wpe-test || exit 1
URI="${1:-https://www.w3schools.com/html/mov_bbb.mp4}"
REF=$(curl -s -m 5 http://127.0.0.1/api/getcurrent | sed -n 's/.*"ref": "\([^"]*\)".*/\1/p' | head -1)
[ -n "$REF" ] || { echo "cannot read the current service"; exit 1; }
PLANE=$(cat /proc/stb/vmpeg/0/dst_left /proc/stb/vmpeg/0/dst_top /proc/stb/vmpeg/0/dst_width /proc/stb/vmpeg/0/dst_height | tr "\n" " ")
w() { echo $1 > /proc/stb/vmpeg/0/dst_left; echo $2 > /proc/stb/vmpeg/0/dst_top; echo $3 > /proc/stb/vmpeg/0/dst_width; echo $4 > /proc/stb/vmpeg/0/dst_height; echo 1 > /proc/stb/vmpeg/0/dst_apply; }
restore() { curl -s -m 8 "http://127.0.0.1/api/zap?sRef=$REF" >/dev/null; sleep 4; set -- $PLANE; w 00000010 00000010 000002b0 00000220; sleep 1; w $1 $2 $3 $4; echo "restored $REF"; }
trap restore EXIT
curl -s -m 8 "http://127.0.0.1/api/zap?sRef=1:0:1:FFFF:FFFF:FFFF:FFFF:0:0:0:" >/dev/null
sleep 3
[ -z "$(fuser /dev/dvb/adapter0/video0 /dev/dvb/adapter0/audio0 2>&1 | tr -d ' ')" ] || { echo "decoder not released - aborting"; exit 2; }
export GST_DEBUG=1
echo "########## e2-async off"
./bin/dvb_probe "$URI" --secs 16 2>&1 | grep -av "^$"
sleep 2
echo "########## e2-async ON"
./bin/dvb_probe "$URI" --e2-async --secs 16 2>&1 | grep -av "^$"
