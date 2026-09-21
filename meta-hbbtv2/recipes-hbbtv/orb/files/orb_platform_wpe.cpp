/*
 * orb_platform_wpe.cpp - ORBPlatform for the WPE embedder (libORBPlatformImpl.so).
 *
 * Seed of the real enigma2 platform layer: it starts as ORB's platform mock (fake channel list, fake configuration,
 * canned answers) and overrides only what must reach the browser. Everything else gets replaced by enigma2-backed
 * implementations one group at a time (Configuration, Network, Broadcast, ...).
 *
 * Application_Load / Application_SetVisible go to the embedder through orb_host_platform_*(): those symbols are
 * defined in libORBHost.so, which the embedder links, so the dynamic linker resolves them from the global scope
 * when the engine dlopen()s this library. Link with -Wl,--allow-multiple-definition and this object first: the
 * mock defines its own Create/Destroy.
 */
#include "ORBPlatformMockImpl.h"
#include "orb_host.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace orb;

namespace {
/* The channel the box is tuned to (set by the embedder with orb_host_set_channel), or null before it was told. */
std::shared_ptr<Channel> TunedChannel()
{
    int onid = 0, tsid = 0, sid = 0;
    char name[128] = "";
    if (!orb_host_current_channel(&onid, &tsid, &sid, name, sizeof name))
        return nullptr;
    char ccid[48];
    snprintf(ccid, sizeof ccid, "ccid:%d.%d.%d", onid, tsid, sid);
    return std::make_shared<Channel>(ccid, name, "0", "0", Channel::CHANNEL_TYPE_TV, Channel::CHANNEL_ID_DVB_S, 0, 0, onid, onid, tsid, sid, false, 0);
}

std::shared_ptr<ORBPlatformEventHandler> g_events;

/* The embedder (orb_host_set_components) says that the components of the tuned channel changed: tell the application. Called from the
 * embedder's main loop while the engine may be busy with a request: report from a thread of our own, like ReportPresenting(). */
void ComponentsChanged(int type, int selectionChanged)
{
    std::shared_ptr<ORBPlatformEventHandler> events = g_events;
    if (!events)
        return;
    std::thread([events, type, selectionChanged]() {
        if (!selectionChanged)
            events->OnComponentChanged(type);
        events->OnSelectedComponentChanged(type);
    }).detach();
}

/* The id of a component: "video_<pid>", "audio_<pid>", "subtitle_<pid>". */
std::string ComponentId(const char *kind, int pid)
{
    return std::string(kind) + "_" + std::to_string(pid);
}
} // namespace

class ORBPlatformWpe : public ORBPlatformMockImpl {
public:
    /* The embedder already sends HbbTV/JS key codes; the mock maps every key to 0. */
    unsigned int Platform_MapKeyCode(unsigned int keyCode) override { return keyCode; }

    /* ESC (27) is what the embedder sends for the remote's EXIT key. */
    bool Platform_IsExitButton(unsigned int keyCode) override { return keyCode == 27; }

    /* The mock keeps its event handler private: keep our own reference to report the channel status. */
    void Platform_Initialise(std::shared_ptr<ORBPlatformEventHandler> platformEventHandler) override
    {
        m_events = platformEventHandler;
        g_events = platformEventHandler;
        orb_host_platform_on_components(ComponentsChanged);
        ORBPlatformMockImpl::Platform_Initialise(platformEventHandler);
    }

    /* An application that binds a video/broadcast object to the current channel waits for the platform to say that the channel is
     * being presented (ChannelStatusChanged). enigma2 is presenting the tuned service all the time: say so as soon as the application
     * takes over the broadcast presentation. */
    void Broadcast_SetPresentationSuspended(bool presentationSuspended) override
    {
        ORBPlatformMockImpl::Broadcast_SetPresentationSuspended(presentationSuspended);
        if (!presentationSuspended)
            ReportPresenting();
    }

    /* Selecting the channel that is tuned already is a success; tuning another one is not possible from here (yet). */
    int Broadcast_SetChannelToCcid(std::string ccid, bool trickplay, std::string contentAccessDescriptorURL, int quiet) override
    {
        std::shared_ptr<Channel> channel = TunedChannel();
        if (channel && channel->GetCcid() == ccid) {
            ReportPresenting();
            return Channel::CHANNEL_STATUS_CONNECTING;
        }
        return Channel::CHANNEL_ERROR_STATE_CANNOT_BE_CHANGED;
    }

    int Broadcast_SetChannelToTriplet(int idType, int onid, int tsid, int sid, int sourceID, std::string ipBroadcastID, bool trickplay,
        std::string contentAccessDescriptorURL, int quiet) override
    {
        int tunedOnid = 0, tunedTsid = 0, tunedSid = 0;
        if (orb_host_current_channel(&tunedOnid, &tunedTsid, &tunedSid, nullptr, 0) && tunedOnid == onid && tunedTsid == tsid && tunedSid == sid) {
            ReportPresenting();
            return Channel::CHANNEL_STATUS_CONNECTING;
        }
        return Channel::CHANNEL_ERROR_STATE_CANNOT_BE_CHANGED;
    }

