/*
 * orb_test - run ORBCore with a platform library on the box and fire bridge requests at it, exactly the way the
 * polyfill's wpeBridge.request() does (JSON string in, JSON string out). No browser involved.
 *
 *   ORB_PLATFORM_LIB=/media/hdd/wpe-test/orb/libORBPlatformImpl.so ./orb_test [http://app/url]
 */
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>

#include "ORBEngine.h"
#include "ORBEventListener.h"
#include "application_manager.h"
#include "json.hpp"

using nlohmann::json;

struct Listener : orb::ORBEventListener {
    void OnJavaScriptEventDispatchRequested(std::string name, std::string properties, std::string targetOrigin, bool broadcastRelated) override
    {
        printf("[event] dispatchBridgeEvent('%s', %.120s) target=%s broadcastRelated=%d\n", name.c_str(), properties.c_str(), targetOrigin.c_str(),
            (int)broadcastRelated);
    }
    void OnDvbUrlLoaded(int requestId, std::vector<uint8_t> content, unsigned int contentLength) override
    {
        printf("[event] dvb url loaded id=%d, %u bytes\n", requestId, contentLength);
    }
    void OnDvbUrlLoadedNoData(int requestId, unsigned int contentLength) override { printf("[event] dvb url loaded (no data) id=%d\n", requestId); }
    void OnInputKeyGenerated(int keyCode, uint8_t keyAction) override { printf("[event] key %d action %d\n", keyCode, (int)keyAction); }
    void OnExitButtonPressed() override { printf("[event] exit button\n"); }
};

int main(int argc, char **argv)
{
    const std::string appUrl = argc > 1 ? argv[1] : "http://example.org/app.html";
    orb::ORBEngine &engine = orb::ORBEngine::GetSharedInstance();

    if (!engine.Start(std::make_shared<Listener>())) {
        printf("ORBEngine::Start FAILED (platform library not loadable?)\n");
        return 2;
    }
    printf("engine started, UA: %s\n", engine.GetUserAgentString().c_str());

    // A token only exists while an application runs: start one the way the platform would for a URL launch.
    const bool created = engine.GetApplicationManager()->CreateApplication(INVALID_APP_ID, appUrl);
    printf("CreateApplication(%s) -> %d, current app id %u\n", appUrl.c_str(), (int)created, (unsigned)engine.GetCurrentAppId());

    const std::string tokenText = engine.CreateToken(appUrl);
    printf("token for %s: %.160s\n", appUrl.c_str(), tokenText.c_str());
    json token = json::parse(tokenText, nullptr, false);

    auto request = [&](const char *method, json params = json::object()) {
        json body = { { "token", token }, { "method", method }, { "params", params } };
        std::string reply = engine.ExecuteBridgeRequest(body.dump());
        printf("%-42s -> %.200s\n", method, reply.c_str());
    };

    request("Configuration.getLocalSystem");
    request("Configuration.getCapabilities");
    request("Configuration.getPreferredUILanguage");
    request("Configuration.getPreferredAudioLanguage");
    request("Configuration.getCountryId");
    request("Configuration.getSubtitlesEnabled");
    request("Configuration.getVideoProfiles");
    request("Configuration.getPrimaryDisplay");
    request("Network.resolveHostAddress", { { "hostname", "localhost" } });
    request("Manager.getKeyValues", { { "appId", 0 } });
    request("Broadcast.getChannelList");
    request("Broadcast.getCurrentChannel");
    request("Bogus.noSuchMethod");

    engine.Stop();
    printf("engine stopped\n");
    return 0;
}
