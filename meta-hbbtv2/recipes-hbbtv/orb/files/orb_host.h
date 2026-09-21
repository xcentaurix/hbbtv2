/*
 * orb_host.h - plain C interface to the ORB engine, for an embedder that is not C++ (wpe_fb).
 *
 * The host runs ORBEngine in-process, serves the web process extension's bridge socket (see orb_ext.c) and reports
 * what the engine wants done through OrbHostCallbacks. The callbacks may be invoked from ANY thread: the embedder
 * has to hop to its own main loop.
 */
#ifndef ORB_HOST_H
#define ORB_HOST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void (*eval_js)(const char *script, void *user); /* run this script in the application's top frame */
    void (*load_url)(const char *url, void *user); /* navigate the application view */
    void (*set_visible)(int visible, void *user); /* show/hide the application */
    void (*exit_pressed)(void *user); /* the EXIT key was pressed while an application ran */
    void *user;
} OrbHostCallbacks;

/* Load the platform library (ORB_PLATFORM_LIB or /usr/lib/libORBPlatformImpl.so), start the engine, listen on
 * socket_path. Returns 0 on success. */
int orb_host_start(const char *socket_path, const OrbHostCallbacks *callbacks);
void orb_host_stop(void);

/* Token (JSON text, malloc'd, caller frees) for a page of the running application: what ORBEngine::CreateToken() returns. */
char *orb_host_create_token(const char *uri);

/* The HbbTV part of the user agent (e.g. "HbbTV/1.6.1 (; OBS; WPE; v1.0.0-alpha; ; OBS;)"), to append to the browser's own. */
const char *orb_host_user_agent(void);

/* Create and run a broadcast-independent application from a URL (entry page or XML AIT). Blocks while the URL is
 * fetched to classify it - call from a worker thread. Returns 1 if the application was created. */
int orb_host_launch(const char *url);

/* The service the box is tuned to (enigma2 tells the embedder). Applications launched with orb_host_launch_broadcast() are
 * broadcast-related applications of this service: their Broadcast.* requests are answered, with this channel as the current one. */
void orb_host_set_channel(int onid, int tsid, int sid, const char *name);

/* Same for the platform library: 1 and the values if a channel was set, else 0. name gets at most size bytes, always terminated. */
int orb_host_current_channel(int *onid, int *tsid, int *sid, char *name, unsigned long size);

/* Like orb_host_launch(), but as a broadcast-related application of the channel set with orb_host_set_channel() (without one it
 * is the same as orb_host_launch()). A url of the form dvb://current.ait/<org id>.<app id>[?parameters] is a locator: the engine looks
 * the application up in the AIT of the selected service (see orb_host_ait_section), as an application's createApplication() does. */
int orb_host_launch_broadcast(const char *url);

/* The real AIT. These three are what a platform reports to the engine (OnChannelStatusChanged(CONNECTING), OnAitSectionReceived,
 * OnBroadcastStopped): the service was selected (the engine now waits for its AIT and, when it is there, keeps, kills or starts
 * applications by what it signals); a raw AIT section of that service (sections of one table are fed as they arrive, the engine collects
 * them and acts when the table is complete or changes); the broadcast stopped (a broadcast-related application is killed or becomes
 * broadcast-independent). The engine then runs the AUTOSTART application by itself, resolves dvb://current.ait/... locators and kills
 * applications the AIT does not signal any more. */
void orb_host_service_selected(int onid, int tsid, int sid);
void orb_host_ait_section(int pid, int sid, const unsigned char *data, unsigned int length);
void orb_host_broadcast_stopped(void);

/* Feed a remote-control key (HbbTV/JS key code, e.g. 403 = red) to the engine. Returns 1 if an application
 * consumed it (in its key set, or EXIT). */
int orb_host_key(int key_code, int down);

/* The embedder's view failed to load the application page / navigated to another page. */
void orb_host_load_failed(const char *url, const char *description);

/* The components (video, audio, subtitle streams) of the service enigma2 is tuned to, with what enigma2 knows about them. */
#define ORB_HOST_COMPONENT_VIDEO 0
#define ORB_HOST_COMPONENT_AUDIO 1
#define ORB_HOST_COMPONENT_SUBTITLE 2
typedef struct {
    int type; /* ORB_HOST_COMPONENT_* */
    int pid;
    int encrypted;
    int active; /* presented now */
    int extra; /* video: aspect ratio (0 4:3, 1 16:9, ...); audio: number of channels (0 = not known); subtitle: 1 = for the hearing impaired */
    int flag; /* audio: 1 = audio description; else 0 */
    char encoding[24];
    char language[8]; /* ISO 639-2, "und" if not known; audio and subtitle */
} OrbHostComponent;

/* Replace the components with the ones described by `text` (what the plugin sends with the ctl command "components": records separated by
 * ';', fields by ':' -
 *     V:<pid>:<encoding>:<encrypted>:<aspect>
 *     A:<pid>:<language>:<encoding>:<channels>:<active>:<audio description>
 *     S:<pid>:<language>:<encoding>:<active>:<hearing impaired>
 * ). An empty text = no components. What changed is reported to the platform library (orb_host_platform_on_components). */
void orb_host_set_components(const char *text);

/* Same for the platform library: copies at most `max` components (all types) and returns how many there are; 0 = none received / none. */
int orb_host_components(OrbHostComponent *out, int max);

/* The embedder's answer to a component selection of the application (Broadcast.overrideComponentSelection / restoreComponentSelection):
 * `what` is "<pid>" for a component, "default" (restore) or "none" (subtitles/audio off) - the embedder forwards it to enigma2. */
void orb_host_set_component_handler(void (*handler)(int type, const char *what, void *user), void *user);

/* Called by the platform library (libORBPlatformImpl.so) - resolved from the embedder's global symbols. */
void orb_host_platform_load(const char *url);
void orb_host_platform_set_visible(int visible);
/* `changed(type, selection_changed)`: the components of this type changed (selection_changed: only which one is presented). It is called from
 * whatever thread the embedder set them from: hop to a thread of your own before calling back into the engine. */
void orb_host_platform_on_components(void (*changed)(int type, int selection_changed));
void orb_host_platform_select_component(int type, const char *what);

#ifdef __cplusplus
}
#endif

#endif
