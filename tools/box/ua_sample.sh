#!/bin/sh
# Poor man's profiler of the web process's MAIN thread with the installed stack, headless: while 60 key presses navigate the ZDF main app, gdb attaches
# to the web process again and again, prints the top of the main thread's stack and lets go. Results in /tmp/samp_<label>/ (one file per sample and the
# maps of the web process); resolve the addresses on the PC with tools/box/resolve_samples.py.   usage: sh ua_sample.sh <label> [extra wpe_fb options]
L=$1; shift
D=/usr/lib/enigma2/python/Plugins/Extensions/WPEHbbTV
export FONTCONFIG_FILE=$D/fonts.conf XDG_RUNTIME_DIR=/tmp/wpe-runtime HOME=/tmp/wpe-home WEBKIT_DISABLE_GL_FENCE=1
mkdir -p $XDG_RUNTIME_DIR $HOME /tmp/wpe-fontconfig-cache; chmod 700 $XDG_RUNTIME_DIR
export ORB_PLATFORM_LIB=/usr/lib/orb/wpe/libORBPlatformImpl.so GST_DEBUG=2
CTL=/tmp/sp.ctl; OUT=/tmp/samp_$L; rm -rf $OUT $CTL; mkdir -p $OUT
cd $D
/usr/bin/wpe_fb --orb /usr/lib/orb --autoplay deny --no-debug-js --hidpi 1.5 --fine-damage --transparent --persist /media/hdd/wpe-test/pers --ctl $CTL --secs 0 "$@" > $OUT/wpe.log 2>&1 &
PID=$!
n=0; while [ ! -p $CTL ] && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done
echo "channel 1 1011 11110 ZDFHD" > $CTL
echo "app http://new-hbbtv.zdf.de" > $CTL
sleep 28
WEB=$(pidof WPEWebProcess | awk '{print $1}')
cp /proc/$WEB/maps $OUT/maps.txt
( for r in 1 2 3 4 5; do for k in down down right right down left right down down right left up; do echo "key $k" > $CTL; sleep 1.5; done; done; echo done > $OUT/keys_done ) &
i=0
while [ ! -f $OUT/keys_done ]; do
  i=$((i+1))
  gdb -p $WEB -batch -ex "set pagination off" -ex "thread 1" -ex "bt 14" 2>/dev/null | grep -a "^#" > $OUT/s$i.txt
done
echo quit > $CTL
n=0; while kill -0 $PID 2>/dev/null && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done; kill $PID 2>/dev/null
echo "$i samples in $OUT ($(ls $OUT/s*.txt | wc -l) files, $(cat $OUT/s*.txt | wc -l) frames)"
