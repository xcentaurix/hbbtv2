/*
 * orb_host.cpp - hosts ORBEngine inside the browser embedder and serves the web process extension's socket.
 * See orb_host.h for the interface and orb_ext.c for the wire format.
 */
#include "orb_host.h"

#include <arpa/inet.h>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <memory>
#include <mutex>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <thread>
#include <unistd.h>
#include <vector>

#include "ORBEngine.h"
#include "ORBEventListener.h"
#include "application_manager.h"

namespace {

OrbHostCallbacks g_cb;
int g_listenFd = -1;
std::string g_socketPath;
std::thread g_acceptThread;
volatile bool g_running = false;

void EvalJs(const std::string &script)
{
    if (g_cb.eval_js)
        g_cb.eval_js(script.c_str(), g_cb.user);
}

/* HbbTV key code -> UI Events `code` label, the table of the polyfill's keyevent.js ("0" when it has none). */
const char *KeyCodeLabel(int keyCode)
{
    switch (keyCode) {
    case 403: return "ColorF0Red";
    case 404: return "ColorF1Green";
    case 405: return "ColorF2Yellow";
    case 406: return "ColorF3Blue";
    case 37: return "ArrowLeft";
    case 38: return "ArrowUp";
    case 39: return "ArrowRight";
    case 40: return "ArrowDown";
    case 13: return "Enter";
    case 461: return "BrowserBack";
    case 27: return "Exit";
    case 413: return "MediaStop";
    case 415: return "MediaPlay";
    case 19: return "MediaPause";
    case 402: return "MediaPlayPause";
    case 417: return "MediaFastForward";
    case 412: return "MediaRewind";
    case 416: return "MediaRecord";
    default:
        break;
    }
    static const char *digits[] = { "Digit0", "Digit1", "Digit2", "Digit3", "Digit4", "Digit5", "Digit6", "Digit7", "Digit8", "Digit9" };
    if (keyCode >= 48 && keyCode <= 57)
        return digits[keyCode - 48];
    return "0";
}

/* What ORB's RDK web extension does for these notifications, but the embedder evaluates the script. */
struct HostListener : orb::ORBEventListener {
    void OnJavaScriptEventDispatchRequested(std::string name, std::string properties, std::string targetOrigin, bool broadcastRelated) override
    {
        EvalJs("document.dispatchBridgeEvent('" + name + "', " + (properties.empty() ? "{}" : properties) + ")");
    }
    void OnDvbUrlLoaded(int requestId, std::vector<uint8_t> content, unsigned int contentLength) override
    {
        fprintf(stderr, "[orb_host] dvb url loaded id=%d (%u bytes): dvb: scheme not handled yet\n", requestId, contentLength);
    }
    void OnDvbUrlLoadedNoData(int requestId, unsigned int contentLength) override
    {
        fprintf(stderr, "[orb_host] dvb url loaded (no data) id=%d\n", requestId);
    }
    void OnInputKeyGenerated(int keyCode, uint8_t keyAction) override
    {
        /* The polyfill (polyfill/keyevent.js) re-dispatches every key event whose `code` is empty, from a window
         * listener, to add the UI Events `code` label. An application listening on document would then see each
         * key twice (the bare event on its way up, then the labelled copy), so the label is supplied here. */
        const std::string args = "{'keyCode':" + std::to_string(keyCode) + ",'code':'" + KeyCodeLabel(keyCode) + "','bubbles':true}";
        if (keyAction == 1) {
            EvalJs("document.activeElement.dispatchEvent(new KeyboardEvent('keydown'," + args + "));");
        } else {
            EvalJs("document.activeElement.dispatchEvent(new KeyboardEvent('keypress'," + args + "));");
            EvalJs("document.activeElement.dispatchEvent(new KeyboardEvent('keyup'," + args + "));");
        }
    }
    void OnExitButtonPressed() override
    {
        if (g_cb.exit_pressed)
            g_cb.exit_pressed(g_cb.user);
    }
};

bool IoAll(int fd, void *buf, size_t len, bool writing)
{
    char *p = static_cast<char *>(buf);
    while (len) {
        ssize_t n = writing ? send(fd, p, len, MSG_NOSIGNAL) : read(fd, p, len);
        if (n < 0 && errno == EINTR)
            continue;
        if (n <= 0)
            return false;
        p += n;
        len -= static_cast<size_t>(n);
    }
    return true;
}

std::string Handle(char type, const std::string &payload)
{
    orb::ORBEngine &engine = orb::ORBEngine::GetSharedInstance();
    try {
        switch (type) {
        case 'R':
            return engine.ExecuteBridgeRequest(payload);
        case 'T':
            return engine.CreateToken(payload);
        case 'P':
            engine.NotifyApplicationPageChanged(payload);
            return "{}";
        case 'L':
            fprintf(stderr, "[page] %s\n", payload.c_str());
            return "{}";
        }
    } catch (const std::exception &e) {
        fprintf(stderr, "[orb_host] request type '%c' threw: %s\n", type, e.what());
    }
    return "{}";
}

void Serve(int fd)
{
    for (;;) {
        uint32_t len;
        if (!IoAll(fd, &len, 4, false))
            break;
        len = ntohl(len);
        if (len < 1 || len > (64u << 20))
            break;
        std::string frame(len, '\0');
        if (!IoAll(fd, &frame[0], len, false))
            break;
        const std::string reply = Handle(frame[0], frame.substr(1));
        uint32_t rlen = htonl(static_cast<uint32_t>(reply.size()));
        if (!IoAll(fd, &rlen, 4, true) || !IoAll(fd, const_cast<char *>(reply.data()), reply.size(), true))
            break;
    }
    close(fd);
}

void AcceptLoop()
{
    while (g_running) {
        int fd = accept(g_listenFd, nullptr, nullptr);
        if (fd < 0) {
            if (errno == EINTR)
                continue;
            break;
        }
        std::thread(Serve, fd).detach();
    }
}

} // namespace

