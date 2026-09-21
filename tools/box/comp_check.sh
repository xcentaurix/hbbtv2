#!/bin/sh
# Headless check of the components path with the INSTALLED stack (/usr/bin/wpe_fb, /usr/lib): what an application sees through
# video/broadcast.getComponents(), the change events, and the "select ..." events that go back to the plugin. Nothing is drawn on the TV.
# The script plays the plugin: it sends the "components" lines and reads the event FIFO.   usage: sh comp_check.sh
# needs pages/orb_components.html next to it (copy tools/box/pages/orb_components.html to /media/hdd/wpe-test/pages/).
W=/media/hdd/wpe-test
D=/usr/lib/enigma2/python/Plugins/Extensions/WPEHbbTV
export FONTCONFIG_FILE=$D/fonts.conf XDG_RUNTIME_DIR=/tmp/wpe-runtime HOME=/tmp/wpe-home WEBKIT_DISABLE_GL_FENCE=1
mkdir -p $XDG_RUNTIME_DIR $HOME /tmp/wpe-fontconfig-cache; chmod 700 $XDG_RUNTIME_DIR
export ORB_PLATFORM_LIB=/usr/lib/orb/wpe/libORBPlatformImpl.so GST_DEBUG=2
CTL=/tmp/cc.ctl; EVT=/tmp/cc.evt; LOG=/tmp/cc.log; EVTLOG=/tmp/cc_evt.log
rm -f $CTL $LOG $EVTLOG
pkill -f "http.server 8099" 2>/dev/null
(cd $W/pages && exec python3 -m http.server 8099 --bind 127.0.0.1 >/tmp/cc_http.log 2>&1) &
HTTP=$!
n=0; while ! wget -q -O /dev/null http://127.0.0.1:8099/orb_components.html 2>/dev/null && [ $n -lt 50 ]; do sleep 0.2; n=$((n+1)); done # wait until the page can be fetched
cd $D
/usr/bin/wpe_fb --orb /usr/lib/orb --hwvideo-lazy --evt $EVT --autoplay deny --hidpi 1.0 --fine-damage --transparent --ctl $CTL --secs 0 > $LOG 2>&1 &
PID=$!
n=0; while [ ! -p $CTL ] && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done
n=0; while [ ! -p $EVT ] && [ $n -lt 50 ]; do sleep 0.1; n=$((n+1)); done
cat $EVT > $EVTLOG &
CAT=$!
V="V:5101:H.264:0:1"
A1="A:5102:deu:AC3:6:1:0"; A2="A:5103:eng:HEAAC:2:0:0"; A2ON="A:5103:eng:HEAAC:2:1:0"; A1OFF="A:5102:deu:AC3:6:0:0"
S1="S:5105:deu:DVB:0:0"; S2="S:5106:eng:TELETEXT:0:0"
echo "channel 1 1011 11110 ZDF" > $CTL
echo "components $V;$A1;$A2;$S1;$S2" > $CTL
echo "app http://127.0.0.1:8099/orb_components.html" > $CTL
sleep 8
echo "--- the application selected its way (the plugin would now switch enigma2 and send the new list):"
sleep 1
echo "components $V;$A1OFF;$A2ON;$S1;$S2" > $CTL   # audio track 5103 is in use now
sleep 3
echo "components $V;$A1OFF;$A2ON;$S1" > $CTL        # a subtitle track went away
sleep 3
echo quit > $CTL
n=0; while kill -0 $PID 2>/dev/null && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done; kill $PID 2>/dev/null
kill $CAT $HTTP 2>/dev/null
echo "=== page log (COMP lines):"; grep -a "COMP " $LOG | sed 's/.*COMP /COMP /' | cut -c1-260
echo "=== events written for the plugin:"; cat $EVTLOG
echo "=== orb_host:"; grep -a "\[orb_host\] \(components\|select\)" $LOG | cut -c1-160
