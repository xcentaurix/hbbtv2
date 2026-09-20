p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/run_wpe.sh"
s = open(p).read()
old = '''	while [ -n "$(fuser /dev/dvb/adapter0/video0 /dev/dvb/adapter0/audio0 2>&1 | tr -d ' ')" ] && [ $n -lt 80 ]; do sleep 0.1; n=$((n+1)); done
	HW="--hwvideo"
'''
new = '''	while [ -n "$(fuser /dev/dvb/adapter0/video0 /dev/dvb/adapter0/audio0 2>&1 | tr -d ' ')" ] && [ $n -lt 80 ]; do sleep 0.1; n=$((n+1)); done
	# only if it really is free: never open the decoder while enigma2 still uses it (that would disturb the live picture)
	if [ -z "$(fuser /dev/dvb/adapter0/video0 /dev/dvb/adapter0/audio0 2>&1 | tr -d ' ')" ]; then
		HW="--hwvideo"
	else
		echo "run_wpe: the video decoder is still in use, hardware video disabled" >&2
	fi
'''
assert s.count(old) == 1
open(p, "w").write(s.replace(old, new))
print("ok")
