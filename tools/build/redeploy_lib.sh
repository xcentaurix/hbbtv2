set -uo pipefail
SP=/mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad
bash /tmp/inspect_ipk.sh 2>&1 | tail -1
bash /tmp/mk_deploy.sh 2>&1 | grep -E 'patched|NOT FOUND'
L=/home/alpha/wpe-test/deploy/lib/libWPEWebKit-2.0.so.1
ls -la --time-style=+%H:%M:%S $L | awk '{print $5,$6}'
strings -a $L | grep -E 'get-decoder-time|KEY_UNIT|seekCompletes|DreamboxHolePunch' | sort -u