    /* The components (video, audio, subtitles) of the tuned channel, as enigma2 reports them (the plugin sends them with the ctl command
     * "components", see orb_host_set_components). A video/broadcast object stays in CONNECTING until it has seen some: while enigma2
     * has told us none (an embedder run by hand, a channel without a service yet), one video and one audio component without PIDs
     * stand in for them, enough to say "the service is presented". */
    std::vector<Component> Broadcast_GetComponents(std::string ccid, int componentType) override
    {
        std::shared_ptr<Channel> channel = TunedChannel();
        if (!channel || channel->GetCcid() != ccid)
            return ORBPlatformMockImpl::Broadcast_GetComponents(ccid, componentType);
        std::vector<Component> components;
        OrbHostComponent host[64];
        const int count = orb_host_components(host, 64);
        for (int i = 0; i < count && i < 64; i++) {
            const OrbHostComponent &c = host[i];
            if (componentType != COMPONENT_TYPE_ANY && componentType != c.type)
                continue;
            /* no component_tag is known (enigma2 does not expose the PMT's stream identifier descriptors): -1 */
            switch (c.type) {
            case ORB_HOST_COMPONENT_VIDEO:
                components.push_back(*Component::CreateVideoComponent(ComponentId("video", c.pid), -1, c.pid, c.encoding, c.encrypted != 0, c.active != 0, false, c.extra));
                break;
            case ORB_HOST_COMPONENT_AUDIO:
                components.push_back(*Component::CreateAudioComponent(ComponentId("audio", c.pid), -1, c.pid, c.encoding, c.encrypted != 0, c.active != 0, false, c.language, c.flag != 0, c.extra));
                break;
            case ORB_HOST_COMPONENT_SUBTITLE:
                components.push_back(*Component::CreateSubtitleComponent(ComponentId("subtitle", c.pid), -1, c.pid, c.encoding, false, c.active != 0, false, c.language, c.extra != 0, c.language));
                break;
            default:
                break;
            }
        }
        if (count == 0) {
            if (componentType == COMPONENT_TYPE_ANY || componentType == COMPONENT_TYPE_VIDEO)
                components.push_back(*Component::CreateVideoComponent("video_0", 0, 0, "H.264", false, true, false, 0));
            if (componentType == COMPONENT_TYPE_ANY || componentType == COMPONENT_TYPE_AUDIO)
                components.push_back(*Component::CreateAudioComponent("audio_0", 1, 0, "HEAAC", false, true, false, "deu", false, 2));
        }
        return components;
    }

    /* The application selects a component (an audio track, a subtitle track) or gives the choice back to the terminal. enigma2 does the
     * switching: the embedder passes this on to the plugin, and the plugin's next list of components (with the new "active") is what
     * tells the application that it happened. The video cannot be switched, and presentation cannot be disabled, except for subtitles. */
    void Broadcast_OverrideComponentSelection(int componentType, std::string id) override
    {
        if (componentType != COMPONENT_TYPE_AUDIO && componentType != COMPONENT_TYPE_SUBTITLE)
            return;
        if (id.empty()) {
            orb_host_platform_select_component(componentType, "none");
            return;
        }
        const size_t underscore = id.rfind('_');
        if (underscore == std::string::npos)
            return;
        orb_host_platform_select_component(componentType, std::to_string(atoi(id.c_str() + underscore + 1)).c_str());
    }

    void Broadcast_RestoreComponentSelection(int componentType) override
    {
        if (componentType == COMPONENT_TYPE_AUDIO || componentType == COMPONENT_TYPE_SUBTITLE)
            orb_host_platform_select_component(componentType, "default");
    }

    /* The current channel is the one enigma2 is tuned to (the mock's is an empty one). The channel list is that channel only for
     * now (enigma2's whole bouquet list is not handed over yet). */
    std::shared_ptr<Channel> Broadcast_GetCurrentChannel() override
    {
        std::shared_ptr<Channel> channel = TunedChannel();
        return channel ? channel : ORBPlatformMockImpl::Broadcast_GetCurrentChannel();
    }

    std::vector<Channel> Broadcast_GetChannelList() override
    {
        std::shared_ptr<Channel> channel = TunedChannel();
        if (!channel)
            return ORBPlatformMockImpl::Broadcast_GetChannelList();
        return std::vector<Channel>{*channel};
    }

    bool Application_Load(std::string url) override
    {
        orb_host_platform_load(url.c_str());
        return true;
    }

    bool Application_SetVisible(bool visible) override
    {
        orb_host_platform_set_visible(visible ? 1 : 0);
        return true;
    }

private:
    /* ChannelStatusChanged(presenting) for the tuned channel, a moment later (the page registers its listener right after the call
     * that caused this returns; the engine may also be inside a request when we are called). */
    void ReportPresenting()
    {
        int onid = 0, tsid = 0, sid = 0;
        if (!m_events || !orb_host_current_channel(&onid, &tsid, &sid, nullptr, 0))
            return;
        std::shared_ptr<ORBPlatformEventHandler> events = m_events;
        std::thread([events, onid, tsid, sid]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            events->OnChannelStatusChanged(onid, tsid, sid, Channel::CHANNEL_STATUS_PRESENTING, false);
        }).detach();
    }

    std::shared_ptr<ORBPlatformEventHandler> m_events;
};

extern "C" ORBPlatform *Create()
{
    return new ORBPlatformWpe();
}

extern "C" void Destroy(ORBPlatform *platform)
{
    delete static_cast<ORBPlatformWpe *>(platform);
}
