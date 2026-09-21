#!/bin/sh
# Navigation benchmark (docs/performance-plan.txt, phase 0): runs a scripted session of the ZDF mediathek HEADLESS (no --fb: nothing is
# drawn on the TV, the live service is not touched) and leaves a timestamped trace in /tmp/nav_<label>.log for tools/box/nav_analyze.py.
#
#   usage: sh nav_bench.sh <label> [hidpi=1.5] [debug=1] [fast_anim=0] [dump=0]
#     hidpi      render scale (1.5 = the real setting)
#     debug      1: like the real setup (orb/debug.js + GST_DEBUG level 4 categories); 0: quiet (no debug.js, GST_DEBUG=2)
#     fast_anim  1: --fast-anim (CSS transitions 1 ms, no smooth scrolling)
#     dump       1: write /tmp/nav_<label>_<phase>.ppm of the canvas after the main phases (6 MB each, RAM!) - for checking the scenario
#   environment: NAV_APP overrides the application URL; NAV_CHANNEL="<onid> <tsid> <sid> <name>" makes it a broadcast-related application of that service; NAV_BIN the binary (default wpe_fb.trace); PERSIST=<name> a persistent session; REPEAT=1 sends
#                the burst as auto-repeat (first key "key", the rest "keyrepeat"); MAINSAMPLE=1 also samples wpe_fb's main thread at 10 Hz (state, CPU, wchan)
#                into /tmp/nav_<label>.main, to find out what a main loop stall ("loop-late" in the trace) is doing.
#
# The session: launch the channel application, wait until the frames stop; RED (opens the mediathek), wait until idle; 15 single
# focus moves 1.5 s apart; a burst of 10 "right" 120 ms apart (what a held key does); OK (page transition), BACK; quit.
# All phases are marked in the trace ("T <us> mark ...") together with a CPU / network sample every second.
LABEL=${1:?usage: nav_bench.sh <label> [hidpi] [debug] [fast_anim] [dump]}
HIDPI=${2:-1.5}
DEBUG=${3:-1}
FASTANIM=${4:-0}
DUMP=${5:-0}
W=/media/hdd/wpe-test
APP=${NAV_APP:-http://hbbtv.zdf.de/zdfstart/index.php}
CTL=/tmp/nav_bench.ctl
LOG=/tmp/nav_$LABEL.log

if pidof wpe_fb wpe_fb.trace >/dev/null 2>&1; then # by process name: pgrep -f would also match the shell that started this script
	echo "a wpe_fb is running (the plugin?) - not starting"
	exit 1
fi

. $W/env.sh
export WEBKIT_SHM_READBACK_LOG=1
mkdir -p $W/mediacache
export WPE_SHELL_MEDIA_DISK_CACHE_PATH=$W/mediacache
export WPE_SHELL_MEDIA_DISK_CACHE_SIZE_BYTES=8388608
export WPE_SHELL_MEDIA_DISK_CACHE_SIZE_NSEC=10000000000
if [ "$DEBUG" = 1 ]; then
	ORBDIR=$W/orb
	export GST_DEBUG="2,webkitmediaplayer:4,webkitquirks:4,dvbvideosink:4,dvbaudiosink:4"
else
	# the same polyfill and modules without debug.js (wpe_fb injects debug.js only when it exists in the ORB directory)
	ORBDIR=$W/orb-nodebug
	mkdir -p $ORBDIR
	for f in hbbtv.js iframe.js dash.all.min.js playerpage.html ext wpe; do ln -sf $W/orb/$f $ORBDIR/$f; done
	export GST_DEBUG=2
fi
export ORB_PLATFORM_LIB=$ORBDIR/wpe/libORBPlatformImpl.so

BIN=${NAV_BIN:-wpe_fb.trace} # wpe_fb.p1 = with the phase 1 options
OPTS="--orb $ORBDIR --autoplay deny --hidpi $HIDPI --fine-damage --transparent --ctl $CTL --trace --secs 0"
[ -n "$PERSIST" ] && OPTS="$OPTS --persist $W/persist-$PERSIST" # PERSIST=<name>: cache, cookies, storage in persist-<name> (delete it for a cold start)
[ "$FASTANIM" = 1 ] && OPTS="$OPTS --fast-anim"
[ -n "$NAV_EXTRA" ] && OPTS="$OPTS $NAV_EXTRA" # any other wpe_fb options

rm -f $CTL $LOG /tmp/nav_$LABEL*.ppm
$W/bin/$BIN $OPTS > $LOG 2>&1 &
PID=$!
n=0
while [ ! -p $CTL ] && [ $n -lt 100 ]; do sleep 0.1; n=$((n + 1)); done
[ -p $CTL ] || { echo "wpe_fb did not start"; tail -5 $LOG; kill $PID 2>/dev/null; exit 1; }

ctl() { echo "$*" > $CTL; }
frames() { grep -c '^T [0-9]* frame ' $LOG; }
ticks() { awk '{print $14+$15}' /proc/$1/stat 2>/dev/null || echo 0; }
rx() { awk 'NR>2{sub(/^ +/,""); split($0,a,":"); if (a[1]!="lo") {split(a[2],b," "); s+=b[1]}} END{print s}' /proc/net/dev; }
procpid() { pgrep -f "$1" | head -1; }
uptime_s() { cut -d' ' -f1 /proc/uptime; } # CLOCK_BOOTTIME seconds: the harness's own clock, aligned with the trace by nav_analyze.py
# CPU ticks of ALL processes whose name matches: WebKit starts a new web process when the application navigates to another site
sumticks() { awk -v pat="$1" '$2 ~ pat {s += $14 + $15} END {print s + 0}' /proc/[0-9]*/stat 2>/dev/null; }
# a key: the send time (harness clock) goes into the trace first, so that the delay until wpe_fb has read the key is measurable
key() { ctl "mark send $1 $(uptime_s)"; ctl "key $1"; }
rkey() { ctl "mark send $1 $(uptime_s)"; ctl "keyrepeat $1"; } # what the remote's auto-repeat sends
vm() { awk '/^(allocstall|pgscan_direct_normal|pgscan_kswapd_normal|pgmajfault) /{printf "%s=%s ", $1, $2}' /proc/vmstat; }
threads() { # cumulative CPU ticks per thread of every web process: "<comm> <ticks>"
	for web in $(pgrep -f WPEWebProcess); do
		for t in /proc/$web/task/*; do echo "$(cat $t/comm) $(awk '{print $14+$15}' $t/stat)"; done
	done
}

# wait until frames stop: at least <minframes> new frames since the call, then <quiet> seconds without one; give up after <max> s
wait_idle() {
	max=$1; quiet=$2; minframes=$3
	base=$(frames); last=$base; still=0; t=0
	while [ $t -lt $max ]; do
		sleep 1; t=$((t + 1)); cur=$(frames)
		if [ "$cur" = "$last" ]; then still=$((still + 1)); else still=0; fi
		last=$cur
		if [ $still -ge $quiet ] && [ $((cur - base)) -ge $minframes ]; then ctl "mark idle after=${t}s frames=$((cur - base))"; return 0; fi
	done
	ctl "mark idle-timeout after=${t}s frames=$((last - base))"
	return 1
}

# CPU / network / load sample into the trace every second
(
	while kill -0 $PID 2>/dev/null; do
		# ui = whole wpe_fb (uiu user / uis system ticks), uimain = its main thread; web/net = all web / network processes
		[ -p $CTL ] && ctl "mark cpu ui=$(ticks $PID) web=$(sumticks WPEWebProcess) net=$(sumticks WPENetworkProce) rx=$(rx) load=$(cut -d' ' -f1 /proc/loadavg) up=$(uptime_s) $(awk '{printf "uiu=%d uis=%d ", $14, $15}' /proc/$PID/stat) $(awk '{printf "uimain=%d ", $14 + $15}' /proc/$PID/task/$PID/stat) $(vm)"
		# ticks per thread of wpe_fb: "tid:name:user/system"
		[ -p $CTL ] && ctl "mark uith $(awk '{gsub(/[()]/, ""); printf "%s:%s:%d/%d ", $1, $2, $14, $15}' /proc/$PID/task/*/stat 2>/dev/null)"
		sleep 1
	done
) &
SAMPLER=$!

