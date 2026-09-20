#!/bin/bash
# Gracefully stop any running bitbake client, then relaunch the wpewebkit build fully detached.
SP=/mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad
LOG=/home/alpha/wpe-build6.log

pids=$(pgrep -f "bin/bitbake wpewebkit" || true)
if [ -n "$pids" ]; then
  echo "stopping bitbake client(s): $pids"
  kill -INT $pids
  for i in $(seq 1 60); do
    pgrep -f "bin/bitbake wpewebkit" >/dev/null || break
    sleep 3
  done
fi
if pgrep -f "bin/bitbake wpewebkit" >/dev/null; then
  echo "bitbake client still running after wait; not relaunching"
  exit 1
fi

echo "launching detached build, log: $LOG"
setsid nohup nice -n 10 bash "$SP/bb.lf.sh" wpewebkit > "$LOG" 2>&1 < /dev/null &
sleep 2
pgrep -af "bin/bitbake wpewebkit" | cut -c1-100
