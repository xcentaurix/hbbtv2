#!/bin/sh
# Phase 1 tests (wpe_fb.p1): auto-repeat limiting (r1, r2), persistent session cold/warm (pc, pw1, pw2), and the phase 1 defaults together (p1a).
cd /media/hdd/wpe-test || exit 1
export NAV_BIN=wpe_fb.p1
run() { label=$1; hidpi=$2; debug=$3; echo "start $label $(date +%T)"; sh nav_bench.sh $label $hidpi $debug 0 0 | tail -1; sleep 20; }
REPEAT=1 run r1 1.5 1
REPEAT=1 run r2 1.5 1
rm -rf persist-a
PERSIST=a run pc 1.5 1
echo "persist-a after the cold run: $(du -sk persist-a | cut -f1) KB, $(find persist-a -type f | wc -l) files"
PERSIST=a run pw1 1.5 1
PERSIST=a run pw2 1.5 1
echo "persist-a now: $(du -sk persist-a | cut -f1) KB, $(find persist-a -type f | wc -l) files"
PERSIST=a REPEAT=1 run p1a 1.5 0
echo "batch finished $(date +%T)"
