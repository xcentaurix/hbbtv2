#!/bin/sh
# dvb_test2.sh [uri] : seek-flag test. Same stop/restore as dvb_test.sh. Runs with FLUSH+KEY_UNIT (what enigma2 uses):
#   A) seek back to 1.0 at 3 s, pause at 5 s, resume at 7 s     B) seek FORWARD to 6.0 at 2 s, no pause
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
echo "########## A: KEY_UNIT seek back to 1.0 at 3s, pause 5s, resume 7s"
./bin/dvb_probe "$URI" --key-unit --secs 15 2>&1 | grep -av "^$"
sleep 2
echo "########## B: KEY_UNIT seek forward to 6.0 at 2s, no pause"
./bin/dvb_probe "$URI" --key-unit --seek-at 2 --seek-to 6 --pause-at 0 --resume-at 0 --secs 8 2>&1 | grep -av "^$"
