# HbbTV 2.0 experiment: minimal WPE WebKit for a box with only the vendor
# EGL/GLES2 (no DRM/GBM, no Wayland). Goal of step 1: render a page into a
# buffer through the WPE Platform API headless platform.

# OpenViX opts out of the "opengl" distro feature distro-wide (every box uses a
# vendor EGL), so features_check would skip this recipe. Bypass it for wpewebkit
# only instead of flipping a distro-wide feature, which would rebuild much of
# the image.
REQUIRED_DISTRO_FEATURES = ""

# "video" is required, not optional: upstream 2.54 does not build with
# ENABLE_VIDEO=OFF (JSHTMLMediaElementCustom.cpp is compiled unconditionally but
# JSHTMLMediaElement is only generated with video). HbbTV needs media anyway.
# mediasource/webaudio/mediastream stay off until needed.
# mediasource = Media Source Extensions (window.MediaSource): HbbTV 2.0 applications and the ORB polyfill play DASH through it
PACKAGECONFIG = "dfg-jit jit mediasource remote-inspector unified-builds video woff2 wpe-platform wpe-platform-headless"

# No DRM/GBM device on this box: USE_LIBDRM defaults ON upstream and then demands
# libdrm even though the recipe's "gbm" PACKAGECONFIG (which adds it) is off.
# The libdrm-dependent code is USE(LIBDRM)-guarded; frames go via SHM buffers.
EXTRA_OECMAKE:append = " -DUSE_LIBDRM=OFF"

# The vendor EGL has no GL for gst-gl, and gst-plugins-bad (mpegts) is not needed
# yet. Upstream still lists both as REQUIRED find_package() components with
# video on, so the patch below only requires them when their option is ON
# (avoids rebuilding the image's gst-plugins-base with GL just for a check).
EXTRA_OECMAKE:append = " -DUSE_GSTREAMER_GL=OFF -DUSE_GSTREAMER_MPEGTS=OFF"
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI += "file://0001-GStreamerChecks-only-require-gl-and-mpegts-when-enabled.patch"

# With -DUSE_LIBDRM=OFF, getImageInfoFromBuffer() still used DRM_FORMAT_XRGB8888
# (its include and the later ARGB8888 use are guarded, this one was not).
SRC_URI += "file://0002-AcceleratedBackingStore-guard-DRM_FORMAT-with-USE-LIBDRM.patch"