# MAINSAMPLE=1: 10 Hz state of wpe_fb's main thread into /tmp/nav_<label>.main ("uptime state utime stime wchan"), a file, not the FIFO,
# so that it is not delayed by the main loop stall it is meant to catch (state R = running, S/D = sleeping in wchan)
if [ -n "$MAINSAMPLE" ]; then
	(
		rm -f /tmp/nav_$LABEL.main
		while kill -0 $PID 2>/dev/null; do
			awk 'FILENAME == "/proc/uptime" {u = $1; next} FILENAME ~ /wchan/ {w = $1; next} {s = $3; ut = $14; st = $15} END {print u, s, ut, st, w}' /proc/uptime /proc/$PID/task/$PID/wchan /proc/$PID/task/$PID/stat >> /tmp/nav_$LABEL.main 2>/dev/null
			sleep 0.1
		done
	) &
fi

dump() { [ "$DUMP" = 1 ] && ctl "dump /tmp/nav_${LABEL}_$1.ppm"; }

ctl "mark run label=$LABEL hidpi=$HIDPI debug=$DEBUG fast_anim=$FASTANIM persist=${PERSIST:-none} repeat=${REPEAT:-0} bin=$BIN app=$APP"
sleep 1
ctl "mark phase launch"
[ -n "$NAV_CHANNEL" ] && ctl "channel $NAV_CHANNEL" # NAV_CHANNEL="1 1019 10301 Das Erste HD": start the application as a broadcast-related one of this service
ctl "app $APP"
wait_idle 60 4 3
dump 1_app
sleep 2

