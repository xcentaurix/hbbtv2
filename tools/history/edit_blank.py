p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-shot/files/wpe_fb.c"
s = open(p).read()
old = '''static void plane_blank(void)
{
    int fd = open("/dev/dvb/adapter0/video0", O_RDWR | O_NONBLOCK);'''
new = '''static void plane_blank(void)
{
    if (getenv("WPE_FB_NO_BLANK")) { /* protocol tests: the decoder may still belong to the live service */
        fprintf(stderr, "hwvideo: blanking skipped (WPE_FB_NO_BLANK)\n");
        return;
    }
    int fd = open("/dev/dvb/adapter0/video0", O_RDWR | O_NONBLOCK);'''
assert s.count(old) == 1
open(p, "w").write(s.replace(old, new))
print("ok")
