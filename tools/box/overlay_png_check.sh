#!/bin/sh
# On-box check of wpe_fb --overlay-png (draws nothing on the TV): the test page overlay_test.html (three boxes; the red one goes away after 7 s, the
# other two after 11 s) is rendered, wpe_fb writes PNGs of the visible part and announces them on the event FIFO. What arrives is copied to /tmp/ovpng_*
# for the PC (overlay_png_analyze.py) and the events are printed.   usage: sh overlay_png_check.sh [path of a wpe_fb to try instead of /usr/bin/wpe_fb]
W=/media/hdd/wpe-test
D=/usr/lib/enigma2/python/Plugins/Extensions/WPEHbbTV
BIN=${1:-/usr/bin/wpe_fb}
export FONTCONFIG_FILE=$D/fonts.conf XDG_RUNTIME_DIR=/tmp/wpe-runtime HOME=/tmp/wpe-home WEBKIT_DISABLE_GL_FENCE=1
mkdir -p $XDG_RUNTIME_DIR $HOME /tmp/wpe-fontconfig-cache; chmod 700 $XDG_RUNTIME_DIR
rm -f /tmp/wpe_overlay_* /tmp/ovpng_* /tmp/ov.log /tmp/ov.events /tmp/ov.evt
cd $D
$BIN --fb --fullscreen --overlay-png /tmp/wpe_overlay --transparent --hidpi 1.5 --fine-damage --hwvideo-lazy --evt /tmp/ov.evt --ctl /tmp/ov.ctl \
	--secs 15 $W/pages/overlay_test.html > /tmp/ov.log 2>&1 &
PID=$!
n=0; while [ ! -p /tmp/ov.evt ] && [ $n -lt 50 ]; do sleep 0.1; n=$((n+1)); done
cat /tmp/ov.evt > /tmp/ov.events &
CAT=$!
sleep 5;  cp $(ls -t /tmp/wpe_overlay_*.png | head -1) /tmp/ovpng_A.png   # all three boxes
sleep 4;  cp $(ls -t /tmp/wpe_overlay_*.png | head -1) /tmp/ovpng_B.png   # (page time 7 s: the red box is gone)
sleep 4;  ls -l /tmp/wpe_overlay_* 2>&1 | tail -6                          # (page time 11 s: nothing visible)
wait $PID
kill $CAT 2>/dev/null
echo "--- events"
grep -a '^overlay' /tmp/ov.events
echo "--- files left after the exit"
ls /tmp/wpe_overlay_* 2>&1
grep -a -E "overlay|== sink" /tmp/ov.log | grep -v "handover: event" | head
