VU+ probe for the HbbTV 2.0 port (WPE WebKit + Open Red Button)
================================================================

What it is: two read-only programs that answer "can this box run it, and what would have to change?" - nothing is installed, nothing is drawn on the TV,
no setting is changed.

  vu_probe.sh      collects: model, image, CPU, memory, C library, python, GStreamer and its dvb sinks, the installed libraries the browser needs, the GPU
                   libraries and device nodes, the framebuffer, the video plane (/proc/stb/vmpeg), who holds the decoder, enigma2's OSD settings.
  vu_egl_probe     (started by vu_probe.sh) opens EGL/GLES OFFSCREEN for a few seconds: can another process than enigma2 get a display and a GLES context
                   (with or without a surface), GLES version and extensions, are the colours right (R/B), how fast is reading a rendered frame back
                   (the frames of the browser go from the GPU to the CPU this way), and the framebuffer's size, pages and colour layout.

How to run (on the box, as root, enigma2 running normally, NOTHING RECORDING):

  1. copy vuplus-probe.tar.gz to the box (e.g. into /home/root or /media/hdd; not a noexec place)
  2. cd there;  tar xzf vuplus-probe.tar.gz;  cd vuplus-probe;  chmod +x vu_egl_probe
  3. sh vu_probe.sh                          (about half a minute; prints only a start and an end line)
  4. send /tmp/vu_probe_report.txt (about 15-30 KB of text)

If step 3 stops at once with "GLIBC_2.34 not found" the image's C library is older than the probe needs: tell me the image and version, nothing else is
needed. If the probe itself crashes or hangs it ends by itself after 20 s and the report says at which step - that is an answer too.

Risk, honestly: the EGL part starts a second GPU client next to enigma2. On other boxes this has always been harmless, but a driver may object; the worst
that should happen is a short hiccup of the OSD. Run it when nobody is watching a recording or a timeshift you care about.

An optional second step (not in this package, it draws for a few seconds on the TV): a test of how the OSD blends alpha (straight or premultiplied).
