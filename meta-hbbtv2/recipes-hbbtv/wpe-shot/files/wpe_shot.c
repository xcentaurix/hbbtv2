/*
 * wpe_shot - headless WPE WebKit smoke test for the HbbTV 2.0 experiment.
 *
 * Creates the WPE Platform API headless display, loads a small test page (or
 * an HTML file given as argv[1]) into a WebKitWebView, waits for the load to
 * finish and writes a snapshot as a binary PPM (argv[2], default
 * ./wpe_shot.ppm). It prints a text verdict so it can be judged over a plain
 * shell without viewing the image:
 *
 *   - which stage worked (display connect, EGL display, load, JS, snapshot)
 *   - the pixel bytes at the centre of three known colour boxes, to prove the
 *     web process really rendered and to show the channel order
 *
 * Exit code: 0 = rendered and colours as expected, non-zero = a stage failed.
 */
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wpe/webkit.h>
#include <wpe/headless/wpe-headless.h>

#define VIEW_W 1280
#define VIEW_H 720

static const char *k_test_html =
    "<!doctype html><meta charset=utf-8><title>loading</title>"
    "<body style='margin:0;background:#fff;font:32px sans-serif'>"
    "<div style='position:absolute;left:100px;top:100px;width:150px;height:150px;background:#f00'></div>"
    "<div style='position:absolute;left:300px;top:100px;width:150px;height:150px;background:#0f0'></div>"
    "<div style='position:absolute;left:500px;top:100px;width:150px;height:150px;background:#00f'></div>"
    "<div style='position:absolute;left:100px;top:300px;width:600px;height:100px;"
    "background:linear-gradient(90deg,#000,#fff)'></div>"
    "<div style='position:absolute;left:100px;top:450px'>HbbTV 2.0 WPE headless test</div>"
    "<script>document.title='js-ok';</script></body>";

static GMainLoop *loop;
static WebKitWebView *view;
static int rc = 1;
static gint64 t0;
static const char *out_path = "wpe_shot.ppm";

#define MS() ((long)((g_get_monotonic_time() - t0) / 1000))
#define LOG(...) do { fprintf(stderr, "[%6ldms] ", MS()); fprintf(stderr, __VA_ARGS__); fputc('\n', stderr); } while (0)

static void finish(int code)
{
    rc = code;
    g_main_loop_quit(loop);
}

/* Pixel bytes as stored: the snapshot is expected to be BGRA (Skia N32 on little endian). */
static int probe(const guint8 *px, int stride, int x, int y, const char *name, int er, int eg, int eb)
{
    const guint8 *p = px + (size_t)y * stride + (size_t)x * 4;
    int ok_bgra = p[2] == er && p[1] == eg && p[0] == eb;
    int ok_rgba = p[0] == er && p[1] == eg && p[2] == eb;
    LOG("probe %-5s at (%d,%d): bytes %02x %02x %02x %02x  -> %s", name, x, y, p[0], p[1], p[2], p[3],
        ok_bgra ? "BGRA order OK" : ok_rgba ? "RGBA order (R/B swapped vs expected BGRA)" : "UNEXPECTED colour");
    return ok_bgra ? 1 : ok_rgba ? 2 : 0;
}

