#!/bin/sh
# Verify partial read-back: compare every partial frame with a full read-back and log timings.
. /media/hdd/wpe-test/env.sh
cd /media/hdd/wpe-test
for page in bench_light.html bench_portal.html bench_full.html; do
  echo "#### $page"
  WPE_SHOT_FINE_DAMAGE=1 WEBKIT_SHM_READBACK_LOG=1 WEBKIT_SHM_READBACK_VERIFY=1 WPE_SHOT_RUN_MS=6000 \
    timeout 60 /media/hdd/wpe-test/bin/wpe_shot /media/hdd/wpe-test/pages/$page /tmp/verify.ppm 2>&1 | grep -E "shm-readback|fine-grained" > /tmp/verify_$page.txt
  total=$(grep -c "shm-readback\] \(partial\|full\)" /tmp/verify_$page.txt)
  partial=$(grep -c "shm-readback\] partial" /tmp/verify_$page.txt)
  full=$(grep -c "shm-readback\] full" /tmp/verify_$page.txt)
  ok=$(grep -c "verify: ok" /tmp/verify_$page.txt)
  bad=$(grep -c "verify: MISMATCH" /tmp/verify_$page.txt)
  grep fine-grained /tmp/verify_$page.txt | head -1; echo "read-backs: $total (partial $partial, full $full) | verify ok: $ok, MISMATCH: $bad"
  echo "-- sample partial frames:"; grep "shm-readback\] partial" /tmp/verify_$page.txt | sed -n '3p;10p;20p' | cut -c1-140
  [ "$bad" -gt 0 ] && { echo "-- first mismatches:"; grep MISMATCH /tmp/verify_$page.txt | head -3 | cut -c1-160; }
done
