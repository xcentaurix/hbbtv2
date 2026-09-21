#!/bin/sh
# Headless check of the real-AIT path with the INSTALLED stack (nothing is drawn on the TV): a captured AIT (tools/box/testdata/ait_zdfhd.txt, copy it to
# /media/hdd/wpe-test/) is fed to wpe_fb the way run_wpe.sh does it; the engine must start the AUTOSTART application by itself, resolve a
# dvb://current.ait/<org>.<app> locator and react to a stopped broadcast.   usage: sh ait_check.sh [ait file] [org.app to ask for]
AIT=${1:-/media/hdd/wpe-test/ait_zdfhd.txt}; WANT=${2:-17.3}
D=/usr/lib/enigma2/python/Plugins/Extensions/WPEHbbTV
export FONTCONFIG_FILE=$D/fonts.conf XDG_RUNTIME_DIR=/tmp/wpe-runtime HOME=/tmp/wpe-home WEBKIT_DISABLE_GL_FENCE=1
mkdir -p $XDG_RUNTIME_DIR $HOME /tmp/wpe-fontconfig-cache; chmod 700 $XDG_RUNTIME_DIR
export ORB_PLATFORM_LIB=/usr/lib/orb/wpe/libORBPlatformImpl.so GST_DEBUG=2
CTL=/tmp/at.ctl; EVT=/tmp/at.evt; LOG=/tmp/at.log; rm -f $CTL $LOG
cd $D
/usr/bin/wpe_fb --orb /usr/lib/orb --hwvideo-lazy --evt $EVT --autoplay deny --no-debug-js --hidpi 1.0 --fine-damage --transparent --persist /media/hdd/wpe-test/pers --ctl $CTL --secs 0 > $LOG 2>&1 &
PID=$!
n=0; while [ ! -p $CTL ] && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done
SID=$(head -1 $AIT | awk '{print $2}')
echo "channel 1 1011 $SID ZDF" > $CTL
echo "service 1 1011 $SID" > $CTL
echo "--- feeding the AIT ($(wc -l < $AIT) section(s))"
while read -r line; do echo "ait $line" > $CTL; done < $AIT
sleep 10
echo "--- asking for dvb://current.ait/$WANT"
echo "app dvb://current.ait/$WANT" > $CTL
sleep 8
echo "--- the broadcast stops"
echo "ait-stop" > $CTL
sleep 3
echo quit > $CTL
n=0; while kill -0 $PID 2>/dev/null && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done; kill $PID 2>/dev/null
echo "=== engine log:"
grep -a -E "\[orb_host\] (service|AIT|CreateApplication|broadcast)|OnPerformAutostart|autostart|orb: loading application page|Kill running app|KillRunningApp|RunApp: Loading|No AIT|early out|Could not find app|isBroadcast" $LOG | sed 's/^\[INFO\] //' | cut -c1-200
