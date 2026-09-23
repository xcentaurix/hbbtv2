/*
 * vu_egl_probe - what can this box's EGL/GLES do for WPE WebKit? Read-only: it draws nothing on the TV (offscreen only) and changes nothing.
 *
 * No vendor headers and no link-time dependency on the GPU libraries: libEGL.so.1 and libGLESv2.so.2 are loaded at run time, so the same binary runs on any
 * ARMv7 hard-float box and tells what it finds - and where it fails: every step is printed before it is done, a crash or a hang (SIGSEGV, SIGABRT, 20 s
 * alarm) prints the last step and ends the program cleanly.
 *
 * What the questions are for (HbbTV 2.0 = WPE WebKit + Open Red Button):
 *   - can a process other than enigma2 get an EGL display, a GLES context (surfaceless or on a pbuffer)?            WebKit's web process needs one
 *   - GLES version, extensions (BGRA read-back, EGL image/fence, ...)                                              Skia GPU rendering, fast read-back
 *   - does an FBO give correct colours (R/B) and how fast is glReadPixels of a frame, of a damaged rectangle        the frames of the page go from the GPU to the CPU
 *   - framebuffer /dev/fb0: size, pages, bits, colour layout                                                       the full-screen mode writes there
 *
 *   build (any ARMv7 hf cross compiler):  arm-...-gcc -Os -Wall vu_egl_probe.c -o vu_egl_probe -ldl -lm      (see build_vu_probe.sh)
 *   run:  ./vu_egl_probe          (vu_probe.sh runs it together with the system questions)
 */
#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <ucontext.h>
#include <unistd.h>

typedef void *EGLDisplay, *EGLConfig, *EGLContext, *EGLSurface;
typedef int EGLint;
typedef unsigned int GLenum, GLuint;
typedef int GLint, GLsizei;
typedef float GLfloat;

#define EGL_SURFACE_TYPE 0x3033
#define EGL_RENDERABLE_TYPE 0x3040
#define EGL_RED_SIZE 0x3024
#define EGL_GREEN_SIZE 0x3023
#define EGL_BLUE_SIZE 0x3022
#define EGL_ALPHA_SIZE 0x3021
#define EGL_NONE 0x3038
#define EGL_PBUFFER_BIT 1
#define EGL_PIXMAP_BIT 2
#define EGL_WINDOW_BIT 4
#define EGL_OPENGL_ES2_BIT 4
#define EGL_OPENGL_ES3_BIT 0x40
#define EGL_OPENGL_ES_API 0x30A0
#define EGL_CONTEXT_CLIENT_VERSION 0x3098
#define EGL_WIDTH 0x3057
#define EGL_HEIGHT 0x3056
#define EGL_VENDOR 0x3053
#define EGL_VERSION 0x3054
#define EGL_EXTENSIONS 0x3055
#define EGL_CLIENT_APIS 0x308D
#define EGL_PLATFORM_GBM_KHR 0x31D7
#define EGL_PLATFORM_SURFACELESS_MESA 0x31DD

#define GL_VENDOR 0x1F00
#define GL_RENDERER 0x1F01
#define GL_VERSION 0x1F02
#define GL_EXTENSIONS 0x1F03
#define GL_SHADING_LANGUAGE_VERSION 0x8B8C
#define GL_MAX_TEXTURE_SIZE 0x0D33
#define GL_TEXTURE_2D 0x0DE1
#define GL_RGBA 0x1908
#define GL_BGRA_EXT 0x80E1
#define GL_UNSIGNED_BYTE 0x1401
#define GL_FRAMEBUFFER 0x8D40
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_COLOR_BUFFER_BIT 0x4000
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_FLOAT 0x1406
#define GL_TRIANGLE_STRIP 5
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A

static EGLDisplay (*eglGetDisplay)(void *);
static EGLDisplay (*eglGetPlatformDisplayEXT)(GLenum, void *, const EGLint *);
static EGLDisplay (*eglGetPlatformDisplay)(GLenum, void *, const EGLint *); /* EGL 1.5 core, no "EXT" suffix */
static void *(*eglGetProcAddress)(const char *);
static int (*eglInitialize)(EGLDisplay, EGLint *, EGLint *);
static const char *(*eglQueryString)(EGLDisplay, EGLint);
static int (*eglGetConfigs)(EGLDisplay, EGLConfig *, EGLint, EGLint *);
static int (*eglGetConfigAttrib)(EGLDisplay, EGLConfig, EGLint, EGLint *);
static int (*eglBindAPI)(GLenum);
static EGLContext (*eglCreateContext)(EGLDisplay, EGLConfig, EGLContext, const EGLint *);
static int (*eglMakeCurrent)(EGLDisplay, EGLSurface, EGLSurface, EGLContext);
static EGLSurface (*eglCreatePbufferSurface)(EGLDisplay, EGLConfig, const EGLint *);
static EGLint (*eglGetError)(void);
static int (*eglTerminate)(EGLDisplay);