extern "C" {

int orb_host_start(const char *socket_path, const OrbHostCallbacks *callbacks)
{
    if (callbacks)
        g_cb = *callbacks;

    g_listenFd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
    if (g_listenFd < 0)
        return 1;
    sockaddr_un sa {};
    sa.sun_family = AF_UNIX;
    strncpy(sa.sun_path, socket_path, sizeof sa.sun_path - 1);
    unlink(socket_path);
    if (bind(g_listenFd, reinterpret_cast<sockaddr *>(&sa), sizeof sa) < 0 || listen(g_listenFd, 8) < 0) {
        fprintf(stderr, "[orb_host] cannot listen on %s: %s\n", socket_path, strerror(errno));
        close(g_listenFd);
        g_listenFd = -1;
        return 2;
    }
    chmod(socket_path, 0600);
    g_socketPath = socket_path;

    if (!orb::ORBEngine::GetSharedInstance().Start(std::make_shared<HostListener>())) {
        fprintf(stderr, "[orb_host] ORBEngine::Start failed (platform library not loadable?)\n");
        return 3;
    }
    g_running = true;
    g_acceptThread = std::thread(AcceptLoop);
    fprintf(stderr, "[orb_host] engine started, bridge on %s, UA: %s\n", socket_path, orb::ORBEngine::GetSharedInstance().GetUserAgentString().c_str());
    return 0;
}

void orb_host_stop(void)
{
    g_running = false;
    if (g_listenFd >= 0) {
        shutdown(g_listenFd, SHUT_RDWR);
        close(g_listenFd);
        g_listenFd = -1;
    }
    if (g_acceptThread.joinable())
        g_acceptThread.join();
    if (!g_socketPath.empty())
        unlink(g_socketPath.c_str());
    orb::ORBEngine::GetSharedInstance().Stop();
}

char *orb_host_create_token(const char *uri)
{
    return strdup(orb::ORBEngine::GetSharedInstance().CreateToken(uri ? uri : "").c_str());
}

const char *orb_host_user_agent(void)
{
    static std::string ua;
    if (ua.empty())
        ua = orb::ORBEngine::GetSharedInstance().GetUserAgentString();
    return ua.c_str();
}

int orb_host_launch(const char *url)
{
    bool ok = orb::ORBEngine::GetSharedInstance().GetApplicationManager()->CreateApplication(INVALID_APP_ID, url);
    fprintf(stderr, "[orb_host] CreateApplication(%s) -> %s\n", url, ok ? "ok" : "FAILED");
    return ok ? 1 : 0;
}

int orb_host_key(int key_code, int down)
{
    return orb::ORBEngine::GetSharedInstance().SendKeyEvent(key_code, down ? 1 : 0) ? 1 : 0;
}

void orb_host_load_failed(const char *url, const char *description)
{
    orb::ORBEngine::GetSharedInstance().NotifyApplicationLoadFailed(url ? url : "", description ? description : "");
}

void orb_host_platform_load(const char *url)
{
    if (g_cb.load_url)
        g_cb.load_url(url, g_cb.user);
}

void orb_host_platform_set_visible(int visible)
{
    if (g_cb.set_visible)
        g_cb.set_visible(visible, g_cb.user);
}

} // extern "C"
