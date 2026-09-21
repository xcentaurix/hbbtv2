#!/bin/sh
# A/B run of scripted navigation in the ZDF main app with the INSTALLED stack (/usr/bin/wpe_fb, /usr/lib), headless (nothing on the TV):
# CPU seconds of the web process and of wpe_fb, frames and read-back time during 12 key presses.
#   usage: sh ua_ab.sh <label> <orb dir> [extra wpe_fb options]      e.g.  sh ua_ab.sh base /usr/lib/orb
#   the orb dir may be a private copy with another user agent (see ua_orbdir.sh); persisted consent: /media/hdd/wpe-test/pers
L=$1; ORBDIR=$2; shift 2
D=/usr/lib/enigma2/python/Plugins/Extensions/WPEHbbTV
export FONTCONFIG_FILE=$D/fonts.conf XDG_RUNTIME_DIR=/tmp/wpe-runtime HOME=/tmp/wpe-home WEBKIT_DISABLE_GL_FENCE=1
mkdir -p $XDG_RUNTIME_DIR $HOME /tmp/wpe-fontconfig-cache; chmod 700 $XDG_RUNTIME_DIR
export ORB_PLATFORM_LIB=$ORBDIR/wpe/libORBPlatformImpl.so WEBKIT_SHM_READBACK_LOG=1 GST_DEBUG=2
CTL=/tmp/ab.ctl; LOG=/tmp/ab_$L.log; rm -f $CTL $LOG
cd $D
/usr/bin/wpe_fb --orb $ORBDIR --autoplay deny ${AB_DEBUGJS:+} $( [ -n "$AB_DEBUGJS" ] || echo --no-debug-js ) --hidpi 1.5 --fine-damage --transparent --persist /media/hdd/wpe-test/pers --ctl $CTL --secs 0 "$@" > $LOG 2>&1 &
PID=$!
n=0; while [ ! -p $CTL ] && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done
echo "channel 1 1011 11110 ZDFHD" > $CTL
echo "app http://new-hbbtv.zdf.de" > $CTL
sleep 28
WEB=$(pidof WPEWebProcess | awk '{print $1}')
ticks() { awk '{print $14+$15}' /proc/$1/stat; }
threads() { for t in /proc/$WEB/task/*; do echo "$(cat $t/comm | tr ' ' '_') $(awk '{print $14+$15}' $t/stat)"; done; }
threads > /tmp/ab_thr0.txt
W0=$(ticks $WEB); F0=$(ticks $PID); N0=$(grep -a -c "shm-readback\] \(full\|partial\)" $LOG); T0=$(date +%s)
for k in down down right right down left right down down right left up; do echo "key $k" > $CTL; sleep 1.5; done
sleep 3
threads > /tmp/ab_thr1.txt
W1=$(ticks $WEB); F1=$(ticks $PID); N1=$(grep -a -c "shm-readback\] \(full\|partial\)" $LOG); T1=$(date +%s)
echo quit > $CTL
n=0; while kill -0 $PID 2>/dev/null && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done; kill $PID 2>/dev/null
FR=$((N1-N0))
MS=$(grep -a "shm-readback\] \(full\|partial\)" $LOG | tail -n $FR | awk '{ms=$0; sub(/.*\), /,"",ms); sub(/ ms.*/,"",ms); t+=ms} END {if (NR) printf "%.0f", t/NR; else print 0}')
UA=$(grep -a "^orb: user agent" $LOG | sed 's/.*HbbTV/HbbTV/' | cut -c1-60)
echo "$L: web CPU $(( (W1-W0) ))0 ms, wpe_fb CPU $(( (F1-F0) ))0 ms, frames $FR, avg read-back $MS ms, per key: web $(( (W1-W0)*10/12 )) ms, frames $((FR*10/12))e-1   [$UA]"
# per-thread CPU of the web process during the key presses (ms), busiest first (threads of the same name added up)
paste -d' ' /tmp/ab_thr0.txt /tmp/ab_thr1.txt | awk '{d[$1]+=$4-$2} END {for (k in d) if (d[k] > 0) printf "   %-18s %6d ms\n", k, d[k]*10}' | sort -k2 -n -r | head -8
