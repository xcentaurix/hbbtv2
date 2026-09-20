p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/run_wpe.sh"
s = open(p).read()
old = 'export GST_DEBUG="${GST_DEBUG:-2,webkitmediaplayer:4,webkitquirks:4,dvbvideosink:4,dvbaudiosink:4}"\n'
new = old + '''# Progressive media (a whole film as one MP4) is buffered in a temporary file, by default in /var/tmp = a 500 MB tmpfs (RAM!) that fills
# up within half a minute at broadband speed; and the default buffering thresholds (100 KB) are a tenth of a second of HD video, which
# makes the player stall over and over. Put the file on the disk (WebKit unlinks it right after creating it) and size the buffer for video.
mkdir -p /media/hdd/wpe-test/mediacache
export WPE_SHELL_MEDIA_DISK_CACHE_PATH=/media/hdd/wpe-test/mediacache
export WPE_SHELL_MEDIA_DISK_CACHE_SIZE_BYTES=8388608
export WPE_SHELL_MEDIA_DISK_CACHE_SIZE_NSEC=10000000000
'''
assert s.count(old) == 1
open(p, "w").write(s.replace(old, new))
print("ok")
