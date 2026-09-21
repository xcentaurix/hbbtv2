/* pixmap_bench: spike S1 (docs/performance-plan.txt): can a rendered frame reach the CPU much faster than glReadPixels (13.7 MB/s) on the
 * Dreambox vendor EGL (VideoCore V / V3D-530, libvc5dream)?
 *
 * The driver renders natively into "pixmap" surfaces described by a struct dmegl_pixmap_handle (EGL/dreameglplatform.h): memory the caller
 * provides (phys address + a CPU mapping). enigma2's gEGLDC does exactly that with the framebuffer pages. Here the memory comes from ION
 * (the BMEM heap enigma2 uses for its accelerator surfaces), so the CPU can read what the GPU drew without glReadPixels.
 *
 *   1  raw CPU speed of the ION mappings (uncached? cached?): write, memcpy read, NEON read - for every ION flag combination
 *   2  a pixmap surface on that memory: does creation work, is the content linear, which byte order / orientation, GPU cost
 *   3  what a WebKit integration would do: the compositor's FBO texture drawn into the pixmap surface (GPU blit), then the CPU reads it
 *   4  baseline: glReadPixels from the same surface / from a texture FBO
 *   usage: pixmap_bench [width height]      (default 1280 720)
 */
#define BROADCOM_PLATFORM 1
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/dreameglplatform.h>
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>
#include <arm_neon.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include "ion_dream.h"

#define ION_HEAP_TYPE_BMEM (ION_HEAP_TYPE_CUSTOM + 1)
#define ION_HEAP_ID_MASK (1 << ION_HEAP_TYPE_BMEM)
#define DRM_FORMAT_ABGR8888 0x34324241 /* memory order R,G,B,A */
#define DRM_FORMAT_ARGB8888 0x34325241 /* memory order B,G,R,A */
#define ITER 10

static double now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

static void report(const char *name, double total_ms, size_t bytes)
{
    double per = total_ms / ITER;
    printf("  %-62s %8.2f ms  %8.1f MB/s\n", name, per, (bytes / 1e6) / (per / 1000.0));
    fflush(stdout);
}

/* ---- ION ---- */
struct ionbuf {
    int ion, fd;
    unsigned long phys;
    size_t len;
    void *addr;
};

static int ion_get(struct ionbuf *b, size_t len, unsigned flags)
{
    memset(b, 0, sizeof *b);
    b->ion = open("/dev/ion", O_RDWR | O_CLOEXEC);
    if (b->ion < 0) { printf("  open /dev/ion: %s\n", strerror(errno)); return -1; }
    struct ion_allocation_data a;
    memset(&a, 0, sizeof a);
    a.len = len;
    a.align = 4096;
    a.heap_id_mask = ION_HEAP_ID_MASK;
    a.flags = flags;
    if (ioctl(b->ion, ION_IOC_ALLOC, &a) < 0) { printf("  ION_IOC_ALLOC(len %zu flags %u): %s\n", len, flags, strerror(errno)); close(b->ion); return -1; }
    struct ion_phys_data p;
    memset(&p, 0, sizeof p);
    p.handle = a.handle;
    if (ioctl(b->ion, ION_IOC_PHYS, &p) < 0) { printf("  ION_IOC_PHYS: %s\n", strerror(errno)); return -1; }
    struct ion_fd_data s;
    memset(&s, 0, sizeof s);
    s.handle = a.handle;
    if (ioctl(b->ion, ION_IOC_SHARE, &s) < 0) { printf("  ION_IOC_SHARE: %s\n", strerror(errno)); return -1; }
    struct ion_handle_data f = { a.handle };
    ioctl(b->ion, ION_IOC_FREE, &f); /* the shared fd keeps the buffer alive */
    b->fd = s.fd;
    b->phys = p.addr;
    b->len = len;
    b->addr = mmap(0, len, PROT_READ | PROT_WRITE, MAP_SHARED, s.fd, 0);
    if (b->addr == MAP_FAILED) { printf("  mmap: %s\n", strerror(errno)); b->addr = NULL; return -1; }
    return 0;
}

static void ion_put(struct ionbuf *b)
{
    if (b->addr) munmap(b->addr, b->len);
    if (b->fd > 0) close(b->fd);
    if (b->ion > 0) close(b->ion);
    memset(b, 0, sizeof *b);
}

