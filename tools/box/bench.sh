#!/bin/sh
# Frame-rate / CPU / memory benchmark of WPE on this box.
#   usage: sh bench.sh [run_ms]        (default 12000)
. /media/hdd/wpe-test/env.sh
cd /media/hdd/wpe-test
RUN_MS=${1:-12000}

uptime_s() { awk '{print $1}' /proc/uptime; }
avail()    { awk '/MemAvailable/{print $2}' /proc/meminfo; }
ticks_now() {
  s=0
  for p in $(pgrep -f "WPEWebProcess|WPENetworkProcess|bin/wpe_shot"); do
    t=$(awk '{print $14+$15}' /proc/$p/stat 2>/dev/null)
    s=$((s + ${t:-0}))
  done
  echo $s
}

run() {
  page="$1"; label="$2"; shift 2
  out=/tmp/bench_out.txt
  env WPE_SHOT_RUN_MS=$RUN_MS "$@" /media/hdd/wpe-test/bin/wpe_shot /media/hdd/wpe-test/pages/$page /media/hdd/wpe-test/shot_bench_$label.ppm > $out 2>&1 &
  pid=$!
  t0=$(uptime_s); t3ticks=""; t3time=""; max=0; base=$(avail); minav=$base
  while kill -0 $pid 2>/dev/null; do
    tk=$(ticks_now); now=$(uptime_s)
    [ "$tk" -gt "$max" ] && max=$tk
    if [ -z "$t3ticks" ] && awk "BEGIN{exit !($now-$t0>=3.0)}"; then t3ticks=$tk; t3time=$now; fi
    a=$(avail); [ "$a" -lt "$minav" ] && minav=$a
    sleep 1
  done
  wait $pid; rc=$?
  t1=$(uptime_s)
  awk -v page="$page" -v label="$label" -v rc="$rc" -v max="$max" -v t3="${t3ticks:-0}" -v t3t="${t3time:-$t0}" -v t1="$t1" \
      -v drop=$((base - minav)) '
    /page reports fps=/ { sub(/.*fps=/, ""); split($0, a, " "); f = a[1] + 0; n++; sum += f; if (min == "" || f < min) min = f;
                          m = a[2]; sub(/maxdt=/, "", m); sub(/ms/, "", m); if (m + 0 > worst) worst = m + 0 }
    /RESULT/ { res = $0; sub(/.*RESULT: /, "", res) }
    END {
      secs = t1 - t3t; cpu = (secs > 0) ? (max - t3) / secs : 0;
      printf "%-18s %-4s fps avg %5.1f min %5.1f | worst frame gap %4d ms | CPU %3.0f%% of one core (2 cores = 200%%) | mem drop %5d kB | exit %s\n",
             page, label, (n ? sum / n : 0), min, worst, cpu, drop, rc
    }' $out
}

echo "== WPE benchmark: ${RUN_MS} ms per run, 1280x720, dual-core Cortex-A15, enigma2 running =="
for page in bench_light.html bench_portal.html bench_full.html; do
  run $page GPU  X=1
  run $page CPU  WEBKIT_SKIA_ENABLE_CPU_RENDERING=1
done