static const unsigned char *(*glGetString)(GLenum);
static void (*glGetIntegerv)(GLenum, GLint *);
static GLenum (*glGetError)(void);
static void (*glGenTextures)(GLsizei, GLuint *);
static void (*glBindTexture)(GLenum, GLuint);
static void (*glTexImage2D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
static void (*glGenFramebuffers)(GLsizei, GLuint *);
static void (*glBindFramebuffer)(GLenum, GLuint);
static void (*glFramebufferTexture2D)(GLenum, GLenum, GLenum, GLuint, GLint);
static GLenum (*glCheckFramebufferStatus)(GLenum);
static void (*glClearColor)(GLfloat, GLfloat, GLfloat, GLfloat);
static void (*glClear)(GLuint);
static void (*glReadPixels)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *);
static void (*glFinish)(void);
static GLuint (*glCreateShader)(GLenum);
static void (*glShaderSource)(GLuint, GLsizei, const char *const *, const GLint *);
static void (*glCompileShader)(GLuint);
static GLuint (*glCreateProgram)(void);
static void (*glAttachShader)(GLuint, GLuint);
static void (*glBindAttribLocation)(GLuint, GLuint, const char *);
static void (*glLinkProgram)(GLuint);
static void (*glUseProgram)(GLuint);
static void (*glViewport)(GLint, GLint, GLsizei, GLsizei);
static void (*glEnableVertexAttribArray)(GLuint);
static void (*glVertexAttribPointer)(GLuint, GLint, GLenum, unsigned char, GLsizei, const void *);
static void (*glDrawArrays)(GLenum, GLint, GLsizei);

static const char *step_name = "start";
static char step_buf[200];

static int try_display_strategies(void);
static void try_register_display_platform(void);

static void step(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
static void step(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(step_buf, sizeof step_buf, fmt, ap);
    va_end(ap);
    step_name = step_buf;
    printf(">> %s\n", step_buf);
    fflush(stdout);
}

/* SA_SIGINFO variant: on SIGSEGV/SIGBUS/SIGILL, ucontext_t carries the ARM registers at the moment of the fault (Linux ARM's mcontext_t = struct
 * sigcontext, arm_* fields). This is the same information a debugger's "info registers" gives after a crash, without needing a debugger attached -
 * useful here because these reports come from a team member's box, not one this session has direct access to. */
static void on_signal(int sig, siginfo_t *info, void *context)
{
    printf("\n!! signal %d (%s) during: %s\n", sig, sig == SIGALRM ? "no answer within 20 s" : sig == SIGSEGV ? "crash (SIGSEGV)" :
        sig == SIGBUS ? "crash (SIGBUS)" : sig == SIGILL ? "crash (SIGILL)" : "abort", step_name);
#if defined(__arm__) && defined(__linux__)
    if (context && (sig == SIGSEGV || sig == SIGBUS || sig == SIGILL)) {
        ucontext_t *uc = (ucontext_t *)context;
        struct sigcontext *mc = (struct sigcontext *)&uc->uc_mcontext;
        printf("   fault address: %p\n", info ? info->si_addr : NULL);
        printf("   pc=%08lx lr=%08lx sp=%08lx cpsr=%08lx\n", mc->arm_pc, mc->arm_lr, mc->arm_sp, mc->arm_cpsr);
        printf("   r0=%08lx r1=%08lx r2=%08lx r3=%08lx r4=%08lx r5=%08lx\n", mc->arm_r0, mc->arm_r1, mc->arm_r2, mc->arm_r3, mc->arm_r4, mc->arm_r5);
        printf("   r6=%08lx r7=%08lx r8=%08lx r9=%08lx r10=%08lx fp=%08lx ip=%08lx\n", mc->arm_r6, mc->arm_r7, mc->arm_r8, mc->arm_r9, mc->arm_r10,
            mc->arm_fp, mc->arm_ip);
    }
#else
    (void)info;
    (void)context;
#endif
    printf("SUMMARY: FAILED at '%s'\n", step_name);
    fflush(stdout);
    _exit(10);
}

static void install_signal_handlers(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_sigaction = on_signal;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGBUS, &sa, NULL);
    sigaction(SIGILL, &sa, NULL);
    sigaction(SIGABRT, &sa, NULL);
    sigaction(SIGALRM, &sa, NULL);
}

static double now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

