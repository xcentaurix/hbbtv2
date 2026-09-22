#!/bin/sh
# On-box check that wpe_fb --overlay-png switches to the framebuffer when the application grows too big for pictures (png_promote). It DRAWS ON THE TV for
# ~8 s: a small red banner, then the whole screen dark blue (the "application"), then, at the end, the screen must be clear again.
#   usage: sh overlay_big_check.sh [path of a wpe_fb to try instead of /usr/bin/wpe_fb]      (plugin closed, nothing recording)
W=/media/hdd/wpe-test
D=/usr/lib/enigma2/python/Plugins/Extensions/WPEHbbTV
BIN=${1:-/usr/bin/wpe_fb}
export FONTCONFIG_FILE=$D/fonts.conf XDG_RUNTIME_DIR=/tmp/wpe-runtime HOME=/tmp/wpe-home WEBKIT_DISABLE_GL_FENCE=1
mkdir -p $XDG_RUNTIME_DIR $HOME /tmp/wpe-fontconfig-cache; chmod 700 $XDG_RUNTIME_DIR
rm -f /tmp/wpe_overlay_* /tmp/ov.log /tmp/ov.events /tmp/ov.evt /tmp/bigcap_*
cd $D
python3 $W/fbshot.py /tmp/bigcap_0.raw > /dev/null
$BIN --fb --fullscreen --overlay-png /tmp/wpe_overlay --transparent --hidpi 1.5 --fine-damage --hwvideo-lazy --evt /tmp/ov.evt --ctl /tmp/ov.ctl \
	--secs 11 $W/pages/overlay_big.html > /tmp/ov.log 2>&1 &
PID=$!
n=0; while [ ! -p /tmp/ov.evt ] && [ $n -lt 50 ]; do sleep 0.1; n=$((n+1)); done
cat /tmp/ov.evt > /tmp/ov.events &
CAT=$!
sleep 8
python3 $W/fbshot.py /tmp/bigcap_A.raw > /dev/null   # in the full-screen phase
wait $PID
kill $CAT 2>/dev/null
sleep 1
python3 $W/fbshot.py /tmp/bigcap_E.raw > /dev/null   # after the exit
echo "--- events"
grep -a '^overlay' /tmp/ov.events
echo "--- log"
grep -a -E "^overlay|== guard" /tmp/ov.log | grep -v "handover: event"
echo "--- files left"
ls /tmp/wpe_overlay_* 2>&1
python3 - <<'EOF'
import sys
def stats(name):
    d = open(name, "rb").read()
    n = len(d) // 4
    alpha = d[3::4]
    return sum(1 for a in alpha if a), n, d[(540 * 1920 + 960) * 4:(540 * 1920 + 960) * 4 + 4].hex()
for name, want in (("/tmp/bigcap_0.raw", "before"), ("/tmp/bigcap_A.raw", "full-screen phase"), ("/tmp/bigcap_E.raw", "after the exit")):
    vis, n, mid = stats(name)
    print("%-18s: %7d of %d pixels not transparent, middle pixel (BGRA) %s" % (want, vis, n, mid))
EOF
