/*
 * dvb_probe - play a clip through GStreamer's playbin with the Dreambox dvb sinks and log what the pipeline and the sinks
 * report while it is seeked, paused and resumed. Ground truth for the WebKit "dreambox" quirks, without a browser.
 *
 *   dvb_probe <uri> [--e2-async] [--key-unit] [--seek-at S] [--seek-to S] [--pause-at S] [--resume-at S] [--secs N]
 *
 * Every 250 ms: pipeline state, position from a plain query on the pipeline, and "get-decoder-time" of the audio and the
 * video sink (the position enigma2's own player uses). It needs the video/audio decoder: stop the live service first.
 */
#include <gst/gst.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static GstElement *pb, *asink, *vsink;
static GMainLoop *loop;
static gint64 t0;

static double now(void)
{
    return (g_get_monotonic_time() - t0) / 1e6;
}

static const char *sec(gint64 ns, char *buf)
{
    if (!GST_CLOCK_TIME_IS_VALID((guint64)ns))
        return "    -";
    snprintf(buf, 16, "%5.2f", ns / 1e9);
    return buf;
}

static gboolean tick(gpointer d)
{
    gint64 q = -1, a = -1, v = -1;
    char b1[16], b2[16], b3[16];
    GstState st = GST_STATE_NULL, pending = GST_STATE_NULL;
    gst_element_get_state(pb, &st, &pending, 0);
    if (!gst_element_query_position(pb, GST_FORMAT_TIME, &q))
        q = -1;
    if (asink && g_signal_lookup("get-decoder-time", G_OBJECT_TYPE(asink)))
        g_signal_emit_by_name(asink, "get-decoder-time", &a);
    if (vsink && g_signal_lookup("get-decoder-time", G_OBJECT_TYPE(vsink)))
        g_signal_emit_by_name(vsink, "get-decoder-time", &v);
    printf("%6.2f  %-8s pending %-8s  query %s  audio-decoder %s  video-decoder %s\n", now(), gst_element_state_get_name(st),
        gst_element_state_get_name(pending), sec(q, b1), sec(a, b2), sec(v, b3));
    fflush(stdout);
    return G_SOURCE_CONTINUE;
}

static double seek_to = 1.0;
static GstSeekFlags seek_flags = (GstSeekFlags)(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE);

static gboolean do_seek(gpointer d)
{
    printf("%6.2f  ==== ACTION flushing seek to %.2f\n", now(), seek_to);
    gboolean ok = gst_element_seek_simple(pb, GST_FORMAT_TIME, seek_flags, (gint64)(seek_to * GST_SECOND));
    printf("%6.2f  seek returned %s\n", now(), ok ? "TRUE" : "FALSE");
    return G_SOURCE_REMOVE;
}

static gboolean do_pause(gpointer d)
{
    printf("%6.2f  ==== ACTION set PAUSED\n", now());
    GstStateChangeReturn r = gst_element_set_state(pb, GST_STATE_PAUSED);
    printf("%6.2f  -> %s\n", now(), gst_element_state_change_return_get_name(r));
    return G_SOURCE_REMOVE;
}

static gboolean do_resume(gpointer d)
{
    printf("%6.2f  ==== ACTION set PLAYING\n", now());
    GstStateChangeReturn r = gst_element_set_state(pb, GST_STATE_PLAYING);
    printf("%6.2f  -> %s\n", now(), gst_element_state_change_return_get_name(r));
    return G_SOURCE_REMOVE;
}

static gboolean do_quit(gpointer d)
{
    printf("%6.2f  ==== time is up\n", now());
    g_main_loop_quit(loop);
    return G_SOURCE_REMOVE;
}