#define LOAD(lib, name) \
    do { \
        *(void **)&name = dlsym(lib, #name); \
        if (!name && eglGetProcAddress) \
            *(void **)&name = eglGetProcAddress(#name); \
        if (!name) { \
            printf("   (missing: %s)\n", #name); \
            missing++; \
        } \
    } while (0)

static void has(const char *label, const char *list, const char *const want[])
{
    printf("%s:\n", label);
    for (int i = 0; want[i]; i++)
        printf("   %-40s %s\n", want[i], list && strstr(list, want[i]) ? "yes" : "no");
}

static void framebuffer(void)
{
    step("framebuffer /dev/fb0");
    int fd = open("/dev/fb0", O_RDONLY);
    if (fd < 0) {
        printf("   cannot open /dev/fb0\n");
        return;
    }
    unsigned var[40] = { 0 };
    unsigned char fix[96] = { 0 };
    if (ioctl(fd, 0x4600, var) == 0) { /* FBIOGET_VSCREENINFO */
        printf("   FB %ux%u, virtual %ux%u (%u pages), yoffset %u, %u bpp\n", var[0], var[1], var[2], var[3], var[1] ? var[3] / var[1] : 0, var[5], var[6]);
        printf("   FB layout (offset/length): red %u/%u  green %u/%u  blue %u/%u  alpha %u/%u\n", var[8], var[9], var[11], var[12], var[14], var[15], var[17], var[18]);
        printf("   FB %s\n", var[8] == 16 && var[11] == 8 && var[14] == 0 && var[17] == 24 ? "is ARGB8888 (B in the lowest byte)"
            : var[8] == 0 && var[11] == 8 && var[14] == 16 ? "is ABGR8888 / RGBA (R in the lowest byte)" : "has another layout");
    } else
        printf("   FBIOGET_VSCREENINFO failed\n");
    if (ioctl(fd, 0x4602, fix) == 0) /* FBIOGET_FSCREENINFO: id[16], smem_start, smem_len, ..., line_length at 44 */
        printf("   FB id '%.16s', smem_len %u, line_length %u\n", fix, *(unsigned *)(fix + 20), *(unsigned *)(fix + 44));
    void *m = mmap(NULL, 4096, PROT_READ, MAP_SHARED, fd, 0);
    printf("   mmap of the framebuffer: %s\n", m == MAP_FAILED ? "FAILED" : "ok");
    if (m != MAP_FAILED)
        munmap(m, 4096);
    close(fd);
}

static const char *vs_src = "attribute vec2 p; varying vec2 uv; void main(){ uv=p*0.5+0.5; gl_Position=vec4(p,0.0,1.0);}";
static const char *fs_src = "precision mediump float; varying vec2 uv; uniform float t; void main(){ gl_FragColor=vec4(uv.x, uv.y, 0.25, 1.0);}";

static void readback(int has_bgra)
{
    enum { W = 1280, H = 720, ITER = 6 };
    GLuint tex = 0, fbo = 0;
    step("FBO %dx%d for the read-back test", W, H);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("   FBO %dx%d not complete\n", W, H);
        return;
    }
    step("shader and quad");
    GLuint vs = glCreateShader(GL_VERTEX_SHADER), fs = glCreateShader(GL_FRAGMENT_SHADER), pr = glCreateProgram();
    glShaderSource(vs, 1, &vs_src, NULL);
    glCompileShader(vs);
    glShaderSource(fs, 1, &fs_src, NULL);
    glCompileShader(fs);
    glAttachShader(pr, vs);
    glAttachShader(pr, fs);
    glBindAttribLocation(pr, 0, "p");
    glLinkProgram(pr);
    static const GLfloat quad[] = { -1, -1, 1, -1, -1, 1, 1, 1 };
    unsigned char *buf = malloc((size_t)W * H * 4);
    double draw = 0, full = 0, part = 0, fullbgra = 0;
    for (int i = 0; i < ITER; i++) {
        double t0 = now_ms();
        glViewport(0, 0, W, H);
        glUseProgram(pr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, quad);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glFinish();
        double t1 = now_ms();
        step("glReadPixels %dx%d RGBA", W, H);
        glReadPixels(0, 0, W, H, GL_RGBA, GL_UNSIGNED_BYTE, buf);
        double t2 = now_ms();
        step("glReadPixels 256x128 RGBA");
        glReadPixels(100, 100, 256, 128, GL_RGBA, GL_UNSIGNED_BYTE, buf);
        double t3 = now_ms();
        double t4 = t3;
        if (has_bgra) {
            step("glReadPixels %dx%d BGRA", W, H);
            glReadPixels(0, 0, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, buf);
            t4 = now_ms();
        }
        if (i) { /* the first pass warms up */
            draw += t1 - t0;
            full += t2 - t1;
            part += t3 - t2;
            fullbgra += t4 - t3;
        }
    }
    int n = ITER - 1;
    printf("   draw + finish of a full-frame quad : %6.1f ms\n", draw / n);
    printf("   glReadPixels 1280x720 RGBA         : %6.1f ms  (%.1f MB/s, max %.1f fps)\n", full / n, W * H * 4 / 1e6 / (full / n / 1000), 1000 / (full / n));
    printf("   glReadPixels 256x128 RGBA (damage) : %6.1f ms  (%.1f MB/s)\n", part / n, 256 * 128 * 4 / 1e6 / (part / n / 1000));
    if (has_bgra)
        printf("   glReadPixels 1280x720 BGRA         : %6.1f ms  (%.1f MB/s, max %.1f fps)\n", fullbgra / n, W * H * 4 / 1e6 / (fullbgra / n / 1000), 1000 / (fullbgra / n));
    printf("READBACK_MS_FULL %.1f\n", full / n);
    free(buf);
}

/* eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS) - querying "client extensions" before any display exists - is legal EGL 1.5 / EGL_EXT_client_extensions,
 * and is what an EGL_EXT_platform_base-style display chooser (the pattern WPE's platform code can use) calls first. On some vendor drivers it crashes
 * instead of returning NULL. It is not needed for anything above (eglGetDisplay(EGL_DEFAULT_DISPLAY) does not need it), so it is tried last, in a forked
 * child: if the vendor driver crashes here, the report above - the part that matters - is already complete and on disk. */
static void try_client_extensions(void)
{
    step("eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS) - tried last, in a child process (see the comment in the source)");
    alarm(10); /* fresh headroom for this step: the parent's original 20 s budget may be mostly spent by now, and it must survive waitpid() below */
    fflush(stdout);
    pid_t pid = fork();
    if (pid < 0) {
        printf("   (fork failed: %s)\n", strerror(errno));
        return;
    }
    if (pid == 0) {
        alarm(5);
        const char *client = eglQueryString(NULL, EGL_EXTENSIONS);
        printf("   client extensions: %s\n", client ? client : "(none / query failed)");
        fflush(stdout);
        _exit(0);
    }
    int status = 0;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status))
        printf("   client extensions: CRASHED (signal %d) - this vendor EGL needs a real display before it can be asked about extensions\n", WTERMSIG(status));
    else if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
        printf("   client extensions: query did not complete normally (status 0x%x)\n", status);
}