# The remaining patches, only when building from the tarball (no EXTERNALSRC). In development mode (see the end of this file) the
# patched tree already has them, and adding them to SRC_URI would change the task signatures: that re-runs do_configure, and
# cmake.bbclass then DELETES the whole build directory (cleandirs = ${B}, which externalsrc only keeps when it lies inside the source
# tree) = a clean ~2h rebuild. So: do not touch SRC_URI or anything else that reaches do_configure while a dev build is in progress.
python () {
    if d.getVar('EXTERNALSRC'):
        return
    d.appendVar('SRC_URI', ' \
        file://0003-Enable-default-EGL-display-fallback-for-WPE.patch \
        file://0004-WPE-handle-PlatformDisplay-Type-Default.patch \
        file://0005-GLFence-add-WEBKIT_DISABLE_GL_FENCE-opt-out.patch \
        file://0006-WPE-SHM-read-back-only-the-damaged-regions.patch \
        file://0007-Treat-application-vnd.hbbtv.xhtml-xml-as-XHTML.patch \
        file://0008-GStreamer-add-Dreambox-quirk-and-hole-punch-quirk.patch \
        file://0009-GStreamer-Dreambox-decoder-position-and-seeking.patch \
        file://0010-GStreamer-Dreambox-negotiate-the-decoder-with-the-embedder.patch \
        file://0011-GStreamer-Dreambox-hole-punch-scale.patch \
        file://0012-GStreamer-Dreambox-hole-punch-dry-run.patch \
        file://0013-WPE-SHM-fast-read-back-through-an-ION-pixmap-surface-on-Dreambox.patch \
        file://0014-WebKitWebSrc-a-416-at-the-end-of-the-file-is-end-of-stream.patch \
        file://0015-WebKitWebSrc-do-not-EOS-a-spurious-EOF-probe-that-pre-empted-real-content.patch \
        file://0016-GStreamer-bounded-buffering-for-large-progressive-downloads.patch \
        file://0017-WPE-join-and-register-with-Nexus-before-any-EGL-call.patch \
    ')
}
# 0003-0006: vendor EGL (Broadcom V3D) without GBM/Mesa surfaceless: the default EGL display and the WPE platform fixes it needs.
# 0007: HbbTV - application/vnd.hbbtv.xhtml+xml is XHTML.
# 0008-0012: <video> plays on the hardware video plane (hole punch quirk for dvbvideosink/dvbaudiosink), decoder position and seeking,
#            decoder hand-over with the embedder, view scale, dry run for tests.
# 0013: frame read-back through an ION pixmap surface (4-9x faster than glReadPixels on the Dreambox V3D driver); Skia's readPixels() is the fallback.
# 0014: webkitwebsrc: a 416 for a range that starts at the end of the file is the end of the stream, not an error (an MP4 with a small box after a big
#       'mdat' made the demuxer ask for the byte at the size of the file: "Received 416 HTTP error code", the whole playback failed).
# 0015: webkitwebsrc: when a spurious at-EOF probe pre-empts a real, unserved request, surface a visible playback error instead of a silent
#       EOS (0014's own 416-to-EOS conversion was, unintentionally, also matching this case: the real content was never delivered, but the
#       whole element quietly ended as if it had). A safety net, not the actual fix - see 0016.
# 0016: never request unbounded "download" mode for progressive playback (use the same bounded ring buffer as blob URIs instead, and never
#       set GST_PLAY_FLAG_DOWNLOAD). This is the real fix for the >=4GiB-progressive-MP4-never-starts bug that 0014/0015 were only reacting
#       to symptoms of: for a multi-GiB file, downloadbuffer's own eager, unbounded prefetch starves qtdemux's small pull-mode probe reads
#       for tens of seconds to minutes (confirmed: 89s in one reproduction), during which nothing plays and nothing errors. Removing the
#       unbounded prefetch removes the starvation itself; as a side effect for progressive MP4, qtdemux also falls back to its simpler
#       push-mode/adapter state machine (transitions to MOVIE state right after moov, no full-file scan needed). 0014/0015 stay as a safety
#       net for any other timing collision on the same shared mutex; they should now rarely if ever trigger.
# 0017: PlatformDisplayDefault::create() joins Nexus (NxClient_Join) and registers the EGL memory/display interface
#       (NXPL_RegisterNexusDisplayPlatform, libnxpl.so) before its existing eglGetDisplay() call, fixing "Memory interface not registered" /
#       eglInitialize abort on Nexus-based Broadcom boxes (GigaBlue gbquad4kpro confirmed 2026-09-23 via tools/vuplus-probe). Pure runtime
#       dlopen/dlsym detection, no link-time dependency - true no-op on the DM900 (libvc5dream, no Nexus at all), regression-tested clean.

# Vendor eglplatform.h falls back to X11 types unless BROADCOM_PLATFORM is set
# (see the libepoxy bbappend).
CFLAGS:append = " -DBROADCOM_PLATFORM"
CXXFLAGS:append = " -DBROADCOM_PLATFORM"

# KEPT (measured 2026-09-22, see memory: ~2.5% faster on a synthetic JS benchmark, builds and smoke-tests clean, no downside found).
# ENABLE_C_LOOP's CMake option is OFF for our target (WebKitFeatures.cmake wants JSC's native ARMv7 LLInt assembly interpreter, not the
# portable C++ CLoop one) - but an "off" WebKit CMake option never reaches the compiler as a -D flag at all (only "on" options get a bare,
# unvalued one), so PlatformEnable.h never sees it and falls back to deriving it itself: since ENABLE_JIT is unconditionally forced to 0 for
# our 32-bit value representation and the CPU is neither x86-64 nor ARM64, that fallback picks CLoop (1) - the slower portable interpreter,
# silently overriding what CMake actually wanted. This line forces the value CMake already intended, explicitly.
CFLAGS:append = " -DENABLE_C_LOOP=0"
CXXFLAGS:append = " -DENABLE_C_LOOP=0"

