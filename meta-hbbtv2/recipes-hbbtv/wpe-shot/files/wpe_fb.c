/*
 * wpe_fb - WPE Platform API embedder that shows live web frames on a Linux framebuffer (HbbTV 2.0 experiment).
 *
 * It provides its own WPE platform (WPEDisplay / WPEToplevel / WPEView subclasses). The view's render_buffer()
 * receives every frame the web process produces, together with its damage rectangles; only those rectangles are
 * copied to a shadow canvas and, optionally, to the visible framebuffer page (the compositor's slow read-back
 * only ever produces the damaged regions, see the WebKit patches).
 *
 *   wpe_fb [options] <page.html | http(s)://url | file:///path>
 *     --size WxH        web view size (default 1280x720)
 *     --secs N          run time in seconds (default 10)
 *     --fb              draw to /dev/fb0's visible page (saves and restores the pixels it overwrites)
 *     --pos X,Y         where the frame goes on the framebuffer (default: centred)
 *     --unpremul        convert premultiplied alpha to straight alpha when writing to the framebuffer
 *                       (the default with --fb: the Dreambox display blends with straight alpha)
 *     --premul          with --fb, write the premultiplied pixels as delivered (for experiments)
 *     --opaque          ignore the frame's alpha (write 0xff)
 *     --dump file.ppm   write the shadow canvas (RGB, alpha ignored) when done
 *     --scale F         show the view scaled by F (bilinear); --fullscreen (with --fb) scales it to fill the screen. HbbTV
 *                       applications are laid out at 1280x720 and shown scaled to the whole screen
 *     --dump-out f.ppm  with --scale: write the scaled output as it goes to the framebuffer
 *     --hidpi F         device scale factor: the page is laid out at --size but rendered F times larger (sharp text; 1.5 gives
 *                       1920x1080 for a 1280x720 page, so --fullscreen then needs no scaling at all). Costs read-back time.
 *     --fine-damage     turn off WebKit's UnifyDamagedRegions feature (several damage rects per frame)
 *     --transparent     transparent page background
 *     --orb DIR         host the ORB HbbTV engine: DIR holds hbbtv.js (polyfill) and ext/libORBWebExt.so; ctl "app <url>" launches an app
 *     --hwvideo         <video> plays on the hardware video plane (dvbvideosink hole-punch, needs the WebKit Dreambox quirks)
 *     --hwvideo-lazy    like --hwvideo, but the live service keeps playing until media needs the decoder: the web process
 *                       asks for it over a socket (see "decoder handover"), ctl "decoder-free" answers
 *     --evt PATH        FIFO on which "acquire"/"release" events for the enigma2 plugin are written (with --hwvideo-lazy)
 *     --info            print the framebuffer parameters and exit
 */
#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <glib-unix.h>
#include <glib.h>
#include <linux/fb.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>

#include <wpe/webkit.h>

#include "orb_host.h"

/* ------------------------------------------------------------------------------------------------ output ---- */

typedef struct {
    int w, h; /* the web view */
    guint8 *canvas; /* BGRA, premultiplied, tightly packed, w x h */
    /* Output: the view scaled by `scale` (HbbTV applications are laid out at 1280x720 and shown scaled to the whole screen).
     * conv holds the output in framebuffer format (ow x oh) whenever there is a framebuffer or a scaled dump. */
    double scale;
    int ow, oh;
    int *xi0, *xi1, *yi0, *yi1; /* bilinear sampling: the two source columns/rows of every output column/row ... */
    guint16 *xwt, *ywt; /* ... and the weight (0..256) of the second one */

    gboolean fb_on, unpremul, opaque;
    int unpremul_from_y; /* -1 = off */
    int fb_fd;
    guint8 *fb_map;
    size_t fb_len;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    int fb_x, fb_y;
    guint8 *fb_saved;
    int fb_saved_yoffset;
    int sx, sy, sw, sh; /* clipped region saved */

    /* guard mode: the display owner (enigma2) redraws and flips pages under us, which wipes our overlay; keep a
     * converted copy of the frame in framebuffer format and repaint it whenever a flip or overwrite is seen */
    gboolean guard;
    guint32 *conv;
    int last_page;
    unsigned painted; /* bit mask of the pages we have painted */
    guint64 flips, repaints, overwrites;
    double max_repaint_ms;

    guint64 frames, pixels;
    double blit_ms;
    gint64 first_us, last_us;
} Out;

static Out out;
static GMainLoop *loop;
static WebKitWebView *view;

static void fb_read_var(void)
{
    if (ioctl(out.fb_fd, FBIOGET_VSCREENINFO, &out.vinfo) < 0)
        perror("FBIOGET_VSCREENINFO");
}

static void fb_print_info(void)
{
    fprintf(stderr, "fb: %ux%u virtual %ux%u, %u bpp, line_length %u, yoffset %u\n", out.vinfo.xres, out.vinfo.yres, out.vinfo.xres_virtual,
        out.vinfo.yres_virtual, out.vinfo.bits_per_pixel, out.finfo.line_length, out.vinfo.yoffset);
    fprintf(stderr, "fb: red %u/%u green %u/%u blue %u/%u alpha %u/%u (offset/length), smem_len %u\n", out.vinfo.red.offset, out.vinfo.red.length,
        out.vinfo.green.offset, out.vinfo.green.length, out.vinfo.blue.offset, out.vinfo.blue.length, out.vinfo.transp.offset,
        out.vinfo.transp.length, out.finfo.smem_len);
}

static gboolean fb_open(void)
{
    out.fb_fd = open("/dev/fb0", O_RDWR);
    if (out.fb_fd < 0) {
        perror("open /dev/fb0");
        return FALSE;
    }
    if (ioctl(out.fb_fd, FBIOGET_FSCREENINFO, &out.finfo) < 0) {
        perror("FBIOGET_FSCREENINFO");
        return FALSE;
    }
    fb_read_var();
    fb_print_info();
    if (out.vinfo.bits_per_pixel != 32) {
        fprintf(stderr, "fb: only 32 bpp is supported\n");
        return FALSE;
    }
    out.fb_len = out.finfo.smem_len;
    out.fb_map = mmap(NULL, out.fb_len, PROT_READ | PROT_WRITE, MAP_SHARED, out.fb_fd, 0);
    if (out.fb_map == MAP_FAILED) {
        perror("mmap fb0");
        out.fb_map = NULL;
        return FALSE;
    }
    return TRUE;
}

/* Convert n BGRA (premultiplied) pixels to the framebuffer's pixel layout. */
static void convert_pixels(guint32 *dst, const guint8 *src, int n)
{
    const struct fb_var_screeninfo *v = &out.vinfo;
    const gboolean native_bgra = v->red.offset == 16 && v->green.offset == 8 && v->blue.offset == 0 && v->transp.offset == 24;
    if (native_bgra && !out.unpremul && !out.opaque) {
        memcpy(dst, src, (size_t)n * 4);
        return;
    }
    /* The Dreambox display blends the OSD with STRAIGHT alpha (verified on screen), while WPE delivers
     * premultiplied pixels: colour = premultiplied * 255 / alpha, via a 16.16 reciprocal table. */
    static guint32 recip[256];
    if (!recip[1]) {
        for (int i = 1; i < 256; i++)
            recip[i] = (guint32)((255u * 65536u + i / 2) / i);
    }
    for (int i = 0; i < n; i++, src += 4) {
        unsigned b = src[0], g = src[1], r = src[2], a = src[3];
        if (out.unpremul && a && a < 255) {
            const guint32 k = recip[a];
            r = (r * k + 32768) >> 16; if (r > 255) r = 255;
            g = (g * k + 32768) >> 16; if (g > 255) g = 255;
            b = (b * k + 32768) >> 16; if (b > 255) b = 255;
        }
        if (out.opaque)
            a = 255;
        dst[i] = ((guint32)r << v->red.offset) | ((guint32)g << v->green.offset) | ((guint32)b << v->blue.offset) | ((guint32)a << v->transp.offset);
    }
}