/* Opt-in only (env TRY_REGISTER_DISPLAY=1) - everything above this point is read-only or a standard, non-disruptive IPC handshake (NxClient_Join).
 * default_nexus.h (see hbbtv2/headers/gb-nexus-headers/) declares:
 *   NXPL_EXPORT void NXPL_RegisterNexusDisplayPlatform(NXPL_PlatformHandle *handle, NEXUS_DISPLAYHANDLE display);
 *   "Register a display for exclusive use. The client application should not use the display until calling
 *    NXPL_UnregisterNexusDisplayPlatform. It will register its own memory, h/w and display APIs suitable for basic
 *    exclusive mode rendering on a Nexus display."
 * "register its own memory ... APIs" matches "Memory interface not registered" (gmem_abstract.c:132) exactly - this is very likely the actual fix -
 * but "exclusive use" is a materially different kind of risk than anything tried so far: it could plausibly affect enigma2's live OSD while held,
 * not just cost a GPU client slot. So, unlike every other step in this file, it does not run unless explicitly asked for. In client (multi-process)
 * mode NEXUS_DISPLAYHANDLE is just void* (see default_nexus.h's #else branch), not a real handle from NEXUS_Display_Open (that call is
 * single-process-only) - NULL is the simplest, most conservative first try. Runs register -> eglGetDisplay -> eglInitialize -> unregister all in
 * one short-lived forked child, to keep any window where the display is "exclusive" as brief as possible; a crash here is caught exactly like
 * every other step (SA_SIGINFO register dump, does not stop the rest of the report) - the fork is still useful even with nothing else after it. */
static void try_register_display_platform(void)
{
    const char *opt = getenv("TRY_REGISTER_DISPLAY");
    if (!opt || strcmp(opt, "1") != 0) {
        step("NXPL_RegisterNexusDisplayPlatform - SKIPPED (opt-in only: set TRY_REGISTER_DISPLAY=1 to try it)");
        printf("   default_nexus.h: 'Register a display for exclusive use ... registers its own memory, h/w and display APIs' - looks like the\n");
        printf("   actual fix for 'Memory interface not registered', but 'exclusive use' means it could plausibly affect enigma2's live OSD while\n");
        printf("   held, unlike every read-only/join-only step tried so far - opt-in deliberately, run only when a brief OSD hiccup is acceptable.\n");
        return;
    }
    step("NXPL_RegisterNexusDisplayPlatform (libnxpl.so) - TRY_REGISTER_DISPLAY=1 set: attempting the real fix for 'Memory interface not registered'");
    printf("   default_nexus.h: NXPL_RegisterNexusDisplayPlatform(NXPL_PlatformHandle *handle, NEXUS_DISPLAYHANDLE display) - 'exclusive use',\n");
    printf("   registers memory/h+w/display APIs for a Nexus display. Client mode: NEXUS_DISPLAYHANDLE is void* - trying NULL.\n");
    printf("   register -> eglGetDisplay -> eglInitialize -> unregister, all in one short-lived forked child.\n");
    alarm(15);
    fflush(stdout);
    pid_t pid = fork();
    if (pid < 0) {
        printf("   (fork failed: %s)\n", strerror(errno));
        return;
    }
    if (pid == 0) {
        alarm(10);
        void *nxpl = dlopen("libnxpl.so", RTLD_NOW | RTLD_GLOBAL);
        if (!nxpl) {
            printf("   dlopen(\"libnxpl.so\"): %s\n", dlerror());
            fflush(stdout);
            _exit(2);
        }
        void (*Register)(void **, void *) = (void (*)(void **, void *))dlsym(nxpl, "NXPL_RegisterNexusDisplayPlatform");
        void (*Unregister)(void *) = (void (*)(void *))dlsym(nxpl, "NXPL_UnregisterNexusDisplayPlatform");
        printf("   NXPL_RegisterNexusDisplayPlatform: %s, NXPL_UnregisterNexusDisplayPlatform: %s\n",
               Register ? "found" : "not found", Unregister ? "found" : "not found");
        if (!Register || !Unregister) {
            fflush(stdout);
            _exit(2);
        }
        void *handle = NULL;
        printf("   calling NXPL_RegisterNexusDisplayPlatform(&handle, NULL)...\n");
        fflush(stdout);
        Register(&handle, NULL);
        printf("   returned, handle=%p\n", handle);
        fflush(stdout);

        EGLDisplay dpy = eglGetDisplay(NULL);
        printf("   eglGetDisplay(EGL_DEFAULT_DISPLAY): %p\n", dpy);
        fflush(stdout);
        int ok = 0;
        if (dpy) {
            EGLint maj = 0, min = 0;
            printf("   calling eglInitialize...\n");
            fflush(stdout);
            ok = eglInitialize(dpy, &maj, &min);
            printf("   eglInitialize: %s (EGL %d.%d)\n", ok ? "SUCCESS" : "failed", maj, min);
        }
        fflush(stdout);
        printf("   calling NXPL_UnregisterNexusDisplayPlatform(handle)...\n");
        fflush(stdout);
        Unregister(handle);
        printf("   unregistered\n");
        fflush(stdout);
        _exit(ok ? 0 : 1);
    }
    int status = 0;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status))
        printf("   SUMMARY: CRASHED (signal %d) during the register/init/unregister sequence\n", WTERMSIG(status));
    else if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        printf("   SUMMARY: eglInitialize SUCCEEDED after NXPL_RegisterNexusDisplayPlatform(NULL) - this is very likely the actual fix\n");
    else
        printf("   SUMMARY: did not succeed (exit code %d)\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
}