ctl "mark phase red"
key red
wait_idle 90 4 5
dump 2_mediathek
sleep 2
threads > /tmp/nav_$LABEL.thr0

ctl "mark phase steps"
for k in right right right right right right down down down right right up up left left; do
	ctl "mark step $k"
	key $k
	sleep 1.5
done
dump 3_after_steps

ctl "mark phase burst"
i=0
while [ $i -lt 10 ]; do
	if [ "$REPEAT" = 1 ] && [ $i -gt 0 ]; then rkey right; else key right; fi
	sleep 0.12
	i=$((i + 1))
done
ctl "mark burst-end"
wait_idle 30 3 1
dump 4_after_burst

ctl "mark phase transition"
key ok
wait_idle 40 4 3
dump 5_after_ok
sleep 1
ctl "mark phase back"
key back
wait_idle 30 4 2
dump 6_after_back

threads > /tmp/nav_$LABEL.thr1
for p in $PID $(procpid WPEWebProcess) $(procpid WPENetworkProcess); do echo "rss $(cat /proc/$p/comm 2>/dev/null) $(grep VmRSS /proc/$p/status 2>/dev/null)" >> /tmp/nav_$LABEL.thr1; done
free | awk 'NR==2{print "mem total="$2" free="$4" cached="$6}' >> /tmp/nav_$LABEL.thr1
ctl "mark end"
sleep 1
ctl quit
n=0
while kill -0 $PID 2>/dev/null && [ $n -lt 100 ]; do sleep 0.1; n=$((n + 1)); done
kill $SAMPLER 2>/dev/null
kill $PID 2>/dev/null
echo "done: $LOG ($(wc -l < $LOG) lines, $(grep -c '^T [0-9]* frame ' $LOG) frames)"