static void fb_save_area(void)
{
    fb_read_var();
    out.fb_saved_yoffset = out.vinfo.yoffset;
    out.sx = MAX(0, out.fb_x);
    out.sy = MAX(0, out.fb_y);
    out.sw = MIN(out.fb_x + out.ow, (int)out.vinfo.xres) - out.sx;
    out.sh = MIN(out.fb_y + out.oh, (int)out.vinfo.yres) - out.sy;
    if (out.sw <= 0 || out.sh <= 0) {
        out.sw = out.sh = 0;
        return;
    }
    out.fb_saved = g_malloc((size_t)out.sw * out.sh * 4);
    for (int row = 0; row < out.sh; row++) {
        const guint8 *src = out.fb_map + (size_t)(out.fb_saved_yoffset + out.sy + row) * out.finfo.line_length + (size_t)out.sx * 4;
        memcpy(out.fb_saved + (size_t)row * out.sw * 4, src, (size_t)out.sw * 4);
    }
    fprintf(stderr, "fb: saved %dx%d pixels at (%d,%d) of page yoffset %d\n", out.sw, out.sh, out.sx, out.sy, out.fb_saved_yoffset);
}

/* Copy a rect of the converted frame (out.conv) to the framebuffer page starting at row `yoffset`. */
static void fb_write_rect(int yoffset, int rx, int ry, int rw, int rh)
{
    if (out.vinfo.yres)
        out.painted |= 1u << (yoffset / out.vinfo.yres);
    for (int row = 0; row < rh; row++) {
        int fy = out.fb_y + ry + row;
        int fx = out.fb_x + rx;
        int n = rw;
        if (fy < 0 || fy >= (int)out.vinfo.yres || fx >= (int)out.vinfo.xres)
            continue;
        if (fx < 0) { n += fx; fx = 0; }
        if (fx + n > (int)out.vinfo.xres)
            n = out.vinfo.xres - fx;
        if (n <= 0)
            continue;
        memcpy(out.fb_map + (size_t)(yoffset + fy) * out.finfo.line_length + (size_t)fx * 4, out.conv + (size_t)(ry + row) * out.ow + (fx - out.fb_x),
            (size_t)n * 4);
    }
}

/* How many of 96 sample points on the page starting at row `yoffset` differ from our frame. */
static int fb_mismatches(int yoffset)
{
    int bad = 0;
    for (int k = 0; k < 96; k++) {
        int x = (k * 211 + 17) % out.ow, y = (k * 97 + 5) % out.oh;
        int fx = out.fb_x + x, fy = out.fb_y + y;
        if (fx < 0 || fx >= (int)out.vinfo.xres || fy < 0 || fy >= (int)out.vinfo.yres)
            continue;
        const guint32 v = *(const guint32 *)(out.fb_map + (size_t)(yoffset + fy) * out.finfo.line_length + (size_t)fx * 4);
        if (v != out.conv[(size_t)y * out.ow + x])
            bad++;
    }
    return bad;
}

/* Repaint the whole frame on the currently visible page; returns the time it took in ms. */
static double fb_paint_all(void)
{
    gint64 t0 = g_get_monotonic_time();
    fb_read_var();
    fb_write_rect(out.vinfo.yoffset, 0, 0, out.ow, out.oh);
    return (g_get_monotonic_time() - t0) / 1000.0;
}

/* Guard: poll for page flips and overwrites by the display owner and repair the overlay. */
static gboolean guard_tick(gpointer data)
{
    if (!out.fb_on || !out.guard || !out.frames)
        return G_SOURCE_CONTINUE; /* nothing painted yet */
    fb_read_var();
    const int page = out.vinfo.yoffset / out.vinfo.yres;
    const gboolean flipped = page != out.last_page;
    if (flipped) {
        out.flips++;
        out.last_page = page;
    }
    if (flipped || fb_mismatches(out.vinfo.yoffset) > 2) {
        double ms = fb_paint_all();
        out.repaints++;
        if (!flipped)
            out.overwrites++;
        if (ms > out.max_repaint_ms)
            out.max_repaint_ms = ms;
    }
    return G_SOURCE_CONTINUE;
}

/* Hand the screen back: on every page we painted and that still holds our frame, put back the pixels that were
 * there before (same page) or clear our area to transparent (other pages, where the old pixels are stale). */
static void fb_restore_area(void)
{
    if (!out.fb_on)
        return;
    fb_read_var();
    const int pages = out.vinfo.yres_virtual / out.vinfo.yres;
    int restored = 0, cleared = 0;
    for (int p = 0; p < pages && p < 8; p++) {
        if (!(out.painted & (1u << p)))
            continue;
        const int yoff = p * out.vinfo.yres;
        if (fb_mismatches(yoff) > 8)
            continue; /* the display owner has already replaced our frame on this page */
        const gboolean same_page = out.fb_saved && yoff == out.fb_saved_yoffset;
        for (int row = 0; row < out.sh; row++) {
            guint8 *dst = out.fb_map + (size_t)(yoff + out.sy + row) * out.finfo.line_length + (size_t)out.sx * 4;
            if (same_page)
                memcpy(dst, out.fb_saved + (size_t)row * out.sw * 4, (size_t)out.sw * 4);
            else
                memset(dst, 0, (size_t)out.sw * 4);
        }
        same_page ? restored++ : cleared++;
    }
    fprintf(stderr, "fb: released the screen (%d page(s) restored to the original pixels, %d cleared to transparent)\n", restored, cleared);
    g_clear_pointer(&out.fb_saved, g_free);
}

/* Bilinear sampling tables for output size ow x oh from a view of w x h (pixel centres aligned). */
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

/* Copy one damaged rect of a frame to the shadow canvas and the framebuffer. */
static void out_blit_rect(const guint8 *src, int stride, int rx, int ry, int rw, int rh)
{
    if (rx < 0) { rw += rx; rx = 0; }
    if (ry < 0) { rh += ry; ry = 0; }
    if (rx + rw > out.w) rw = out.w - rx;
    if (ry + rh > out.h) rh = out.h - ry;
    if (rw <= 0 || rh <= 0)
        return;

    for (int row = 0; row < rh; row++)
        memcpy(out.canvas + ((size_t)(ry + row) * out.w + rx) * 4, src + (size_t)(ry + row) * stride + (size_t)rx * 4, (size_t)rw * 4);

    if (out.scale != 1.0) {
        if (out.conv)
            out_scale_rect(rx, ry, rw, rh);
        return;
    }
    if (!out.fb_on)
        return;

    /* convert the damaged rows into the framebuffer format once, then copy them to the visible page */
    for (int row = 0; row < rh; row++) {
        /* --unpremul-from-y: rows from that view row on are converted to straight alpha (side-by-side alpha test) */
        if (out.unpremul_from_y >= 0)
            out.unpremul = (ry + row) >= out.unpremul_from_y;
        convert_pixels(out.conv + (size_t)(ry + row) * out.w + rx, src + (size_t)(ry + row) * stride + (size_t)rx * 4, rw);
    }
    fb_read_var(); /* the visible page can change under us when the owner flips; the guard notices and repaints */
    fb_write_rect(out.vinfo.yoffset, rx, ry, rw, rh);
}

/* ------------------------------------------------------------------------- the custom WPE platform ---- */

static GType display_type, toplevel_type, view_type;
static gpointer toplevel_parent, view_parent;
static WPEBuffer *pending_buffer;
static guint pending_source;
static gint64 last_complete_us;

static gboolean complete_frame(gpointer data)
{
    WPEView *v = WPE_VIEW(data);
    pending_source = 0;
    if (pending_buffer) {
        WPEBuffer *b = pending_buffer;
        pending_buffer = NULL;
        wpe_view_buffer_rendered(v, b);
        wpe_view_buffer_released(v, b); /* the pixels were copied already */
        g_object_unref(b);
    }
    last_complete_us = g_get_monotonic_time();
    return G_SOURCE_REMOVE;
}