int main(void)
{
    int missing = 0;
    setvbuf(stdout, NULL, _IOLBF, 0);
    install_signal_handlers();
    alarm(20);

    framebuffer();

    /* On the DM900 and a VU+ Ultimo, libEGL.so(.1)/libGLESv2.so(.2) are themselves just symlinks to the vendor GPU driver .so - the EGL/GLES symbols
     * live in that file. Some Nexus-based Broadcom images (GigaBlue) have no libEGL.so at all; try the driver .so itself, and a Nexus Platform Layer
     * shim, as fallbacks. Every name that resolves is reported, so which one actually worked is visible in a partial/failed run too. */
    static const char *const egl_names[] = { "libEGL.so.1", "libEGL.so", "libv3ddriver.so", "libnxpl.so", NULL };
    static const char *const gles_names[] = { "libGLESv2.so.2", "libGLESv2.so", "libv3ddriver.so", "libnxpl.so", NULL };
    step("dlopen libEGL (or a driver library that provides it)");
    void *egl = NULL;
    for (int i = 0; egl_names[i] && !egl; i++) {
        egl = dlopen(egl_names[i], RTLD_NOW | RTLD_GLOBAL);
        printf("   dlopen(\"%s\"): %s\n", egl_names[i], egl ? "ok" : dlerror());
    }
    if (!egl) {
        printf("SUMMARY: no EGL library found under any of the usual names\n");
        return 1;
    }
    step("dlopen libGLESv2 (or a driver library that provides it)");
    void *gles = NULL;
    for (int i = 0; gles_names[i] && !gles; i++) {
        gles = dlopen(gles_names[i], RTLD_NOW | RTLD_GLOBAL);
        printf("   dlopen(\"%s\"): %s\n", gles_names[i], gles ? "ok" : dlerror());
    }
    if (!gles) {
        printf("SUMMARY: no GLESv2 library found under any of the usual names\n");
        return 1;
    }
    *(void **)&eglGetProcAddress = dlsym(egl, "eglGetProcAddress");
    LOAD(egl, eglGetDisplay);
    LOAD(egl, eglInitialize);
    LOAD(egl, eglQueryString);
    LOAD(egl, eglGetConfigs);
    LOAD(egl, eglGetConfigAttrib);
    LOAD(egl, eglBindAPI);
    LOAD(egl, eglCreateContext);
    LOAD(egl, eglMakeCurrent);
    LOAD(egl, eglCreatePbufferSurface);
    LOAD(egl, eglGetError);
    LOAD(egl, eglTerminate);
    *(void **)&eglGetPlatformDisplayEXT = eglGetProcAddress ? eglGetProcAddress("eglGetPlatformDisplayEXT") : NULL;
    *(void **)&eglGetPlatformDisplay = dlsym(egl, "eglGetPlatformDisplay");
    if (!eglGetPlatformDisplay && eglGetProcAddress)
        *(void **)&eglGetPlatformDisplay = eglGetProcAddress("eglGetPlatformDisplay");
    LOAD(gles, glGetString);
    LOAD(gles, glGetIntegerv);
    LOAD(gles, glGetError);
    LOAD(gles, glGenTextures);
    LOAD(gles, glBindTexture);
    LOAD(gles, glTexImage2D);
    LOAD(gles, glGenFramebuffers);
    LOAD(gles, glBindFramebuffer);
    LOAD(gles, glFramebufferTexture2D);
    LOAD(gles, glCheckFramebufferStatus);
    LOAD(gles, glClearColor);
    LOAD(gles, glClear);
    LOAD(gles, glReadPixels);
    LOAD(gles, glFinish);
    LOAD(gles, glCreateShader);
    LOAD(gles, glShaderSource);
    LOAD(gles, glCompileShader);
    LOAD(gles, glCreateProgram);
    LOAD(gles, glAttachShader);
    LOAD(gles, glBindAttribLocation);
    LOAD(gles, glLinkProgram);
    LOAD(gles, glUseProgram);
    LOAD(gles, glViewport);
    LOAD(gles, glEnableVertexAttribArray);
    LOAD(gles, glVertexAttribPointer);
    LOAD(gles, glDrawArrays);
    if (missing) {
        printf("SUMMARY: %d entry points missing\n", missing);
        return 1;
    }

    step("eglGetPlatformDisplayEXT / eglGetPlatformDisplay (symbols only, not called yet)");
    printf("   eglGetPlatformDisplayEXT: %s\n", eglGetPlatformDisplayEXT ? "available" : "not available");
    printf("   eglGetPlatformDisplay (EGL 1.5 core): %s\n", eglGetPlatformDisplay ? "available" : "not available");

    /* Nexus-based Broadcom boxes (GigaBlue confirmed 2026-09-22: eglInitialize asserts "Memory interface not registered" at
     * libs/platform/bcg_abstract/gmem_abstract.c:132:gmem_init) require a process to join Nexus - NxClient_Join(), from libnxclient.so - before
     * touching EGL at all; see hbbtv2/headers/gb-nexus-headers/nxclient.h. Try it here, before any EGL call, so this run can show directly whether
     * it fixes eglInitialize. Harmless no-op on boxes without libnxclient.so (e.g. dm900/libvc5dream, plain VU+ libv3ddriver-only images). No Nexus
     * SDK headers at build time: NxClient_JoinSettings' exact layout is unknown here, so an oversized zeroed buffer is used instead of the real
     * struct - NxClient_GetDefaultJoinSettings only WRITES into it and NxClient_Join only reads back what was just written, so this is safe as
     * long as the buffer is at least as large as the real struct (1024 bytes is generous; the real struct is roughly name[32]+a few ints+a
     * certificate, well under 200 bytes in known Broadcom SDKs). */
    step("NxClient_Join (libnxclient.so) - the Nexus client-join step other Nexus-based boxes needed before EGL would work");
    void *nxclient = dlopen("libnxclient.so", RTLD_NOW | RTLD_GLOBAL);
    printf("   dlopen(\"libnxclient.so\"): %s\n", nxclient ? "ok" : dlerror());
    if (nxclient) {
        void (*NxClient_GetDefaultJoinSettings)(void *) = dlsym(nxclient, "NxClient_GetDefaultJoinSettings");
        int (*NxClient_Join)(const void *) = dlsym(nxclient, "NxClient_Join");
        printf("   NxClient_GetDefaultJoinSettings: %s, NxClient_Join: %s\n",
               NxClient_GetDefaultJoinSettings ? "found" : "not found",
               NxClient_Join ? "found" : "not found");
        if (NxClient_GetDefaultJoinSettings && NxClient_Join) {
            static unsigned char join_settings[1024];
            memset(join_settings, 0, sizeof(join_settings));
            NxClient_GetDefaultJoinSettings(join_settings);
            int rc = NxClient_Join(join_settings);
            printf("   NxClient_Join() returned %d (0 = NEXUS_SUCCESS on this platform's convention)\n", rc);
        } else {
            printf("   libnxclient.so found but missing expected symbols - skipping join attempt\n");
        }
    } else {
        printf("   no libnxclient.so on this box - skipping (expected on non-Nexus platforms, e.g. dm900/libvc5dream)\n");
    }

    try_register_display_platform();

    return try_display_strategies();
}

