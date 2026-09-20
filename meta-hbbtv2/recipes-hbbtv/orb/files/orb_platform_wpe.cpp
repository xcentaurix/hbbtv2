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

class ORBPlatformWpe : public ORBPlatformMockImpl {
public:
    /* The embedder already sends HbbTV/JS key codes; the mock maps every key to 0. */
    unsigned int Platform_MapKeyCode(unsigned int keyCode) override { return keyCode; }

    /* ESC (27) is what the embedder sends for the remote's EXIT key. */
    bool Platform_IsExitButton(unsigned int keyCode) override { return keyCode == 27; }

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
};

extern "C" ORBPlatform *Create()
{
    return new ORBPlatformWpe();
}

extern "C" void Destroy(ORBPlatform *platform)
{
    delete static_cast<ORBPlatformWpe *>(platform);
}
