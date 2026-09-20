#!/bin/bash
set -euo pipefail
cd /home/alpha/wpe-src/wpewebkit-2.54.0
G=Source/WebCore/platform/gstreamer
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-browser/wpewebkit/files
# 0009 becomes part of the local baseline, so that the diff below is 0010 alone
git add -A && git -c user.name=hbbtv2 -c user.email=noreply@localhost commit -q -m "apply patch 0009" || true
python3 - <<'PY'
def edit(path, old, new, count=1):
    s = open(path).read()
    assert s.count(old) == count, (path, old[:70], s.count(old))
    open(path, "w").write(s.replace(old, new))

G = "Source/WebCore/platform/gstreamer/"

# ---- the lease: declared in the hole-punch quirk's header, used by both Dreambox quirks
edit(G + "GStreamerHolePunchQuirkDreambox.h",
     "class GStreamerHolePunchQuirkDreambox final : public GStreamerHolePunchQuirk {",
     '''// The video and audio decoder are shared with the live service that enigma2 plays, which must not be disturbed until media
// really needs them. If the embedder set WPE_DREAM_HANDOVER (the path of a UNIX socket) the web process asks it for the
// decoder before it creates a dvb sink ("acquire\\n", answered by "ok\\n" once the live service has been stopped) and keeps
// the connection open as a lease that ends when the last dvb sink is destroyed, whereupon the embedder gives the live service
// back. Without the variable nothing is negotiated (the embedder has taken care of the decoder). Returns false when the
// decoder was denied; the caller then falls back to the software sinks.
bool acquireDreamboxDecoder();
// Ties the lease to the sink: it is given up when the sink is destroyed.
GstElement* leaseDreamboxDecoder(GstElement* sink);

class GStreamerHolePunchQuirkDreambox final : public GStreamerHolePunchQuirk {''')

edit(G + "GStreamerHolePunchQuirkDreambox.cpp",
     "#include <algorithm>\n#include <cstdio>\n#include <cstdlib>\n",
     "#include <algorithm>\n#include <cstdio>\n#include <cstdlib>\n#include <poll.h>\n#include <sys/socket.h>\n#include <sys/un.h>\n#include <unistd.h>\n#include <wtf/Lock.h>\n#include <wtf/Locker.h>\n")

edit(G + "GStreamerHolePunchQuirkDreambox.cpp",
     "GstElement* GStreamerHolePunchQuirkDreambox::createHolePunchVideoSink(bool, const MediaPlayer*)\n{\n    return makeGStreamerElement(\"dvbvideosink\"_s, \"DreamboxVideoSink\"_s);\n}\n",
     '''static Lock decoderLeaseLock;
static int decoderLeaseFd WTF_GUARDED_BY_LOCK(decoderLeaseLock) = -1;
static unsigned decoderLeaseCount WTF_GUARDED_BY_LOCK(decoderLeaseLock) = 0;

bool acquireDreamboxDecoder()
{
    const char* path = getenv("WPE_DREAM_HANDOVER");
    if (!path || !*path)
        return true; // nothing to negotiate

    Locker locker { decoderLeaseLock };
    if (decoderLeaseFd >= 0) {
        decoderLeaseCount++;
        return true;
    }

    int fd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
    if (fd < 0)
        return false;
    struct sockaddr_un address = { };
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, path, sizeof(address.sun_path) - 1);
    char request[48];
    int requestLength = snprintf(request, sizeof(request), "acquire %d\\n", static_cast<int>(getpid()));
    if (connect(fd, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) < 0 || write(fd, request, requestLength) != requestLength) {
        close(fd);
        return false;
    }
    // The embedder has to get enigma2 to stop the live service first: give it time, but not forever.
    struct pollfd pfd = { fd, POLLIN, 0 };
    char reply[8] = { };
    if (poll(&pfd, 1, 10000) <= 0 || read(fd, reply, sizeof(reply) - 1) <= 0 || strncmp(reply, "ok", 2)) {
        GST_WARNING("Dreambox decoder was not granted by the embedder");
        close(fd);
        return false;
    }
    decoderLeaseFd = fd;
    decoderLeaseCount = 1;
    return true;
}

static void releaseDreamboxDecoder()
{
    Locker locker { decoderLeaseLock };
    if (!decoderLeaseCount || --decoderLeaseCount)
        return;
    close(decoderLeaseFd); // the embedder sees the end of the connection and gives the live service back
    decoderLeaseFd = -1;
}

GstElement* leaseDreamboxDecoder(GstElement* sink)
{
    if (!sink)
        return nullptr;
    if (getenv("WPE_DREAM_HANDOVER"))
        g_object_weak_ref(G_OBJECT(sink), [](gpointer, GObject*) { releaseDreamboxDecoder(); }, nullptr);
    return sink;
}

GstElement* GStreamerHolePunchQuirkDreambox::createHolePunchVideoSink(bool, const MediaPlayer*)
{
    if (!acquireDreamboxDecoder())
        return nullptr;
    GstElement* sink = makeGStreamerElement("dvbvideosink"_s, "DreamboxVideoSink"_s);
    if (!sink) {
        releaseDreamboxDecoder();
        return nullptr;
    }
    return leaseDreamboxDecoder(sink);
}
''')

# the audio sink is created first (when the player is constructed) and is what the decoder handover is about for audio
edit(G + "GStreamerQuirkDreambox.cpp",
     "GstElement* GStreamerQuirkDreambox::createAudioSink()\n{\n    return makeGStreamerElement(\"dvbaudiosink\"_s);\n}\n",
     "GstElement* GStreamerQuirkDreambox::createAudioSink()\n{\n"
     "    // denied (or missing) decoder: nullptr lets playbin pick its own sink, i.e. software audio\n"
     "    if (!acquireDreamboxDecoder())\n        return nullptr;\n"
     "    GstElement* sink = makeGStreamerElement(\"dvbaudiosink\"_s);\n"
     "    if (!sink)\n        return nullptr;\n"
     "    return leaseDreamboxDecoder(sink);\n}\n")
edit(G + "GStreamerQuirkDreambox.cpp",
     '#include "GStreamerCommon.h"\n',
     '#include "GStreamerCommon.h"\n#include "GStreamerHolePunchQuirkDreambox.h"\n')
PY
git diff --stat | tail -5
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] GStreamer: Dreambox quirks negotiate the decoder with the embedder"
  echo
  echo "enigma2 holds the video and audio decoder for the live service, and the dvb sinks open them when they are created. If the"
  echo "embedder sets WPE_DREAM_HANDOVER (a UNIX socket path), ask it for the decoder before a dvb sink is created and hold the"
  echo "connection open as a lease that ends when the last sink is destroyed, so that the live service keeps playing until media"
  echo "really needs the decoder (HbbTV applications run on top of the live picture) and comes back afterwards."
  echo
  echo "---"
  git diff --no-color -- $G
} > $LAYER/0010-GStreamer-Dreambox-negotiate-the-decoder-with-the-embedder.patch
grep -c '^+' $LAYER/0010-GStreamer-Dreambox-negotiate-the-decoder-with-the-embedder.patch