/* How to get *some* EGLDisplay differs enough across vendor EGL implementations (and at least one - VU+ Ultimo 4K, 2026-09-22 report - crashes
 * outright inside eglInitialize(eglGetDisplay(EGL_DEFAULT_DISPLAY), ...) with no diagnostic) that trying only the one conventional way and giving up
 * on a crash wastes a whole report round-trip through a team member's box. Each strategy below runs in its own forked child: a crash in one (caught by
 * the SA_SIGINFO handler above, with a register dump) does not stop the next strategy from being tried, and the first strategy that gets all the way
 * through the probe keeps running normally (configs, context, read-back) inside that same child, so its output is the full report. */
struct display_strategy {
    const char *label;
    int kind; /* 0 = eglGetDisplay(EGL_DEFAULT_DISPLAY); 1 = eglGetDisplay(native=1) - some non-compliant vendor EGLs do not accept NULL as "default";
                 2/3 = eglGetPlatformDisplay(EGL_PLATFORM_GBM_KHR / EGL_PLATFORM_SURFACELESS_MESA, NULL, NULL) - only tried if the symbol resolved */
};

static EGLDisplay acquire_display(const struct display_strategy *s)
{
    switch (s->kind) {
    case 0: return eglGetDisplay(NULL);
    case 1: return eglGetDisplay((void *)1);
    case 2: return eglGetPlatformDisplay ? eglGetPlatformDisplay(EGL_PLATFORM_GBM_KHR, NULL, NULL) : NULL;
    case 3: return eglGetPlatformDisplay ? eglGetPlatformDisplay(EGL_PLATFORM_SURFACELESS_MESA, NULL, NULL) : NULL;
    }
    return NULL;
}

