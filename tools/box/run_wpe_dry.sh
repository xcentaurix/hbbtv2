#!/bin/sh
# Start wpe_fb for the enigma2 WPE HbbTV test plugin: full-screen overlay on the framebuffer, control FIFO, runs until "quit".
#   usage: run_wpe.sh <page.html | url>
#
# Pages named orb_*.html are HbbTV applications: they are served over HTTP from pages/ (the ORB engine fetches the URL to
# classify it) and started through the ORB engine (wpe_fb --orb + the "app <url>" control command), so the OIPF objects and
# the HbbTV key codes are available. Anything else is shown as a plain page, as before.
. /media/hdd/wpe-test/env.sh
cd /media/hdd/wpe-test || exit 1
CTL=/tmp/wpe_fb.ctl
PORT=8088

case "$(basename "$1")" in
orb_*.html)
	export ORB_PLATFORM_LIB=/media/hdd/wpe-test/orb/wpe/libORBPlatformImpl.so
	pkill -f "http.server $PORT" 2>/dev/null
	(cd pages && exec python3 -m http.server $PORT --bind 127.0.0.1 >/tmp/wpe_http.log 2>&1) &
	HTTP=$!
	trap 'kill $HTTP 2>/dev/null' EXIT INT TERM
	# the plugin sends "quit" through the FIFO; the app is launched once wpe_fb has created it
	( n=0; while [ ! -p $CTL ] && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done
	  sleep 1
	  [ -p $CTL ] && echo "app http://127.0.0.1:$PORT/$(basename "$1")" > $CTL ) &
	./bin/wpe_fb --orb /media/hdd/wpe-test/orb --transparent --fine-damage --ctl $CTL --secs 0
	;;
*)
	exec ./bin/wpe_fb --transparent --fine-damage --ctl $CTL --secs 0 "$1"
	;;
esac
