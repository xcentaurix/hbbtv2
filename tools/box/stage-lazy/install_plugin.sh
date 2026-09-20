#!/bin/sh
# Installs the plugin from stage-lazy/WPEHbbTV (the previous one is kept in stage-lazy/backup-plugin) and restarts the GUI.
S=/media/hdd/wpe-test/stage-lazy; P=/usr/lib/enigma2/python/Plugins/Extensions/WPEHbbTV
[ -z "$(ps | grep '[b]in/wpe_fb')" ] || { echo "wpe_fb is running: leave the app first"; exit 1; }
[ "$(curl -s -m 5 http://127.0.0.1/api/timerlist | grep -c '"state": 2')" = 0 ] || { echo "a recording is running: not restarting the GUI"; exit 1; }
mkdir -p $S/backup-plugin && cp $P/plugin.py $P/keymap.xml $P/__init__.py $S/backup-plugin/ || exit 1
cp $S/WPEHbbTV/plugin.py $S/WPEHbbTV/keymap.xml $S/WPEHbbTV/__init__.py $P/ && rm -f $P/plugin.pyc
echo "plugin installed; restarting the GUI"
init 4; sleep 4; init 3; sleep 20
echo "enigma2 pid: $(pidof enigma2)"; ls $P | tr '\n' ' '
