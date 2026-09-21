#!/bin/sh
# final check of the repeat switch with the final code: without --limit-repeat every repeat must pass, with it most are dropped
cd /media/hdd/wpe-test || exit 1
export NAV_BIN=wpe_fb.p2 REPEAT=1
echo "start rn $(date +%T)"; sh nav_bench.sh rn 1.5 0 0 0 | tail -1; sleep 15
echo "start rl $(date +%T)"; NAV_EXTRA=--limit-repeat sh nav_bench.sh rl 1.5 0 0 0 | tail -1
echo "batch finished $(date +%T)"
