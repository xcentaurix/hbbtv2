set -e
B=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-browser/wpewebkit/wpewebkit_%.bbappend
grep -n '^PACKAGECONFIG = ' $B
sed -i 's|^PACKAGECONFIG = "dfg-jit jit remote-inspector unified-builds video woff2 wpe-platform wpe-platform-headless"|# mediasource = Media Source Extensions (window.MediaSource): HbbTV 2.0 applications and the ORB polyfill play DASH through it\nPACKAGECONFIG = "dfg-jit jit mediasource remote-inspector unified-builds video woff2 wpe-platform wpe-platform-headless"|' $B
grep -n 'PACKAGECONFIG = ' $B
cd /home/alpha
setsid nohup bash /home/alpha/bb.sh wpewebkit > /home/alpha/wpe-build14.log 2>&1 < /dev/null &
sleep 30
tail -c 600 /home/alpha/wpe-build14.log | tr '\r' '\n' | tail -4