static int run_probe_with_display(const char *label, EGLDisplay dpy)
{
    step("eglInitialize (%s)", label);
    EGLint maj = 0, min = 0;
    if (!eglInitialize(dpy, &maj, &min)) {
        printf("   eglInitialize FAILED 0x%x\nSUMMARY: eglInitialize failed (%s)\n", eglGetError(), label);
        return 3;
    }
    printf("   EGL %d.%d, vendor '%s', version '%s', client APIs '%s'\n", maj, min, eglQueryString(dpy, EGL_VENDOR), eglQueryString(dpy, EGL_VERSION),
        eglQueryString(dpy, EGL_CLIENT_APIS));
    const char *dext = eglQueryString(dpy, EGL_EXTENSIONS);
    printf("   display extensions: %s\n", dext ? dext : "(none)");
    const char *const want[] = { "EGL_KHR_surfaceless_context", "EGL_KHR_create_context", "EGL_KHR_image_base", "EGL_KHR_gl_texture_2D_image",
        "EGL_KHR_fence_sync", "EGL_EXT_image_dma_buf_import", "EGL_KHR_platform_gbm", "EGL_MESA_platform_surfaceless", "EGL_EXT_platform_base",
        "EGL_KHR_no_config_context", "EGL_ANDROID_native_fence_sync", "EGL_KHR_wait_sync", NULL };
    has("wanted display extensions", dext, want);

    step("eglGetConfigs");
    EGLint n = 0;
    eglGetConfigs(dpy, NULL, 0, &n);
    EGLConfig cfgs[256];
    if (n > 256)
        n = 256;
    eglGetConfigs(dpy, cfgs, n, &n);
    int pb = 0, win = 0, pix = 0, es2 = 0, es3 = 0;
    EGLConfig pick = NULL;
    for (int i = 0; i < n; i++) {
        EGLint st = 0, rt = 0, r = 0, g = 0, b = 0, a = 0;
        eglGetConfigAttrib(dpy, cfgs[i], EGL_SURFACE_TYPE, &st);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_RENDERABLE_TYPE, &rt);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_RED_SIZE, &r);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_GREEN_SIZE, &g);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_BLUE_SIZE, &b);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_ALPHA_SIZE, &a);
        pb += !!(st & EGL_PBUFFER_BIT);
        win += !!(st & EGL_WINDOW_BIT);
        pix += !!(st & EGL_PIXMAP_BIT);
        es2 += !!(rt & EGL_OPENGL_ES2_BIT);
        es3 += !!(rt & EGL_OPENGL_ES3_BIT);
        if ((rt & EGL_OPENGL_ES2_BIT) && !pick && (st & EGL_PBUFFER_BIT) && a > 0)
            pick = cfgs[i];
        if (i < 8)
            printf("   cfg%-2d %d%d%d%d surface=%s%s%s gles2=%d gles3=%d\n", i, r, g, b, a, (st & EGL_WINDOW_BIT) ? "W" : "", (st & EGL_PBUFFER_BIT) ? "B" : "",
                (st & EGL_PIXMAP_BIT) ? "P" : "", !!(rt & EGL_OPENGL_ES2_BIT), !!(rt & EGL_OPENGL_ES3_BIT));
    }
    printf("   %d configs: window %d, pbuffer %d, pixmap %d, gles2 %d, gles3 %d\n", n, win, pb, pix, es2, es3);
    if (!pick) {
        for (int i = 0; i < n; i++) {
            EGLint rt = 0;
            eglGetConfigAttrib(dpy, cfgs[i], EGL_RENDERABLE_TYPE, &rt);
            if (rt & EGL_OPENGL_ES2_BIT) {
                pick = cfgs[i];
                break;
            }
        }
        printf("   (no ES2 pbuffer config with alpha: the first ES2 config is used)\n");
    }
    if (!pick) {
        printf("SUMMARY: no GLES2 config\n");
        return 4;
    }

    step("eglBindAPI(ES) and eglCreateContext (ES 3, else ES 2)");
    eglBindAPI(EGL_OPENGL_ES_API);
    int version = 3;
    EGLint ctxattr[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    EGLContext ctx = eglCreateContext(dpy, pick, NULL, ctxattr);
    if (!ctx) {
        printf("   ES 3 context: no (error 0x%x)\n", eglGetError());
        ctxattr[1] = 2;
        version = 2;
        ctx = eglCreateContext(dpy, pick, NULL, ctxattr);
    }
    printf("   context %p (GLES %d)\n", ctx, ctx ? version : 0);
    if (!ctx) {
        printf("SUMMARY: no GLES context (error 0x%x)\n", eglGetError());
        return 5;
    }

    step("eglMakeCurrent without a surface");
    int surfaceless = eglMakeCurrent(dpy, NULL, NULL, ctx);
    printf("   surfaceless make-current: %s (error 0x%x)\n", surfaceless ? "WORKS" : "no", surfaceless ? 0 : eglGetError());
    int pbok = 0;
    if (pb) {
        step("eglCreatePbufferSurface and eglMakeCurrent");
        const EGLint pbattr[] = { EGL_WIDTH, 64, EGL_HEIGHT, 64, EGL_NONE };
        EGLSurface pbs = eglCreatePbufferSurface(dpy, pick, pbattr);
        printf("   pbuffer surface %p (error 0x%x)\n", pbs, pbs ? 0 : eglGetError());
        if (pbs) {
            pbok = eglMakeCurrent(dpy, pbs, pbs, ctx);
            printf("   pbuffer make-current: %s\n", pbok ? "WORKS" : "no");
        }
    }
    if (!surfaceless && !pbok) {
        printf("SUMMARY: display and context, but nothing to make current on (surfaceless %d, pbuffer %d)\n", surfaceless, pbok);
        return 6;
    }

    step("glGetString");
    printf("   GL_VENDOR    %s\n   GL_RENDERER  %s\n   GL_VERSION   %s\n   GLSL         %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER),
        glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    const char *gext = (const char *)glGetString(GL_EXTENSIONS);
    printf("   GL extensions: %s\n", gext ? gext : "(none)");
    GLint maxtex = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxtex);
    printf("   GL_MAX_TEXTURE_SIZE %d\n", maxtex);
    const char *const gwant[] = { "GL_EXT_read_format_bgra", "GL_EXT_texture_format_BGRA8888", "GL_OES_EGL_image", "GL_OES_EGL_image_external",
        "GL_EXT_unpack_subimage", "GL_EXT_texture_rg", "GL_OES_rgb8_rgba8", "GL_OES_packed_depth_stencil", "GL_EXT_discard_framebuffer", NULL };
    has("wanted GL extensions", gext, gwant);
    int has_bgra = gext && strstr(gext, "GL_EXT_read_format_bgra");

    step("FBO with a red clear, read back");
    GLuint tex = 0, fbo = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
    int colours = 0;
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        unsigned char px[4] = { 0 };
        glReadPixels(32, 32, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);
        colours = px[0] == 255 && px[1] == 0 && px[2] == 0;
        printf("   red clear, glReadPixels(RGBA) -> %02x %02x %02x %02x   %s\n", px[0], px[1], px[2], px[3], colours ? "correct" : "R/B SWAPPED or wrong");
        GLint rf = 0, rtp = 0;
        glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT, &rf);
        glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_TYPE, &rtp);
        printf("   the implementation's preferred read format 0x%x type 0x%x (0x1908 RGBA / 0x80e1 BGRA, 0x1401 UNSIGNED_BYTE)\n", rf, rtp);
    } else
        printf("   FBO not complete\n");

    readback(has_bgra != 0);

    try_client_extensions();

    step("done");
    printf("SUMMARY: OK (%s)  GLES %d  surfaceless=%d pbuffer=%d colours=%s  window-configs=%d\n", label, version, surfaceless, pbok,
        colours ? "ok" : "WRONG", win);
    eglMakeCurrent(dpy, NULL, NULL, NULL);
    eglTerminate(dpy);
    return 0;
}

