#!/bin/bash
# Build the ORB JS polyfill (plain concatenation via the repo's Makefile) in a WSL-native copy.
set -uo pipefail
SP=/mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad
W=/home/alpha/orb
if [ ! -d "$W/.git" ]; then
  rm -rf "$W"
  git clone --depth 1 https://github.com/OpenRedButtonProject/orb.git "$W" 2>&1 | tail -1
fi
cd "$W" && git log -1 --format='orb %h %ad %s' --date=short
make build ORB_NATIVE=rdk BBC_API_ENABLE=0 2>&1 | tail -8
echo "== outputs"
ls -la out/resources/assets/polyfill 2>&1 | awk '{print $5, $NF}'
echo "== sanity: bridge entry points present in hbbtv.js"
grep -c "wpeBridge.request" out/resources/assets/polyfill/hbbtv.js 2>/dev/null
grep -o "oipfApplicationManager\|oipfCapabilities\|oipfConfiguration\|video/broadcast" out/resources/assets/polyfill/hbbtv.js 2>/dev/null | sort | uniq -c
