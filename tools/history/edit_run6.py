import re
p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/run_wpe.sh"
s = open(p).read()
start = s.index("# WPE_HWVIDEO=1 (set by the plugin")
end = s.index('if [ -n "$APP" ]; then')
new = '''# WPE_HWVIDEO=1 (set by the plugin): <video> plays on the hardware video plane, but the live service keeps playing until media really
# needs the decoder (wpe_fb "decoder handover": it asks the plugin, through the event FIFO, to stop the service and gives it back
# afterwards).
HW=""
if [ -n "$WPE_HWVIDEO" ]; then
	HW="--hwvideo-lazy --evt /tmp/wpe_fb.evt"
fi

'''
s = s[:start] + new + s[end:]
open(p, "w").write(s)
print("ok")