static gboolean on_bus(GstBus *bus, GstMessage *m, gpointer d)
{
    switch (GST_MESSAGE_TYPE(m)) {
    case GST_MESSAGE_ERROR: {
        GError *e;
        gchar *dbg;
        gst_message_parse_error(m, &e, &dbg);
        printf("%6.2f  BUS error from %s: %s (%s)\n", now(), GST_OBJECT_NAME(m->src), e->message, dbg ? dbg : "");
        g_main_loop_quit(loop);
        break;
    }
    case GST_MESSAGE_WARNING: {
        GError *e;
        gchar *dbg;
        gst_message_parse_warning(m, &e, &dbg);
        printf("%6.2f  BUS warning from %s: %s\n", now(), GST_OBJECT_NAME(m->src), e->message);
        break;
    }
    case GST_MESSAGE_EOS:
        printf("%6.2f  BUS EOS\n", now());
        break;
    case GST_MESSAGE_ASYNC_DONE:
        printf("%6.2f  BUS async-done\n", now());
        break;
    case GST_MESSAGE_STATE_CHANGED:
        if (m->src == GST_OBJECT(pb)) {
            GstState o, n, p;
            gst_message_parse_state_changed(m, &o, &n, &p);
            printf("%6.2f  BUS pipeline %s -> %s (pending %s)\n", now(), gst_element_state_get_name(o), gst_element_state_get_name(n),
                gst_element_state_get_name(p));
        }
        break;
    default:
        break;
    }
    return TRUE;
}

int main(int argc, char **argv)
{
    gst_init(&argc, &argv);
    const char *uri = NULL;
    gboolean e2async = FALSE;
    double seek_at = 3, pause_at = 5, resume_at = 7, secs = 20;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--e2-async")) e2async = TRUE;
        else if (!strcmp(argv[i], "--key-unit")) seek_flags = (GstSeekFlags)(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT);
        else if (!strcmp(argv[i], "--seek-at") && i + 1 < argc) seek_at = atof(argv[++i]);
        else if (!strcmp(argv[i], "--seek-to") && i + 1 < argc) seek_to = atof(argv[++i]);
        else if (!strcmp(argv[i], "--pause-at") && i + 1 < argc) pause_at = atof(argv[++i]);
        else if (!strcmp(argv[i], "--resume-at") && i + 1 < argc) resume_at = atof(argv[++i]);
        else if (!strcmp(argv[i], "--secs") && i + 1 < argc) secs = atof(argv[++i]);
        else if (argv[i][0] != '-') uri = argv[i];
    }
    if (!uri) {
        fprintf(stderr, "usage: dvb_probe <uri> [--e2-async] [--key-unit] [--seek-at S] [--seek-to S] [--pause-at S] [--resume-at S] [--secs N]\n");
        return 2;
    }

    pb = gst_element_factory_make("playbin", "probe");
    vsink = gst_element_factory_make("dvbvideosink", "vsink");
    asink = gst_element_factory_make("dvbaudiosink", "asink");
    if (!pb || !vsink || !asink) {
        fprintf(stderr, "missing element (playbin %p, dvbvideosink %p, dvbaudiosink %p)\n", (void *)pb, (void *)vsink, (void *)asink);
        return 3;
    }
    if (e2async) {
        g_object_set(vsink, "e2-async", TRUE, NULL);
        g_object_set(asink, "e2-async", TRUE, NULL);
    }
    /* video | audio | native-video | native-audio */
    g_object_set(pb, "uri", uri, "video-sink", vsink, "audio-sink", asink, "flags", 0x1 | 0x2 | 0x20 | 0x40, NULL);
    printf("uri %s, e2-async %s; seek to %.1f at %.1f s, pause at %.1f, resume at %.1f\n", uri, e2async ? "ON" : "off", seek_to, seek_at, pause_at, resume_at);

    loop = g_main_loop_new(NULL, FALSE);
    gst_bus_add_watch(GST_ELEMENT_BUS(pb), on_bus, NULL);
    t0 = g_get_monotonic_time();
    g_timeout_add(250, tick, NULL);
    if (seek_at > 0) g_timeout_add((guint)(seek_at * 1000), do_seek, NULL);
    if (pause_at > 0) g_timeout_add((guint)(pause_at * 1000), do_pause, NULL);
    if (resume_at > 0) g_timeout_add((guint)(resume_at * 1000), do_resume, NULL);
    g_timeout_add((guint)(secs * 1000), do_quit, NULL);
    GstStateChangeReturn r = gst_element_set_state(pb, GST_STATE_PLAYING);
    printf("%6.2f  set PLAYING -> %s\n", now(), gst_element_state_change_return_get_name(r));
    g_main_loop_run(loop);
    gst_element_set_state(pb, GST_STATE_NULL);
    gst_object_unref(pb);
    return 0;
}
