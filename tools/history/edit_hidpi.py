p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-shot/files/wpe_fb.c"
s = open(p).read()


def sub(old, new, count=1):
    global s
    assert s.count(old) == count, (old[:80], s.count(old))
    s = s.replace(old, new)


# option + variable
sub("    gboolean fullscreen = FALSE;\n    out.scale = 1.0;\n", "    gboolean fullscreen = FALSE;\n    double hidpi = 0;\n    out.scale = 1.0;\n")
sub('        else if (!strcmp(argv[i], "--fullscreen")) fullscreen = TRUE;\n',
    '        else if (!strcmp(argv[i], "--fullscreen")) fullscreen = TRUE;\n'
    '        else if (!strcmp(argv[i], "--hidpi") && i + 1 < argc) hidpi = atof(argv[++i]);\n')

# the view is W x H logical pixels; with --hidpi its buffers are F times larger
sub('''    out.w = W;
    out.h = H;
    out.canvas = g_malloc0((size_t)W * H * 4);
''', '''    out.w = W;
    out.h = H;
    if (hidpi > 1.0) {
        out.w = (int)(W * hidpi + 0.5); /* buffers of a view with scale F are F times the logical size */
        out.h = (int)(H * hidpi + 0.5);
    }
    out.canvas = g_malloc0((size_t)out.w * out.h * 4);
''')
# everything below that computes the output from W/H uses the buffer size
sub("            out.scale = MIN((double)out.vinfo.xres / W, (double)out.vinfo.yres / H);\n",
    "            out.scale = MIN((double)out.vinfo.xres / out.w, (double)out.vinfo.yres / out.h);\n")
sub("        out.ow = (int)(W * out.scale + 0.5);\n        out.oh = (int)(H * out.scale + 0.5);\n        out.fb_x = px >= 0",
    "        out.ow = (int)(out.w * out.scale + 0.5);\n        out.oh = (int)(out.h * out.scale + 0.5);\n        out.fb_x = px >= 0")
sub("    } else {\n        out.ow = (int)(W * out.scale + 0.5);\n        out.oh = (int)(H * out.scale + 0.5);\n",
    "    } else {\n        out.ow = (int)(out.w * out.scale + 0.5);\n        out.oh = (int)(out.h * out.scale + 0.5);\n")

# the toplevel size stays logical, its scale is the device scale factor
sub("        wpe_toplevel_resize(top, W, H);\n",
    "        wpe_toplevel_resize(top, W, H);\n"
    "    if (top && hidpi > 1.0) {\n        wpe_toplevel_scale_changed(top, hidpi);\n        fprintf(stderr, \"hidpi: view %dx%d at scale %.2f renders %dx%d\\n\", W, H, hidpi, out.w, out.h);\n    }\n")

# the dumps and statistics use the buffer size
sub('            fprintf(f, "P6\\n%d %d\\n255\\n", W, H);\n            for (int i = 0; i < W * H; i++) {',
    '            fprintf(f, "P6\\n%d %d\\n255\\n", out.w, out.h);\n            for (int i = 0; i < out.w * out.h; i++) {')
sub("out.frames ? 100.0 * out.pixels / out.frames / ((double)W * H) : 0.0", "out.frames ? 100.0 * out.pixels / out.frames / ((double)out.w * out.h) : 0.0")
sub("    for (long i = 0; i < (long)W * H; i++) {\n            guint8 a = out.canvas[i * 4 + 3];",
    "    for (long i = 0; i < (long)out.w * out.h; i++) {\n            guint8 a = out.canvas[i * 4 + 3];")
sub("a0 * 100.0 / ((double)W * H)", "a0 * 100.0 / ((double)out.w * out.h)", 0) if False else None

# documentation
sub(" *     --dump-out f.ppm  with --scale: write the scaled output as it goes to the framebuffer\n",
    " *     --dump-out f.ppm  with --scale: write the scaled output as it goes to the framebuffer\n"
    " *     --hidpi F         device scale factor: the page is laid out at --size but rendered F times larger (sharp text; 1.5 gives\n"
    " *                       1920x1080 for a 1280x720 page, so --fullscreen then needs no scaling at all). Costs read-back time.\n")
open(p, "w").write(s)
print("ok")
