#!/bin/bash
# Re-extract the new wpewebkit packages, rebuild the private deploy dir and both test programs.
set -uo pipefail
SP=/mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad
P=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp/deploy/ipk/cortexa15hf-neon-vfpv4
echo "== new packages"
ls -la --time-style=+%H:%M $P/libwpewebkit-2.0-1_*.ipk $P/libwpewebkit-2.0-dev_*.ipk 2>&1 | awk '{print $5, $6, $7}'
echo "== extract"; bash "$SP/inspect_ipk.lf.sh" 2>&1 | grep -E "runtime package|libWPEWebKit|WPE.*Process|extracted size" | head -8
echo "== deploy dir"; bash "$SP/mk_deploy.lf.sh" 2>&1 | grep -E "patched|NOT FOUND|total deploy"
echo "== test programs"
bash "$SP/hand_build_shot.lf.sh" 2>&1 | grep -E "compile exit|wpe_shot$"
bash "$SP/build_egl_probe.lf.sh" 2>&1 | grep -E "compile exit"
echo "== is the EGL fallback in the new library?"
L=/home/alpha/wpe-test/deploy/lib/libWPEWebKit-2.0.so.1
strings -a "$L" | grep -cE "Could not create default EGL display" | sed 's/^/default-display code strings: /'
ls -la /home/alpha/wpe-test/deploy/lib/libWPEWebKit-2.0.so.1 /home/alpha/wpe-test/deploy/bin | awk '{print $5, $NF}'
