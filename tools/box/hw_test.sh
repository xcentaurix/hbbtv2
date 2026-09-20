#!/bin/sh
# hw_test.sh <page> <secs> : hardware video test on the TV.
# Saves the current service, stops it (a service that does not exist makes enigma2 drop the current one, which frees
# /dev/dvb/adapter0/video0 + audio0), runs wpe_fb --hwvideo on the framebuffer, and zaps back afterwards no matter what.
cd /media/hdd/wpe-test || exit 1
. ./env.sh
PAGE="$1"; SECS="${2:-25}"
REF=$(curl -s -m 5 http://127.0.0.1/api/getcurrent | sed -n 's/.*"ref": "\([^"]*\)".*/\1/p' | head -1)
[ -n "$REF" ] || { echo "cannot read the current service from OpenWebif"; exit 1; }
echo "current service: $REF"
PLANE=$(cat /proc/stb/vmpeg/0/dst_left /proc/stb/vmpeg/0/dst_top /proc/stb/vmpeg/0/dst_width /proc/stb/vmpeg/0/dst_height | tr "
" " ")
restore() { set -- $PLANE; for n in left top width height; do echo "$1" > /proc/stb/vmpeg/0/dst_$n; shift; done; echo 1 > /proc/stb/vmpeg/0/dst_apply; curl -s -m 8 "http://127.0.0.1/api/zap?sRef=$REF" >/dev/null; sleep 4; set -- $PLANE; L=$1; T=$2; W=$3; H=$4; w() { echo $1 > /proc/stb/vmpeg/0/dst_left; echo $2 > /proc/stb/vmpeg/0/dst_top; echo $3 > /proc/stb/vmpeg/0/dst_width; echo $4 > /proc/stb/vmpeg/0/dst_height; echo 1 > /proc/stb/vmpeg/0/dst_apply; }; w 00000010 00000010 000002b0 00000220; sleep 1; w $L $T $W $H; echo "restored $REF (plane bounced to $PLANE)"; }
trap restore EXIT
curl -s -m 8 "http://127.0.0.1/api/zap?sRef=1:0:1:FFFF:FFFF:FFFF:FFFF:0:0:0:" >/dev/null
sleep 3
V=$(fuser /dev/dvb/adapter0/video0 2>&1); A=$(fuser /dev/dvb/adapter0/audio0 2>&1)
echo "decoder holders after stop: video0=[$V] audio0=[$A]"
if [ -n "$(echo $V | tr -d ' ')" ] || [ -n "$(echo $A | tr -d ' ')" ]; then
	echo "decoder not released - aborting"; exit 2
fi
export GST_DEBUG="${GST_DEBUG:-2,webkitquirks:4,webkitmediaplayer:5,dvbvideosink:4,dvbaudiosink:4}"
./bin/wpe_fb --fb --hwvideo --transparent --fine-damage --secs "$SECS" "$PAGE" > /tmp/hw_test.log 2>&1
echo "wpe_fb exit: $?"
echo "pts/dst at end: $(cat /proc/stb/vmpeg/0/dst_left /proc/stb/vmpeg/0/dst_top /proc/stb/vmpeg/0/dst_width /proc/stb/vmpeg/0/dst_height 2>/dev/null | tr '\n' ' ')"
