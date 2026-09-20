#!/bin/sh
S=/media/hdd/wpe-test/stage-full; T=/media/hdd/wpe-test; P=/usr/lib/enigma2/python/Plugins/Extensions/WPEHbbTV
[ -d $S/backup ] || { echo "no backup"; exit 1; }
[ -z "$(ps | grep '[b]in/wpe_fb')" ] || { echo "wpe_fb is running: leave the app first"; exit 1; }
cp $S/backup/libWPEWebKit-2.0.so.1 $T/lib/x.new && mv -f $T/lib/x.new $T/lib/libWPEWebKit-2.0.so.1
cp $S/backup/wpe_fb $T/bin/x.new && chmod +x $T/bin/x.new && mv -f $T/bin/x.new $T/bin/wpe_fb
cp $S/backup/run_wpe.sh $T/x.new && chmod +x $T/x.new && mv -f $T/x.new $T/run_wpe.sh
cp $S/backup/WPEHbbTV/* $P/ && rm -f $P/plugin.pyc
init 4; sleep 4; init 3; sleep 20; echo "rolled back; enigma2 pid: $(pidof enigma2)"
