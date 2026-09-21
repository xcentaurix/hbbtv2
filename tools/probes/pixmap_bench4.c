/* pixmap_bench4: spike S1, part 4. A CACHED ION buffer (heap 1, system_contig) as pixmap surface reads at ~1300 MB/s, but the CPU cache does not see what
 * the GPU wrote (ION_IOC_SYNC is a "for device" clean, not an invalidate, on this kernel). What exactly goes stale, and can it be fixed from user space?
 *   E1 fresh buffer (the CPU never touched it): does the CPU see what the GPU drew?
 *   E2 the CPU read the whole frame, the GPU drew something else: which pixels are stale (values, position)?
 *   E3 same + ION_IOC_SYNC       E4 same + streaming a 8 MB dummy buffer through the cache (eviction)
 *   E5 same + cacheflush() syscall (clean only on ARMv7, expected useless)
 *   usage: pixmap_bench4 [width height]
 */
#define BROADCOM_PLATFORM 1
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/dreameglplatform.h>
#include <GLES3/gl3.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>
#include "ion_dream.h"
#define DRM_FORMAT_ABGR8888 0x34324241

struct ionbuf { int ion, fd; unsigned long phys; size_t len; void *addr; };

static int ion_get(struct ionbuf *b, size_t len, unsigned mask, unsigned flags)
{
    memset(b, 0, sizeof *b);
    b->ion = open("/dev/ion", O_RDWR | O_CLOEXEC);
    struct ion_allocation_data a;
    memset(&a, 0, sizeof a);
    a.len = len; a.align = 4096; a.heap_id_mask = mask; a.flags = flags;
    if (ioctl(b->ion, ION_IOC_ALLOC, &a) < 0) { printf("alloc: %s\n", strerror(errno)); return -1; }
    struct ion_phys_data p;
    memset(&p, 0, sizeof p);
    p.handle = a.handle;
    if (ioctl(b->ion, ION_IOC_PHYS, &p) < 0) return -1;
    struct ion_fd_data s;
    memset(&s, 0, sizeof s);
    s.handle = a.handle;
    if (ioctl(b->ion, ION_IOC_SHARE, &s) < 0) return -1;
    struct ion_handle_data f = { a.handle };
    ioctl(b->ion, ION_IOC_FREE, &f);
    b->fd = s.fd; b->phys = p.addr; b->len = len;
    b->addr = mmap(0, len, PROT_READ | PROT_WRITE, MAP_SHARED, s.fd, 0);
    return b->addr == MAP_FAILED ? -1 : 0;
}

static const char *vs_src = "attribute vec2 p; varying vec2 uv; void main(){ uv=p*0.5+0.5; gl_Position=vec4(p,0.0,1.0);} ";
static const char *fs_grad = "precision mediump float; varying vec2 uv; uniform float t; void main(){ gl_FragColor=vec4(uv.x, uv.y, t, 1.0);} ";

static void quad(GLuint prog, float t, int w, int h)
{
    static const GLfloat q[] = { -1, -1, 1, -1, -1, 1, 1, 1 };
    glViewport(0, 0, w, h);
    glUseProgram(prog);
    glUniform1f(glGetUniformLocation(prog, "t"), t);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, q);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

/* share of the sampled pixels (every 8th of each row) whose blue is not `want`; the mean blue of those and the row range they are in */
static void check(const char *what, const unsigned char *m, int W, int H, int want)
{
    long bad = 0, sum = 0;
    int first = -1, last = -1;
    for (int y = 0; y < H; y++) {
        int rowbad = 0;
        for (int x = 0; x < W; x += 8) {
            int v = m[((size_t)y * W + x) * 4 + 2];
            if (abs(v - want) > 1) { rowbad++; bad++; sum += v; }
        }
        if (rowbad) { if (first < 0) first = y; last = y; }
    }
    long total = (long)H * ((W + 7) / 8);
    printf("  %-58s wrong %5.1f%%", what, 100.0 * bad / total);
    if (bad) printf("  (mean blue of the wrong ones %ld, rows %d..%d)", sum / bad, first, last);
    printf("\n");
}

static volatile unsigned sink;
static void touch(const unsigned char *m, size_t n)
{
    unsigned s = 0;
    for (size_t i = 0; i < n; i += 32) s += m[i];
    sink += s;
}

