p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-shot/files/wpe_fb.c"
s = open(p).read()


def sub(old, new, count=1):
    global s
    assert s.count(old) == count, (old[:80], s.count(old))
    s = s.replace(old, new)


# ---- 1. Out: output size, scale, lookup tables
sub("    int w, h;\n    guint8 *canvas; /* BGRA, premultiplied, tightly packed */\n",
    "    int w, h; /* the web view */\n"
    "    guint8 *canvas; /* BGRA, premultiplied, tightly packed, w x h */\n"
    "    /* Output: the view scaled by `scale` (HbbTV applications are laid out at 1280x720 and shown scaled to the whole screen).\n"
    "     * conv holds the output in framebuffer format (ow x oh) whenever there is a framebuffer or a scaled dump. */\n"
    "    double scale;\n"
    "    int ow, oh;\n"
    "    int *xi0, *xi1, *yi0, *yi1; /* bilinear sampling: the two source columns/rows of every output column/row ... */\n"
    "    guint16 *xwt, *ywt; /* ... and the weight (0..256) of the second one */\n")

# ---- 2. every place that used the view size for the converted output now uses the output size
sub("    out.sw = MIN(out.fb_x + out.w, (int)out.vinfo.xres) - out.sx;\n    out.sh = MIN(out.fb_y + out.h, (int)out.vinfo.yres) - out.sy;\n",
    "    out.sw = MIN(out.fb_x + out.ow, (int)out.vinfo.xres) - out.sx;\n    out.sh = MIN(out.fb_y + out.oh, (int)out.vinfo.yres) - out.sy;\n")
sub("out.conv + (size_t)(ry + row) * out.w + (fx - out.fb_x),\n            (size_t)n * 4);",
    "out.conv + (size_t)(ry + row) * out.ow + (fx - out.fb_x),\n            (size_t)n * 4);")
sub("        int x = (k * 211 + 17) % out.w, y = (k * 97 + 5) % out.h;\n", "        int x = (k * 211 + 17) % out.ow, y = (k * 97 + 5) % out.oh;\n")
sub("        if (v != out.conv[(size_t)y * out.w + x])\n", "        if (v != out.conv[(size_t)y * out.ow + x])\n")
sub("    fb_write_rect(out.vinfo.yoffset, 0, 0, out.w, out.h);\n    return (g_get_monotonic_time() - t0) / 1000.0;",
    "    fb_write_rect(out.vinfo.yoffset, 0, 0, out.ow, out.oh);\n    return (g_get_monotonic_time() - t0) / 1000.0;")

