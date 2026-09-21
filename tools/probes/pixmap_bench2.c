/* pixmap_bench2: spike S1, part 2 (see pixmap_bench.c). Part 1 showed: the GPU renders into ION (BMEM) memory through a pixmap surface, the
 * layout is linear, the GPU cost is ~2 ms per frame, but the CPU mapping is uncached (memcpy 27 MB/s, NEON vld4 103 MB/s; glReadPixels 13.7).
 *
 *   A  which ION heaps / flags exist (a cached mapping would read at memory speed)
 *   B  the CPU read of the uncached mapping: which load pattern is fastest, and what a copy into ordinary (cached) memory costs
 *   C  the WebKit-shaped path at the real size (default 1920x1080): render into a texture FBO, glBlitFramebuffer the DAMAGED RECTS into the
 *      pixmap surface, glFinish, copy the rects out row by row - against glReadPixels of the same rects
 *   usage: pixmap_bench2 [width height]
 */
#define BROADCOM_PLATFORM 1
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/dreameglplatform.h>
#include <GLES3/gl3.h>
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

static int ion_get(struct ionbuf *b, size_t len, unsigned mask, unsigned flags, int quiet)
{
    memset(b, 0, sizeof *b);
    b->ion = open("/dev/ion", O_RDWR | O_CLOEXEC);
    if (b->ion < 0) return -1;
    struct ion_allocation_data a;
    memset(&a, 0, sizeof a);
    a.len = len; a.align = 4096; a.heap_id_mask = mask; a.flags = flags;
    if (ioctl(b->ion, ION_IOC_ALLOC, &a) < 0) { if (!quiet) printf("  alloc mask=0x%x flags=%u: %s\n", mask, flags, strerror(errno)); close(b->ion); b->ion = 0; return -1; }
    struct ion_phys_data p; memset(&p, 0, sizeof p); p.handle = a.handle;
    int have_phys = ioctl(b->ion, ION_IOC_PHYS, &p) == 0;
    struct ion_fd_data s; memset(&s, 0, sizeof s); s.handle = a.handle;
    if (ioctl(b->ion, ION_IOC_SHARE, &s) < 0) { struct ion_handle_data f = { a.handle }; ioctl(b->ion, ION_IOC_FREE, &f); return -1; }
    struct ion_handle_data f = { a.handle };
    ioctl(b->ion, ION_IOC_FREE, &f);
    b->fd = s.fd; b->phys = have_phys ? p.addr : 0; b->len = len;
    b->addr = mmap(0, len, PROT_READ | PROT_WRITE, MAP_SHARED, s.fd, 0);
    if (b->addr == MAP_FAILED) { b->addr = NULL; if (!quiet) printf("  mmap: %s\n", strerror(errno)); return -1; }
    if (!have_phys && !quiet) printf("  (no ION_IOC_PHYS for this heap)\n");
    return 0;
}

static void ion_put(struct ionbuf *b)
{
    if (b->addr) munmap(b->addr, b->len);
    if (b->fd > 0) close(b->fd);
    if (b->ion > 0) close(b->ion);
    memset(b, 0, sizeof *b);
}

