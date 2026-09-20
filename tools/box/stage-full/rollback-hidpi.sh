#!/bin/sh
T=/media/hdd/wpe-test; B=$T/stage-full/backup-hidpi
[ -z "$(ps | grep '[b]in/wpe_fb')" ] || { echo 'wpe_fb is running'; exit 1; }
cp $B/wpe_fb $T/bin/x.new && chmod +x $T/bin/x.new && mv -f $T/bin/x.new $T/bin/wpe_fb
cp $B/run_wpe.sh $T/x.new && chmod +x $T/x.new && mv -f $T/x.new $T/run_wpe.sh && echo 'rolled back wpe_fb + run_wpe.sh (the library is compatible)'
