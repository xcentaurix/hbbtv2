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

namespace {
struct HostChannel {
    bool set = false;
    int onid = 0, tsid = 0, sid = 0;
    std::string name;
};
HostChannel g_channel;
std::mutex g_channelMutex;
} // namespace

void orb_host_set_channel(int onid, int tsid, int sid, const char *name)
{
    std::lock_guard<std::mutex> lock(g_channelMutex);
    g_channel.set = onid >= 0 && tsid >= 0 && sid >= 0;
    g_channel.onid = onid;
    g_channel.tsid = tsid;
    g_channel.sid = sid;
    g_channel.name = name ? name : "";
    fprintf(stderr, "[orb_host] channel %d/%d/%d \"%s\"\n", onid, tsid, sid, g_channel.name.c_str());
}

int orb_host_current_channel(int *onid, int *tsid, int *sid, char *name, unsigned long size)
{
    std::lock_guard<std::mutex> lock(g_channelMutex);
    if (!g_channel.set)
        return 0;
    if (onid)
        *onid = g_channel.onid;
    if (tsid)
        *tsid = g_channel.tsid;
    if (sid)
        *sid = g_channel.sid;
    if (name && size) {
        snprintf(name, size, "%s", g_channel.name.c_str());
    }
    return 1;
}

namespace {
std::vector<OrbHostComponent> g_components;
bool g_haveComponents = false; /* the plugin has sent a list (possibly an empty one) */
std::mutex g_componentsMutex;
void (*g_componentsChanged)(int type, int selectionChanged) = nullptr;
void (*g_componentHandler)(int type, const char *what, void *user) = nullptr;
void *g_componentHandlerUser = nullptr;

std::vector<std::string> Split(const std::string &text, char separator)
{
    std::vector<std::string> parts;
    size_t start = 0;
    for (;;) {
        size_t end = text.find(separator, start);
        parts.push_back(text.substr(start, end == std::string::npos ? std::string::npos : end - start));
        if (end == std::string::npos)
            return parts;
        start = end + 1;
    }
}

bool ParseComponent(const std::string &record, OrbHostComponent &out)
{
    std::vector<std::string> f = Split(record, ':');
    if (f.empty() || f[0].size() != 1)
        return false;
    auto number = [&](size_t i) { return i < f.size() ? atoi(f[i].c_str()) : 0; };
    auto text = [&](size_t i, char *destination, size_t size) { snprintf(destination, size, "%s", i < f.size() ? f[i].c_str() : ""); };
    memset(&out, 0, sizeof out);
    switch (f[0][0]) {
    case 'V': /* V:<pid>:<encoding>:<encrypted>:<aspect> */
        out.type = ORB_HOST_COMPONENT_VIDEO;
        out.pid = number(1);
        text(2, out.encoding, sizeof out.encoding);
        out.encrypted = number(3) != 0;
        out.extra = number(4);
        out.active = 1;
        break;
    case 'A': /* A:<pid>:<language>:<encoding>:<channels>:<active>:<audio description> */
        out.type = ORB_HOST_COMPONENT_AUDIO;
        out.pid = number(1);
        text(2, out.language, sizeof out.language);
        text(3, out.encoding, sizeof out.encoding);
        out.extra = number(4);
        out.active = number(5) != 0;
        out.flag = number(6) != 0;
        break;
    case 'S': /* S:<pid>:<language>:<encoding>:<active>:<hearing impaired> */
        out.type = ORB_HOST_COMPONENT_SUBTITLE;
        out.pid = number(1);
        text(2, out.language, sizeof out.language);
        text(3, out.encoding, sizeof out.encoding);
        out.active = number(4) != 0;
        out.extra = number(5) != 0;
        break;
    default:
        return false;
    }
    return true;
}

/* Do the components of `type` differ in anything but which one is presented? / in which one is presented? */
void Compare(const std::vector<OrbHostComponent> &before, const std::vector<OrbHostComponent> &after, int type, bool &listChanged, bool &selectionChanged)
{
    std::vector<OrbHostComponent> a, b;
    for (const auto &c : before)
        if (c.type == type)
            a.push_back(c);
    for (const auto &c : after)
        if (c.type == type)
            b.push_back(c);
    listChanged = selectionChanged = false;
    if (a.size() != b.size()) {
        listChanged = true;
        return;
    }
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i].pid != b[i].pid || a[i].encrypted != b[i].encrypted || a[i].extra != b[i].extra || a[i].flag != b[i].flag
            || strcmp(a[i].encoding, b[i].encoding) || strcmp(a[i].language, b[i].language))
            listChanged = true;
        if (a[i].active != b[i].active)
            selectionChanged = true;
    }
}
} // namespace

