#!/bin/sh
# Isolated JS interpreter speed probe (tools/box/pages/jsspeed.html), through --orb mode so console.log is captured (debug.js is only injected there).
# Headless (no --fb): draws nothing on the TV. Plugin closed, nothing else on the box disturbed.   usage: sh jsspeed_check.sh [secs]
D=/usr/lib/enigma2/python/Plugins/Extensions/WPEHbbTV
W=/media/hdd/wpe-test
ORB=/usr/lib/orb
SECS=${1:-60}
[ -n "$(pidof wpe_fb)" ] && { echo "wpe_fb is running - close the plugin first"; exit 1; }
export FONTCONFIG_FILE=$D/fonts.conf XDG_RUNTIME_DIR=/tmp/wpe-runtime HOME=/tmp/wpe-home WEBKIT_DISABLE_GL_FENCE=1 ORB_PLATFORM_LIB=$ORB/wpe/libORBPlatformImpl.so
mkdir -p $XDG_RUNTIME_DIR $HOME /tmp/wpe-fontconfig-cache; chmod 700 $XDG_RUNTIME_DIR
rm -f /tmp/jsspeed.log /tmp/jsspeed.ctl
PORT=8099
pkill -f "http.server $PORT" 2>/dev/null
(cd $W/pages && exec python3 -m http.server $PORT --bind 127.0.0.1 >/tmp/jsspeed-http.log 2>&1) &
HTTP=$!
trap 'kill $HTTP 2>/dev/null' EXIT INT TERM
n=0; until wget -q -O /dev/null "http://127.0.0.1:$PORT/jsspeed.html"; do n=$((n+1)); [ $n -ge 50 ] && { echo "http server never came up"; exit 1; }; sleep 0.1; done
cd $D
/usr/bin/wpe_fb --orb $ORB --transparent --fine-damage --ctl /tmp/jsspeed.ctl --secs $SECS > /tmp/jsspeed.log 2>&1 &
PID=$!
n=0; while [ ! -p /tmp/jsspeed.ctl ] && [ $n -lt 50 ]; do sleep 0.1; n=$((n+1)); done
[ -p /tmp/jsspeed.ctl ] && echo "app http://127.0.0.1:$PORT/jsspeed.html" > /tmp/jsspeed.ctl
wait $PID
echo "--- result"
grep -a "\[jsspeed\]" /tmp/jsspeed.log
echo "--- installed lib"
opkg list-installed | grep libwpewebkit-2.0-1