static void on_snapshot(GObject *source, GAsyncResult *result, gpointer user_data)
{
    GError *error = NULL;
    WebKitImage *img = webkit_web_view_get_snapshot_finish(WEBKIT_WEB_VIEW(source), result, &error);
    if (!img) {
        LOG("SNAPSHOT FAILED: %s", error ? error->message : "(no error)");
        g_clear_error(&error);
        finish(6);
        return;
    }

    int w = webkit_image_get_width(img), h = webkit_image_get_height(img), stride = webkit_image_get_stride(img);
    GBytes *bytes = webkit_image_as_bytes(img);
    gsize len = 0;
    const guint8 *px = g_bytes_get_data(bytes, &len);
    LOG("snapshot ok: %dx%d stride %d, %zu bytes", w, h, stride, (size_t)len);
    if (!px || w < 400 || h < 300 || (gsize)stride * h > len) {
        LOG("SNAPSHOT TOO SMALL / SHORT");
        finish(7);
        return;
    }

    /* coarse colour census: quantise to 3 bits/channel, count buckets in use */
    static guint8 seen[512];
    long nonwhite = 0;
    for (int y = 0; y < h; y++) {
        const guint8 *row = px + (size_t)y * stride;
        for (int x = 0; x < w; x++) {
            const guint8 *p = row + x * 4;
            if (p[0] != 255 || p[1] != 255 || p[2] != 255)
                nonwhite++;
            seen[(p[2] >> 5) << 6 | (p[1] >> 5) << 3 | (p[0] >> 5)] = 1;
        }
    }
    int buckets = 0;
    for (int i = 0; i < 512; i++)
        buckets += seen[i];
    LOG("census: %ld non-white pixels of %ld, %d colour buckets in use", nonwhite, (long)w * h, buckets);

    int r = probe(px, stride, 175, 175, "red", 255, 0, 0);
    int g = probe(px, stride, 375, 175, "green", 0, 255, 0);
    int b = probe(px, stride, 575, 175, "blue", 0, 0, 255);

    FILE *f = fopen(out_path, "wb");
    if (f) {
        fprintf(f, "P6\n%d %d\n255\n", w, h);
        for (int y = 0; y < h; y++) {
            const guint8 *row = px + (size_t)y * stride;
            for (int x = 0; x < w; x++) {
                const guint8 *p = row + x * 4; /* BGRA -> RGB */
                fputc(p[2], f);
                fputc(p[1], f);
                fputc(p[0], f);
            }
        }
        fclose(f);
        LOG("wrote %s", out_path);
    } else
        LOG("could not write %s", out_path);

    if (r == 1 && g == 1 && b == 1 && nonwhite > 10000)
        LOG("RESULT: PASS - page rendered with correct colours");
    else if (r && g && b && nonwhite > 10000)
        LOG("RESULT: RENDERED but channel order differs (see probes)");
    else
        LOG("RESULT: FAIL - snapshot does not contain the expected page");
    finish((r == 1 && g == 1 && b == 1 && nonwhite > 10000) ? 0 : (r && g && b) ? 8 : 9);
}

static gboolean take_snapshot(gpointer data)
{
    LOG("title after load: '%s'", webkit_web_view_get_title(view) ? webkit_web_view_get_title(view) : "(null)");
    LOG("requesting snapshot");
    webkit_web_view_get_snapshot(view, WEBKIT_SNAPSHOT_REGION_VISIBLE, WEBKIT_SNAPSHOT_OPTIONS_NONE, NULL,
        on_snapshot, NULL);
    return G_SOURCE_REMOVE;
}

/* Benchmark support: WPE_SHOT_RUN_MS=<ms> keeps the page running that long before the snapshot, and every
 * document.title change is printed, so an animated test page can report its own frame rate via the title. */
static void on_title_changed(GObject *obj, GParamSpec *pspec, gpointer data)
{
    const char *t = webkit_web_view_get_title(WEBKIT_WEB_VIEW(obj));
    if (t && strncmp(t, "fps=", 4) == 0)
        LOG("page reports %s", t);
}

static void on_load_changed(WebKitWebView *v, WebKitLoadEvent ev, gpointer data)
{
    static const char *names[] = { "STARTED", "REDIRECTED", "COMMITTED", "FINISHED" };
    LOG("load-changed: %s", (unsigned)ev < 4 ? names[ev] : "?");
    if (ev == WEBKIT_LOAD_FINISHED) {
        const char *run = getenv("WPE_SHOT_RUN_MS");
        guint delay = run && atoi(run) > 0 ? (guint)atoi(run) : 700; /* default: let the first frame be produced */
        g_timeout_add(delay, take_snapshot, NULL);
    }
}

static gboolean on_load_failed(WebKitWebView *v, WebKitLoadEvent ev, const char *uri, GError *error, gpointer data)
{
    LOG("LOAD FAILED (%s): %s", uri, error ? error->message : "?");
    finish(3);
    return TRUE;
}

static gboolean on_crashed(WebKitWebView *v, WebKitWebProcessTerminationReason reason, gpointer data)
{
    LOG("WEB PROCESS TERMINATED, reason %d (0=crashed, 1=memory limit, 2=by API)", (int)reason);
    finish(4);
    return TRUE;
}