# ---- 3. scaling: tables + the scaled blit
old_blit_start = "/* Copy one damaged rect of a frame to the shadow canvas and the framebuffer. */\nstatic void out_blit_rect("
sub(old_blit_start,
    '''/* Bilinear sampling tables for output size ow x oh from a view of w x h (pixel centres aligned). */
static void scale_setup(void)
{
    out.xi0 = g_new(int, out.ow); out.xi1 = g_new(int, out.ow); out.xwt = g_new(guint16, out.ow);
    out.yi0 = g_new(int, out.oh); out.yi1 = g_new(int, out.oh); out.ywt = g_new(guint16, out.oh);
    for (int d = 0; d < out.ow; d++) {
        double s = (d + 0.5) / out.scale - 0.5;
        int i0 = (int)floor(s);
        double f = s - i0;
        out.xi0[d] = CLAMP(i0, 0, out.w - 1);
        out.xi1[d] = CLAMP(i0 + 1, 0, out.w - 1);
        out.xwt[d] = (guint16)CLAMP((int)(f * 256.0 + 0.5), 0, 256);
    }
    for (int d = 0; d < out.oh; d++) {
        double s = (d + 0.5) / out.scale - 0.5;
        int i0 = (int)floor(s);
        double f = s - i0;
        out.yi0[d] = CLAMP(i0, 0, out.h - 1);
        out.yi1[d] = CLAMP(i0 + 1, 0, out.h - 1);
        out.ywt[d] = (guint16)CLAMP((int)(f * 256.0 + 0.5), 0, 256);
    }
}

/* a * (256 - w) + b * w, all four channels of two BGRA pixels at once (two 16-bit lanes per multiplication) */
static inline guint32 lerp_px(guint32 a, guint32 b, guint32 w)
{
    guint32 rb = (((a & 0x00ff00ffu) * (256 - w) + (b & 0x00ff00ffu) * w) >> 8) & 0x00ff00ffu;
    guint32 ag = (((a >> 8) & 0x00ff00ffu) * (256 - w) + ((b >> 8) & 0x00ff00ffu) * w) & 0xff00ff00u;
    return rb | ag;
}

/* The view rect (in view pixels) has changed in out.canvas: recompute the output pixels it touches, scaled bilinearly (on the
 * premultiplied pixels, which is the right thing to interpolate), converted to the framebuffer format, and put them on the page. */
static void out_scale_rect(int rx, int ry, int rw, int rh)
{
    int ox0 = MAX(0, (int)floor((rx - 1) * out.scale)), ox1 = MIN(out.ow, (int)ceil((rx + rw + 1) * out.scale));
    int oy0 = MAX(0, (int)floor((ry - 1) * out.scale)), oy1 = MIN(out.oh, (int)ceil((ry + rh + 1) * out.scale));
    if (ox1 <= ox0 || oy1 <= oy0)
        return;
    static guint32 *row;
    static int row_len;
    if (row_len < ox1 - ox0) {
        g_free(row);
        row_len = out.ow;
        row = g_new(guint32, row_len);
    }
    const guint32 *cv = (const guint32 *)out.canvas;
    for (int dy = oy0; dy < oy1; dy++) {
        const guint32 *r0 = cv + (size_t)out.yi0[dy] * out.w, *r1 = cv + (size_t)out.yi1[dy] * out.w;
        const guint32 wy = out.ywt[dy];
        for (int dx = ox0; dx < ox1; dx++) {
            const int a = out.xi0[dx], b = out.xi1[dx];
            const guint32 wx = out.xwt[dx];
            row[dx - ox0] = lerp_px(lerp_px(r0[a], r0[b], wx), lerp_px(r1[a], r1[b], wx), wy);
        }
        convert_pixels(out.conv + (size_t)dy * out.ow + ox0, (const guint8 *)row, ox1 - ox0);
    }
    if (out.fb_on) {
        fb_read_var();
        fb_write_rect(out.vinfo.yoffset, ox0, oy0, ox1 - ox0, oy1 - oy0);
    }
}

'''
    + old_blit_start)

sub("    if (!out.fb_on)\n        return;\n\n    /* convert the damaged rows into the framebuffer format once, then copy them to the visible page */\n",
    "    if (out.scale != 1.0) {\n        if (out.conv)\n            out_scale_rect(rx, ry, rw, rh);\n        return;\n    }\n"
    "    if (!out.fb_on)\n        return;\n\n    /* convert the damaged rows into the framebuffer format once, then copy them to the visible page */\n")

# ---- 4. options
sub("    const char *page = NULL, *dump = NULL;\n", "    const char *page = NULL, *dump = NULL, *dump_out = NULL;\n    gboolean fullscreen = FALSE;\n    out.scale = 1.0;\n")
sub('        else if (!strcmp(argv[i], "--dump") && i + 1 < argc) dump = argv[++i];\n',
    '        else if (!strcmp(argv[i], "--dump") && i + 1 < argc) dump = argv[++i];\n'
    '        else if (!strcmp(argv[i], "--dump-out") && i + 1 < argc) dump_out = argv[++i];\n'
    '        else if (!strcmp(argv[i], "--scale") && i + 1 < argc) out.scale = atof(argv[++i]);\n'
    '        else if (!strcmp(argv[i], "--fullscreen")) fullscreen = TRUE;\n')

