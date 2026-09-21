#!/bin/sh
# Headless probe of one HbbTV application as a BROADCAST-RELATED application of the channel the box is tuned to (nothing is drawn on the
# TV, the service is not touched): launches it, waits, takes a screenshot of what it rendered, and reports which ORB requests it made and
# how they were answered.
#   usage: sh app_probe.sh <label> [url] [seconds] [keys...]
#     url      default: the ARD start application; NAV_BIN overrides the wpe_fb binary (default wpe_fb.p3, in /media/hdd/wpe-test/bin)
#     keys     sent one by one, 3 s apart, after the wait (e.g. red right ok)
#     PROBE_VIEW  view size and scale, default "--hidpi 1.5"; "--size 1920x1080 --hidpi 1.0" = a Full-HD CSS viewport
#   output: /tmp/probe_<label>.log and /tmp/probe_<label>.ppm (6 MB, RAM: delete it after use)
LABEL=${1:?usage: app_probe.sh <label> [url] [seconds] [keys...]}
URL=${2:-http://itv.ard.de/ardstart/index.html}
SECS=${3:-25}
shift 3 2>/dev/null
W=/media/hdd/wpe-test
BIN=${NAV_BIN:-wpe_fb.p3}
CTL=/tmp/probe.ctl
LOG=/tmp/probe_$LABEL.log

if pidof wpe_fb wpe_fb.trace wpe_fb.p1 wpe_fb.p2 wpe_fb.p3 >/dev/null 2>&1; then
	echo "a wpe_fb is running - not starting"
	exit 1
fi

# the channel enigma2 is tuned to: service reference 1:0:<type>:<sid>:<tsid>:<onid>:<namespace>:0:0:0:
JSON=$(wget -qO- http://127.0.0.1/api/getcurrent 2>/dev/null)
REF=$(echo "$JSON" | grep -o '"ref": *"[^"]*"' | head -1 | sed 's/.*"\([^"]*\)"$/\1/')
NAME=$(echo "$JSON" | grep -o '"name": *"[^"]*"' | sed -n 2p | sed 's/.*"\([^"]*\)"$/\1/')
[ -n "$NAME" ] || NAME=$(echo "$JSON" | grep -o '"name": *"[^"]*"' | head -1 | sed 's/.*"\([^"]*\)"$/\1/')
[ -n "$PROBE_REF" ] && { REF=$PROBE_REF; NAME=${PROBE_NAME:-probe}; } # PROBE_REF=1:0:19:283D:3FB:1:C00000:0:0:0: PROBE_NAME="Das Erste HD": another service than the tuned one
IFS=: read -r _ _ _ SID TSID ONID _ <<EOF
$REF
EOF
echo "tuned: $NAME ref=$REF  onid=$((0x$ONID)) tsid=$((0x$TSID)) sid=$((0x$SID))"

. $W/env.sh
export WEBKIT_SHM_READBACK_LOG=1 GST_DEBUG=2
ORBDIR=$W/orb
export ORB_PLATFORM_LIB=$ORBDIR/wpe/libORBPlatformImpl.so
rm -f $CTL $LOG /tmp/probe_$LABEL.ppm
$W/bin/$BIN --orb $ORBDIR --autoplay deny ${PROBE_VIEW:---hidpi 1.5} --fine-damage --transparent --ctl $CTL --trace --secs 0 > $LOG 2>&1 &
PID=$!
n=0; while [ ! -p $CTL ] && [ $n -lt 100 ]; do sleep 0.1; n=$((n + 1)); done
[ -p $CTL ] || { echo "wpe_fb did not start"; tail -5 $LOG; kill $PID 2>/dev/null; exit 1; }

echo "channel $((0x$ONID)) $((0x$TSID)) $((0x$SID)) $NAME" > $CTL
echo "app $URL" > $CTL
if [ -n "$DUMP_AT" ]; then
	prev=0
	for t in $DUMP_AT; do sleep $((t - prev)); prev=$t; echo "dump /tmp/probe_${LABEL}_$t.ppm" > $CTL; done
	sleep 2
else
	sleep $SECS
fi
for k in "$@"; do
	echo "key $k" > $CTL
	sleep 3
done
sleep ${PROBE_TAIL:-0} # seconds to wait after the last key (PROBE_TAIL=12: let the next page load)
echo "dump /tmp/probe_$LABEL.ppm" > $CTL
sleep 3
echo quit > $CTL
n=0; while kill -0 $PID 2>/dev/null && [ $n -lt 100 ]; do sleep 0.1; n=$((n + 1)); done
kill $PID 2>/dev/null

echo "== launch:"; grep -a -E '\[orb_host\]|orb: (application|loading)' $LOG | head -6 | cut -c1-170
echo "== ORB requests (object.method  x count):"; grep -a -o 'object=[A-Za-z]* method=[A-Za-z]*' $LOG | sort | uniq -c | sort -rn | cut -c1-90
echo "== answered: $(grep -a -c 'response={"result"' $LOG) results, $(grep -a -c 'response={"error"' $LOG) errors:"; grep -a -o 'response={"error":"[A-Za-z]*"' $LOG | sort | uniq -c
echo "== frames: $(grep -a -c '^T [0-9]* frame ' $LOG)"
