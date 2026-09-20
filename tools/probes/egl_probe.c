/* egl_probe: what can the vendor EGL/GLES2 do offscreen? (HbbTV/WPE experiment) */
#define BROADCOM_PLATFORM 1
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <stdio.h>
#include <string.h>

static void ext(const char *label, const char *s, const char *want[])
{
    printf("%s:\n", label);
    for (int i = 0; want[i]; i++)
        printf("   %-34s %s\n", want[i], s && strstr(s, want[i]) ? "yes" : "no");
}

int main(void)
{
    const char *client = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
    printf("client extensions: %s\n", client ? client : "(none / query failed)");

    EGLDisplay dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    printf("eglGetDisplay(DEFAULT) = %p\n", dpy);
    if (dpy == EGL_NO_DISPLAY) return 2;

    EGLint maj = 0, min = 0;
    if (!eglInitialize(dpy, &maj, &min)) { printf("eglInitialize FAILED 0x%x\n", eglGetError()); return 3; }
    printf("EGL %d.%d  vendor '%s'  version '%s'\n", maj, min, eglQueryString(dpy, EGL_VENDOR), eglQueryString(dpy, EGL_VERSION));
    const char *dext = eglQueryString(dpy, EGL_EXTENSIONS);
    printf("display extensions: %s\n", dext ? dext : "(none)");
    const char *want[] = { "EGL_KHR_surfaceless_context", "EGL_KHR_create_context", "EGL_KHR_image_base", "EGL_KHR_gl_texture_2D_image",
        "EGL_KHR_fence_sync", "EGL_EXT_image_dma_buf_import", "EGL_KHR_platform_gbm", "EGL_MESA_platform_surfaceless",
        "EGL_EXT_platform_base", "EGL_KHR_no_config_context", NULL };
    ext("wanted (display ext)", dext, want);

    EGLint n = 0;
    eglGetConfigs(dpy, NULL, 0, &n);
    printf("configs: %d\n", n);
    EGLConfig cfgs[128];
    if (n > 128) n = 128;
    eglGetConfigs(dpy, cfgs, n, &n);
    int pb = 0, win = 0, pix = 0, es2 = 0;
    EGLConfig pick = NULL;
    for (int i = 0; i < n; i++) {
        EGLint st = 0, rt = 0, r = 0, g = 0, b = 0, a = 0;
        eglGetConfigAttrib(dpy, cfgs[i], EGL_SURFACE_TYPE, &st);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_RENDERABLE_TYPE, &rt);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_RED_SIZE, &r);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_GREEN_SIZE, &g);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_BLUE_SIZE, &b);
        eglGetConfigAttrib(dpy, cfgs[i], EGL_ALPHA_SIZE, &a);
        pb += !!(st & EGL_PBUFFER_BIT); win += !!(st & EGL_WINDOW_BIT); pix += !!(st & EGL_PIXMAP_BIT);
        if (rt & EGL_OPENGL_ES2_BIT) {
            es2++;
            if (!pick && (st & EGL_PBUFFER_BIT) && a > 0) pick = cfgs[i];
        }
        if (i < 6)
            printf("   cfg%-2d %d%d%d%d surface=%s%s%s gles2=%d\n", i, r, g, b, a, (st & EGL_WINDOW_BIT) ? "W" : "", (st & EGL_PBUFFER_BIT) ? "B" : "",
                (st & EGL_PIXMAP_BIT) ? "P" : "", !!(rt & EGL_OPENGL_ES2_BIT));
    }
    printf("configs with: window=%d pbuffer=%d pixmap=%d gles2=%d\n", win, pb, pix, es2);

    if (!eglBindAPI(EGL_OPENGL_ES_API)) printf("eglBindAPI(ES) failed\n");
    if (!pick) {
        /* fall back to any ES2 config */
        for (int i = 0; i < n; i++) {
            EGLint rt = 0;
            eglGetConfigAttrib(dpy, cfgs[i], EGL_RENDERABLE_TYPE, &rt);
            if (rt & EGL_OPENGL_ES2_BIT) { pick = cfgs[i]; break; }
        }
        printf("no ES2 pbuffer config with alpha; fell back to first ES2 config %p\n", pick);
    }
    if (!pick) { printf("NO ES2 CONFIG\n"); return 4; }

    const EGLint ctxattr[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    EGLContext ctx = eglCreateContext(dpy, pick, EGL_NO_CONTEXT, ctxattr);
    printf("eglCreateContext(ES2) = %p (err 0x%x)\n", ctx, ctx ? 0 : eglGetError());
    if (!ctx) return 5;

    /* 1. surfaceless make-current (what WebKit's offscreen compositor wants) */
    int surfaceless = eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, ctx);
    printf("eglMakeCurrent(NO_SURFACE)  = %s (err 0x%x)\n", surfaceless ? "OK  <-- surfaceless works" : "FAILED", surfaceless ? 0 : eglGetError());

    /* 2. pbuffer make-current */
    EGLSurface pbs = EGL_NO_SURFACE;
    int pbok = 0;
    if (pb) {
        const EGLint pbattr[] = { EGL_WIDTH, 64, EGL_HEIGHT, 64, EGL_NONE };
        pbs = eglCreatePbufferSurface(dpy, pick, pbattr);
        printf("eglCreatePbufferSurface = %p (err 0x%x)\n", pbs, pbs ? 0 : eglGetError());
        if (pbs) {
            pbok = eglMakeCurrent(dpy, pbs, pbs, ctx);
            printf("eglMakeCurrent(pbuffer)     = %s (err 0x%x)\n", pbok ? "OK" : "FAILED", pbok ? 0 : eglGetError());
        }
    }

    if (surfaceless || pbok) {
        printf("GL_VENDOR   %s\nGL_RENDERER %s\nGL_VERSION  %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
        const char *gext = (const char *)glGetString(GL_EXTENSIONS);
        printf("GL extensions: %s\n", gext ? gext : "(none)");

        /* render into an FBO and read it back: proves offscreen rendering works even without a surface */
        GLuint fbo = 0, tex = 0;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
        GLenum fs = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        printf("FBO status 0x%x (0x8cd5 = complete)\n", fs);
        if (fs == GL_FRAMEBUFFER_COMPLETE) {
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f); /* red */
            glClear(GL_COLOR_BUFFER_BIT);
            unsigned char px[4] = { 0 };
            glReadPixels(32, 32, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);
            printf("FBO clear red, glReadPixels(RGBA) -> %02x %02x %02x %02x  %s\n", px[0], px[1], px[2], px[3],
                (px[0] == 255 && px[1] == 0 && px[2] == 0) ? "CORRECT (red is R=ff)" : "UNEXPECTED (R/B swapped?)");
        }
        printf("glGetError 0x%x\n", glGetError());
    }
    printf("SUMMARY: surfaceless=%d pbuffer=%d\n", surfaceless, pbok);
    eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglTerminate(dpy);
    return 0;
}
