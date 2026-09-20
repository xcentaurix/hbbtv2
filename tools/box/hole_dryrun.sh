#!/bin/sh
# Where would the video plane go for a <video> at css (100,50) 640x360? Dry run: /proc is not written. Needs no session running.
cd /media/hdd/wpe-test || exit 1
. ./env.sh
export WPE_DREAM_VIDEO_DRYRUN=1
for H in 1.0 1.5; do
  echo "== --hidpi $H"
  if [ "$H" = "1.0" ]; then ARG=""; else ARG="--hidpi $H"; fi
  ./bin/wpe_fb.hidpi --hwvideo $ARG --transparent --fine-damage --secs 9 pages/hole_test.html 2>&1 | grep -a "dry run\|hidpi:\|hwvideo: video plane origin" | sort -u | head -6
done
echo "plane after (must be untouched): $(cat /proc/stb/vmpeg/0/dst_left /proc/stb/vmpeg/0/dst_top /proc/stb/vmpeg/0/dst_width /proc/stb/vmpeg/0/dst_height | tr '\n' ' ')"
