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
    ')
}
# 0003-0006: vendor EGL (Broadcom V3D) without GBM/Mesa surfaceless: the default EGL display and the WPE platform fixes it needs.
# 0007: HbbTV - application/vnd.hbbtv.xhtml+xml is XHTML.
# 0008-0012: <video> plays on the hardware video plane (hole punch quirk for dvbvideosink/dvbaudiosink), decoder position and seeking,
#            decoder hand-over with the embedder, view scale, dry run for tests.
# 0013: frame read-back through an ION pixmap surface (4-9x faster than glReadPixels on the Dreambox V3D driver); Skia's readPixels() is the fallback.
# 0014: webkitwebsrc: a 416 for a range that starts at the end of the file is the end of the stream, not an error (an MP4 with a small box after a big
#       'mdat' made the demuxer ask for the byte at the size of the file: "Received 416 HTTP error code", the whole playback failed).

# Vendor eglplatform.h falls back to X11 types unless BROADCOM_PLATFORM is set
# (see the libepoxy bbappend).
CFLAGS:append = " -DBROADCOM_PLATFORM"
CXXFLAGS:append = " -DBROADCOM_PLATFORM"

# The build is reproducible as it stands: the tarball plus the recipe's own two patches plus the fourteen above, in this order.
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
PKGR = "r2"
