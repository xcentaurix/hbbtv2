p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/run_wpe.sh"
s = open(p).read()
old = '''	# the plugin sends "quit" through the FIFO; the app is launched once wpe_fb has created it
	( n=0; while [ ! -p $CTL ] && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done
	  sleep 1
	  [ -p $CTL ] && echo "app $APP" > $CTL ) &'''
new = '''	# the plugin sends "quit" through the FIFO; the app is launched as soon as wpe_fb has created it (it reads its FIFO once it
	# is fully set up, commands wait in the pipe until then)
	( n=0; while [ ! -p $CTL ] && [ $n -lt 100 ]; do sleep 0.1; n=$((n+1)); done
	  [ -p $CTL ] && echo "app $APP" > $CTL ) &'''
assert s.count(old) == 1
open(p, "w").write(s.replace(old, new))
print("ok")
