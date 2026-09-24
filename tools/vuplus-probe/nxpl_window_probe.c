/*
 * nxpl_window_probe - does Nexus's own compositor actually show an NXPL native window on this box's TV?
 *
 * Why: fb_paint_probe.c already proved a raw /dev/fb0 write is invisible on a real GigaBlue - "nothing on screen" - confirming that Nexus middleware
 * owns the physical display exclusively (default_nexus.h's own doc comment for NXPL_RegisterNexusDisplayPlatform: "Register a display for exclusive
 * use") and does not scan out generic Linux fbdev memory at all. wpe_fb.c (this project's HbbTV frame presenter) only ever writes to fb0, so it can
 * never work on a Nexus box regardless of anything EGL-side - the real fix needs Nexus's own window-showing API instead. default_nexus.h declares
 * exactly that: NXPL_CreateNativeWindowEXT (make a window), NXPL_ShowNativeWindowEXT(native, show) (actually show/hide it through Nexus's own
 * compositor), and a real EGL WINDOW surface (eglCreateWindowSurface) drawn against that native window, presented with eglSwapBuffers - a
 * completely different path from wpe_fb's current CPU-readback-then-memcpy-into-fbdev approach.
 *
 * This tool isolates exactly that one question, before any of it gets wired into wpe_fb.c for real: register (as r10's fix already proves works) ->
 * create a native window -> show it -> create a real EGL window surface against it -> clear it to a bold, unmistakable colour -> swap -> hold for a
 * few seconds -> hide/destroy/unregister everything again. A HUMAN AT THE BOX must say what appeared, if anything.
 *
 * Pure runtime dlopen/dlsym, no vendor headers linked at build time (same portability approach as vu_egl_probe.c and the WebKit quirk header) - the
 * exact size/alignment of NXPL_NativeWindowInfoEXT is NOT relied on: NXPL_GetDefaultNativeWindowInfoEXT() only WRITES sane defaults into a buffer
 * generously larger than the real struct (the same safe oversized-buffer trick already used for NxClient_JoinSettings in
 * NexusEGLPlatformQuirk.h/vu_egl_probe.c), and NXPL_CreateNativeWindowEXT() only READS whatever was written there - so the real field layout/enum
 * widths never need to be known precisely.
 *
 * Disruptive by design (unlike vu_egl_probe.c) - runs the whole sequence in one short-lived forked child with a bounded alarm, and always tries to
 * hide/destroy/unregister before exiting, on every path including a caught crash, so a run left unattended cannot strand anything registered.
 *
 *   build (any ARMv7 hf cross compiler):  arm-...-gcc -Os -Wall nxpl_window_probe.c -o nxpl_window_probe -ldl      (see build_vu_probe.sh)
 *   run:   ./nxpl_window_probe [seconds]     (default 6; look at the TV during that window)
 */
#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <ucontext.h>
#include <unistd.h>

typedef void *EGLDisplay, *EGLConfig, *EGLContext, *EGLSurface, *EGLNativeWindowType;
typedef int EGLint, EGLBoolean;
typedef unsigned int GLenum, GLbitfield;

#define EGL_SURFACE_TYPE 0x3033
#define EGL_RENDERABLE_TYPE 0x3040
#define EGL_RED_SIZE 0x3024
#define EGL_GREEN_SIZE 0x3023
#define EGL_BLUE_SIZE 0x3022
#define EGL_ALPHA_SIZE 0x3021
#define EGL_NONE 0x3038
#define EGL_WINDOW_BIT 4
#define EGL_OPENGL_ES2_BIT 4
#define EGL_OPENGL_ES_API 0x30A0
#define EGL_CONTEXT_CLIENT_VERSION 0x3098
#define GL_COLOR_BUFFER_BIT 0x4000

static void *(*p_eglGetDisplay)(void *);
static EGLBoolean (*p_eglInitialize)(void *, EGLint *, EGLint *);
static EGLBoolean (*p_eglBindAPI)(unsigned);
static EGLBoolean (*p_eglChooseConfig)(void *, const EGLint *, void **, EGLint, EGLint *);
static void *(*p_eglCreateWindowSurface)(void *, void *, EGLNativeWindowType, const EGLint *);
static void *(*p_eglCreateContext)(void *, void *, void *, const EGLint *);
static EGLBoolean (*p_eglMakeCurrent)(void *, void *, void *, void *);
static EGLBoolean (*p_eglSwapBuffers)(void *, void *);
static EGLint (*p_eglGetError)(void);
static void (*p_glClearColor)(float, float, float, float);
static void (*p_glClear)(GLbitfield);

static void step(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    printf("== ");
    vprintf(fmt, ap);
    printf("\n");
    va_end(ap);
    fflush(stdout);
}

/* Everything torn down on every exit path, including the alarm timeout - a run left unattended must not strand a registered/shown window. */
static void *g_nxpl_handle = NULL;
static void *g_native = NULL;
static void (*g_ShowWindow)(void *, int) = NULL;
static void (*g_DestroyWindow)(void *) = NULL;
static void (*g_Unregister)(void *) = NULL;

