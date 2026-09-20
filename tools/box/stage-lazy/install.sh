#!/bin/sh
# Switches the box to the "lazy decoder" design (live TV keeps playing until media needs the decoder). Everything is replaced by
# rename (safe for running programs); the previous versions are kept in stage-lazy/backup for rollback.sh.
S=/media/hdd/wpe-test/stage-lazy
T=/media/hdd/wpe-test
P=/usr/lib/enigma2/python/Plugins/Extensions/WPEHbbTV
[ -z "$(ps | grep '[b]in/wpe_fb')" ] || { echo "wpe_fb is running: leave the app first"; exit 1; }
[ "$(curl -s -m 5 http://127.0.0.1/api/timerlist | grep -c '"state": 2')" = 0 ] || { echo "a recording is running: not restarting the GUI"; exit 1; }
mkdir -p $S/backup/WPEHbbTV
cp $T/lib/libWPEWebKit-2.0.so.1 $S/backup/ && cp $T/bin/wpe_fb $S/backup/ && cp $T/run_wpe.sh $S/backup/ && cp $P/plugin.py $P/keymap.xml $P/__init__.py $S/backup/WPEHbbTV/ || exit 1
cp $S/libWPEWebKit-2.0.so.1 $T/lib/libWPEWebKit-2.0.so.1.new && mv -f $T/lib/libWPEWebKit-2.0.so.1.new $T/lib/libWPEWebKit-2.0.so.1
cp $S/wpe_fb $T/bin/wpe_fb.new && chmod +x $T/bin/wpe_fb.new && mv -f $T/bin/wpe_fb.new $T/bin/wpe_fb
cp $S/run_wpe.sh $T/run_wpe.sh.new && chmod +x $T/run_wpe.sh.new && mv -f $T/run_wpe.sh.new $T/run_wpe.sh
cp $S/WPEHbbTV/plugin.py $S/WPEHbbTV/keymap.xml $S/WPEHbbTV/__init__.py $P/ && rm -f $P/plugin.pyc
echo "installed; restarting the GUI"
init 4; sleep 4; init 3; sleep 20
echo "enigma2 pid: $(pidof enigma2)"; ls $P | tr '\n' ' '