static gboolean view_render_buffer(WPEView *v, WPEBuffer *buffer, const WPERectangle *rects, guint n_rects, GError **error)
{
    gint64 t0 = g_get_monotonic_time();
    const guint8 *px = NULL;
    int stride = 0;
    GBytes *bytes = NULL;
    const int w = wpe_buffer_get_width(buffer), h = wpe_buffer_get_height(buffer);

    if (WPE_IS_BUFFER_SHM(buffer)) {
        WPEBufferSHM *shm = WPE_BUFFER_SHM(buffer);
        bytes = g_bytes_ref(wpe_buffer_shm_get_data(shm));
        stride = wpe_buffer_shm_get_stride(shm);
    } else {
        bytes = wpe_buffer_import_to_pixels(buffer, error);
        stride = w * 4;
    }
    if (!bytes)
        return FALSE;
    px = g_bytes_get_data(bytes, NULL);

    gint64 pixels = 0;
    if (n_rects == 0) {
        out_blit_rect(px, stride, 0, 0, w, h);
        pixels = (gint64)w * h;
    } else {
        for (guint i = 0; i < n_rects; i++) {
            out_blit_rect(px, stride, rects[i].x, rects[i].y, rects[i].width, rects[i].height);
            pixels += (gint64)rects[i].width * rects[i].height;
        }
    }
    g_bytes_unref(bytes);

    gint64 t1 = g_get_monotonic_time();
    out.frames++;
    out.pixels += pixels;
    out.blit_ms += (t1 - t0) / 1000.0;
    if (!out.first_us)
        out.first_us = t1;
    out.last_us = t1;

    /* pace the frame loop at ~60 Hz like a vsync'd display */
    if (pending_buffer)
        g_object_unref(pending_buffer);
    pending_buffer = g_object_ref(buffer);
    if (!pending_source) {
        gint64 next = last_complete_us + G_USEC_PER_SEC / 60;
        guint delay_ms = next > t1 ? (guint)((next - t1) / 1000) : 0;
        pending_source = g_timeout_add(delay_ms, complete_frame, v);
    }
    return TRUE;
}

static void view_notify_toplevel(GObject *o, GParamSpec *pspec, gpointer data)
{
    WPEView *v = WPE_VIEW(o);
    WPEToplevel *top = wpe_view_get_toplevel(v);
    if (!top) {
        wpe_view_unmap(v);
        return;
    }
    int w, h;
    wpe_toplevel_get_size(top, &w, &h);
    if (w && h)
        wpe_view_resized(v, w, h);
    wpe_view_map(v);
}

static void view_constructed(GObject *o)
{
    G_OBJECT_CLASS(view_parent)->constructed(o);
    g_signal_connect(o, "notify::toplevel", G_CALLBACK(view_notify_toplevel), NULL);
}

static void view_class_init(gpointer klass, gpointer data)
{
    view_parent = g_type_class_peek_parent(klass);
    G_OBJECT_CLASS(klass)->constructed = view_constructed;
    WPE_VIEW_CLASS(klass)->render_buffer = view_render_buffer;
}

static void toplevel_constructed(GObject *o)
{
    G_OBJECT_CLASS(toplevel_parent)->constructed(o);
    wpe_toplevel_state_changed(WPE_TOPLEVEL(o), WPE_TOPLEVEL_STATE_ACTIVE);
}

static gboolean toplevel_foreach_view_cb(WPEToplevel *t, WPEView *v, gpointer data)
{
    int w, h;
    wpe_toplevel_get_size(t, &w, &h);
    wpe_view_resized(v, w, h);
    return FALSE;
}

static gboolean toplevel_resize(WPEToplevel *t, int w, int h)
{
    wpe_toplevel_resized(t, w, h);
    wpe_toplevel_foreach_view(t, toplevel_foreach_view_cb, NULL);
    return TRUE;
}

static gboolean toplevel_set_fullscreen(WPEToplevel *t, gboolean fs)
{
    WPEToplevelState s = wpe_toplevel_get_state(t);
    s = fs ? (WPEToplevelState)(s | WPE_TOPLEVEL_STATE_FULLSCREEN) : (WPEToplevelState)(s & ~WPE_TOPLEVEL_STATE_FULLSCREEN);
    wpe_toplevel_state_changed(t, s);
    return TRUE;
}

static void toplevel_class_init(gpointer klass, gpointer data)
{
    toplevel_parent = g_type_class_peek_parent(klass);
    G_OBJECT_CLASS(klass)->constructed = toplevel_constructed;
    WPE_TOPLEVEL_CLASS(klass)->resize = toplevel_resize;
    WPE_TOPLEVEL_CLASS(klass)->set_fullscreen = toplevel_set_fullscreen;
}

static gboolean display_connect(WPEDisplay *d, GError **error)
{
    return TRUE;
}

static WPEView *display_create_view(WPEDisplay *d)
{
    return WPE_VIEW(g_object_new(view_type, "display", d, NULL));
}

static WPEToplevel *display_create_toplevel(WPEDisplay *d, guint max_views)
{
    return WPE_TOPLEVEL(g_object_new(toplevel_type, "display", d, NULL));
}

static gpointer display_get_egl_display(WPEDisplay *d, GError **error)
{
    g_set_error_literal(error, WPE_EGL_ERROR, WPE_EGL_ERROR_NOT_AVAILABLE, "wpe_fb has no EGL display (frames come as shared memory)");
    return NULL;
}

static void display_class_init(gpointer klass, gpointer data)
{
    WPEDisplayClass *dc = WPE_DISPLAY_CLASS(klass);
    dc->connect = display_connect;
    dc->create_view = display_create_view;
    dc->create_toplevel = display_create_toplevel;
    dc->get_egl_display = display_get_egl_display;
}

static GType register_subclass(GType parent, const char *name, GClassInitFunc class_init)
{
    GTypeQuery q;
    g_type_query(parent, &q); /* the base instance structs are opaque: size the subclass from what GLib reports */
    return g_type_register_static_simple(parent, name, q.class_size, class_init, q.instance_size, NULL, 0);
}

/* ------------------------------------------------------------------------------- hardware video plane ---- */

/* With --hwvideo the web process moves the hardware video plane (/proc/stb/vmpeg/0/dst_*) to wherever a <video> sits.
 * enigma2 only rewrites those values when its own video widget changes, so whatever we leave behind stays: remember the
 * rectangle at start and put it back on exit. */
static const char *const plane_names[4] = { "left", "top", "width", "height" };
static char plane_saved[4][16];
static gboolean plane_have_saved;

static gboolean plane_read(char values[4][16])
{
    for (int i = 0; i < 4; i++) {
        char path[64];
        snprintf(path, sizeof path, "/proc/stb/vmpeg/0/dst_%s", plane_names[i]);
        FILE *f = fopen(path, "r");
        if (!f || !fgets(values[i], 16, f)) {
            if (f)
                fclose(f);
            return FALSE;
        }
        fclose(f);
        g_strstrip(values[i]);
    }
    return TRUE;
}

/* NOT USED: blanking the plane from here left the video output dark after enigma2 played the service again (the picture only
 * came back after another stop/play cycle of the service), so the frozen last frame of the live service is left alone: it is
 * replaced by the first video frame, and it is only visible where the page is transparent. What it was for: enigma2 leaves the last decoded frame on the video plane when it stops the live service (stopService() only closes the
 * decoder); wherever the page is transparent that stale picture would show. Blank the plane the way eTSMPEGDecoder::
 * blankPrimaryVideoDecoder() does: VIDEO_STOP with mode 1 on the (free) video device. */
#ifndef VIDEO_STOP
#define VIDEO_STOP _IO('o', 21)
#endif
static void plane_blank(void) __attribute__((unused));
static void plane_blank(void)
{
    if (getenv("WPE_FB_NO_BLANK")) { /* protocol tests: the decoder may still belong to the live service */
        fprintf(stderr, "hwvideo: blanking skipped (WPE_FB_NO_BLANK)\n");
        return;
    }
    int fd = open("/dev/dvb/adapter0/video0", O_RDWR | O_NONBLOCK);
    if (fd < 0) {
        fprintf(stderr, "hwvideo: cannot open the video decoder to blank it: %s\n", g_strerror(errno));
        return;
    }
    fprintf(stderr, "hwvideo: blanking the video plane (VIDEO_STOP %s)\n", ioctl(fd, VIDEO_STOP, 1) < 0 ? g_strerror(errno) : "ok");
    close(fd);
}

static void plane_save(void)
{
    plane_have_saved = plane_read(plane_saved);
    if (plane_have_saved)
        fprintf(stderr, "hwvideo: video plane at start: %s,%s %sx%s\n", plane_saved[0], plane_saved[1], plane_saved[2], plane_saved[3]);
}

