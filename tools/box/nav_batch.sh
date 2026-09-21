#!/bin/sh
# Phase 0 batch: the variants of docs/performance-plan.txt, one after the other (about 5 minutes each). Logs: /tmp/nav_<label>.log
cd /media/hdd/wpe-test || exit 1
for v in "base2 1.5 1 0" "base3 1.5 1 0" "h10 1.0 1 0" "fa1 1.5 1 1" "q0 1.5 0 0" "h125 1.25 1 0"; do
	set -- $v
	echo "start $1 $(date +%T)"
	sh nav_bench.sh $1 $2 $3 $4 0 | tail -1
	sleep 20
done
echo "batch finished $(date +%T)"
