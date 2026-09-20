/* gl_bench: how expensive is reading a rendered frame back on the Dreambox vendor GLES? (HbbTV/WPE experiment) */
#define BROADCOM_PLATFORM 1
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static double now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

#define ITER 10

static void report(const char *name, double total, int w, int h)
{
    double per = total / ITER;
    printf("  %-58s %7.1f ms/frame  (%5.1f MB/s, max %4.1f fps)\n", name, per, (w * h * 4 / 1e6) / (per / 1000.0), 1000.0 / per);
    fflush(stdout);
}

static const char *vs_src = "attribute vec2 p; varying vec2 uv; void main(){ uv=p*0.5+0.5; gl_Position=vec4(p,0.0,1.0);} ";
static const char *fs_src = "precision mediump float; varying vec2 uv; uniform float t; void main(){ gl_FragColor=vec4(uv.x, uv.y, fract(t), 1.0);} ";

static GLuint make_prog(void)
{
    GLuint vs = glCreateShader(GL_VERTEX_SHADER), fs = glCreateShader(GL_FRAGMENT_SHADER), pr = glCreateProgram();
    glShaderSource(vs, 1, &vs_src, NULL); glCompileShader(vs);
    glShaderSource(fs, 1, &fs_src, NULL); glCompileShader(fs);
    glAttachShader(pr, vs); glAttachShader(pr, fs);
    glBindAttribLocation(pr, 0, "p");
    glLinkProgram(pr);
    return pr;
}

static void draw_frame(GLuint prog, float t, int w, int h)
{
    static const GLfloat quad[] = { -1, -1, 1, -1, -1, 1, 1, 1 };
    glViewport(0, 0, w, h);
    glUseProgram(prog);
    glUniform1f(glGetUniformLocation(prog, "t"), t);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, quad);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

int main(void)
{
    EGLDisplay dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    EGLint maj, min;
    if (!eglInitialize(dpy, &maj, &min)) { printf("eglInitialize failed\n"); return 1; }
    eglBindAPI(EGL_OPENGL_ES_API);
    EGLint cfgattr[] = { EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT, EGL_SURFACE_TYPE, EGL_PBUFFER_BIT, EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_NONE };
    EGLConfig cfg; EGLint n = 0;
    if (!eglChooseConfig(dpy, cfgattr, &cfg, 1, &n) || !n) { cfgattr[1] = EGL_OPENGL_ES2_BIT; eglChooseConfig(dpy, cfgattr, &cfg, 1, &n); }
    EGLint ctxattr[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    EGLContext ctx = eglCreateContext(dpy, cfg, EGL_NO_CONTEXT, ctxattr);
    if (!ctx) { ctxattr[1] = 2; ctx = eglCreateContext(dpy, cfg, EGL_NO_CONTEXT, ctxattr); }
    if (!eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, ctx)) { printf("makecurrent failed\n"); return 2; }
    printf("GL_RENDERER: %s\nGL_VERSION: %s\n", glGetString(GL_RENDERER), glGetString(GL_VERSION));
    const char *ext = (const char *)glGetString(GL_EXTENSIONS);
    int has_bgra = ext && strstr(ext, "GL_EXT_read_format_bgra");
    printf("GL_EXT_read_format_bgra: %s   GL_EXT_texture_format_BGRA8888: %s\n", has_bgra ? "yes" : "no", ext && strstr(ext, "GL_EXT_texture_format_BGRA8888") ? "yes" : "no");

    GLuint prog = make_prog();
    int W = 1280, H = 720;
    unsigned char *buf = malloc((size_t)W * H * 4);
    double t0;

    for (int pass = 0; pass < 2; pass++) {
        GLuint fbo, tex = 0, rb = 0;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        if (pass == 0) {
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
            printf("\n-- FBO colour attachment: TEXTURE (what WebKit's compositor uses) --\n");
        } else {
            glGenRenderbuffers(1, &rb);
            glBindRenderbuffer(GL_RENDERBUFFER, rb);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, W, H);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rb);
            printf("\n-- FBO colour attachment: RENDERBUFFER --\n");
        }
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) { printf("FBO incomplete\n"); continue; }

        /* A: GPU cost alone: draw a full-screen quad + glFinish, no read-back */
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) { draw_frame(prog, i * 0.1f, W, H); glFinish(); }
        report("draw fullscreen quad + glFinish (no read-back)", now_ms() - t0, W, H);

        /* B: draw + readback RGBA */
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) { draw_frame(prog, i * 0.1f, W, H); glReadPixels(0, 0, W, H, GL_RGBA, GL_UNSIGNED_BYTE, buf); }
        report("draw + glReadPixels 1280x720 RGBA/UNSIGNED_BYTE", now_ms() - t0, W, H);

        /* C: BGRA readback (WebKit/enigma2 want BGRA) */
        if (has_bgra) {
            t0 = now_ms();
            for (int i = 0; i < ITER; i++) { draw_frame(prog, i * 0.1f, W, H); glReadPixels(0, 0, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, buf); }
            report("draw + glReadPixels 1280x720 BGRA_EXT", now_ms() - t0, W, H);
        }

        /* D: same but only the readback cost (draw once, read repeatedly) */
        draw_frame(prog, 0.5f, W, H); glFinish();
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) glReadPixels(0, 0, W, H, GL_RGBA, GL_UNSIGNED_BYTE, buf);
        report("glReadPixels only (frame already finished)", now_ms() - t0, W, H);

        /* E: half resolution readback */
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) glReadPixels(0, 0, W / 2, H / 2, GL_RGBA, GL_UNSIGNED_BYTE, buf);
        report("glReadPixels 640x360 (quarter area)", now_ms() - t0, W / 2, H / 2);

        /* F: small strip (damage-rect style): 1280x64 */
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) glReadPixels(0, 0, W, 64, GL_RGBA, GL_UNSIGNED_BYTE, buf);
        report("glReadPixels 1280x64 strip (damage-rect style)", now_ms() - t0, W, 64);

        /* G: PBO async readback */
        GLuint pbo;
        glGenBuffers(1, &pbo);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
        glBufferData(GL_PIXEL_PACK_BUFFER, W * H * 4, NULL, GL_STREAM_READ);
        t0 = now_ms();
        for (int i = 0; i < ITER; i++) {
            draw_frame(prog, i * 0.1f, W, H);
            glReadPixels(0, 0, W, H, GL_RGBA, GL_UNSIGNED_BYTE, 0);
            void *m = glMapBufferRange(GL_PIXEL_PACK_BUFFER, 0, W * H * 4, GL_MAP_READ_BIT);
            if (m) { memcpy(buf, m, (size_t)W * H * 4); glUnmapBuffer(GL_PIXEL_PACK_BUFFER); }
        }
        report("draw + PBO glReadPixels + map + memcpy", now_ms() - t0, W, H);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
        glDeleteBuffers(1, &pbo);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteFramebuffers(1, &fbo);
        if (tex) glDeleteTextures(1, &tex);
        if (rb) glDeleteRenderbuffers(1, &rb);
    }
    printf("\nglGetError: 0x%x\n", glGetError());
    return 0;
}
