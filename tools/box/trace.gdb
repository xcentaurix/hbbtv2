set pagination off
set confirm off
set breakpoint pending on
handle SIGPIPE nostop noprint pass
handle SIG32 nostop noprint pass
handle SIG33 nostop noprint pass

# --- EGL: name + first four args (r0-r3), non-stopping ---
dprintf eglGetDisplay,"EGL eglGetDisplay(%p)\n",$r0
dprintf eglInitialize,"EGL eglInitialize(%p)\n",$r0
dprintf eglBindAPI,"EGL eglBindAPI(0x%x)\n",$r0
dprintf eglChooseConfig,"EGL eglChooseConfig(dpy=%p attrs=%p)\n",$r0,$r1
dprintf eglCreateContext,"EGL eglCreateContext(dpy=%p cfg=%p share=%p attrs=%p)\n",$r0,$r1,$r2,$r3
dprintf eglMakeCurrent,"EGL eglMakeCurrent(dpy=%p draw=%p read=%p ctx=%p)\n",$r0,$r1,$r2,$r3
dprintf eglCreatePbufferSurface,"EGL eglCreatePbufferSurface(dpy=%p cfg=%p attrs=%p)\n",$r0,$r1,$r2
dprintf eglCreateWindowSurface,"EGL eglCreateWindowSurface(dpy=%p cfg=%p win=%p attrs=%p)\n",$r0,$r1,$r2,$r3
dprintf eglCreatePixmapSurface,"EGL eglCreatePixmapSurface(dpy=%p cfg=%p pix=%p attrs=%p)\n",$r0,$r1,$r2,$r3
dprintf eglDestroySurface,"EGL eglDestroySurface(%p %p)\n",$r0,$r1
dprintf eglSwapBuffers,"EGL eglSwapBuffers(dpy=%p surf=%p)\n",$r0,$r1
dprintf eglCreateImage,"EGL eglCreateImage(dpy=%p ctx=%p target=0x%x buf=%p)\n",$r0,$r1,$r2,$r3
dprintf eglCreateImageKHR,"EGL eglCreateImageKHR(dpy=%p ctx=%p target=0x%x buf=%p)\n",$r0,$r1,$r2,$r3
dprintf eglCreateSync,"EGL eglCreateSync(dpy=%p type=0x%x)\n",$r0,$r1
dprintf eglCreateSyncKHR,"EGL eglCreateSyncKHR(dpy=%p type=0x%x)\n",$r0,$r1
dprintf eglClientWaitSyncKHR,"EGL eglClientWaitSyncKHR\n"
dprintf eglWaitClient,"EGL eglWaitClient\n"
dprintf eglGetProcAddress,"EGL eglGetProcAddress(%s)\n",$r0

# --- GL calls that can resolve/copy/blit surfaces ---
dprintf glReadPixels,"GL glReadPixels(x=%d y=%d w=%d h=%d)\n",$r0,$r1,$r2,$r3
dprintf glFinish,"GL glFinish\n"
dprintf glFlush,"GL glFlush\n"
dprintf glBlitFramebuffer,"GL glBlitFramebuffer\n"
dprintf glCopyTexImage2D,"GL glCopyTexImage2D\n"
dprintf glCopyTexSubImage2D,"GL glCopyTexSubImage2D\n"
dprintf glBindFramebuffer,"GL glBindFramebuffer(0x%x, %u)\n",$r0,$r1
dprintf glFramebufferTexture2D,"GL glFramebufferTexture2D(fb=0x%x att=0x%x tex=%u)\n",$r0,$r1,$r3
dprintf glCheckFramebufferStatus,"GL glCheckFramebufferStatus\n"
dprintf glTexImage2D,"GL glTexImage2D(target=0x%x level=%d ifmt=0x%x w=%d)\n",$r0,$r1,$r2,$r3
dprintf glTexSubImage2D,"GL glTexSubImage2D\n"
dprintf glClear,"GL glClear(0x%x)\n",$r0
dprintf glDrawElements,"GL glDrawElements\n"
dprintf glDrawArrays,"GL glDrawArrays\n"
dprintf glLinkProgram,"GL glLinkProgram(%u)\n",$r0
dprintf glCompileShader,"GL glCompileShader(%u)\n",$r0
dprintf glEGLImageTargetTexture2DOES,"GL glEGLImageTargetTexture2DOES\n"
dprintf glGetString,"GL glGetString(0x%x)\n",$r0
dprintf glGetIntegerv,"GL glGetIntegerv(0x%x)\n",$r0

run
echo \n==== CRASH ====\n
info program
echo \n==== BACKTRACE ====\n
bt 12
echo \n==== last registers ====\n
info registers r0 r1 r2 r3 lr pc
