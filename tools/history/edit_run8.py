p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/run_wpe.sh"
s = open(p).read()
assert s.count("--fb --fullscreen --transparent") == 2
s = s.replace("--fb --fullscreen --transparent", "--fb --fullscreen --hidpi 1.5 --transparent")
open(p, "w").write(s)
print("ok")
