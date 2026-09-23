VU+ probe for the HbbTV 2.0 port (WPE WebKit + Open Red Button)
================================================================

What it is: two read-only programs that answer "can this box run it, and what would have to change?" - nothing is installed, nothing is drawn on the TV,
no setting is changed.

  vu_probe.sh      collects: model, image, CPU, memory, C library, python, GStreamer and its dvb sinks, the installed libraries the browser needs, the GPU
                   libraries and device nodes, the framebuffer, the video plane (/proc/stb/vmpeg), who holds the decoder, enigma2's OSD settings.
  vu_egl_probe     (started by vu_probe.sh) opens EGL/GLES OFFSCREEN for a few seconds: can another process than enigma2 get a display and a GLES context
                   (with or without a surface), GLES version and extensions, are the colours right (R/B), how fast is reading a rendered frame back
                   (the frames of the browser go from the GPU to the CPU this way), and the framebuffer's size, pages and colour layout. On a Nexus-based
                   box it now also tries NxClient_Join() (libnxclient.so) before touching EGL at all - confirmed 2026-09-22 on a GigaBlue box that
                   eglInitialize otherwise asserts "Memory interface not registered" and aborts; harmless no-op where libnxclient.so does not exist
                   (dm900, plain VU+ images without it). NxClient_Join() alone was NOT enough (report(9), 2026-09-23): eglInitialize still asserted
                   the same way. Tracing that through the header dump (hbbtv2/headers/gb-nexus-headers/default_nexus.h) and the full symbol table of
                   libnxpl.so (report(10)) found the real candidate: NXPL_RegisterNexusDisplayPlatform(&handle, display), whose own doc comment says
                   it "registers its own memory, h/w and display APIs" - matching the assertion text exactly. Its doc also says "exclusive use",
                   which could plausibly affect enigma2's live OSD while held - a bigger risk than anything else this probe does - so this step is
                   OPT-IN ONLY: set TRY_REGISTER_DISPLAY=1 in the environment before running vu_probe.sh to try it (default run skips it, and says so
                   in the report). When it runs: register(NULL) -> eglGetDisplay -> eglInitialize -> unregister, all in one short-lived forked child
                   (same crash-safe pattern as every display strategy below it), to keep any exclusive-use window as brief as possible.
  dynsym_dump      (started by vu_probe.sh) lists a shared library's dynamic symbols without needing nm/readelf/objdump on the box (several of these
                   images have none of the three). vu_probe.sh points it at libnexus*.so, if present, and greps for "join"/"init"/"client" - the
                   Nexus client/server GPU-memory join step other Nexus-based boxes needed before EGL would work - and now also "begl": report(7) on a
                   GigaBlue gbquad4kpro showed NxClient_Join() succeeding but eglInitialize() STILL asserting "Memory interface not registered" -
                   Broadcom's own begl_memplatform.h (see hbbtv2/headers/gb-nexus-headers/EGL/) declares extern void BEGL_RegisterMemoryInterface(...),
                   which matches that message exactly (a separate, EGL/GLES-specific memory-allocator registration, not the general Nexus client join).
                   This new query checks whether libv3ddriver.so (or the other EGL-stack libraries) EXPORTS BEGL_RegisterMemoryInterface/
                   BEGL_RegisterDisplayInterface/BEGL_RegisterSchedInterface for an app to call, before anyone writes a from-scratch implementation of
                   Broadcom's own (not-in-this-header-dump) gmem_abstract.c. report(9) confirmed libv3ddriver.so DOES export real (non-stub)
                   implementations of all three - AND that libnxpl.so imports (does not implement) those same three symbols, meaning libnxpl.so is
                   itself Broadcom's own working glue that builds a Nexus-backed memory interface and registers it - so vu_probe.sh now also dumps
                   libnxpl.so's COMPLETE symbol table unfiltered (it only has 153 symbols total, cheap to read in full) to find whatever top-level
                   "create a GLES platform" entry point it exports that the join/init/client/begl filters would not catch by name. Read-only, never
                   writes to the file.

How to run (on the box, as root, enigma2 running normally, NOTHING RECORDING):

  1. copy vuplus-probe.tar.gz to the box (e.g. into /home/root or /media/hdd; not a noexec place)
  2. cd there;  tar xzf vuplus-probe.tar.gz;  cd vuplus-probe;  chmod +x vu_egl_probe dynsym_dump
  3. sh vu_probe.sh                          (about half a minute; prints only a start and an end line)
  4. send /tmp/vu_probe_report.txt (about 15-30 KB of text)

If step 3 stops at once with "GLIBC_2.34 not found" the image's C library is older than the probe needs: tell me the image and version, nothing else is
needed. If the probe itself crashes or hangs it ends by itself after 20 s and the report says at which step - that is an answer too.

Optional, higher-risk step (NXPL_RegisterNexusDisplayPlatform - see vu_egl_probe above): only after a normal run has been sent and looked at, run again
with  TRY_REGISTER_DISPLAY=1 sh vu_probe.sh  . This one is not "nothing is drawn on the TV, nothing changed" like the rest of the probe - its own
Broadcom doc comment says "exclusive use", so it could plausibly disrupt enigma2's live picture for the brief moment it is held (register ->
eglInitialize -> unregister, all in one short child process). Run it only when a short OSD hiccup is acceptable, not during a recording or a timeshift
you care about; if the picture does not come back on its own, a reboot is the fallback recovery.

vu_egl_probe now tries a few different ways of getting an EGL display (each in its own throwaway process, so one crashing does not stop the next one
being tried), and if one crashes it prints the CPU registers at that moment - useful even from a report alone, no debugger needed on the box.

Risk, honestly: the EGL part starts a second GPU client next to enigma2. On other boxes this has always been harmless, but a driver may object; the worst
that should happen is a short hiccup of the OSD. Run it when nobody is watching a recording or a timeshift you care about.

An optional second step (not in this package, it draws for a few seconds on the TV): a test of how the OSD blends alpha (straight or premultiplied).
