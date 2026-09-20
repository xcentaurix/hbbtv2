p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/run_wpe.sh"
s = open(p).read()
a = "./bin/wpe_fb $HW --orb /media/hdd/wpe-test/orb --fb --transparent"
b = "exec ./bin/wpe_fb $HW --fb --transparent"
assert s.count(a) == 1 and s.count(b) == 1
s = s.replace(a, "./bin/wpe_fb $HW --orb /media/hdd/wpe-test/orb --fb --fullscreen --transparent")
s = s.replace(b, "exec ./bin/wpe_fb $HW --fb --fullscreen --transparent")
open(p, "w").write(s)
print("ok")
