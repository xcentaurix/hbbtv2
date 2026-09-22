#!/bin/sh
# Plays one file in a plain <video> of wpe_fb (headless: nothing on the TV, no decoder taken) with WebKit's HTTP source and the MP4 demuxer logging, to see which
# ranges it asks for and where it fails. Plugin closed.   usage: sh bigfile_check.sh <url> [seconds] [log file]     (log: /tmp/bigfile.log)
W=/media/hdd/wpe-test
D=/usr/lib/enigma2/python/Plugins/Extensions/WPEHbbTV
URL=$1
SECS=${2:-25}
LOG=${3:-/tmp/bigfile.log}
[ -n "$(pidof wpe_fb)" ] && { echo "wpe_fb is running - close the plugin first"; exit 1; }
export FONTCONFIG_FILE=$D/fonts.conf XDG_RUNTIME_DIR=/tmp/wpe-runtime HOME=/tmp/wpe-home WEBKIT_DISABLE_GL_FENCE=1
mkdir -p $XDG_RUNTIME_DIR $HOME /tmp/wpe-fontconfig-cache /tmp/wpe-mediacache; chmod 700 $XDG_RUNTIME_DIR
export WPE_SHELL_MEDIA_DISK_CACHE_PATH=/tmp/wpe-mediacache WPE_SHELL_MEDIA_DISK_CACHE_SIZE_BYTES=8388608 WPE_SHELL_MEDIA_DISK_CACHE_SIZE_NSEC=10000000000
export GST_DEBUG="${GST_DEBUG:-2,webkitwebsrc:6,qtdemux:4,webkitmediaplayer:4}"
cd $D
/usr/bin/wpe_fb --transparent --fine-damage --secs $SECS "file://$W/pages/bigfile.html?src=$URL" > "$LOG" 2>&1
echo "--- page events"
grep -a "\[bigfile\]" "$LOG" | sed 's/.*\[bigfile\]/[bigfile]/' | cut -c1-160
echo "--- http source"
grep -a -E "webkitwebsrc" "$LOG" | grep -a -i -E "range|seek|size|416|206|request|content-length|position|Received" | cut -c1-230 | head -40
echo "--- qtdemux"
grep -a -E "qtdemux" "$LOG" | grep -a -i -E "seek|offset|error|co64|stco|mdat|moov|found|no more" | cut -c1-200 | head -20
