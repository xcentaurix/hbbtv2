/* pixmap_bench3: spike S1, part 3 (see pixmap_bench.c, pixmap_bench2.c). Part 2: an uncached BMEM mapping reads at ~200 MB/s with vldmia d0-d7,
 * and ION heap 1 (system_contig) accepts ION_FLAG_CACHED and has physical addresses.
 *   A  faster loads on the uncached mapping: 128 byte vldmia, two reader threads
 *   B  a CACHED heap-1 buffer as the pixmap: does the GPU render into it correctly, what does ION_IOC_SYNC do, how fast does the CPU read it
 *   usage: pixmap_bench3 [width height]
 */
#define BROADCOM_PLATFORM 1
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/dreameglplatform.h>
#include <GLES3/gl3.h>
#include <arm_neon.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include "ion_dream.h"

#define ION_HEAP_TYPE_BMEM (ION_HEAP_TYPE_CUSTOM + 1)
#define DRM_FORMAT_ABGR8888 0x34324241
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
    printf("  %-66s %8.2f ms  %8.1f MB/s\n", name, per, (bytes / 1e6) / (per / 1000.0));
    fflush(stdout);
}

struct ionbuf { int ion, fd; unsigned long phys; size_t len; void *addr; };

static int ion_get(struct ionbuf *b, size_t len, unsigned mask, unsigned flags)
{
    memset(b, 0, sizeof *b);
    b->ion = open("/dev/ion", O_RDWR | O_CLOEXEC);
    struct ion_allocation_data a;
    memset(&a, 0, sizeof a);
    a.len = len; a.align = 4096; a.heap_id_mask = mask; a.flags = flags;
    if (ioctl(b->ion, ION_IOC_ALLOC, &a) < 0) { printf("  alloc mask=0x%x flags=%u: %s\n", mask, flags, strerror(errno)); return -1; }
    struct ion_phys_data p; memset(&p, 0, sizeof p); p.handle = a.handle;
    if (ioctl(b->ion, ION_IOC_PHYS, &p) < 0) { printf("  PHYS: %s\n", strerror(errno)); return -1; }
    struct ion_fd_data s; memset(&s, 0, sizeof s); s.handle = a.handle;
    if (ioctl(b->ion, ION_IOC_SHARE, &s) < 0) { printf("  SHARE: %s\n", strerror(errno)); return -1; }
    struct ion_handle_data f = { a.handle };
    ioctl(b->ion, ION_IOC_FREE, &f);
    b->fd = s.fd; b->phys = p.addr; b->len = len;
    b->addr = mmap(0, len, PROT_READ | PROT_WRITE, MAP_SHARED, s.fd, 0);
    if (b->addr == MAP_FAILED) { b->addr = NULL; printf("  mmap: %s\n", strerror(errno)); return -1; }
    return 0;
}

static void ion_put(struct ionbuf *b)
{
    if (b->addr) munmap(b->addr, b->len);
    if (b->fd > 0) close(b->fd);
    if (b->ion > 0) close(b->ion);
    memset(b, 0, sizeof *b);
}

static int ion_sync(struct ionbuf *b)
{
    struct ion_fd_data s = { 0, b->fd };
    return ioctl(b->ion, ION_IOC_SYNC, &s);
}

