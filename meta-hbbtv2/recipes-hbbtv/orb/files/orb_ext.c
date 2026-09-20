/*
 * orb_ext.c - WPE web process extension for the ORB HbbTV polyfill.
 *
 * Same job as ORB's RDK "ORBWPEWebExtension" (rdk/ORBBrowser/ORBWPEWebExtension), minus the Thunder/RDK client:
 *   - defines wpeBridge.request(json) -> json, a SYNCHRONOUS call the polyfill (natives/rdk.js) uses for every OIPF
 *     method, in every top frame;
 *   - defines document.token for the page (ORBEngine::CreateToken(uri)) before any page script runs;
 *   - tells the engine when the page URL changes (ApplicationManager::OnApplicationPageChanged).
 *
 * All three go to the ORB engine in the UI process over a UNIX stream socket (the path arrives as the extension's
 * initialization user data, a GVariant string). Frames: request  = u32 be length | u8 type | payload
 *                                                       response = u32 be length | payload
 * types: 'R' bridge request, 'T' create token for URI, 'P' page URI changed, 'L' log line (wpeBridge.log). Asynchronous engine -> page events do
 * not come through here: the UI process evaluates document.dispatchBridgeEvent(...) itself.
 *
 * The web process blocks in these calls; the UI process never waits for the web process while serving them, so
 * there is no deadlock.
 */
#include <wpe/webkit-web-process-extension.h>
#include <jsc/jsc.h>

#include <gmodule.h>

#include <arpa/inet.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

static char *bridge_path;
static int bridge_fd = -1;
static GMutex bridge_lock;

static gboolean io_all(int fd, void *buf, size_t len, gboolean writing)
{
    char *p = buf;
    while (len) {
        ssize_t n = writing ? send(fd, p, len, MSG_NOSIGNAL) : read(fd, p, len);
        if (n < 0 && errno == EINTR)
            continue;
        if (n <= 0)
            return FALSE;
        p += n;
        len -= (size_t)n;
    }
    return TRUE;
}

static gboolean bridge_connect(void)
{
    if (bridge_fd >= 0)
        return TRUE;
    if (!bridge_path)
        return FALSE;
    int fd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
    if (fd < 0)
        return FALSE;
    struct sockaddr_un sa = { .sun_family = AF_UNIX };
    g_strlcpy(sa.sun_path, bridge_path, sizeof sa.sun_path);
    if (connect(fd, (struct sockaddr *)&sa, sizeof sa) < 0) {
        g_printerr("orb_ext: cannot connect to %s: %s\n", bridge_path, strerror(errno));
        close(fd);
        return FALSE;
    }
    bridge_fd = fd;
    return TRUE;
}

/* One synchronous round trip. Returns a newly allocated string, or NULL if the engine is unreachable. */
static char *bridge_call(char type, const char *payload)
{
    char *reply = NULL;
    size_t plen = payload ? strlen(payload) : 0;

    g_mutex_lock(&bridge_lock);
    for (int attempt = 0; attempt < 2 && !reply; attempt++) {
        if (!bridge_connect())
            break;
        uint32_t len = htonl((uint32_t)(plen + 1));
        if (io_all(bridge_fd, &len, 4, TRUE) && io_all(bridge_fd, &type, 1, TRUE) && io_all(bridge_fd, (void *)payload, plen, TRUE)
            && io_all(bridge_fd, &len, 4, FALSE)) {
            uint32_t rlen = ntohl(len);
            if (rlen < (64u << 20)) {
                char *buf = g_malloc(rlen + 1);
                if (io_all(bridge_fd, buf, rlen, FALSE)) {
                    buf[rlen] = 0;
                    reply = buf;
                } else
                    g_free(buf);
            }
        }
        if (!reply) { /* broken connection: drop it and retry once on a fresh one */
            close(bridge_fd);
            bridge_fd = -1;
        }
    }
    g_mutex_unlock(&bridge_lock);
    return reply;
}

/* wpeBridge.request(string) -> string; the polyfill JSON.parses the answer. */
static char *js_bridge_request(const char *request)
{
    char *reply = bridge_call('R', request);
    return reply ? reply : g_strdup("{}");
}

/* wpeBridge.log(string): a line for the embedder's log (debug.js forwards console output and media events through it). */
static void js_bridge_log(const char *message)
{
    g_free(bridge_call('L', message));
}

static void expose_bridge(JSCContext *ctx)
{
    JSCValue *object = jsc_value_new_from_json(ctx, "{}");
    jsc_context_set_value(ctx, "wpeBridge", object);
    JSCValue *fn = jsc_value_new_function(ctx, "request", G_CALLBACK(js_bridge_request), NULL, NULL, G_TYPE_STRING, 1, G_TYPE_STRING);
    jsc_value_object_set_property(object, "request", fn);
    g_object_unref(fn);
    fn = jsc_value_new_function(ctx, "log", G_CALLBACK(js_bridge_log), NULL, NULL, G_TYPE_NONE, 1, G_TYPE_STRING);
    jsc_value_object_set_property(object, "log", fn);
    g_object_unref(fn);
    g_object_unref(object);
}

static void expose_token(JSCContext *ctx, const char *uri)
{
    char *token = bridge_call('T', uri);
    char *script = g_strdup_printf("document.token = %s;", token && *token ? token : "{}");
    JSCValue *result = jsc_context_evaluate(ctx, script, -1);
    g_clear_object(&result);
    g_free(script);
    g_free(token);
}

static void on_window_object_cleared(WebKitScriptWorld *world, WebKitWebPage *page, WebKitFrame *frame, gpointer data)
{
    const char *uri = webkit_frame_get_uri(frame);
    gboolean main_frame = webkit_frame_is_main_frame(frame);
    if (!uri)
        uri = "";

    /* the polyfill's video player page (orb://player) needs the bridge too, but no token of its own */
    gboolean player = g_str_has_prefix(uri, "orb://player");
    if (!main_frame && !player)
        return;

    JSCContext *ctx = webkit_frame_get_js_context_for_script_world(frame, world);
    expose_bridge(ctx);
    if (main_frame && !player)
        expose_token(ctx, uri);
    g_object_unref(ctx);
}

static void on_page_uri_changed(WebKitWebPage *page, GParamSpec *pspec, gpointer data)
{
    const char *uri = webkit_web_page_get_uri(page);
    char *reply = bridge_call('P', uri ? uri : "");
    g_free(reply);
}

static void on_page_created(WebKitWebProcessExtension *extension, WebKitWebPage *page, gpointer data)
{
    g_signal_connect(page, "notify::uri", G_CALLBACK(on_page_uri_changed), NULL);
}

G_MODULE_EXPORT void webkit_web_process_extension_initialize_with_user_data(WebKitWebProcessExtension *extension, const GVariant *user_data)
{
    if (user_data && g_variant_is_of_type((GVariant *)user_data, G_VARIANT_TYPE_STRING))
        bridge_path = g_strdup(g_variant_get_string((GVariant *)user_data, NULL));
    g_signal_connect(webkit_script_world_get_default(), "window-object-cleared", G_CALLBACK(on_window_object_cleared), NULL);
    g_signal_connect(extension, "page-created", G_CALLBACK(on_page_created), NULL);
}