# ---- 5. setup in main
sub('''    out.w = W;
    out.h = H;
    out.canvas = g_malloc0((size_t)W * H * 4);
''', '''    out.w = W;
    out.h = H;
    out.canvas = g_malloc0((size_t)W * H * 4);
    if (!want_fb && fullscreen)
        fprintf(stderr, "--fullscreen needs --fb: ignored\\n");
    if (!want_fb) {
        /* no framebuffer: the layout of the pixels an output dump is written in */
        out.vinfo.red.offset = 16; out.vinfo.green.offset = 8; out.vinfo.blue.offset = 0; out.vinfo.transp.offset = 24;
        out.vinfo.bits_per_pixel = 32;
    }
''')
sub('''        out.fb_x = px >= 0 ? px : ((int)out.vinfo.xres - W) / 2;
        out.fb_y = py >= 0 ? py : ((int)out.vinfo.yres - H) / 2;
        fb_save_area();
        out.conv = g_malloc0((size_t)W * H * 4);
''', '''        if (fullscreen) /* the whole screen, in the view's aspect ratio */
            out.scale = MIN((double)out.vinfo.xres / W, (double)out.vinfo.yres / H);
        out.ow = (int)(W * out.scale + 0.5);
        out.oh = (int)(H * out.scale + 0.5);
        out.fb_x = px >= 0 ? px : ((int)out.vinfo.xres - out.ow) / 2;
        out.fb_y = py >= 0 ? py : ((int)out.vinfo.yres - out.oh) / 2;
        fb_save_area();
        out.conv = g_malloc0((size_t)out.ow * out.oh * 4);
''')
sub('''        fprintf(stderr, "fb: frame goes to (%d,%d)\\n", out.fb_x, out.fb_y);
    }
''', '''        fprintf(stderr, "fb: frame goes to (%d,%d), %dx%d (scale %.3f)\\n", out.fb_x, out.fb_y, out.ow, out.oh, out.scale);
    } else {
        out.ow = (int)(W * out.scale + 0.5);
        out.oh = (int)(H * out.scale + 0.5);
        if (out.scale != 1.0 && dump_out) /* only a scaled dump needs the converted output */
            out.conv = g_malloc0((size_t)out.ow * out.oh * 4);
    }
    if (out.scale != 1.0)
        scale_setup();
''')

# ---- 6. hardware video: the hole is scaled with the view
sub('''        snprintf(origin, sizeof origin, "%d,%d", out.fb_on ? out.fb_x : 0, out.fb_on ? out.fb_y : 0);''',
    '''        char scale_text[16];
        snprintf(scale_text, sizeof scale_text, "%.6f", out.scale);
        g_setenv("WPE_DREAM_VIDEO_SCALE", scale_text, TRUE); /* a <video> rectangle is in view pixels, the screen is `scale` times larger */
        snprintf(origin, sizeof origin, "%d,%d", out.fb_on ? out.fb_x : 0, out.fb_on ? out.fb_y : 0);''')

# ---- 7. output dump
sub('''    if (dump) {
        FILE *f = fopen(dump, "wb");''', '''    if (dump_out && out.conv) { /* the scaled output as it goes to the framebuffer (straight alpha, alpha ignored) */
        FILE *f = fopen(dump_out, "wb");
        if (f) {
            fprintf(f, "P6\\n%d %d\\n255\\n", out.ow, out.oh);
            for (long i = 0; i < (long)out.ow * out.oh; i++) {
                guint32 px = out.conv[i];
                fputc((px >> out.vinfo.red.offset) & 0xff, f); fputc((px >> out.vinfo.green.offset) & 0xff, f); fputc((px >> out.vinfo.blue.offset) & 0xff, f);
            }
            fclose(f);
            fprintf(stderr, "wrote %s (%dx%d)\\n", dump_out, out.ow, out.oh);
        }
    }
    if (dump) {
        FILE *f = fopen(dump, "wb");''')

# ---- 8. documentation
sub(" *     --dump file.ppm   write the shadow canvas (RGB, alpha ignored) when done\n",
    " *     --dump file.ppm   write the shadow canvas (RGB, alpha ignored) when done\n"
    " *     --scale F         show the view scaled by F (bilinear); --fullscreen (with --fb) scales it to fill the screen. HbbTV\n"
    " *                       applications are laid out at 1280x720 and shown scaled to the whole screen\n"
    " *     --dump-out f.ppm  with --scale: write the scaled output as it goes to the framebuffer\n")

# math.h for floor/ceil
sub("#include <linux/fb.h>\n", "#include <linux/fb.h>\n#include <math.h>\n")
open(p, "w").write(s)
print("ok")