static void cp_vldm8(void *d, const void *s, size_t n)
{
    asm volatile("1: vldmia %1!, {d0-d7}\n vstmia %0!, {d0-d7}\n subs %2, %2, #64\n bne 1b\n"
                 : "+r"(d), "+r"(s), "+r"(n) :: "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "cc", "memory");
}
static void cp_vldm16(void *d, const void *s, size_t n) /* 128 bytes: d0-d15 (d8-d15 are callee saved: the clobber list makes the compiler save them) */
{
    asm volatile("1: vldmia %1!, {d0-d15}\n vstmia %0!, {d0-d15}\n subs %2, %2, #128\n bne 1b\n"
                 : "+r"(d), "+r"(s), "+r"(n) :: "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "d10", "d11", "d12", "d13", "d14", "d15", "cc", "memory");
}

struct job { void *d; const void *s; size_t n; void (*fn)(void *, const void *, size_t); };
static void *worker(void *p) { struct job *j = p; j->fn(j->d, j->s, j->n); return NULL; }

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

/* how many sampled pixels have blue == want (the shader writes t into blue) */
static int check_blue(const unsigned char *m, int W, int H, int want)
{
    int ok = 0, total = 0;
    for (int y = 5; y < H; y += 61)
        for (int x = 5; x < W; x += 67) { total++; ok += abs((int)m[((size_t)y * W + x) * 4 + 2] - want) <= 1; }
    return ok * 1000 / total; /* per mille */
}

int main(int argc, char **argv)
{
    int W = argc > 2 ? atoi(argv[1]) : 1920, H = argc > 2 ? atoi(argv[2]) : 1080;
    size_t frame = (size_t)W * H * 4, len = (frame + 4095) & ~(size_t)4095;
    printf("pixmap_bench3 %dx%d\n", W, H);

    /* ---- A ---- */
    printf("\n[A] uncached BMEM mapping, %zu bytes\n", frame);
    struct ionbuf src;
    if (ion_get(&src, len, 1u << ION_HEAP_TYPE_BMEM, 0) < 0) return 1;
    memset(src.addr, 0x5a, len);
    void *dst;
    if (posix_memalign(&dst, 128, len)) return 1;
    memset(dst, 0, len);
    double t0 = now_ms();
    for (int i = 0; i < ITER; i++) cp_vldm8(dst, src.addr, frame);
    report("vldmia d0-d7 (64 B), one thread", now_ms() - t0, frame);
    t0 = now_ms();
    for (int i = 0; i < ITER; i++) cp_vldm16(dst, src.addr, frame);
    report("vldmia d0-d15 (128 B), one thread", now_ms() - t0, frame);
    for (int nt = 2; nt <= 2; nt++) {
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) {
            pthread_t th[4];
            struct job jobs[4];
            size_t part = (frame / nt) & ~(size_t)127;
            for (int k = 0; k < nt; k++) {
                jobs[k] = (struct job){ (char *)dst + k * part, (char *)src.addr + k * part, k == nt - 1 ? (frame - k * part) & ~(size_t)127 : part, cp_vldm16 };
                pthread_create(&th[k], NULL, worker, &jobs[k]);
            }
            for (int k = 0; k < nt; k++) pthread_join(th[k], NULL);
        }
        report("vldmia d0-d15, 2 threads (halves)", now_ms() - t0, frame);
    }
    ion_put(&src);

    /* ---- EGL ---- */
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

    struct { const char *name; unsigned mask, flags; } heaps[] = {
        { "heap 1 system_contig, CACHED", 1u << ION_HEAP_TYPE_SYSTEM_CONTIG, ION_FLAG_CACHED },
        { "heap 1 system_contig, CACHED|NEEDS_SYNC", 1u << ION_HEAP_TYPE_SYSTEM_CONTIG, ION_FLAG_CACHED | ION_FLAG_CACHED_NEEDS_SYNC },
        { "heap 1 system_contig, uncached", 1u << ION_HEAP_TYPE_SYSTEM_CONTIG, 0 },
    };
    GLuint prog = 0;
    for (unsigned k = 0; k < sizeof heaps / sizeof heaps[0]; k++) {
        printf("\n[B] pixmap surface on %s\n", heaps[k].name);
        struct ionbuf pm;
        if (ion_get(&pm, len, heaps[k].mask, heaps[k].flags) < 0) continue;
        printf("  phys=0x%lx addr=%p\n", pm.phys, pm.addr);
        struct dmegl_pixmap_handle h;
        memset(&h, 0, sizeof h);
        h.mem.magic = DMEGL_PIXMAP_MAGIC; h.mem.length = len; h.mem.fd = -1; h.mem.phys = pm.phys; h.mem.addr = pm.addr;
        h.width = W; h.height = H; h.pitch = W * 4; h.format = DRM_FORMAT_ABGR8888;
        EGLSurface surf = createPixmap(dpy, cfg, &h, NULL);
        if (surf == EGL_NO_SURFACE || !eglMakeCurrent(dpy, surf, surf, ctx)) { printf("  surface/makecurrent failed 0x%x\n", eglGetError()); ion_put(&pm); continue; }
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

        /* coherence, the way the embedder would use it (the CPU never writes the buffer): the GPU renders A, the CPU reads the whole frame (its cache
         * now holds valid lines of A), the GPU renders B; does the CPU see B without / with ION_IOC_SYNC? */
        for (int round = 0; round < 3; round++) {
            int a = 40 + round * 50, b = 200 - round * 30;
            unsigned char *tmp = malloc(len);
            quad(prog, a / 255.0f, W, H);
            glFinish();
            ion_sync(&pm);
            memcpy(tmp, pm.addr, frame); /* touches every line */
            quad(prog, b / 255.0f, W, H);
            glFinish();
            int raw = check_blue(pm.addr, W, H, b);
            int rc = ion_sync(&pm);
            int synced = check_blue(pm.addr, W, H, b);
            printf("  round %d (A=%d then B=%d): sees B without sync %d.%d%%, after ION_IOC_SYNC (rc %d) %d.%d%%\n", round, a, b, raw / 10, raw % 10, rc, synced / 10, synced % 10);
            free(tmp);
        }

        /* speed: read the frame after the GPU finished */
        void *out;
        posix_memalign(&out, 128, len);
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) { quad(prog, 0.5f, W, H); glFinish(); }
        report("GPU: draw quad + glFinish", now_ms() - t0, frame);
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) cp_vldm16(out, pm.addr, frame);
        report("CPU: copy of the whole frame (vldmia d0-d15), no sync", now_ms() - t0, frame);
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) { ion_sync(&pm); cp_vldm16(out, pm.addr, frame); }
        report("CPU: ION_IOC_SYNC + copy of the whole frame", now_ms() - t0, frame);
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) ion_sync(&pm);
        report("ION_IOC_SYNC alone (whole buffer)", now_ms() - t0, frame);
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) { quad(prog, i * 0.01f, W, H); glFinish(); ion_sync(&pm); memcpy(out, pm.addr, frame); }
        report("TOTAL per frame: draw + glFinish + sync + memcpy", now_ms() - t0, frame);
        free(out);
        eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroySurface(dpy, surf);
        ion_put(&pm);
        eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, ctx);
    }
    printf("\ndone\n");
    return 0;
}
