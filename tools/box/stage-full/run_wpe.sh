#!/bin/sh
# Start wpe_fb for the enigma2 WPE HbbTV test plugin: full-screen overlay on the framebuffer, control FIFO, runs until "quit".
#   usage: run_wpe.sh <page.html | url>
#
# HbbTV applications are started through the ORB engine (wpe_fb --orb + the "app <url>" control command), so the OIPF
# objects and the HbbTV key codes are available:
#   - pages named orb_*.html are served over HTTP from pages/ first (the engine fetches the URL to classify it);
#   - http(s):// URLs (e.g. the AIT autostart URL of the current channel) are launched as they are.
# Anything else is shown as a plain page, as before.
. /media/hdd/wpe-test/env.sh
# media pipeline diagnostics into the log (/tmp/wpe_fb.log): player, quirks and the dvb sinks; the page's own console/media events
# come from orb/debug.js as "[page] ..." lines
export GST_DEBUG="${GST_DEBUG:-2,webkitmediaplayer:4,webkitquirks:4,dvbvideosink:4,dvbaudiosink:4}"
# Progressive media (a whole film as one MP4) is buffered in a temporary file, by default in /var/tmp = a 500 MB tmpfs (RAM!) that fills
# up within half a minute at broadband speed; and the default buffering thresholds (100 KB) are a tenth of a second of HD video, which
# makes the player stall over and over. Put the file on the disk (WebKit unlinks it right after creating it) and size the buffer for video.
mkdir -p /media/hdd/wpe-test/mediacache
export WPE_SHELL_MEDIA_DISK_CACHE_PATH=/media/hdd/wpe-test/mediacache
export WPE_SHELL_MEDIA_DISK_CACHE_SIZE_BYTES=8388608
export WPE_SHELL_MEDIA_DISK_CACHE_SIZE_NSEC=10000000000
cd /media/hdd/wpe-test || exit 1
CTL=/tmp/wpe_fb.ctl
PORT=8088
APP=""
HTTP=""

case "$1" in
http://* | https://*) APP="$1" ;;
*)
	case "$(basename "$1")" in
	orb_*.html)
		pkill -f "http.server $PORT" 2>/dev/null
		(cd pages && exec python3 -m http.server $PORT --bind 127.0.0.1 >/tmp/wpe_http.log 2>&1) &
		HTTP=$!
		trap 'kill $HTTP 2>/dev/null' EXIT INT TERM
		APP="http://127.0.0.1:$PORT/$(basename "$1")"
		;;
	esac
	;;
esac

# WPE_HWVIDEO=1 (set by the plugin): <video> plays on the hardware video plane, but the live service keeps playing until media really
# needs the decoder (wpe_fb "decoder handover": it asks the plugin, through the event FIFO, to stop the service and gives it back
# afterwards).
HW=""
if [ -n "$WPE_HWVIDEO" ]; then
	HW="--hwvideo-lazy --evt /tmp/wpe_fb.evt"
fi

if [ -n "$APP" ]; then
	export ORB_PLATFORM_LIB=/media/hdd/wpe-test/orb/wpe/libORBPlatformImpl.so
	# the plugin sends "quit" through the FIFO; the app is launched as soon as wpe_fb has created it (it reads its FIFO once it
	# is fully set up, commands wait in the pipe until then)
	( n=0; while [ ! -p $CTL ] && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done
	  [ -p $CTL ] && echo "app $APP" > $CTL ) &
	./bin/wpe_fb $HW --orb /media/hdd/wpe-test/orb --fb --fullscreen --transparent --fine-damage --ctl $CTL --secs 0
else
	exec ./bin/wpe_fb $HW --fb --fullscreen --transparent --fine-damage --ctl $CTL --secs 0 "$1"
fi