/* ---- copy kernels: len a multiple of 64, src/dst 64-byte aligned ---- */
static void cp_memcpy(void *d, const void *s, size_t n) { memcpy(d, s, n); }
static void cp_vld4(void *d, const void *s, size_t n)
{
    for (size_t i = 0; i < n; i += 64) vst4q_u8((uint8_t *)d + i, vld4q_u8((const uint8_t *)s + i));
}
static void cp_vld1x4(void *d, const void *s, size_t n)
{
    for (size_t i = 0; i < n; i += 64) {
        uint8x16_t a = vld1q_u8((const uint8_t *)s + i), b = vld1q_u8((const uint8_t *)s + i + 16), c = vld1q_u8((const uint8_t *)s + i + 32), e = vld1q_u8((const uint8_t *)s + i + 48);
        vst1q_u8((uint8_t *)d + i, a); vst1q_u8((uint8_t *)d + i + 16, b); vst1q_u8((uint8_t *)d + i + 32, c); vst1q_u8((uint8_t *)d + i + 48, e);
    }
}
static void cp_vldm(void *d, const void *s, size_t n)
{
    asm volatile("1: vldmia %1!, {d0-d7}\n vstmia %0!, {d0-d7}\n subs %2, %2, #64\n bne 1b\n"
                 : "+r"(d), "+r"(s), "+r"(n) :: "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "cc", "memory");
}
static void cp_vld1_256(void *d, const void *s, size_t n)
{
    asm volatile("1: vld1.64 {d0-d3}, [%1:256]!\n vld1.64 {d4-d7}, [%1:256]!\n vst1.64 {d0-d3}, [%0:256]!\n vst1.64 {d4-d7}, [%0:256]!\n subs %2, %2, #64\n bne 1b\n"
                 : "+r"(d), "+r"(s), "+r"(n) :: "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "cc", "memory");
}
static void cp_vld1_pld(void *d, const void *s, size_t n)
{
    asm volatile("1: pld [%1, #256]\n vld1.64 {d0-d3}, [%1:256]!\n vld1.64 {d4-d7}, [%1:256]!\n vst1.64 {d0-d3}, [%0:256]!\n vst1.64 {d4-d7}, [%0:256]!\n subs %2, %2, #64\n bne 1b\n"
                 : "+r"(d), "+r"(s), "+r"(n) :: "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "cc", "memory");
}
static void cp_ldm(void *d, const void *s, size_t n)
{
    asm volatile("1: ldmia %1!, {r3-r10}\n stmia %0!, {r3-r10}\n ldmia %1!, {r3-r10}\n stmia %0!, {r3-r10}\n subs %2, %2, #64\n bne 1b\n"
                 : "+r"(d), "+r"(s), "+r"(n) :: "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "cc", "memory");
}

static const char *vs_src = "attribute vec2 p; varying vec2 uv; void main(){ uv=p*0.5+0.5; gl_Position=vec4(p,0.0,1.0);} ";
static const char *fs_grad = "precision mediump float; varying vec2 uv; void main(){ gl_FragColor=vec4(uv.x, uv.y, 0.5, 1.0);} ";

static void quad(GLuint prog, int w, int h)
{
    static const GLfloat q[] = { -1, -1, 1, -1, -1, 1, 1, 1 };
    glViewport(0, 0, w, h);
    glUseProgram(prog);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, q);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

struct rect { int x, y, w, h; };

int main(int argc, char **argv)
{
    int W = argc > 2 ? atoi(argv[1]) : 1920, H = argc > 2 ? atoi(argv[2]) : 1080;
    size_t frame = (size_t)W * H * 4, len = (frame + 4095) & ~(size_t)4095;
    printf("pixmap_bench2 %dx%d\n", W, H);

    /* ---- A: heaps ---- */
    printf("\n[A] ION heaps: allocation of 1 MB per heap id and flag set (heap type numbers: 0 system, 1 system_contig, 2 carveout, 3 chunk, 4 dma, 5 custom, 6 = BMEM)\n");
    for (int id = 0; id < 12; id++)
        for (unsigned fl = 0; fl < 4; fl++) {
            struct ionbuf b;
            if (ion_get(&b, 1 << 20, 1u << id, fl, 1) == 0) {
                printf("  heap %2d flags %u: OK  phys=%s\n", id, fl, b.phys ? "yes" : "NO");
                ion_put(&b);
            }
        }

    /* ---- B: read patterns on the BMEM uncached mapping ---- */
    printf("\n[B] copy from the uncached BMEM mapping into cached memory (%zu bytes)\n", frame);
    struct ionbuf src;
    if (ion_get(&src, len, 1u << ION_HEAP_TYPE_BMEM, 0, 0) < 0) return 1;
    memset(src.addr, 0x5a, len);
    void *dst;
    posix_memalign(&dst, 64, len);
    memset(dst, 0, len);
    struct { const char *name; void (*fn)(void *, const void *, size_t); } kernels[] = {
        { "memcpy (glibc)", cp_memcpy }, { "vld4q/vst4q intrinsics", cp_vld4 }, { "4x vld1q/vst1q intrinsics", cp_vld1x4 },
        { "vldmia d0-d7 (64 B)", cp_vldm }, { "vld1.64 {d0-d3}:256 x2", cp_vld1_256 }, { "same + pld", cp_vld1_pld }, { "ldmia r3-r10 x2", cp_ldm },
    };
    for (unsigned k = 0; k < sizeof kernels / sizeof kernels[0]; k++) {
        double t0 = now_ms();
        for (int i = 0; i < ITER; i++) kernels[k].fn(dst, src.addr, frame);
        report(kernels[k].name, now_ms() - t0, frame);
    }
    /* what if the frame is read in several threads (the GPU/CPU otherwise idle)? two halves in parallel would need pthread: measured separately below */
    ion_put(&src);

    /* ---- C: the WebKit-shaped path ---- */
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
    struct ionbuf pm;
    if (ion_get(&pm, len, 1u << ION_HEAP_TYPE_BMEM, 0, 0) < 0) return 2;
    struct dmegl_pixmap_handle h;
    memset(&h, 0, sizeof h);
    h.mem.magic = DMEGL_PIXMAP_MAGIC; h.mem.length = len; h.mem.fd = -1; h.mem.phys = pm.phys; h.mem.addr = pm.addr;
    h.width = W; h.height = H; h.pitch = W * 4; h.format = DRM_FORMAT_ABGR8888;
    EGLSurface surf = createPixmap(dpy, cfg, &h, NULL);
    if (surf == EGL_NO_SURFACE || !eglMakeCurrent(dpy, surf, surf, ctx)) { printf("pixmap surface failed 0x%x\n", eglGetError()); return 3; }

    GLuint vs = glCreateShader(GL_VERTEX_SHADER), fs = glCreateShader(GL_FRAGMENT_SHADER), prog = glCreateProgram();
    glShaderSource(vs, 1, &vs_src, NULL); glCompileShader(vs);
    glShaderSource(fs, 1, &fs_grad, NULL); glCompileShader(fs);
    glAttachShader(prog, vs); glAttachShader(prog, fs);
    glBindAttribLocation(prog, 0, "p");
    glLinkProgram(prog);

    GLuint tex, fbo;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
    quad(prog, W, H);
    glFinish();

    /* correctness: what glReadPixels gives for the texture, against what the blit leaves in the pixmap memory */
    unsigned char *ref = malloc(frame);
    glReadPixels(0, 0, W, H, GL_RGBA, GL_UNSIGNED_BYTE, ref);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    memset(pm.addr, 0, len);
    glBlitFramebuffer(0, 0, W, H, 0, 0, W, H, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glFinish();
    printf("\n[C] texture FBO -> glBlitFramebuffer -> pixmap; glGetError 0x%x\n", glGetError());
    int same = 0, flipped = 0, total = 0;
    for (int y = 3; y < H; y += 97)
        for (int x = 3; x < W; x += 89) {
            const unsigned char *a = ref + ((size_t)y * W + x) * 4, *m0 = (unsigned char *)pm.addr + ((size_t)y * W + x) * 4, *m1 = (unsigned char *)pm.addr + ((size_t)(H - 1 - y) * W + x) * 4;
            same += !memcmp(a, m0, 4);
            flipped += !memcmp(a, m1, 4);
            total++;
        }
    printf("  samples equal to glReadPixels at the same memory row: %d/%d; at the vertically mirrored row: %d/%d\n", same, total, flipped, total);

    /* typical damage: rectangles seen in the ZDF/ARD traces (1.5x pixels) */
    struct { const char *name; int nrect; struct rect r[4]; } cases[] = {
        { "small focus move, 1 rect 300x225", 1, { { 810, 423, 300, 225 } } },
        { "tile row, 1 rect 1730x272", 1, { { 190, 657, 1730, 272 } } },
        { "hero + tiles, 3 rects (~1.5 Mpx)", 3, { { 190, 342, 437, 587 }, { 258, 276, 986, 652 }, { 190, 657, 1730, 272 } } },
        { "big repaint, 1785x1005", 1, { { 135, 0, 1785, 1005 } } },
        { "whole frame", 1, { { 0, 0, 0, 0 } } },
    };
    unsigned char *out = NULL;
    posix_memalign((void **)&out, 64, frame);
    for (unsigned c = 0; c < sizeof cases / sizeof cases[0]; c++) {
        struct rect rs[4];
        size_t bytes = 0;
        for (int i = 0; i < cases[c].nrect; i++) {
            rs[i] = cases[c].r[i];
            if (rs[i].w == 0) { rs[i].w = W; rs[i].h = H; }
            if (rs[i].x + rs[i].w > W) rs[i].w = W - rs[i].x;
            if (rs[i].y + rs[i].h > H) rs[i].h = H - rs[i].y;
            bytes += (size_t)rs[i].w * rs[i].h * 4;
        }
        printf("\n  -- %s: %.2f Mpx, %.1f MB\n", cases[c].name, bytes / 4e6, bytes / 1e6);
        double t0;
        /* today: glReadPixels per rectangle from the texture FBO */
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        t0 = now_ms();
        for (int i = 0; i < 3; i++)
            for (int r = 0; r < cases[c].nrect; r++) {
                glPixelStorei(GL_PACK_ROW_LENGTH, W);
                glReadPixels(rs[r].x, rs[r].y, rs[r].w, rs[r].h, GL_RGBA, GL_UNSIGNED_BYTE, out + ((size_t)rs[r].y * W + rs[r].x) * 4);
                glPixelStorei(GL_PACK_ROW_LENGTH, 0);
            }
        printf("  %-64s %8.2f ms\n", "today: glReadPixels of the rects", (now_ms() - t0) / 3);

        /* new: blit the rects into the pixmap, glFinish, copy them out row by row with NEON */
        for (int variant = 0; variant < 2; variant++) {
            t0 = now_ms();
            double gpu = 0, cpu = 0;
            for (int i = 0; i < 3; i++) {
                double a = now_ms();
                glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
                glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
                for (int r = 0; r < cases[c].nrect; r++)
                    glBlitFramebuffer(rs[r].x, rs[r].y, rs[r].x + rs[r].w, rs[r].y + rs[r].h, rs[r].x, rs[r].y, rs[r].x + rs[r].w, rs[r].y + rs[r].h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
                glFinish();
                double b = now_ms();
                for (int r = 0; r < cases[c].nrect; r++)
                    for (int y = 0; y < rs[r].h; y++) {
                        /* rows are 16 byte multiples for the kernels only when x and w are; the 64 B kernel handles the aligned bulk, memcpy the ends */
                        size_t off = ((size_t)(rs[r].y + y) * W + rs[r].x) * 4, rb = (size_t)rs[r].w * 4;
                        if (variant == 0) memcpy(out + off, (unsigned char *)pm.addr + off, rb);
                        else {
                            size_t head = (64 - (off & 63)) & 63, body;
                            if (head > rb) head = rb;
                            memcpy(out + off, (unsigned char *)pm.addr + off, head);
                            body = (rb - head) & ~(size_t)63;
                            if (body) cp_vld1_256(out + off + head, (unsigned char *)pm.addr + off + head, body);
                            if (rb - head - body) memcpy(out + off + head + body, (unsigned char *)pm.addr + off + head + body, rb - head - body);
                        }
                    }
                double d = now_ms();
                gpu += b - a; cpu += d - b;
            }
            printf("  %-64s %8.2f ms  (blit+finish %.2f, copy %.2f)\n", variant ? "pixmap: blit + finish + NEON row copy" : "pixmap: blit + finish + memcpy row copy", (now_ms() - t0) / 3, gpu / 3, cpu / 3);
        }
    }

    eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroySurface(dpy, surf);
    ion_put(&pm);
    printf("\ndone\n");
    return 0;
}