static void plane_restore(void)
{
    char now[4][16];
    if (!plane_have_saved || !plane_read(now))
        return;
    gboolean same = TRUE;
    for (int i = 0; i < 4; i++)
        same = same && !strcmp(now[i], plane_saved[i]);
    if (same)
        return;
    for (int i = 0; i < 4; i++) {
        char path[64];
        snprintf(path, sizeof path, "/proc/stb/vmpeg/0/dst_%s", plane_names[i]);
        FILE *f = fopen(path, "w");
        if (f) {
            fprintf(f, "%s\n", plane_saved[i]);
            fclose(f);
        }
    }
    FILE *f = fopen("/proc/stb/vmpeg/0/dst_apply", "w");
    if (f) {
        fputs("1\n", f);
        fclose(f);
    }
    fprintf(stderr, "hwvideo: video plane restored to %s,%s %sx%s\n", plane_saved[0], plane_saved[1], plane_saved[2], plane_saved[3]);
}

/* ------------------------------------------------------------------------------------------- main ---- */

static void on_load_changed(WebKitWebView *v, WebKitLoadEvent ev, gpointer data)
{
    static const char *names[] = { "STARTED", "REDIRECTED", "COMMITTED", "FINISHED" };
    fprintf(stderr, "load-changed: %s\n", (unsigned)ev < 4 ? names[ev] : "?");
}

static void on_title_changed(GObject *obj, GParamSpec *pspec, gpointer data)
{
    const char *t = webkit_web_view_get_title(WEBKIT_WEB_VIEW(obj));
    if (t && (strncmp(t, "fps=", 4) == 0 || strncmp(t, "key=", 4) == 0 || strncmp(t, "vid=", 4) == 0))
        fprintf(stderr, "page reports %s\n", t);
}

/* ------------------------------------------------------------------------------- control channel ---- */

/* Remote-control key names (as sent by the enigma2 plugin) -> X keysym + evdev keycode. */
static const struct {
    const char *name;
    guint keyval, evdev;
    int hbbtv; /* JS/HbbTV key code (ETSI TS 102 796 table 11), used in --orb mode */
} key_table[] = {
    { "up", WPE_KEY_Up, 103, 38 }, { "down", WPE_KEY_Down, 108, 40 }, { "left", WPE_KEY_Left, 105, 37 }, { "right", WPE_KEY_Right, 106, 39 },
    { "ok", WPE_KEY_Return, 28, 13 }, { "back", WPE_KEY_BackSpace, 14, 461 }, { "exit", WPE_KEY_Escape, 1, 27 }, { "menu", WPE_KEY_Menu, 139, 0 },
    { "red", WPE_KEY_F1, 59, 403 }, { "green", WPE_KEY_F2, 60, 404 }, { "yellow", WPE_KEY_F3, 61, 405 }, { "blue", WPE_KEY_F4, 62, 406 },
    { "play", WPE_KEY_AudioPlay, 207, 415 }, { "pause", WPE_KEY_AudioPause, 201, 19 }, { "stop", WPE_KEY_AudioStop, 166, 413 },
    { "ff", WPE_KEY_AudioForward, 208, 417 }, { "rew", WPE_KEY_AudioRewind, 168, 412 }, { "rec", WPE_KEY_AudioRecord, 167, 416 },
    { "0", WPE_KEY_0, 11, 48 }, { "1", WPE_KEY_0 + 1, 2, 49 }, { "2", WPE_KEY_0 + 2, 3, 50 }, { "3", WPE_KEY_0 + 3, 4, 51 }, { "4", WPE_KEY_0 + 4, 5, 52 },
    { "5", WPE_KEY_0 + 5, 6, 53 }, { "6", WPE_KEY_0 + 6, 7, 54 }, { "7", WPE_KEY_0 + 7, 8, 55 }, { "8", WPE_KEY_0 + 8, 9, 56 }, { "9", WPE_KEY_0 + 9, 10, 57 },
};

static char *orb_socket; /* per process (/tmp/orb_bridge.<pid>.sock): two instances must never share a bridge */

static gboolean orb_mode;
static const char *orb_dir;

static gboolean send_key(const char *name, gboolean down, gboolean up)
{
    WPEView *wv = webkit_web_view_get_wpe_view(view);
    for (guint i = 0; i < G_N_ELEMENTS(key_table); i++) {
        if (strcmp(key_table[i].name, name))
            continue;
        if (orb_mode) {
            /* the engine decides (key set of the running app) and dispatches the DOM event itself */
            if (!key_table[i].hbbtv)
                return FALSE;
            int consumed = 0;
            if (down)
                consumed |= orb_host_key(key_table[i].hbbtv, 1);
            if (up)
                consumed |= orb_host_key(key_table[i].hbbtv, 0);
            fprintf(stderr, "orb key %s (%d): %s\n", name, key_table[i].hbbtv, consumed ? "consumed by the application" : "not in the application's key set");
            return TRUE;
        }
        for (int phase = 0; phase < 2; phase++) {
            if ((phase == 0 && !down) || (phase == 1 && !up))
                continue;
            WPEEvent *ev = wpe_event_keyboard_new(phase == 0 ? WPE_EVENT_KEYBOARD_KEY_DOWN : WPE_EVENT_KEYBOARD_KEY_UP, wv, WPE_INPUT_SOURCE_KEYBOARD,
                (guint32)(g_get_monotonic_time() / 1000), (WPEModifiers)0, key_table[i].evdev + 8, key_table[i].keyval);
            wpe_view_event(wv, ev);
            wpe_event_unref(ev);
        }
        return TRUE;
    }
    return FALSE;
}

/* ------------------------------------------------------------------------------------ decoder handover ---- */

/* With --hwvideo-lazy the live service keeps playing (an HbbTV application runs on top of the live picture) until media really
 * needs the video/audio decoder. The web process (the Dreambox quirks in WebKit) asks for it over a UNIX socket before it creates
 * a dvb sink and keeps the connection open as a lease while any sink exists:
 *
 *   web process --"acquire <pid>"--> wpe_fb --"acquire" line on the event FIFO--> enigma2 plugin (stops the live service)
 *   plugin --"decoder-free" on the control FIFO--> wpe_fb (blanks the plane) --"ok"--> web process (creates the sinks)
 *   ... last sink destroyed, lease closed --> wpe_fb --"release" on the event FIFO--> plugin (plays the service again)
 *
 * If the plugin does not answer within 9 seconds the request is denied and the web process falls back to software sinks. */
typedef struct {
    int fd;
    guint source;
    gboolean requested, granted;
    char buf[64];
    size_t len;
} Lease;

static gboolean hw_lazy;
static char *handover_path, *evt_path;
static int handover_fd = -1, evt_fd = -1;
static GList *leases;
static gboolean decoder_ours, decoder_requested;
static guint decoder_timeout;

static void evt_send(const char *line)
{
    fprintf(stderr, "handover: event %s", line);
    if (evt_fd >= 0 && write(evt_fd, line, strlen(line)) < 0) {
        /* nobody reads the FIFO (the buffer is full): nothing to do about it */
    }
}

static void lease_reply(Lease *l, const char *text)
{
    if (write(l->fd, text, strlen(text)) < 0) {
        /* the client is gone: its end of the connection is noticed by the read watch */
    }
}

static void decoder_check_release(void)
{
    if (!decoder_ours)
        return;
    for (GList *i = leases; i; i = i->next) {
        if (((Lease *)i->data)->granted)
            return;
    }
    decoder_ours = FALSE;
    evt_send("release\n");
}

/* The client went away or is denied. (If called from its own watch callback, l->source has been zeroed first.) */
static void lease_drop(Lease *l)
{
    leases = g_list_remove(leases, l);
    if (l->source)
        g_source_remove(l->source);
    close(l->fd);
    g_free(l);
    decoder_check_release();
}

static gboolean decoder_timed_out(gpointer data)
{
    decoder_timeout = 0;
    if (!decoder_requested)
        return G_SOURCE_REMOVE;
    fprintf(stderr, "handover: the plugin did not free the decoder in time: denied\n");
    decoder_requested = FALSE;
    GList *copy = g_list_copy(leases);
    for (GList *i = copy; i; i = i->next) {
        Lease *l = i->data;
        if (!l->granted) {
            lease_reply(l, "no\n");
            lease_drop(l);
        }
    }
    g_list_free(copy);
    evt_send("release\n"); /* the plugin may have stopped the service by now */
    return G_SOURCE_REMOVE;
}