void orb_host_set_components(const char *text)
{
    std::vector<OrbHostComponent> parsed;
    for (const std::string &record : Split(text ? text : "", ';')) {
        OrbHostComponent component;
        if (!record.empty() && ParseComponent(record, component))
            parsed.push_back(component);
    }
    std::vector<OrbHostComponent> previous;
    bool hadComponents;
    void (*changed)(int, int);
    {
        std::lock_guard<std::mutex> lock(g_componentsMutex);
        previous = g_components;
        hadComponents = g_haveComponents;
        g_components = parsed;
        g_haveComponents = true;
        changed = g_componentsChanged;
    }
    if (!hadComponents)
        fprintf(stderr, "[orb_host] components: %zu (first list)\n", parsed.size());
    if (!hadComponents || !changed)
        return;
    for (int type = ORB_HOST_COMPONENT_VIDEO; type <= ORB_HOST_COMPONENT_SUBTITLE; type++) {
        bool listChanged, selectionChanged;
        Compare(previous, parsed, type, listChanged, selectionChanged);
        if (listChanged || selectionChanged)
            fprintf(stderr, "[orb_host] components of type %d changed (%s)\n", type, listChanged ? "list" : "selection");
        if (listChanged)
            changed(type, 0);
        else if (selectionChanged)
            changed(type, 1);
    }
}

int orb_host_components(OrbHostComponent *out, int max)
{
    std::lock_guard<std::mutex> lock(g_componentsMutex);
    int count = 0;
    for (const auto &component : g_components) {
        if (out && count < max)
            out[count] = component;
        count++;
    }
    return out && count > max ? max : count;
}

void orb_host_set_component_handler(void (*handler)(int type, const char *what, void *user), void *user)
{
    std::lock_guard<std::mutex> lock(g_componentsMutex);
    g_componentHandler = handler;
    g_componentHandlerUser = user;
}

void orb_host_service_selected(int onid, int tsid, int sid)
{
    auto handler = orb::ORBEngine::GetSharedInstance().GetPlatformEventHandler();
    fprintf(stderr, "[orb_host] service selected %d/%d/%d: waiting for its AIT\n", onid, tsid, sid);
    if (handler)
        handler->OnChannelStatusChanged(onid, tsid, sid, orb::Channel::CHANNEL_STATUS_CONNECTING, false);
}

void orb_host_ait_section(int pid, int sid, const unsigned char *data, unsigned int length)
{
    auto handler = orb::ORBEngine::GetSharedInstance().GetPlatformEventHandler();
    if (!handler || !data || !length)
        return;
    std::vector<unsigned char> copy(data, data + length); /* the engine takes a non-const pointer */
    fprintf(stderr, "[orb_host] AIT section: pid %d service %d, %u bytes\n", pid, sid, length);
    handler->OnAitSectionReceived((unsigned short)pid, (unsigned short)sid, copy.data(), length);
}

void orb_host_broadcast_stopped(void)
{
    auto handler = orb::ORBEngine::GetSharedInstance().GetPlatformEventHandler();
    fprintf(stderr, "[orb_host] broadcast stopped\n");
    if (handler)
        handler->OnBroadcastStopped();
}

unsigned int orb_host_key_set_mask(void)
{
    orb::ORBEngine &engine = orb::ORBEngine::GetSharedInstance();
    const uint16_t appId = engine.GetCurrentAppId();
    if (appId == UINT16_MAX)
        return 0;
    return engine.GetApplicationManager()->GetKeySetMask(appId);
}

int orb_host_launch_broadcast(const char *url)
{
    if (url && !strncmp(url, "dvb://", 6)) { /* dvb://current.ait/<org>.<app>: an application of the AIT of the selected service */
        bool ok = orb::ORBEngine::GetSharedInstance().GetApplicationManager()->CreateApplication(INVALID_APP_ID, url);
        fprintf(stderr, "[orb_host] CreateApplication(%s) -> %s\n", url, ok ? "ok" : "FAILED");
        return ok ? 1 : 0;
    }
    HostChannel channel;
    {
        std::lock_guard<std::mutex> lock(g_channelMutex);
        channel = g_channel;
    }
    if (!channel.set)
        return orb_host_launch(url);
    bool ok = orb::ORBEngine::GetSharedInstance().GetApplicationManager()->CreateBroadcastRelatedApplication(
        url, (uint16_t)channel.onid, (uint16_t)channel.tsid, (uint16_t)channel.sid);
    fprintf(stderr, "[orb_host] CreateBroadcastRelatedApplication(%s, %d/%d/%d) -> %s\n", url, channel.onid, channel.tsid, channel.sid, ok ? "ok" : "FAILED");
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

void orb_host_platform_on_components(void (*changed)(int type, int selection_changed))
{
    std::lock_guard<std::mutex> lock(g_componentsMutex);
    g_componentsChanged = changed;
}

void orb_host_platform_select_component(int type, const char *what)
{
    void (*handler)(int, const char *, void *);
    void *user;
    {
        std::lock_guard<std::mutex> lock(g_componentsMutex);
        handler = g_componentHandler;
        user = g_componentHandlerUser;
    }
    fprintf(stderr, "[orb_host] select component type %d: %s%s\n", type, what ? what : "", handler ? "" : " (nobody to tell)");
    if (handler)
        handler(type, what ? what : "", user);
}

} // extern "C"