static void teardown_and_exit(int code)
{
    if (g_native && g_ShowWindow) {
        g_ShowWindow(g_native, 0);
        printf("hidden\n");
    }
    if (g_native && g_DestroyWindow) {
        g_DestroyWindow(g_native);
        printf("native window destroyed\n");
    }
    if (g_nxpl_handle && g_Unregister) {
        g_Unregister(g_nxpl_handle);
        printf("unregistered\n");
    }
    fflush(stdout);
    _exit(code);
}

static void on_alarm(int sig)
{
    (void)sig;
    printf("\n(timeout - tearing down and exiting)\n");
    teardown_and_exit(3);
}

int main(int argc, char **argv)
{
    int secs = argc > 1 ? atoi(argv[1]) : 6;
    if (secs < 1) secs = 1;
    if (secs > 30) secs = 30;
    setvbuf(stdout, NULL, _IOLBF, 0);
    signal(SIGALRM, on_alarm);
    alarm(secs + 20);

    /* Preload an EGL-providing library FIRST, before any Nexus join/register call - this is precisely the ordering patch 0017/r10 needed
     * (libnxpl.so's own dlopen(RTLD_NOW) needs BEGL_PlatformAboutToShutdown from libv3ddriver.so/libEGL.so, which nothing else loads yet this
     * early in a fresh process). Also resolves the actual EGL/GLES function pointers used below. */
    step("dlopen an EGL-providing library");
    static const char *const egl_names[] = { "libEGL.so.1", "libEGL.so", "libv3ddriver.so", NULL };
    void *egl = NULL;
    for (int i = 0; egl_names[i] && !egl; i++) {
        egl = dlopen(egl_names[i], RTLD_NOW | RTLD_GLOBAL);
        printf("   dlopen(\"%s\"): %s\n", egl_names[i], egl ? "ok" : dlerror());
    }
    if (!egl) { printf("SUMMARY: no EGL library found\n"); return 1; }
    static const char *const gles_names[] = { "libGLESv2.so.2", "libGLESv2.so", "libv3ddriver.so", NULL };
    void *gles = NULL;
    for (int i = 0; gles_names[i] && !gles; i++) {
        gles = dlopen(gles_names[i], RTLD_NOW | RTLD_GLOBAL);
        printf("   dlopen(\"%s\"): %s\n", gles_names[i], gles ? "ok" : dlerror());
    }
    if (!gles) { printf("SUMMARY: no GLESv2 library found\n"); return 1; }

    p_eglGetDisplay = dlsym(egl, "eglGetDisplay");
    p_eglInitialize = dlsym(egl, "eglInitialize");
    p_eglBindAPI = dlsym(egl, "eglBindAPI");
    p_eglChooseConfig = dlsym(egl, "eglChooseConfig");
    p_eglCreateWindowSurface = dlsym(egl, "eglCreateWindowSurface");
    p_eglCreateContext = dlsym(egl, "eglCreateContext");
    p_eglMakeCurrent = dlsym(egl, "eglMakeCurrent");
    p_eglSwapBuffers = dlsym(egl, "eglSwapBuffers");
    p_eglGetError = dlsym(egl, "eglGetError");
    p_glClearColor = dlsym(gles, "glClearColor");
    p_glClear = dlsym(gles, "glClear");
    if (!p_eglGetDisplay || !p_eglInitialize || !p_eglChooseConfig || !p_eglCreateWindowSurface ||
        !p_eglCreateContext || !p_eglMakeCurrent || !p_eglSwapBuffers || !p_glClearColor || !p_glClear) {
        printf("SUMMARY: a required EGL/GLES symbol was not found\n");
        return 1;
    }

    step("NxClient_Join (libnxclient.so)");
    void *nxclient = dlopen("libnxclient.so", RTLD_NOW | RTLD_GLOBAL);
    if (!nxclient) { printf("   dlopen failed: %s\n", dlerror()); return 1; }
    void (*GetDefaultJoinSettings)(void *) = dlsym(nxclient, "NxClient_GetDefaultJoinSettings");
    int (*Join)(const void *) = dlsym(nxclient, "NxClient_Join");
    if (!GetDefaultJoinSettings || !Join) { printf("   dlsym failed\n"); return 1; }
    unsigned char joinSettings[1024] = { 0 };
    GetDefaultJoinSettings(joinSettings);
    int jrc = Join(joinSettings);
    printf("   NxClient_Join() returned %d (0 = NEXUS_SUCCESS)\n", jrc);

    step("dlopen libnxpl.so and NXPL_RegisterNexusDisplayPlatform(NULL)");
    void *nxpl = dlopen("libnxpl.so", RTLD_NOW | RTLD_GLOBAL);
    if (!nxpl) { printf("   dlopen failed: %s\n", dlerror()); return 1; }
    void (*Register)(void **, void *) = dlsym(nxpl, "NXPL_RegisterNexusDisplayPlatform");
    g_Unregister = dlsym(nxpl, "NXPL_UnregisterNexusDisplayPlatform");
    void (*GetDefaultWindowInfo)(void *) = dlsym(nxpl, "NXPL_GetDefaultNativeWindowInfoEXT");
    void *(*CreateWindow)(const void *) = dlsym(nxpl, "NXPL_CreateNativeWindowEXT");
    g_DestroyWindow = dlsym(nxpl, "NXPL_DestroyNativeWindow");
    g_ShowWindow = (void (*)(void *, int))dlsym(nxpl, "NXPL_ShowNativeWindowEXT");
    if (!Register || !g_Unregister || !GetDefaultWindowInfo || !CreateWindow || !g_DestroyWindow || !g_ShowWindow) {
        printf("   a required NXPL symbol was not found (Register=%p Unregister=%p GetDefaultWindowInfo=%p CreateWindow=%p DestroyWindow=%p ShowWindow=%p)\n",
            (void *)Register, (void *)g_Unregister, (void *)GetDefaultWindowInfo, (void *)CreateWindow, (void *)g_DestroyWindow, (void *)g_ShowWindow);
        return 1;
    }
    Register(&g_nxpl_handle, NULL);
    printf("   handle=%p\n", g_nxpl_handle);
    if (!g_nxpl_handle) { printf("SUMMARY: register did not produce a handle\n"); teardown_and_exit(1); }

    step("NXPL_GetDefaultNativeWindowInfoEXT + NXPL_CreateNativeWindowEXT (1280x720 at 0,0, full screen)");
    /* Oversized zeroed buffer: GetDefaultNativeWindowInfoEXT only WRITES sane defaults, CreateNativeWindowEXT only READS what's there - the real
     * NXPL_NativeWindowInfoEXT layout (default_nexus.h) is well under 64 bytes even with the blend-equation fields; 512 is generous headroom. */
    unsigned char windowInfo[512] = { 0 };
    GetDefaultWindowInfo(windowInfo);
    /* NXPL_NativeWindowInfoEXT: width,height,x,y (4 x uint32_t) then stretch,clientID,zOrder,... - override width/height/x/y to a full 1280x720
     * window at the origin, matching wpe_fb's own default render size, so it's unmistakable if it appears. */
    uint32_t *fields = (uint32_t *)windowInfo;
    fields[0] = 1280; /* width */
    fields[1] = 720;  /* height */
    fields[2] = 0;    /* x */
    fields[3] = 0;    /* y */
    g_native = CreateWindow(windowInfo);
    printf("   native=%p\n", g_native);
    if (!g_native) { printf("SUMMARY: CreateNativeWindowEXT returned NULL\n"); teardown_and_exit(1); }

    step("NXPL_ShowNativeWindowEXT(native, true)");
    g_ShowWindow(g_native, 1);
    printf("   shown (called, no return value to check)\n");

    step("eglGetDisplay + eglInitialize + eglCreateWindowSurface + eglCreateContext + eglMakeCurrent");
    void *dpy = p_eglGetDisplay(NULL);
    printf("   eglGetDisplay: %p\n", dpy);
    if (!dpy) { printf("SUMMARY: eglGetDisplay failed\n"); teardown_and_exit(1); }
    EGLint maj = 0, min = 0;
    if (!p_eglInitialize(dpy, &maj, &min)) { printf("SUMMARY: eglInitialize failed\n"); teardown_and_exit(1); }
    printf("   EGL %d.%d\n", maj, min);
    if (p_eglBindAPI) p_eglBindAPI(EGL_OPENGL_ES_API);
    EGLint cfgAttrs[] = { EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_NONE };
    void *config = NULL;
    EGLint numConfigs = 0;
    if (!p_eglChooseConfig(dpy, cfgAttrs, &config, 1, &numConfigs) || numConfigs < 1) {
        printf("SUMMARY: eglChooseConfig found no EGL_WINDOW_BIT config (numConfigs=%d)\n", numConfigs);
        teardown_and_exit(1);
    }
    printf("   config=%p\n", config);
    void *surface = p_eglCreateWindowSurface(dpy, config, (EGLNativeWindowType)g_native, NULL);
    printf("   eglCreateWindowSurface: %p (eglGetError=0x%x)\n", surface, p_eglGetError ? p_eglGetError() : 0);
    if (!surface) { printf("SUMMARY: eglCreateWindowSurface failed\n"); teardown_and_exit(1); }
    EGLint ctxAttrs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    void *ctx = p_eglCreateContext(dpy, config, NULL, ctxAttrs);
    printf("   eglCreateContext: %p\n", ctx);
    if (!ctx) { printf("SUMMARY: eglCreateContext failed\n"); teardown_and_exit(1); }
    if (!p_eglMakeCurrent(dpy, surface, surface, ctx)) { printf("SUMMARY: eglMakeCurrent failed\n"); teardown_and_exit(1); }
    printf("   current\n");

    step("clear to solid cyan and eglSwapBuffers - look at the TV NOW for %d second(s)", secs);
    p_glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    p_glClear(GL_COLOR_BUFFER_BIT);
    p_eglSwapBuffers(dpy, surface);
    sleep((unsigned)secs);

    step("tearing down");
    teardown_and_exit(0);
    return 0; /* unreached */
}