/* ctl "decoder-free": enigma2 has stopped the live service and let go of the decoder */
static void handover_decoder_free(void)
{
    if (!decoder_requested) {
        fprintf(stderr, "handover: decoder-free without a request: ignored\n");
        return;
    }
    decoder_requested = FALSE;
    if (decoder_timeout) {
        g_source_remove(decoder_timeout);
        decoder_timeout = 0;
    }
    decoder_ours = TRUE;
    for (GList *i = leases; i; i = i->next) {
        Lease *l = i->data;
        if (l->requested && !l->granted) {
            l->granted = TRUE;
            lease_reply(l, "ok\n");
        }
    }
    fprintf(stderr, "handover: decoder granted\n");
}

static gboolean lease_readable(gint fd, GIOCondition cond, gpointer data)
{
    Lease *l = data;
    ssize_t n = read(fd, l->buf + l->len, sizeof l->buf - l->len - 1);
    if (n == 0 || (n < 0 && errno != EAGAIN && errno != EINTR)) {
        fprintf(stderr, "handover: lease closed%s\n", l->granted ? "" : " (it was not granted)");
        l->source = 0;
        lease_drop(l);
        return G_SOURCE_REMOVE;
    }
    if (n > 0) {
        l->len += (size_t)n;
        l->buf[l->len] = 0;
    }
    if (!l->requested && strstr(l->buf, "acquire")) {
        l->requested = TRUE;
        fprintf(stderr, "handover: web process asks for the decoder: %s", l->buf);
        if (decoder_ours) {
            l->granted = TRUE;
            lease_reply(l, "ok\n");
        } else if (!decoder_requested) {
            decoder_requested = TRUE;
            evt_send("acquire\n");
            decoder_timeout = g_timeout_add_seconds(9, decoder_timed_out, NULL);
        }
    }
    return G_SOURCE_CONTINUE;
}

