p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/run_wpe.sh"
s = open(p).read()
old = ". /media/hdd/wpe-test/env.sh\n"
new = ". /media/hdd/wpe-test/env.sh\n# media pipeline diagnostics into the log (/tmp/wpe_fb.log): player, quirks and the dvb sinks; the page's own console/media events\n# come from orb/debug.js as \"[page] ...\" lines\nexport GST_DEBUG=\"${GST_DEBUG:-2,webkitmediaplayer:4,webkitquirks:3,dvbvideosink:3,dvbaudiosink:3}\"\n"
assert s.count(old) == 1
open(p, "w").write(s.replace(old, new))
print("ok")
