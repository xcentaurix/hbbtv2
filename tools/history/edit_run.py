p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/run_wpe.sh"
s = open(p).read()
old = '''if [ -n "$APP" ]; then'''
new = '''# WPE_HWVIDEO=1 (set by the plugin, which has stopped the live service): <video> plays on the hardware video plane. Wait until
# enigma2 has really let go of the decoder (the dvb sinks open video0/audio0 and would fight with it).
HW=""
if [ -n "$WPE_HWVIDEO" ]; then
	n=0
	while [ -n "$(fuser /dev/dvb/adapter0/video0 /dev/dvb/adapter0/audio0 2>&1 | tr -d ' ')" ] && [ $n -lt 80 ]; do sleep 0.1; n=$((n+1)); done
	HW="--hwvideo"
fi

if [ -n "$APP" ]; then'''
assert s.count(old) == 1
s = s.replace(old, new)
assert s.count("./bin/wpe_fb --orb /media/hdd/wpe-test/orb --fb --transparent") == 1
s = s.replace("./bin/wpe_fb --orb /media/hdd/wpe-test/orb --fb --transparent", "./bin/wpe_fb $HW --orb /media/hdd/wpe-test/orb --fb --transparent")
assert s.count("exec ./bin/wpe_fb --fb --transparent") == 1
s = s.replace("exec ./bin/wpe_fb --fb --transparent", "exec ./bin/wpe_fb $HW --fb --transparent")
open(p, "w").write(s)
print("ok")