static int try_display_strategies(void)
{
    static const struct display_strategy strategies[] = {
        { "eglGetDisplay(EGL_DEFAULT_DISPLAY)", 0 },
        { "eglGetDisplay(native=1)", 1 },
        { "eglGetPlatformDisplay(EGL_PLATFORM_GBM_KHR)", 2 },
        { "eglGetPlatformDisplay(EGL_PLATFORM_SURFACELESS_MESA)", 3 },
    };
    alarm(90); /* replaces the top-level alarm(20): up to 4 isolated attempts follow, each with its own child-local alarm(15) */
    for (size_t i = 0; i < sizeof strategies / sizeof *strategies; i++) {
        if (strategies[i].kind >= 2 && !eglGetPlatformDisplay) {
            step("skipping display strategy: %s (symbol not available)", strategies[i].label);
            continue;
        }
        step("trying display strategy: %s", strategies[i].label);
        fflush(stdout);
        pid_t pid = fork();
        if (pid < 0) {
            printf("   (fork failed: %s)\n", strerror(errno));
            continue;
        }
        if (pid == 0) {
            alarm(15);
            EGLDisplay dpy = acquire_display(&strategies[i]);
            printf("   display %p\n", dpy);
            if (!dpy) {
                printf("   no display from this strategy\n");
                _exit(2);
            }
            _exit(run_probe_with_display(strategies[i].label, dpy));
        }
        int status = 0;
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status))
            printf("   strategy '%s': the child was killed by signal %d (see the register dump above)\n", strategies[i].label, WTERMSIG(status));
        else if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            printf("   strategy '%s': SUCCEEDED - see the full report above\n", strategies[i].label);
            return 0;
        } else
            printf("   strategy '%s': did not succeed (exit code %d)\n", strategies[i].label, WIFEXITED(status) ? WEXITSTATUS(status) : -1);
    }
    try_client_extensions();
    printf("SUMMARY: no display strategy worked on this box\n");
    return 3;
}