int main(int argc, char **argv)
{
    int W = argc > 2 ? atoi(argv[1]) : 1280, H = argc > 2 ? atoi(argv[2]) : 720;
    size_t frame = (size_t)W * H * 4, len = (frame + 4095) & ~(size_t)4095;
    EGLDisplay dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    EGLint maj, min;
    eglInitialize(dpy, &maj, &min);
    eglBindAPI(EGL_OPENGL_ES_API);
    EGLConfig cfgs[64], cfg = NULL;
    EGLint n = 0;
    eglGetConfigs(dpy, cfgs, 64, &n);
    for (int i = 0; i < n && !cfg; i++) {
        EGLint st = 0, rt = 0, r = 0, g = 0, b = 0, a = 0, d = 0, s = 0;
        eglGetConfigAttrib(dpy, cfgs[i], EGL_SURFACE_TYPE, &st); eglGetConfigAttrib(dpy, cfgs[i], EGL_RENDERABLE_TYPE, &rt);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_RED_SIZE, &r); eglGetConfigAttrib(dpy, cfgs[i], EGL_GREEN_SIZE, &g);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_BLUE_SIZE, &b); eglGetConfigAttrib(dpy, cfgs[i], EGL_ALPHA_SIZE, &a);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_DEPTH_SIZE, &d); eglGetConfigAttrib(dpy, cfgs[i], EGL_STENCIL_SIZE, &s);
        if ((st & EGL_PIXMAP_BIT) && (rt & EGL_OPENGL_ES3_BIT) && r == 8 && g == 8 && b == 8 && a == 8 && !d && !s) cfg = cfgs[i];
    }
    EGLint ctxattr[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    EGLContext ctx = eglCreateContext(dpy, cfg, EGL_NO_CONTEXT, ctxattr);
    PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC createPixmap = (PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC)eglGetProcAddress("eglCreatePlatformPixmapSurfaceEXT");
    unsigned flagsets[] = { ION_FLAG_CACHED, ION_FLAG_CACHED | ION_FLAG_CACHED_NEEDS_SYNC };
    GLuint prog = 0;
    for (int fsi = 0; fsi < 2; fsi++) {
        printf("\n=== heap 1 system_contig, flags %u, %dx%d ===\n", flagsets[fsi], W, H);
        struct ionbuf pm;
        if (ion_get(&pm, len, 1u << ION_HEAP_TYPE_SYSTEM_CONTIG, flagsets[fsi]) < 0) continue;
        struct dmegl_pixmap_handle h;
        memset(&h, 0, sizeof h);
        h.mem.magic = DMEGL_PIXMAP_MAGIC; h.mem.length = len; h.mem.fd = -1; h.mem.phys = pm.phys; h.mem.addr = pm.addr;
        h.width = W; h.height = H; h.pitch = W * 4; h.format = DRM_FORMAT_ABGR8888;
        EGLSurface surf = createPixmap(dpy, cfg, &h, NULL);
        if (surf == EGL_NO_SURFACE || !eglMakeCurrent(dpy, surf, surf, ctx)) { printf("surface failed\n"); continue; }
        if (!prog) {
            GLuint vs = glCreateShader(GL_VERTEX_SHADER), fs = glCreateShader(GL_FRAGMENT_SHADER);
            prog = glCreateProgram();
            glShaderSource(vs, 1, &vs_src, NULL); glCompileShader(vs);
            glShaderSource(fs, 1, &fs_grad, NULL); glCompileShader(fs);
            glAttachShader(prog, vs); glAttachShader(prog, fs);
            glBindAttribLocation(prog, 0, "p");
            glLinkProgram(prog);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        unsigned char *dummy = malloc(8 << 20);
        memset(dummy, 1, 8 << 20);

        quad(prog, 90 / 255.0f, W, H);
        glFinish();
        check("E1 fresh buffer, GPU drew 90, CPU reads", pm.addr, W, H, 90);

        for (int e = 2; e <= 5; e++) {
            quad(prog, 40 / 255.0f, W, H);
            glFinish();
            touch(pm.addr, frame); /* every line is now cached (whatever the GPU drew: A = 40) */
            quad(prog, 200 / 255.0f, W, H);
            glFinish();
            const char *name = e == 2 ? "E2 no maintenance" : e == 3 ? "E3 ION_IOC_SYNC" : e == 4 ? "E4 streamed 2 x 8 MB through the cache" : "E5 cacheflush() syscall";
            if (e == 3) { struct ion_fd_data s = { 0, pm.fd }; ioctl(pm.ion, ION_IOC_SYNC, &s); }
            if (e == 4) { for (int r = 0; r < 2; r++) touch(dummy, 8 << 20); }
            if (e == 5) syscall(0xf0002, pm.addr, (char *)pm.addr + len, 0);
            char buf[120];
            snprintf(buf, sizeof buf, "%s: GPU drew 200, CPU reads", name);
            check(buf, pm.addr, W, H, 200);
        }
        eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroySurface(dpy, surf);
        munmap(pm.addr, len);
        close(pm.fd);
        close(pm.ion);
        free(dummy);
        eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, ctx);
    }
    printf("\ndone\n");
    return 0;
}