static gboolean on_timeout(gpointer data)
{
    LOG("TIMEOUT: nothing finished in time");
    finish(5);
    return G_SOURCE_REMOVE;
}

int main(int argc, char **argv)
{
    t0 = g_get_monotonic_time();
    GError *error = NULL;
    char *html_owned = NULL;
    const char *html = k_test_html;

    if (argc > 1 && strcmp(argv[1], "-") != 0) {
        if (!g_file_get_contents(argv[1], &html_owned, NULL, &error)) {
            fprintf(stderr, "cannot read %s: %s\n", argv[1], error->message);
            return 1;
        }
        html = html_owned;
    }
    if (argc > 2)
        out_path = argv[2];

    LOG("WPE WebKit %u.%u.%u", webkit_get_major_version(), webkit_get_minor_version(), webkit_get_micro_version());

    WPEDisplay *display = wpe_display_headless_new();
    if (!display) {
        LOG("wpe_display_headless_new() returned NULL");
        return 10;
    }
    if (!wpe_display_connect(display, &error)) {
        LOG("display connect FAILED: %s", error ? error->message : "?");
        return 11;
    }
    wpe_display_set_primary(display);
    LOG("headless display connected");

    /* Diagnostic for the crux of the experiment: can the vendor EGL be brought up from the UI process? */
    gpointer egl = wpe_display_get_egl_display(display, &error);
    if (egl)
        LOG("EGL display from WPE: %p (vendor EGL usable in UI process)", egl);
    else {
        LOG("no EGL display from WPE: %s (not fatal for a CPU-painted page)", error ? error->message : "?");
        g_clear_error(&error);
    }

    WebKitNetworkSession *session = webkit_network_session_new_ephemeral();
    view = g_object_new(WEBKIT_TYPE_WEB_VIEW, "network-session", session, NULL);
    /* WPE_SHOT_FINE_DAMAGE=1: turn off the "UnifyDamagedRegions" feature so the compositor reports several
     * damage rectangles instead of one bounding box (an embedder with an expensive frame transport wants that). */
    if (getenv("WPE_SHOT_FINE_DAMAGE")) {
        WebKitSettings *settings = webkit_settings_new();
        WebKitFeatureList *all = webkit_settings_get_all_features();
        gboolean found = FALSE;
        for (gsize i = 0; i < webkit_feature_list_get_length(all); i++) {
            WebKitFeature *feature = webkit_feature_list_get(all, i);
            if (!g_strcmp0(webkit_feature_get_identifier(feature), "UnifyDamagedRegions")) {
                webkit_settings_set_feature_enabled(settings, feature, FALSE);
                found = TRUE;
            }
        }
        webkit_feature_list_unref(all);
        webkit_web_view_set_settings(view, settings);
        g_object_unref(settings);
        LOG("fine-grained damage: %s", found ? "UnifyDamagedRegions turned off" : "feature UnifyDamagedRegions NOT FOUND");
    }
    g_signal_connect(view, "load-changed", G_CALLBACK(on_load_changed), NULL);
    g_signal_connect(view, "notify::title", G_CALLBACK(on_title_changed), NULL);
    g_signal_connect(view, "load-failed", G_CALLBACK(on_load_failed), NULL);
    g_signal_connect(view, "web-process-terminated", G_CALLBACK(on_crashed), NULL);

    WPEView *wv = webkit_web_view_get_wpe_view(view);
    if (wv) {
        WPEToplevel *top = wpe_view_get_toplevel(wv);
        if (top)
            wpe_toplevel_resize(top, VIEW_W, VIEW_H);
        wpe_view_set_visible(wv, TRUE);
        wpe_view_map(wv);
        LOG("view %dx%d mapped", wpe_view_get_width(wv), wpe_view_get_height(wv));
    } else
        LOG("webkit_web_view_get_wpe_view() returned NULL");

    loop = g_main_loop_new(NULL, FALSE);
    g_timeout_add_seconds(90, on_timeout, NULL);
    webkit_web_view_load_html(view, html, "about:blank");
    LOG("load_html issued");
    g_main_loop_run(loop);

    LOG("exit code %d", rc);
    g_free(html_owned);
    return rc;
}
