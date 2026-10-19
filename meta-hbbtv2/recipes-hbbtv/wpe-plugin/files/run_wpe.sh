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

# Settings: /etc/enigma2/wpehbbtv.conf (KEY=VALUE, written by the plugin's settings menu); a value already in the environment wins.
#   WPE_HIDPI       render scale: 1.5 = sharp (default), 1.25, 1.0 = fast. The read-back of a frame from the GPU costs time in
#                   proportion to its pixels: 1.0 is ~3 times quicker to react than 1.5
#   WPE_FAST_ANIM   1: CSS transitions/animations last 1 ms, no smooth scrolling (fewer frames per key press); default 0
#   WPE_PERSIST     1: HTTP cache (<= 75 MB), cookies and local storage survive between runs (default 1, needs /media/hdd)
#   WPE_PERSIST_DIR where they live (default /media/hdd/.wpe-data)
#   WPE_DEBUG       1: debug.js (the page's console and media events in /tmp/wpe_fb.log) and GStreamer debug output; default 0
#   WPE_LIMIT_REPEAT 1: pass the remote's auto-repeat on at most once per delivered frame, so a held key moves fewer steps; a matter
#                   of feel, it does not make the page settle sooner (docs/phase1-results.txt); default 0
CONF=/etc/enigma2/wpehbbtv.conf
if [ -f "$CONF" ]; then
	while IFS='=' read -r k v; do
		case $k in
		WPE_HIDPI | WPE_FAST_ANIM | WPE_PERSIST | WPE_PERSIST_DIR | WPE_DEBUG | WPE_LIMIT_REPEAT | WPE_EGL) eval "[ -n \"\${$k}\" ] || $k=\$v" ;;
		esac
	done <"$CONF"
