#!/bin/bash
# Stop a running bitbake build now: second SIGINT, then kill the compile if it lingers.
pkill -INT -f "bin/bitbake wpe-shot" 2>/dev/null
for i in $(seq 1 20); do
  pgrep -f "bin/bitbake wpe-shot" >/dev/null || break
  sleep 3
done
if pgrep -f "bin/bitbake wpe-shot" >/dev/null; then
  echo "bitbake client still alive; killing the compile (ninja) so it can wind down"
  pkill -f "ninja -v -j 4 all"
  for i in $(seq 1 20); do
    pgrep -f "bin/bitbake wpe-shot" >/dev/null || break
    sleep 3
  done
fi
echo "--- remaining bitbake/ninja processes:"
pgrep -af "bin/bitbake |ninja -v" | cut -c1-100
echo "--- (end)"
