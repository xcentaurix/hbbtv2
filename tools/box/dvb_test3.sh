#!/bin/sh
# dvb_test3.sh: play the failing 1080p trailer, then a 720p reference clip, through playbin + the dvb sinks (no browser, no seeks).
cd /media/hdd/wpe-test || exit 1
BAD="http://tvdlzdf-a.akamaihd.net/none/zdf/diverse/hero_trailer_toedliches_erbe_der_ddr/1/hero_trailer_toedliches_erbe_der_ddr_6660k_p37v17.mp4"
GOOD="https://www.w3schools.com/html/mov_bbb.mp4"
REF=$(curl -s -m 5 http://127.0.0.1/api/getcurrent | sed -n 's/.*"ref": "\([^"]*\)".*/\1/p' | head -1)
[ -n "$REF" ] || { echo "cannot read the current service"; exit 1; }
PLANE=$(cat /proc/stb/vmpeg/0/dst_left /proc/stb/vmpeg/0/dst_top /proc/stb/vmpeg/0/dst_width /proc/stb/vmpeg/0/dst_height | tr "\n" " ")
w() { echo $1 > /proc/stb/vmpeg/0/dst_left; echo $2 > /proc/stb/vmpeg/0/dst_top; echo $3 > /proc/stb/vmpeg/0/dst_width; echo $4 > /proc/stb/vmpeg/0/dst_height; echo 1 > /proc/stb/vmpeg/0/dst_apply; }
restore() {
	n=0; while [ -n "$(fuser /dev/dvb/adapter0/video0 /dev/dvb/adapter0/audio0 2>&1 | tr -d ' ')" ] && [ $n -lt 50 ]; do sleep 0.2; n=$((n+1)); done
	curl -s -m 8 "http://127.0.0.1/api/zap?sRef=$REF" >/dev/null; sleep 4; set -- $PLANE; w 00000010 00000010 000002b0 00000220; sleep 1; w $1 $2 $3 $4; echo "restored $REF"
}
trap restore EXIT
curl -s -m 8 "http://127.0.0.1/api/zap?sRef=1:0:1:FFFF:FFFF:FFFF:FFFF:0:0:0:" >/dev/null
sleep 3
[ -z "$(fuser /dev/dvb/adapter0/video0 /dev/dvb/adapter0/audio0 2>&1 | tr -d ' ')" ] || { echo "decoder not released - aborting"; exit 2; }
export GST_DEBUG=2,dvbvideosink:4,dvbaudiosink:4
echo "########## the failing 1080p trailer"
./bin/dvb_probe "$BAD" --seek-at 0 --pause-at 0 --resume-at 0 --secs 16 2>&1 | grep -av "^$" | cut -c1-220
sleep 2
echo "########## 720p reference"
./bin/dvb_probe "$GOOD" --seek-at 0 --pause-at 0 --resume-at 0 --secs 8 2>&1 | grep -av "^$" | cut -c1-220
