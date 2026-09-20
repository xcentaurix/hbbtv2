p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-shot/files/wpe_fb.c"
s = open(p).read()


def sub(old, new):
    global s
    assert s.count(old) == 1, (old[:60], s.count(old))
    s = s.replace(old, new)


# 1) simplify the request log line
sub('''        fprintf(stderr, "handover: web process asks for the decoder (%s", l->buf);
        fprintf(stderr, "%s)\\n", strchr(l->buf, '\\n') ? "" : "");
''', '''        fprintf(stderr, "handover: web process asks for the decoder: %s", l->buf);
''')
# 2) includes
sub("#include <sys/mman.h>\n", "#include <sys/mman.h>\n#include <sys/socket.h>\n#include <sys/stat.h>\n#include <sys/un.h>\n")
# 3) options
sub('        else if (!strcmp(argv[i], "--hwvideo")) hwvideo = TRUE;\n',
    '        else if (!strcmp(argv[i], "--hwvideo")) hwvideo = TRUE;\n'
    '        else if (!strcmp(argv[i], "--hwvideo-lazy")) { hwvideo = TRUE; hw_lazy = TRUE; }\n'
    '        else if (!strcmp(argv[i], "--evt") && i + 1 < argc) evt_arg = argv[++i];\n')
sub("    const char *ctl = NULL;\n", "    const char *ctl = NULL, *evt_arg = NULL;\n")
# 4) lazy mode: the live service is still playing, so do not blank the plane at start; start the handover
sub("        plane_save();\n        plane_blank();\n", "        plane_save();\n        if (!hw_lazy)\n            plane_blank();\n")
old = '        fprintf(stderr, "hwvideo: video plane origin %s on a %s screen\\n", origin, screen);\n'
sub(old, old + "        if (hw_lazy)\n            handover_start(evt_arg);\n")
# 5) ctl command
old = '    } else if (!strcmp(line, "quit")) {\n'
sub(old, '    } else if (!strcmp(line, "decoder-free")) {\n        handover_decoder_free();\n' + old)
# 6) shutdown
sub("    plane_restore();\n", "    if (hw_lazy)\n        handover_stop();\n    plane_restore();\n")
# 7) documentation
old = " *     --info            print the framebuffer parameters and exit\n"
sub(old, (" *     --hwvideo-lazy    like --hwvideo, but the live service keeps playing until media needs the decoder: the web process\n"
          " *                       asks for it over a socket (see \"decoder handover\"), ctl \"decoder-free\" answers\n"
          " *     --evt PATH        FIFO on which \"acquire\"/\"release\" events for the enigma2 plugin are written (with --hwvideo-lazy)\n") + old)
open(p, "w").write(s)
print("ok")