fi
case "$WPE_HIDPI" in 1 | 1.0 | 1.25 | 1.5) ;; *) WPE_HIDPI=1.5 ;; esac
WPE_PERSIST_DIR=${WPE_PERSIST_DIR:-/media/hdd/.wpe-data}
case "$WPE_PERSIST_DIR" in /*[!A-Za-z0-9_./-]* | [!/]*) WPE_PERSIST_DIR=/media/hdd/.wpe-data ;; esac # an absolute plain path, else the default
OPTS="--hidpi $WPE_HIDPI --transparent --fine-damage"
# Output: enigma2's own EGL renderer (gEGLDC) composites the page when it listens for it (its wake-up socket exists: window-surface platforms such as
# the GigaBlue/Nexus boxes) - no second display window, no CPU conversion/scaling here. WPE_EGL=0 forces the old framebuffer / NXPL path, 1 forces this one.
OUTMODE="--fb --fullscreen"
[ -z "$WPE_EGL" ] && [ -S /tmp/e2_webov.sock ] && WPE_EGL=1
[ "$WPE_EGL" = 1 ] && [ "$WPE_OVERLAY" != 1 ] && OUTMODE="--egl-sink"
[ "$WPE_FAST_ANIM" = 1 ] && OPTS="$OPTS --fast-anim"
[ "$WPE_DEBUG" = 1 ] || OPTS="$OPTS --no-debug-js"
[ "$WPE_LIMIT_REPEAT" = 1 ] && OPTS="$OPTS --limit-repeat"
[ "$WPE_OVERLAY" = 1 ] && OPTS="$OPTS --overlay-png /tmp/wpe_overlay" # set by the plugin for the automatic banner: no framebuffer, the visible part of each frame as a PNG that the plugin shows in a screen of enigma2
if [ "${WPE_PERSIST:-1}" = 1 ] && [ -d "$(dirname "$WPE_PERSIST_DIR")" ] && [ -w "$(dirname "$WPE_PERSIST_DIR")" ]; then
	OPTS="$OPTS --persist $WPE_PERSIST_DIR"
fi

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
if [ "$WPE_DEBUG" = 1 ]; then
	export GST_DEBUG="${GST_DEBUG:-2,webkitmediaplayer:4,webkitquirks:4,dvbvideosink:4,dvbaudiosink:4,webkitwebsrc:5}"
else
	export GST_DEBUG="${GST_DEBUG:-2}"
fi
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
http://* | https://* | ait:*) APP="$1" ;;
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
# WPE_CHANNEL="<onid> <tsid> <sid> <name>" (set by the plugin): the service enigma2 is tuned to. Applications are then started as
# broadcast-related applications of it (Broadcast.* requests answered, channel data from enigma2); without it as broadcast-independent ones.
case "$WPE_CHANNEL" in [0-9]*" "[0-9]*" "[0-9]*" "*) ;; *) WPE_CHANNEL="" ;; esac # three numbers and a name, else none
# WPE_COMPONENTS="V:<pid>:<encoding>:<crypted>:<aspect>;A:<pid>:<language>:<encoding>:<channels>:<active>:<ad>;S:..." (set by the plugin): the
# video, audio and subtitle streams of that service, told to the application before it starts (later changes come over the control FIFO)
case "$WPE_COMPONENTS" in *[!A-Za-z0-9:\;.+-]*) WPE_COMPONENTS="" ;; esac # only what such a line is made of
# WPE_AIT=<file> (set by the plugin): the AIT sections of that service, "<pid> <sid> <hex>" per line. The page argument "ait:" starts the AUTOSTART
# application of that AIT, "ait:<org id>.<app id>" another application of it (dvb://current.ait/<org>.<app>).
case "$WPE_AIT" in /tmp/*[!A-Za-z0-9_./-]* | [!/]*) WPE_AIT="" ;; esac # a plain path under /tmp, else none
HW=""
if [ -n "$WPE_HWVIDEO" ]; then
	HW="--hwvideo-lazy --evt /tmp/wpe_fb.evt"
fi

if [ -n "$APP" ]; then
	export ORB_PLATFORM_LIB=$ORB/wpe/libORBPlatformImpl.so
	# the plugin sends "quit" through the FIFO; the app is launched as soon as wpe_fb has created it (it reads its FIFO once it
	# is fully set up, commands wait in the pipe until then)
	( n=0; while [ ! -p $CTL ] && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done
	  if [ -p $CTL ]; then
		[ -n "$WPE_CHANNEL" ] && echo "channel $WPE_CHANNEL" > $CTL
		[ -n "$WPE_CHANNEL" ] && [ -n "$WPE_COMPONENTS" ] && echo "components $WPE_COMPONENTS" > $CTL
		case "$APP" in
		ait:*)
			# the real AIT: the service was selected and its AIT sections follow; the engine starts the AUTOSTART application by itself when the
			# table is complete ("ait:"), another application is asked for by its locator ("ait:<org>.<app>")
			set -- $WPE_CHANNEL
			if [ -n "$WPE_AIT" ] && [ -r "$WPE_AIT" ] && [ $# -ge 3 ]; then
				echo "service $1 $2 $3" > $CTL
				while read -r line; do echo "ait $line" > $CTL; done <"$WPE_AIT"
			fi
			[ "$APP" != "ait:" ] && echo "app dvb://current.ait/${APP#ait:}" > $CTL
			;;
		*) echo "app $APP" > $CTL ;;
		esac
	  fi ) &
	# WPE_OWNER=<pid> (set by the plugin): enigma2's process. When it is gone (a restart of the GUI, a crash) nobody would ever send "quit": wpe_fb and its
	# web processes stayed behind (300 MB of RAM, the decoder, the FIFOs). A watchdog asks it to end then (SIGTERM = a clean quit), and makes sure.
	case "$WPE_OWNER" in '' | *[!0-9]*) WPE_OWNER="" ;; esac
	$WPE_FB $HW --orb "$ORB" $OUTMODE $OPTS --ctl $CTL --secs 0 &
	WPID=$!
	if [ -n "$WPE_OWNER" ]; then
		( while kill -0 "$WPID" 2>/dev/null; do
			if ! kill -0 "$WPE_OWNER" 2>/dev/null; then
				kill "$WPID" 2>/dev/null
				sleep 4
				kill -9 "$WPID" 2>/dev/null
				break
			fi
			sleep 2
		done ) &
	fi
	wait "$WPID"
	exit $?
else
	exec $WPE_FB $HW $OUTMODE $OPTS --ctl $CTL --secs 0 "$1"
fi