static gboolean handover_accept(gint fd, GIOCondition cond, gpointer data)
{
    int client = accept4(fd, NULL, NULL, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (client < 0)
        return G_SOURCE_CONTINUE;
    Lease *l = g_new0(Lease, 1);
    l->fd = client;
    l->source = g_unix_fd_add(client, G_IO_IN | G_IO_HUP | G_IO_ERR, lease_readable, l);
    leases = g_list_prepend(leases, l);
    return G_SOURCE_CONTINUE;
}

static void handover_start(const char *evt)
{
    handover_path = g_strdup_printf("/tmp/wpe_dream.%d.sock", (int)getpid());
    unlink(handover_path);
    handover_fd = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    struct sockaddr_un address = { .sun_family = AF_UNIX };
    g_strlcpy(address.sun_path, handover_path, sizeof address.sun_path);
    if (handover_fd < 0 || bind(handover_fd, (struct sockaddr *)&address, sizeof address) < 0 || listen(handover_fd, 4) < 0) {
        perror("decoder handover socket");
        return;
    }
    chmod(handover_path, 0600);
    g_unix_fd_add(handover_fd, G_IO_IN, handover_accept, NULL);
    g_setenv("WPE_DREAM_HANDOVER", handover_path, TRUE); /* the web process reads it: set before it is spawned */
    if (evt) {
        evt_path = g_strdup(evt);
        unlink(evt_path);
        if (mkfifo(evt_path, 0600) < 0)
            perror("mkfifo (event channel)");
        else
            evt_fd = open(evt_path, O_RDWR | O_NONBLOCK); /* O_RDWR: writing never blocks or fails for lack of a reader */
    }
    fprintf(stderr, "handover: waiting for decoder requests on %s, events on %s\n", handover_path, evt ? evt : "(no event channel)");
}

static void handover_stop(void)
{
    if (decoder_ours)
        evt_send("release\n");
    for (GList *i = leases; i; i = i->next) {
        Lease *l = i->data;
        close(l->fd);
    }
    g_list_free_full(leases, g_free);
    leases = NULL;
    if (handover_path) {
        unlink(handover_path);
    }
    if (evt_path)
        unlink(evt_path);
}

/* ---------------------------------------------------------------------------------------- ORB host ---- */

/* The engine calls these from its own threads; everything touching the view is hopped onto the main loop. */
static gboolean idle_eval_js(gpointer script)
{
    webkit_web_view_evaluate_javascript(view, script, -1, NULL, NULL, NULL, NULL, NULL);
    return G_SOURCE_REMOVE;
}

static gboolean idle_load_url(gpointer url)
{
    fprintf(stderr, "orb: loading application page %s\n", (char *)url);
    webkit_web_view_load_uri(view, url);
    return G_SOURCE_REMOVE;
}

static gboolean idle_quit(gpointer data)
{
    g_main_loop_quit(loop);
    return G_SOURCE_REMOVE;
}

static void orb_cb_eval_js(const char *script, void *user)
{
    g_main_context_invoke_full(NULL, G_PRIORITY_HIGH_IDLE, idle_eval_js, g_strdup(script), g_free);
}

static void orb_cb_load_url(const char *url, void *user)
{
    g_main_context_invoke_full(NULL, G_PRIORITY_HIGH_IDLE, idle_load_url, g_strdup(url), g_free);
}

static void orb_cb_set_visible(int visible, void *user)
{
    fprintf(stderr, "orb: application %s\n", visible ? "shown" : "hidden");
}

static void orb_cb_exit_pressed(void *user)
{
    fprintf(stderr, "orb: EXIT pressed -> leaving\n");
    g_main_context_invoke(NULL, idle_quit, NULL);
}

/* orb://player: the page the polyfill's media element extension puts in an iframe to play audio/video (see ORB's
 * ORBWPEWebExtensionHelper::HandleORBURISchemeRequest). It is playerpage.html with the token of the page and two scripts
 * (iframe.js: the player logic that talks to the polyfill in the parent through postMessage, dash.all.min.js) inlined. */
static char *orb_read_asset(const char *name)
{
    char *path = g_build_filename(orb_dir, name, NULL), *contents = NULL;
    if (!g_file_get_contents(path, &contents, NULL, NULL))
        fprintf(stderr, "orb: cannot read %s\n", path);
    g_free(path);
    return contents ? contents : g_strdup("");
}

static void on_orb_scheme_request(WebKitURISchemeRequest *request, gpointer data)
{
    const char *uri = webkit_uri_scheme_request_get_uri(request);
    if (!g_str_has_prefix(uri, "orb://player")) {
        GError *err = g_error_new(g_quark_from_string("orb"), 404, "unknown orb URI %s", uri);
        webkit_uri_scheme_request_finish_error(request, err);
        g_error_free(err);
        return;
    }
    static char *page, *iframe_js, *dash_js;
    if (!page) {
        page = orb_read_asset("playerpage.html");
        iframe_js = orb_read_asset("iframe.js");
        dash_js = orb_read_asset("dash.all.min.js");
    }
    char *token = orb_host_create_token(uri);
    const char *head_end = strstr(page, "</head>");
    gsize head_len = head_end ? (gsize)(head_end - page) : strlen(page);
    GString *html = g_string_new(NULL);
    g_string_append_len(html, page, head_len);
    g_string_append_printf(html, "\n<script type=\"text/javascript\">\ndocument.token = %s;\n</script>\n", token && *token ? token : "{}");
    g_string_append_printf(html, "<script type=\"text/javascript\">\n%s\n</script>\n<script type=\"text/javascript\">\n%s\n</script>\n", iframe_js, dash_js);
    g_string_append(html, head_end ? head_end : "");
    free(token);
    gsize len = html->len;
    GInputStream *stream = g_memory_input_stream_new_from_data(g_string_free(html, FALSE), len, g_free);
    webkit_uri_scheme_request_finish(request, stream, len, "text/html");
    g_object_unref(stream);
    fprintf(stderr, "orb: served %s (%lu bytes)\n", uri, (unsigned long)len);
}

static gpointer orb_launch_thread(gpointer url)
{
    orb_host_launch(url);
    g_free(url);
    return NULL;
}

static void on_load_failed(WebKitWebView *v, WebKitLoadEvent ev, const char *uri, GError *err, gpointer data)
{
    fprintf(stderr, "load-failed: %s: %s\n", uri, err ? err->message : "?");
    if (orb_mode)
        orb_host_load_failed(uri, err ? err->message : "");
}

static char *ctl_path;
static int ctl_fd = -1, ctl_dummy_fd = -1;
static char ctl_buf[512];
static size_t ctl_len;

static void ctl_handle_line(char *line)
{
    g_strstrip(line);
    if (!*line)
        return;
    if (!strncmp(line, "key ", 4)) {
        fprintf(stderr, "ctl: %s -> %s\n", line, send_key(line + 4, TRUE, TRUE) ? "sent" : "unknown key");
    } else if (!strncmp(line, "keydown ", 8)) {
        send_key(line + 8, TRUE, FALSE);
    } else if (!strncmp(line, "keyup ", 6)) {
        send_key(line + 6, FALSE, TRUE);
    } else if (!strncmp(line, "load ", 5)) {
        fprintf(stderr, "ctl: load %s\n", line + 5);
        webkit_web_view_load_uri(view, line + 5);
    } else if (!strncmp(line, "app ", 4)) {
        fprintf(stderr, "ctl: launch application %s\n", line + 4);
        if (orb_mode)
            g_thread_unref(g_thread_new("orb-launch", orb_launch_thread, g_strdup(line + 4))); /* the engine fetches the URL: no blocking the loop */
        else
            fprintf(stderr, "ctl: app needs --orb\n");
    } else if (!strcmp(line, "decoder-free")) {
        handover_decoder_free();
    } else if (!strcmp(line, "quit")) {
        fprintf(stderr, "ctl: quit\n");
        g_main_loop_quit(loop);
    } else
        fprintf(stderr, "ctl: unknown command '%s'\n", line);
}

static gboolean ctl_readable(GIOChannel *source, GIOCondition cond, gpointer data)
{
    ssize_t n = read(ctl_fd, ctl_buf + ctl_len, sizeof ctl_buf - ctl_len - 1);
    if (n <= 0)
        return G_SOURCE_CONTINUE;
    ctl_len += (size_t)n;
    ctl_buf[ctl_len] = 0;
    char *start = ctl_buf, *nl;
    while ((nl = strchr(start, '\n'))) {
        *nl = 0;
        ctl_handle_line(start);
        start = nl + 1;
    }
    ctl_len = strlen(start);
    memmove(ctl_buf, start, ctl_len + 1);
    if (ctl_len >= sizeof ctl_buf - 1)
        ctl_len = 0; /* runaway line: drop it */
    return G_SOURCE_CONTINUE;
}

static void ctl_open(const char *path)
{
    ctl_path = g_strdup(path);
    unlink(path);
    if (mkfifo(path, 0600) < 0) {
        perror("mkfifo");
        return;
    }
    ctl_fd = open(path, O_RDONLY | O_NONBLOCK);
    ctl_dummy_fd = open(path, O_WRONLY | O_NONBLOCK); /* keeps the FIFO open so reads don't hit EOF between writers */
    GIOChannel *ch = g_io_channel_unix_new(ctl_fd);
    g_io_add_watch(ch, G_IO_IN, ctl_readable, NULL);
    fprintf(stderr, "control channel ready: %s\n", path);
}

static gboolean on_web_process_terminated(WebKitWebView *v, WebKitWebProcessTerminationReason r, gpointer data)
{
    fprintf(stderr, "WEB PROCESS TERMINATED (reason %d)\n", (int)r);
    g_main_loop_quit(loop);
    return TRUE;
}

static gboolean on_quit(gpointer data)
{
    g_main_loop_quit(loop);
    return G_SOURCE_REMOVE;
}

static void set_fine_damage(WebKitSettings *settings)
{
    WebKitFeatureList *all = webkit_settings_get_all_features();
    gboolean found = FALSE;
    for (gsize i = 0; i < webkit_feature_list_get_length(all); i++) {
        WebKitFeature *f = webkit_feature_list_get(all, i);
        if (!g_strcmp0(webkit_feature_get_identifier(f), "UnifyDamagedRegions")) {
            webkit_settings_set_feature_enabled(settings, f, FALSE);
            found = TRUE;
        }
    }
    webkit_feature_list_unref(all);
    fprintf(stderr, "fine-grained damage: %s\n", found ? "UnifyDamagedRegions turned off" : "feature not found");
}

int main(int argc, char **argv)
{
    int W = 1280, H = 720, secs = 10;
    const char *page = NULL, *dump = NULL, *dump_out = NULL;
    gboolean fullscreen = FALSE;
    double hidpi = 0;
    out.scale = 1.0;
    gboolean want_fb = FALSE, fine = FALSE, transparent = FALSE, info = FALSE, hwvideo = FALSE;
    int px = -1, py = -1;
    int probe_x[8], probe_y[8], nprobes = 0;
    gboolean force_premul = FALSE, no_guard = FALSE;
    const char *ctl = NULL, *evt_arg = NULL;
    out.unpremul_from_y = -1; /* off unless --unpremul-from-y is given */

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--size") && i + 1 < argc) sscanf(argv[++i], "%dx%d", &W, &H);
        else if (!strcmp(argv[i], "--secs") && i + 1 < argc) secs = atoi(argv[++i]);
        else if (!strcmp(argv[i], "--fb")) want_fb = TRUE;
        else if (!strcmp(argv[i], "--pos") && i + 1 < argc) sscanf(argv[++i], "%d,%d", &px, &py);
        else if (!strcmp(argv[i], "--unpremul")) out.unpremul = TRUE;
        else if (!strcmp(argv[i], "--premul")) force_premul = TRUE;
        else if (!strcmp(argv[i], "--no-guard")) no_guard = TRUE;
        else if (!strcmp(argv[i], "--ctl") && i + 1 < argc) ctl = argv[++i];
        else if (!strcmp(argv[i], "--opaque")) out.opaque = TRUE;
        else if (!strcmp(argv[i], "--unpremul-from-y") && i + 1 < argc) out.unpremul_from_y = atoi(argv[++i]);
        else if (!strcmp(argv[i], "--dump") && i + 1 < argc) dump = argv[++i];
        else if (!strcmp(argv[i], "--dump-out") && i + 1 < argc) dump_out = argv[++i];
        else if (!strcmp(argv[i], "--scale") && i + 1 < argc) out.scale = atof(argv[++i]);
        else if (!strcmp(argv[i], "--fullscreen")) fullscreen = TRUE;
        else if (!strcmp(argv[i], "--hidpi") && i + 1 < argc) hidpi = atof(argv[++i]);
        else if (!strcmp(argv[i], "--fine-damage")) fine = TRUE;
        else if (!strcmp(argv[i], "--transparent")) transparent = TRUE;
        else if (!strcmp(argv[i], "--probe") && i + 1 < argc && nprobes < 8) { sscanf(argv[++i], "%d,%d", &probe_x[nprobes], &probe_y[nprobes]); nprobes++; }
        else if (!strcmp(argv[i], "--info")) info = TRUE;
        else if (!strcmp(argv[i], "--orb") && i + 1 < argc) { orb_dir = argv[++i]; orb_mode = TRUE; }
        else if (!strcmp(argv[i], "--hwvideo")) hwvideo = TRUE;
        else if (!strcmp(argv[i], "--hwvideo-lazy")) { hwvideo = TRUE; hw_lazy = TRUE; }
        else if (!strcmp(argv[i], "--evt") && i + 1 < argc) evt_arg = argv[++i];
        else if (argv[i][0] != '-') page = argv[i];
        else { fprintf(stderr, "unknown option %s\n", argv[i]); return 2; }
    }

    if (info) {
        if (!fb_open())
            return 1;
        return 0;
    }
    if (!page && !orb_mode) {
        fprintf(stderr, "usage: wpe_fb [--fb] [--secs N] [--size WxH] [--pos X,Y] [--fine-damage] [--transparent] [--dump f.ppm] <page>\n");
        return 2;
    }

    out.w = W;
    out.h = H;
    if (hidpi > 1.0) {
        out.w = (int)(W * hidpi + 0.5); /* buffers of a view with scale F are F times the logical size */
        out.h = (int)(H * hidpi + 0.5);
    }
    out.canvas = g_malloc0((size_t)out.w * out.h * 4);
    if (!want_fb && fullscreen)
        fprintf(stderr, "--fullscreen needs --fb: ignored\n");
    if (!want_fb) {
        /* no framebuffer: the layout of the pixels an output dump is written in */
        out.vinfo.red.offset = 16; out.vinfo.green.offset = 8; out.vinfo.blue.offset = 0; out.vinfo.transp.offset = 24;
        out.vinfo.bits_per_pixel = 32;
    }

    if (want_fb) {
        /* straight alpha is what this display expects (verified on a DM900): convert unless told otherwise */
        if (!force_premul)
            out.unpremul = TRUE;
        if (!fb_open())
            return 1;
        if (fullscreen) /* the whole screen, in the view's aspect ratio */
            out.scale = MIN((double)out.vinfo.xres / out.w, (double)out.vinfo.yres / out.h);
        out.ow = (int)(out.w * out.scale + 0.5);
        out.oh = (int)(out.h * out.scale + 0.5);
        out.fb_x = px >= 0 ? px : ((int)out.vinfo.xres - out.ow) / 2;
        out.fb_y = py >= 0 ? py : ((int)out.vinfo.yres - out.oh) / 2;
        fb_save_area();
        out.conv = g_malloc0((size_t)out.ow * out.oh * 4);
        out.guard = !no_guard;
        out.last_page = out.vinfo.yoffset / out.vinfo.yres;
        out.fb_on = TRUE;
        fprintf(stderr, "fb: frame goes to (%d,%d), %dx%d (scale %.3f)\n", out.fb_x, out.fb_y, out.ow, out.oh, out.scale);
    } else {
        out.ow = (int)(out.w * out.scale + 0.5);
        out.oh = (int)(out.h * out.scale + 0.5);
        if (out.scale != 1.0 && dump_out) /* only a scaled dump needs the converted output */
            out.conv = g_malloc0((size_t)out.ow * out.oh * 4);
    }
    if (out.scale != 1.0)
        scale_setup();

    if (hwvideo) {
        plane_save();
        /* Media plays through the Dreambox GStreamer quirks (dvbvideosink/dvbaudiosink); the page is punched transparent
         * where a <video> sits and the web process positions the hardware video plane from the element's rectangle. It
         * has to know where this view is on the screen. Set before any web process is spawned. */
        char origin[32], screen[32];
        char scale_text[16];
        snprintf(scale_text, sizeof scale_text, "%.6f", out.scale);
        g_setenv("WPE_DREAM_VIDEO_SCALE", scale_text, TRUE); /* a <video> rectangle is in view pixels, the screen is `scale` times larger */
        snprintf(origin, sizeof origin, "%d,%d", out.fb_on ? out.fb_x : 0, out.fb_on ? out.fb_y : 0);
        snprintf(screen, sizeof screen, "%dx%d", out.fb_on ? (int)out.vinfo.xres : 1920, out.fb_on ? (int)out.vinfo.yres : 1080);
        g_setenv("WEBKIT_GST_QUIRKS", "dreambox", TRUE);
        g_setenv("WEBKIT_GST_HOLE_PUNCH_QUIRK", "dreambox", TRUE);
        g_setenv("WPE_DREAM_VIDEO_ORIGIN", origin, TRUE);
        g_setenv("WPE_DREAM_VIDEO_SCREEN", screen, TRUE);
        fprintf(stderr, "hwvideo: video plane origin %s on a %s screen\n", origin, screen);
        if (hw_lazy)
            handover_start(evt_arg);
    }

    display_type = register_subclass(WPE_TYPE_DISPLAY, "WPEDisplayFb", display_class_init);
    toplevel_type = register_subclass(WPE_TYPE_TOPLEVEL, "WPEToplevelFb", toplevel_class_init);
    view_type = register_subclass(WPE_TYPE_VIEW, "WPEViewFb", view_class_init);

    /* WebKit picks its display with wpe_display_get_default(), which instantiates the highest-priority
     * implementation registered on the "wpe-platform-display" extension point (the built-in headless one has -100). */
    GError *error = NULL;
    GIOExtensionPoint *ext_point = g_io_extension_point_register(WPE_DISPLAY_EXTENSION_POINT_NAME);
    g_io_extension_point_set_required_type(ext_point, WPE_TYPE_DISPLAY);
    g_io_extension_point_implement(WPE_DISPLAY_EXTENSION_POINT_NAME, display_type, "fb", 1000);
    WPEDisplay *display = wpe_display_get_default();
    if (!display) {
        fprintf(stderr, "no WPE display available\n");
        return 3;
    }
    wpe_display_set_primary(display);

    WebKitNetworkSession *session = webkit_network_session_new_ephemeral();
    /* A TV has no pointer and no "user gesture": HbbTV applications start audio/video by themselves, with sound. WebKit's
     * default autoplay policy is ALLOW_WITHOUT_SOUND, which rejects play() of any clip that has an audio track
     * (NotAllowedError). (The media-playback-requires-user-gesture setting is off by default and is not what blocks it.) */
    WebKitWebsitePolicies *policies = webkit_website_policies_new_with_policies("autoplay", WEBKIT_AUTOPLAY_ALLOW, NULL);
    if (orb_mode) {
        /* web process extension (bridge to the engine) + the ORB polyfill as a document-start user script */
        char *ext_dir = g_build_filename(orb_dir, "ext", NULL);
        WebKitWebContext *wctx = webkit_web_context_get_default();
        webkit_web_context_set_web_process_extensions_directory(wctx, ext_dir);
        g_free(ext_dir);
        webkit_security_manager_register_uri_scheme_as_cors_enabled(webkit_web_context_get_security_manager(wctx), "orb");
        webkit_web_context_register_uri_scheme(wctx, "orb", on_orb_scheme_request, NULL, NULL);

        orb_socket = g_strdup_printf("/tmp/orb_bridge.%d.sock", (int)getpid());
        webkit_web_context_set_web_process_extensions_initialization_user_data(wctx, g_variant_new_string(orb_socket));

        WebKitUserContentManager *ucm = webkit_user_content_manager_new();
        {
            /* optional: DIR/debug.js forwards the page's console, errors and media events to this process's log; it goes
             * first so that it also sees what the polyfill and the application do at load time */
            char *debug_path = g_build_filename(orb_dir, "debug.js", NULL), *debug_source = NULL;
            if (g_file_get_contents(debug_path, &debug_source, NULL, NULL)) {
                /* all frames: the polyfill's player runs in an orb://player iframe (frames without wpeBridge skip it) */
                WebKitUserScript *debug_script = webkit_user_script_new(debug_source, WEBKIT_USER_CONTENT_INJECT_ALL_FRAMES, WEBKIT_USER_SCRIPT_INJECT_AT_DOCUMENT_START, NULL, NULL);
                webkit_user_content_manager_add_script(ucm, debug_script);
                webkit_user_script_unref(debug_script);
                g_free(debug_source);
            }
            g_free(debug_path);
        }
        char *js_path = g_build_filename(orb_dir, "hbbtv.js", NULL), *source = NULL;
        if (!g_file_get_contents(js_path, &source, NULL, &error)) {
            fprintf(stderr, "cannot read the polyfill %s: %s\n", js_path, error->message);
            return 1;
        }
        WebKitUserScript *script = webkit_user_script_new(source, WEBKIT_USER_CONTENT_INJECT_TOP_FRAME, WEBKIT_USER_SCRIPT_INJECT_AT_DOCUMENT_START, NULL, NULL);
        webkit_user_content_manager_add_script(ucm, script);
        webkit_user_script_unref(script);
        g_free(source);
        g_free(js_path);
        view = g_object_new(WEBKIT_TYPE_WEB_VIEW, "network-session", session, "user-content-manager", ucm, "website-policies", policies, NULL);
    } else
        view = g_object_new(WEBKIT_TYPE_WEB_VIEW, "network-session", session, "website-policies", policies, NULL);
    g_signal_connect(view, "load-failed", G_CALLBACK(on_load_failed), NULL);
    if (fine) { /* replaces the view's settings object: everything else has to be applied to the result, after this */
        WebKitSettings *settings = webkit_settings_new();
        set_fine_damage(settings);
        webkit_web_view_set_settings(view, settings);
        g_object_unref(settings);
    }
    {
        /* A TV has no pointer and no "user gesture": HbbTV applications start audio/video by themselves (with sound), which
         * WebKit's default autoplay policy would refuse (play() rejected with NotAllowedError). */
        WebKitSettings *media_settings = webkit_web_view_get_settings(view);
        webkit_settings_set_media_playback_requires_user_gesture(media_settings, FALSE);
        webkit_settings_set_media_playback_allows_inline(media_settings, TRUE);
        if (orb_mode)
            webkit_settings_set_enable_write_console_messages_to_stdout(media_settings, TRUE);
    }
    if (transparent) {
        WebKitColor color = { 0, 0, 0, 0 };
        webkit_web_view_set_background_color(view, &color);
    }
    g_signal_connect(view, "load-changed", G_CALLBACK(on_load_changed), NULL);
    g_signal_connect(view, "notify::title", G_CALLBACK(on_title_changed), NULL);
    g_signal_connect(view, "web-process-terminated", G_CALLBACK(on_web_process_terminated), NULL);

    WPEView *wv = webkit_web_view_get_wpe_view(view);
    {
        WPEDisplay *used = webkit_web_view_get_display(view);
        fprintf(stderr, "platform in use: display %s (ours: %s, primary: %s), view %s\n", used ? G_OBJECT_TYPE_NAME(used) : "(none)",
            G_OBJECT_TYPE_NAME(display), wpe_display_get_primary() ? G_OBJECT_TYPE_NAME(wpe_display_get_primary()) : "(none)",
            wv ? G_OBJECT_TYPE_NAME(wv) : "(none)");
    }
    WPEToplevel *top = wv ? wpe_view_get_toplevel(wv) : NULL;
    if (top)
        wpe_toplevel_resize(top, W, H);
    if (top && hidpi > 1.0) {
        wpe_toplevel_scale_changed(top, hidpi);
        fprintf(stderr, "hidpi: view %dx%d at scale %.2f renders %dx%d\n", W, H, hidpi, out.w, out.h);
    }
    if (wv) {
        wpe_view_set_visible(wv, TRUE);
        wpe_view_map(wv);
        wpe_view_focus_in(wv); /* the page must have focus to receive key events */
    }

    loop = g_main_loop_new(NULL, FALSE);
    g_unix_signal_add(SIGINT, on_quit, NULL);
    g_unix_signal_add(SIGTERM, on_quit, NULL);
    if (secs > 0)
        g_timeout_add_seconds(secs, on_quit, NULL);
    if (ctl)
        ctl_open(ctl);
    if (out.fb_on && out.guard)
        g_timeout_add(10, guard_tick, NULL);

    if (orb_mode) {
        OrbHostCallbacks cb = { orb_cb_eval_js, orb_cb_load_url, orb_cb_set_visible, orb_cb_exit_pressed, NULL };
        int rc = orb_host_start(orb_socket, &cb);
        if (rc) {
            fprintf(stderr, "orb_host_start failed (%d)\n", rc);
            fb_restore_area();
            return 4;
        }
        {
            /* HbbTV servers sniff the user agent for the "HbbTV/x.y.z (...)" token the engine provides */
            WebKitSettings *settings = webkit_web_view_get_settings(view);
            char *ua = g_strdup_printf("%s %s", webkit_settings_get_user_agent(settings), orb_host_user_agent());
            webkit_settings_set_user_agent(settings, ua);
            fprintf(stderr, "orb: user agent: %s\n", ua);
            g_free(ua);
        }
        if (page) /* a start application given on the command line */
            g_thread_unref(g_thread_new("orb-launch", orb_launch_thread, g_strdup(page)));
        else
            webkit_web_view_load_html(view, "<html><body></body></html>", "about:blank");
    } else if (g_str_has_prefix(page, "http://") || g_str_has_prefix(page, "https://") || g_str_has_prefix(page, "file://"))
        webkit_web_view_load_uri(view, page);
    else {
        char *html = NULL;
        if (!g_file_get_contents(page, &html, NULL, &error)) {
            fprintf(stderr, "cannot read %s: %s\n", page, error->message);
            fb_restore_area();
            return 1;
        }
        webkit_web_view_load_html(view, html, "about:blank");
        g_free(html);
    }

    g_main_loop_run(loop);

    if (out.fb_on) {
        /* Verify the blit: read the framebuffer region back and compare it with the shadow canvas. */
        fb_read_var();
        const int page = out.vinfo.yoffset;
        long differ = 0, compared = 0, first_x = -1, first_y = -1;
        for (int row = 0; row < out.h; row++) {
            int fy = out.fb_y + row;
            if (fy < 0 || fy >= (int)out.vinfo.yres)
                continue;
            for (int col = 0; col < out.w; col++) {
                int fx = out.fb_x + col;
                if (fx < 0 || fx >= (int)out.vinfo.xres)
                    continue;
                const guint32 fbpx = *(const guint32 *)(out.fb_map + (size_t)(page + fy) * out.finfo.line_length + (size_t)fx * 4);
                const guint32 cvpx = out.conv[(size_t)row * out.w + col];
                compared++;
                if (fbpx != cvpx) {
                    if (!differ) { first_x = col; first_y = row; }
                    differ++;
                }
            }
        }
        fprintf(stderr, "== fb check: visible page yoffset %d (was %d); %ld of %ld pixels differ from the shadow canvas%s\n", page,
            out.fb_saved_yoffset, differ, compared, differ ? "" : "  -> the frame is on the framebuffer");
        if (differ)
            fprintf(stderr, "   first difference at frame pixel (%ld,%ld)\n", first_x, first_y);
    }

    if (out.fb_on)
        fprintf(stderr, "== guard: %s; %llu page flips seen, %llu repaints (%llu without a flip = overwritten in place), slowest repaint %.1f ms\n",
            out.guard ? "on" : "off", (unsigned long long)out.flips, (unsigned long long)out.repaints, (unsigned long long)out.overwrites, out.max_repaint_ms);

    if (orb_mode)
        orb_host_stop();
    if (hw_lazy)
        handover_stop();
    plane_restore();
    fb_restore_area();
    if (ctl_path)
        unlink(ctl_path);

    double secs_run = out.frames > 1 ? (out.last_us - out.first_us) / 1e6 : 0;
    fprintf(stderr, "== sink: %llu frames delivered, %.1f fps, %.0f px/frame average (%.1f%% of the view), %.2f ms per frame copy\n",
        (unsigned long long)out.frames, secs_run > 0 ? (out.frames - 1) / secs_run : 0.0, out.frames ? (double)out.pixels / out.frames : 0.0,
        out.frames ? 100.0 * out.pixels / out.frames / ((double)out.w * out.h) : 0.0, out.frames ? out.blit_ms / out.frames : 0.0);

    {
        /* alpha statistics of the final canvas (premultiplied BGRA as delivered by WPE) */
        long a0 = 0, amid = 0, a255 = 0;
        for (long i = 0; i < (long)out.w * out.h; i++) {
            guint8 a = out.canvas[i * 4 + 3];
            if (a == 0) a0++; else if (a == 255) a255++; else amid++;
        }
        fprintf(stderr, "== alpha: %ld px fully transparent (%.1f%%), %ld partial (%.1f%%), %ld opaque (%.1f%%)\n", a0, 100.0 * a0 / ((double)W * H), amid,
            100.0 * amid / ((double)W * H), a255, 100.0 * a255 / ((double)W * H));
        for (int i = 0; i < nprobes; i++) {
            const guint8 *p = out.canvas + ((size_t)probe_y[i] * W + probe_x[i]) * 4;
            fprintf(stderr, "   probe (%d,%d): B=%u G=%u R=%u A=%u\n", probe_x[i], probe_y[i], p[0], p[1], p[2], p[3]);
        }
    }

    if (dump_out && out.conv) { /* the scaled output as it goes to the framebuffer (straight alpha, alpha ignored) */
        FILE *f = fopen(dump_out, "wb");
        if (f) {
            fprintf(f, "P6\n%d %d\n255\n", out.ow, out.oh);
            for (long i = 0; i < (long)out.ow * out.oh; i++) {
                guint32 px = out.conv[i];
                fputc((px >> out.vinfo.red.offset) & 0xff, f); fputc((px >> out.vinfo.green.offset) & 0xff, f); fputc((px >> out.vinfo.blue.offset) & 0xff, f);
            }
            fclose(f);
            fprintf(stderr, "wrote %s (%dx%d)\n", dump_out, out.ow, out.oh);
        }
    }
    if (dump) {
        FILE *f = fopen(dump, "wb");
        if (f) {
            fprintf(f, "P6\n%d %d\n255\n", out.w, out.h);
            for (int i = 0; i < out.w * out.h; i++) {
                const guint8 *p = out.canvas + (size_t)i * 4;
                fputc(p[2], f); fputc(p[1], f); fputc(p[0], f);
            }
            fclose(f);
            fprintf(stderr, "wrote %s\n", dump);
        }
    }
    return 0;
}
