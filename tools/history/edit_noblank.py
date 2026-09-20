p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-shot/files/wpe_fb.c"
s = open(p).read()

def sub(old, new):
    global s
    assert s.count(old) == 1, (old[:70], s.count(old))
    s = s.replace(old, new)

# the blank is not called any more (see the comment on plane_blank)
sub("    plane_blank(); /* stopService() leaves the last live frame on the plane */\n", "")
sub("        plane_save();\n        if (!hw_lazy)\n            plane_blank();\n", "        plane_save();\n")
sub("/* enigma2 leaves the last decoded frame on the video plane when it stops the live service (stopService() only closes the\n",
    "/* NOT USED: blanking the plane from here left the video output dark after enigma2 played the service again (the picture only\n"
    " * came back after another stop/play cycle of the service), so the frozen last frame of the live service is left alone: it is\n"
    " * replaced by the first video frame, and it is only visible where the page is transparent. What it was for: enigma2 leaves the last decoded frame on the video plane when it stops the live service (stopService() only closes the\n")
sub("static void plane_blank(void)\n{", "static void plane_blank(void) __attribute__((unused));\nstatic void plane_blank(void)\n{")
open(p, "w").write(s)
print("ok")
