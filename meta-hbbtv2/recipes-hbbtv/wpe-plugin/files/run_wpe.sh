#!/bin/sh
# Start wpe_fb for the enigma2 WPE HbbTV plugin: full-screen overlay on the framebuffer, control FIFO, runs until "quit".
#   usage: run_wpe.sh <page.html | url>
#
# HbbTV applications are started through the ORB engine (wpe_fb --orb + the "app <url>" control command), so the OIPF
# objects and the HbbTV key codes are available:
#   - pages named orb_*.html are served over HTTP from pages/ first (the engine fetches the URL to classify it);
#   - http(s):// URLs (e.g. the AIT autostart URL of the current channel) are launched as they are.
# Anything else is shown as a plain page, as before.
#
# Locations (packaged install; override in the environment to run a private build):
#   WPE_FB         the embedder                               (default: wpe_fb from PATH, /usr/bin)
#   WPE_ORB_DIR    ORB: hbbtv.js, debug.js, ext/, wpe/        (default: /usr/lib/orb)
#   WPE_MEDIA_CACHE where progressive media is buffered       (default: /media/hdd/.wpe-mediacache, else /tmp/wpe-mediacache)
D=$(cd "$(dirname "$0")" && pwd)
WPE_FB=${WPE_FB:-wpe_fb}
ORB=${WPE_ORB_DIR:-/usr/lib/orb}

# WPE WebKit runtime environment
export FONTCONFIG_FILE=$D/fonts.conf
export XDG_RUNTIME_DIR=/tmp/wpe-runtime
export HOME=/tmp/wpe-home
mkdir -p "$XDG_RUNTIME_DIR" "$HOME" /tmp/wpe-fontconfig-cache
chmod 700 "$XDG_RUNTIME_DIR"
# The Dreambox vendor EGL crashes in glFlush() once an EGL fence sync exists (WebKit patch 0005 adds this opt-out)
export WEBKIT_DISABLE_GL_FENCE=1

# media pipeline diagnostics into the log (/tmp/wpe_fb.log): player, quirks and the dvb sinks; the page's own console/media events
# come from debug.js (in the ORB directory) as "[page] ..." lines
export GST_DEBUG="${GST_DEBUG:-2,webkitmediaplayer:4,webkitquirks:4,dvbvideosink:4,dvbaudiosink:4}"
# Progressive media (a whole film as one MP4) is buffered in a temporary file, by default in /var/tmp = a 500 MB tmpfs (RAM!) that fills
# up within half a minute at broadband speed; and the default buffering thresholds (100 KB) are a tenth of a second of HD video, which
# makes the player stall over and over. Put the file on the disk (WebKit unlinks it right after creating it) and size the buffer for video.
CACHE=${WPE_MEDIA_CACHE:-/media/hdd/.wpe-mediacache}
if [ -z "$WPE_MEDIA_CACHE" ] && [ ! -w /media/hdd ]; then
	CACHE=/tmp/wpe-mediacache
fi
mkdir -p "$CACHE"
export WPE_SHELL_MEDIA_DISK_CACHE_PATH=$CACHE
export WPE_SHELL_MEDIA_DISK_CACHE_SIZE_BYTES=8388608
export WPE_SHELL_MEDIA_DISK_CACHE_SIZE_NSEC=10000000000
cd "$D" || exit 1
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
	export ORB_PLATFORM_LIB=$ORB/wpe/libORBPlatformImpl.so
	# the plugin sends "quit" through the FIFO; the app is launched as soon as wpe_fb has created it (it reads its FIFO once it
	# is fully set up, commands wait in the pipe until then)
	( n=0; while [ ! -p $CTL ] && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done
	  [ -p $CTL ] && echo "app $APP" > $CTL ) &
	$WPE_FB $HW --orb "$ORB" --fb --fullscreen --hidpi 1.5 --transparent --fine-damage --ctl $CTL --secs 0
else
	exec $WPE_FB $HW --fb --fullscreen --hidpi 1.5 --transparent --fine-damage --ctl $CTL --secs 0 "$1"
fi
