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

/* Feed a remote-control key (HbbTV/JS key code, e.g. 403 = red) to the engine. Returns 1 if an application
 * consumed it (in its key set, or EXIT). */
int orb_host_key(int key_code, int down);

/* The embedder's view failed to load the application page / navigated to another page. */
void orb_host_load_failed(const char *url, const char *description);

/* Called by the platform library (libORBPlatformImpl.so) - resolved from the embedder's global symbols. */
void orb_host_platform_load(const char *url);
void orb_host_platform_set_visible(int visible);

#ifdef __cplusplus
}
#endif

#endif
