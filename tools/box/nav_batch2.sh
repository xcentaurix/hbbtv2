#!/bin/sh
# Phase 1: repeat the quiet variant (no debug.js, GST_DEBUG=2) three times to see whether it beats the baseline spread.
cd /media/hdd/wpe-test || exit 1
for l in q0a q0b q0c; do
	echo "start $l $(date +%T)"
	sh nav_bench.sh $l 1.5 0 0 0 | tail -1
	sleep 20
done
echo "batch finished $(date +%T)"