static void ion_sync(struct ionbuf *b)
{
    struct ion_fd_data s = { 0, b->fd };
    if (ioctl(b->ion, ION_IOC_SYNC, &s) < 0) {
        static int once;
        if (!once++) printf("  ION_IOC_SYNC: %s (ignored from now on)\n", strerror(errno));
    }
}

/* NEON read: 64 bytes per iteration, sums into a sink so the loads cannot be dropped */
static unsigned neon_read(const void *src, size_t len)
{
    const uint8_t *p = src;
    uint32x4_t acc = vdupq_n_u32(0);
    for (size_t i = 0; i + 64 <= len; i += 64) {
        uint8x16x4_t v = vld4q_u8(p + i);
        acc = vaddq_u32(acc, vreinterpretq_u32_u8(veorq_u8(veorq_u8(v.val[0], v.val[1]), veorq_u8(v.val[2], v.val[3]))));
    }
    return vgetq_lane_u32(acc, 0) + vgetq_lane_u32(acc, 1) + vgetq_lane_u32(acc, 2) + vgetq_lane_u32(acc, 3);
}

static volatile unsigned sink;

static void raw_speed(const char *label, unsigned flags, size_t len)
{
    struct ionbuf b;
    printf("\n[1] ION BMEM %zu bytes, flags=%u (%s)\n", len, flags, label);
    if (ion_get(&b, len, flags) < 0) return;
    printf("  phys=0x%lx addr=%p\n", b.phys, b.addr);
    unsigned char *dst = malloc(len);
    double t0;
    t0 = now_ms();
    for (int i = 0; i < ITER; i++) memset(b.addr, i, len);
    report("CPU write (memset)", now_ms() - t0, len);
    t0 = now_ms();
    for (int i = 0; i < ITER; i++) memcpy(dst, b.addr, len);
    report("CPU read  (memcpy to malloc)", now_ms() - t0, len);
    t0 = now_ms();
    for (int i = 0; i < ITER; i++) sink += neon_read(b.addr, len);
    report("CPU read  (NEON vld4q)", now_ms() - t0, len);
    if (flags & 3) {
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) { ion_sync(&b); memcpy(dst, b.addr, len); }
        report("ION_IOC_SYNC + memcpy read", now_ms() - t0, len);
    }
    free(dst);
    ion_put(&b);
}

/* ---- GL ---- */
static const char *vs_src = "attribute vec2 p; varying vec2 uv; void main(){ uv=p*0.5+0.5; gl_Position=vec4(p,0.0,1.0);} ";
static const char *fs_grad = "precision mediump float; varying vec2 uv; uniform float t; void main(){ gl_FragColor=vec4(uv.x, uv.y, fract(t), 1.0);} ";
static const char *fs_tex = "precision mediump float; varying vec2 uv; uniform sampler2D s; void main(){ gl_FragColor=texture2D(s, uv);} ";

static GLuint make_prog(const char *fs_source)
{
    GLuint vs = glCreateShader(GL_VERTEX_SHADER), fs = glCreateShader(GL_FRAGMENT_SHADER), pr = glCreateProgram();
    glShaderSource(vs, 1, &vs_src, NULL); glCompileShader(vs);
    glShaderSource(fs, 1, &fs_source, NULL); glCompileShader(fs);
    glAttachShader(pr, vs); glAttachShader(pr, fs);
    glBindAttribLocation(pr, 0, "p");
    glLinkProgram(pr);
    return pr;
}

static void quad(GLuint prog, float t, int w, int h)
{
    static const GLfloat q[] = { -1, -1, 1, -1, -1, 1, 1, 1 };
    glViewport(0, 0, w, h);
    glUseProgram(prog);
    GLint loc = glGetUniformLocation(prog, "t");
    if (loc >= 0) glUniform1f(loc, t);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, q);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

static void px(const char *what, const unsigned char *base, int pitch, int x, int y)
{
    const unsigned char *p = base + (size_t)y * pitch + (size_t)x * 4;
    printf("    %-22s (%4d,%4d): %02x %02x %02x %02x\n", what, x, y, p[0], p[1], p[2], p[3]);
}

