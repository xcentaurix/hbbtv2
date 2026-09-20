set -uo pipefail
bash /tmp/inspect_ipk.sh 2>&1 | tail -1
bash /tmp/mk_deploy.sh 2>&1 | grep -E 'patched|NOT FOUND'
L=/home/alpha/wpe-test/deploy/lib/libWPEWebKit-2.0.so.1
ls -la --time-style=+%m-%d_%H:%M:%S $L | awk '{print $5,$6}'
echo "MSE markers: $(strings -a $L | grep -c 'MediaPlayerPrivateGStreamerMSE\|webkitmediasrc\|WebKitMediaSrc')"
strings -a $L | grep -E 'DreamboxHolePunch|get-decoder-time' | sort -u