# The build is reproducible as it stands: the tarball plus the recipe's own two patches plus the seventeen above, in this order.
#
# Development mode (incremental rebuilds): OE wipes the build directory whenever SRC_URI changes, and every source fix would cost a
# clean ~2h rebuild. Instead, build from a persistent, already-patched tree with externalsrc, in local.conf like the other packages:
#     EXTERNALSRC:pn-wpewebkit = "/home/alpha/wpe-src/wpewebkit-2.54.0"
#     EXTERNALSRC_BUILD:pn-wpewebkit = "/home/alpha/wpe-src/build"
# (the tree = tarball + the patches in this layer; tools/build/prep_src.sh makes it). The SRC_URI patches are ignored while it is set.

# WebKit compile jobs are memory hungry (unified builds: several GB each).
# -k 0: keep going after a failed compile so one run reports every error.
PARALLEL_MAKE = "-j 6 -k 0"

# r1: patch 0013 (fast frame read-back). A new package revision so that opkg upgrades the package on the box. PKGR, not PR: PR reaches
# do_configure, whose re-run would delete the development build directory (see above); PKGR only reaches the packaging tasks.
# r2: patch 0014 (416 at the end of the file).
# r3: EXPERIMENT, KEEP (measured 2026-09-22: real but small, ~2.5% faster on a synthetic JS benchmark; builds and smoke-tests clean, no downside found) -
# CFLAGS/CXXFLAGS += -DENABLE_C_LOOP=0, forcing JSC's native ARMv7 LLInt assembly interpreter instead of the portable CLoop it silently falls back to
# with JIT off. No source patch, so no PKGR-worthy change in the usual sense - bumped anyway so opkg can tell this build apart from r2.
# r4: TRIED AND REVERTED 2026-09-22 - restored the ARMv7/hardfp/Linux baseline-JIT ENABLE_JIT carve-out that existed through at least
# wpewebkit-2.52.0 and was silently dropped by 2.54.0. It built, linked, and ran (real ~1.6x JS speedup measured), and several genuine
# 32-bit-JIT bugs were found and fixed along the way - but a real HbbTV page (a Redux-style immutable-update helper doing a first-property
# write on a fresh object, AccessType::PutByValStrict) reliably crashes the WebProcess, and the exact cause was not found despite deep
# investigation (see memory: project_hbbtv2_wpe_orb_plan.md). Upstream WebKit has since deleted 32-bit JSVALUE32_64 support from the
# baseline JIT entirely rather than fix bugs like this one, so there is no newer reference implementation to compare against either.
# Reverted back to r3's behaviour (PlatformEnable.h's carve-out removed again); the JIT source-level fixes stay in the dev tree
# (/home/alpha/wpe-src/wpewebkit-2.54.0, all now dead code with ENABLE_JIT back at 0) in case this is revisited later.
# r5: patch 0015 (don't EOS a spurious at-EOF probe that pre-empted real content) - safety net, see r6.
# r6: patch 0016 (bounded buffering instead of unbounded "download" mode) - the real fix: >=4GiB progressive MP4 playback silently never
# starting, verified 2026-09-23 against a synthetic 5,014,522,180-byte file (matching a real failing ZDF film's size) and its
# 4,238,966,549-byte (working) counterpart; both now reach MOVIE state and deliver frames within ~5s, reproducibly.
# r7: patch 0017 (join + register with Nexus before any EGL call) - fixes eglInitialize's "Memory interface not registered" abort on
# Nexus-based Broadcom boxes (GigaBlue confirmed via tools/vuplus-probe). Regression-tested on the DM900 (no Nexus libs, confirmed
# no-op) - not yet tested on an actual Nexus-based box with the full WebKit path (only the standalone probe confirmed the sequence).
PKGR = "r7"