int main(int argc, char **argv)
{
    int W = argc > 2 ? atoi(argv[1]) : 1280, H = argc > 2 ? atoi(argv[2]) : 720;
    size_t frame = (size_t)W * H * 4, len = (frame + 4095) & ~(size_t)4095;

    printf("pixmap_bench %dx%d (%zu bytes/frame)\n", W, H, frame);
    raw_speed("uncached (what fbClass/accel use)", 0, len);
    raw_speed("ION_FLAG_CACHED", ION_FLAG_CACHED, len);
    raw_speed("ION_FLAG_CACHED | CACHED_NEEDS_SYNC", ION_FLAG_CACHED | ION_FLAG_CACHED_NEEDS_SYNC, len);

    /* ---- EGL ---- */
    EGLDisplay dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    EGLint maj, min;
    if (!eglInitialize(dpy, &maj, &min)) { printf("eglInitialize failed 0x%x\n", eglGetError()); return 1; }
    eglBindAPI(EGL_OPENGL_ES_API);
    EGLConfig cfgs[64], cfg = NULL;
    EGLint n = 0;
    eglGetConfigs(dpy, cfgs, 64, &n);
    for (int i = 0; i < n; i++) {
        EGLint st = 0, rt = 0, r = 0, g = 0, b = 0, a = 0, d = 0, s = 0;
        eglGetConfigAttrib(dpy, cfgs[i], EGL_SURFACE_TYPE, &st);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_RENDERABLE_TYPE, &rt);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_RED_SIZE, &r);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_GREEN_SIZE, &g);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_BLUE_SIZE, &b);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_ALPHA_SIZE, &a);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_DEPTH_SIZE, &d);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_STENCIL_SIZE, &s);
        if (!cfg && (st & EGL_PIXMAP_BIT) && (rt & EGL_OPENGL_ES3_BIT) && r == 8 && g == 8 && b == 8 && a == 8 && d == 0 && s == 0) cfg = cfgs[i];
    }
    if (!cfg) { printf("no RGBA8888 pixmap+ES3 config without depth/stencil\n"); return 2; }
    EGLint ctxattr[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    EGLContext ctx = eglCreateContext(dpy, cfg, EGL_NO_CONTEXT, ctxattr);
    if (!ctx) { printf("eglCreateContext failed 0x%x\n", eglGetError()); return 3; }

    PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC createPixmap = (PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC)eglGetProcAddress("eglCreatePlatformPixmapSurfaceEXT");
    printf("\n[2] eglCreatePlatformPixmapSurfaceEXT = %p\n", (void *)createPixmap);
    if (!createPixmap) return 4;

    struct { const char *name; unsigned flags; int fdmode; unsigned fourcc; } tries[] = {
        { "uncached, fd=-1, ABGR8888", 0, 0, DRM_FORMAT_ABGR8888 },
        { "uncached, fd=share, ABGR8888", 0, 1, DRM_FORMAT_ABGR8888 },
        { "cached, fd=-1, ABGR8888", ION_FLAG_CACHED, 0, DRM_FORMAT_ABGR8888 },
        { "cached+needs_sync, fd=-1, ABGR8888", ION_FLAG_CACHED | ION_FLAG_CACHED_NEEDS_SYNC, 0, DRM_FORMAT_ABGR8888 },
        { "uncached, fd=-1, ARGB8888", 0, 0, DRM_FORMAT_ARGB8888 },
    };
    GLuint gradProg = 0, texProg = 0;
    unsigned char *dst = malloc(frame);
    for (unsigned t = 0; t < sizeof tries / sizeof tries[0]; t++) {
        struct ionbuf b;
        printf("\n[2] pixmap surface: %s\n", tries[t].name);
        if (ion_get(&b, len, tries[t].flags) < 0) continue;
        memset(b.addr, 0x55, len);
        struct dmegl_pixmap_handle h;
        memset(&h, 0, sizeof h);
        h.mem.magic = DMEGL_PIXMAP_MAGIC;
        h.mem.length = len;
        h.mem.offset = 0;
        h.mem.fd = tries[t].fdmode ? b.fd : -1;
        h.mem.phys = b.phys;
        h.mem.addr = b.addr;
        h.width = W;
        h.height = H;
        h.pitch = W * 4;
        h.format = tries[t].fourcc;
        EGLSurface surf = createPixmap(dpy, cfg, &h, NULL);
        if (surf == EGL_NO_SURFACE) { printf("  create surface FAILED 0x%x\n", eglGetError()); ion_put(&b); continue; }
        if (!eglMakeCurrent(dpy, surf, surf, ctx)) { printf("  makecurrent FAILED 0x%x\n", eglGetError()); ion_put(&b); continue; }
        if (!gradProg) { gradProg = make_prog(fs_grad); texProg = make_prog(fs_tex); }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        /* content check: R = x/W, G = y/H, B = fract(t) */
        quad(gradProg, 0.5f, W, H);
        glFinish();
        int cached = tries[t].flags & 1;
        if (cached) ion_sync(&b);
        printf("  after draw + glFinish, straight from the mapping (expect R=x/W G=y/H B=80, A=ff in some order):\n");
        px("top-left", b.addr, W * 4, 2, 2);
        px("top-right", b.addr, W * 4, W - 3, 2);
        px("bottom-left", b.addr, W * 4, 2, H - 3);
        px("centre", b.addr, W * 4, W / 2, H / 2);
        px("quarter", b.addr, W * 4, W / 4, H / 4);
        /* linearity: along a row the first byte must rise steadily (tiled memory would jump around) */
        int mono = 1, prev = -1;
        for (int x = 0; x < W; x += 16) {
            int v = ((unsigned char *)b.addr)[(size_t)(H / 2) * W * 4 + (size_t)x * 4 + 0];
            int v2 = ((unsigned char *)b.addr)[(size_t)(H / 2) * W * 4 + (size_t)x * 4 + 2];
            int v_use = (v > v2) ? v : v2; /* whichever of byte 0/2 is the R gradient */
            if (prev >= 0 && v_use + 3 < prev) mono = 0;
            prev = v_use;
        }
        printf("  row is a smooth gradient (linear layout): %s\n", mono ? "YES" : "NO (tiled or scrambled?)");
        unsigned char *m = b.addr;
        int changed = 0;
        for (size_t i = 0; i < frame; i += 4096) changed += (m[i] != 0x55);
        printf("  page samples changed by the GPU: %d of %zu\n", changed, frame / 4096);

        /* timing */
        double t0;
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) { quad(gradProg, i * 0.1f, W, H); glFinish(); }
        report("GPU: draw full-screen quad + glFinish into the pixmap", now_ms() - t0, frame);
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) { if (cached) ion_sync(&b); memcpy(dst, b.addr, frame); }
        report("CPU: memcpy of the whole frame from the mapping", now_ms() - t0, frame);
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) { if (cached) ion_sync(&b); sink += neon_read(b.addr, frame); }
        report("CPU: NEON read of the whole frame from the mapping", now_ms() - t0, frame);
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) { quad(gradProg, i * 0.1f, W, H); glFinish(); if (cached) ion_sync(&b); memcpy(dst, b.addr, frame); }
        report("TOTAL per frame: draw + glFinish + memcpy (replaces glReadPixels)", now_ms() - t0, frame);
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) { quad(gradProg, i * 0.1f, W, H); glReadPixels(0, 0, W, H, GL_RGBA, GL_UNSIGNED_BYTE, dst); }
        report("baseline: draw + glReadPixels of the pixmap surface", now_ms() - t0, frame);

        /* [3] FBO texture (what WebKit renders into) -> GPU blit into the pixmap -> CPU read */
        GLuint tex, fbo;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
            quad(gradProg, 0.5f, W, H);
            glFinish();
            printf("  [3] texture FBO -> pixmap:\n");
            t0 = now_ms();
            for (int i = 0; i < ITER; i++) {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                glBindTexture(GL_TEXTURE_2D, tex);
                glUseProgram(texProg);
                glUniform1i(glGetUniformLocation(texProg, "s"), 0);
                quad(texProg, 0, W, H);
                glFinish();
                if (cached) ion_sync(&b);
                memcpy(dst, b.addr, frame);
                glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            }
            report("texture -> pixmap blit + glFinish + memcpy (whole frame)", now_ms() - t0, frame);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            t0 = now_ms();
            for (int i = 0; i < ITER; i++) glReadPixels(0, 0, W, H, GL_RGBA, GL_UNSIGNED_BYTE, dst);
            report("baseline: glReadPixels of the texture FBO (WebKit today)", now_ms() - t0, frame);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            px("blit result, centre", b.addr, W * 4, W / 2, H / 2);
        } else
            printf("  texture FBO incomplete\n");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteFramebuffers(1, &fbo);
        glDeleteTextures(1, &tex);
        printf("  glGetError 0x%x\n", glGetError());
        eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroySurface(dpy, surf);
        ion_put(&b);
        eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, ctx);
    }
    printf("\ndone\n");
    return 0;
}
