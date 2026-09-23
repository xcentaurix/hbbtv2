#!/bin/sh
# vu_probe.sh - READ-ONLY questions to a set-top box (VU+ 4K etc.) for an HbbTV 2.0 port (WPE WebKit + Open Red Button, enigma2 plugin).
# It changes nothing and draws nothing on the TV; the only thing it starts is vu_egl_probe, which opens EGL/GLES OFFSCREEN for a few seconds (in a second
# process next to enigma2; a hang or crash of that one is caught: it ends itself after 20 s).
#
#   usage:   sh vu_probe.sh            (in the directory that holds vu_egl_probe; enigma2 running normally, nothing recording, as root)
#   result:  /tmp/vu_probe_report.txt  - send that file back.
OUT=/tmp/vu_probe_report.txt
HERE=$(cd "$(dirname "$0")" && pwd)
echo "vu_probe: collecting, takes about half a minute ..."
exec 3>&1 # the terminal, for the last line
exec >"$OUT" 2>&1

sect() { echo; echo "=================== $*"; }

sect "who and when"
date
uname -a
cat /proc/device-tree/model 2>/dev/null; echo
cat /etc/hostname 2>/dev/null
cat /proc/stb/info/model /proc/stb/info/boxtype /proc/stb/info/chipset 2>/dev/null
cat /etc/image-version 2>/dev/null
cat /etc/os-release 2>/dev/null | head -8
cat /etc/issue 2>/dev/null

sect "cpu and memory"
grep -E "model name|Processor|CPU implementer|CPU architecture|CPU part|Features|Hardware" /proc/cpuinfo | sort -u
echo "cores: $(grep -c ^processor /proc/cpuinfo)"
head -6 /proc/meminfo
free 2>/dev/null | head -3
df -h / /tmp /media/hdd /media/usb 2>/dev/null

sect "userland: C library, python, gstreamer"
(ldd --version 2>&1 | head -1) ; ls /lib/libc.so* /lib/libc-* /lib/libc.so.6 2>/dev/null
python3 --version 2>&1
(gst-inspect-1.0 --version 2>&1 | head -2)
echo "-- gstreamer plugins of interest"
ls /usr/lib/gstreamer-1.0 2>/dev/null | grep -i -E "dvb|libav|dash|adaptive|isomp4|matroska|mpegts|videoparsers|audioparsers|soup|playback|app|opengl|gl" | tr '\n' ' '; echo
echo "-- dvb sinks"
gst-inspect-1.0 dvbvideosink 2>&1 | head -45
gst-inspect-1.0 dvbaudiosink 2>&1 | head -30

sect "enigma2 and image packages that matter"
(opkg list-installed 2>/dev/null | grep -i -E "^enigma2 |gstreamer1.0 |gst-plugin-dvb|gst-plugins-(base|good|bad)|libsoup|libicu|icu |harfbuzz|epoxy|libxkbcommon|fontconfig|libxslt|woff2|libwpe|webkit|gles|egl|nexus|v3d|vuplus|libnxpl|libgbm|mesa|drm|libpng|libjpeg|cairo|freetype|libxml2|sqlite|libcurl|curl|openssl|zlib|wayland" | sort)

sect "graphics stack: libraries and devices"
ls -l /usr/lib/libEGL* /usr/lib/libGLES* /usr/lib/libgbm* /usr/lib/libnxpl* /usr/lib/libnexus* /usr/lib/libv3d* /usr/lib/libvc5* /usr/lib/libbrcm* /usr/lib/libwayland* 2>/dev/null
for l in /usr/lib/libEGL.so.1 /usr/lib/libGLESv2.so.2; do echo "-- ldd $l"; ldd $l 2>&1 | head -20; done
ls -l /dev/fb* /dev/dri /dev/ion /dev/nexus* /dev/mali* /dev/galcore /dev/vc* 2>/dev/null
cat /proc/fb 2>/dev/null
for f in /sys/class/graphics/fb0/*; do [ -f "$f" ] && echo "$f: $(head -c 100 "$f" 2>/dev/null | tr '\n' ' ')"; done 2>/dev/null
ls /usr/lib/libEGL* >/dev/null 2>&1 || echo "(no /usr/lib/libEGL* - some Nexus-based images expose EGL/GLES through libnxpl.so or bundle it directly in the GPU driver .so instead of a libEGL.so symlink)"
echo "-- every libEGL*/libGLESv2*/libnxpl*/libv3d* anywhere on the box (not just /usr/lib; up to 60 s)"
timeout 60 find / -xdev -type f \( -iname "libEGL*" -o -iname "libGLESv2*" -o -iname "libnxpl*" -o -iname "libv3d*" -o -iname "libnexus*" \) 2>/dev/null | while read -r f; do echo "$f  ($(wc -c <"$f" 2>/dev/null) bytes)"; done

sect "video plane and decoders (the place of the live picture)"
ls /dev/dvb/adapter0 2>/dev/null | tr '\n' ' '; echo
ls -l /dev/dvb/adapter0/video0 /dev/dvb/adapter0/audio0 2>&1
ls /proc/stb/vmpeg/0 2>/dev/null | tr '\n' ' '; echo
for f in dst_left dst_top dst_width dst_height dst_apply aspect; do echo "vmpeg/0/$f: $(cat /proc/stb/vmpeg/0/$f 2>&1)"; done
ls /proc/stb/video 2>/dev/null | tr '\n' ' '; echo
for f in aspect policy policy2 alpha videomode; do echo "video/$f: $(cat /proc/stb/video/$f 2>&1 | head -1)"; done
echo "-- who holds the decoder now"
for p in /proc/[0-9]*; do for f in $p/fd/*; do case "$(readlink $f 2>/dev/null)" in /dev/dvb/adapter0/video0|/dev/dvb/adapter0/audio0) echo "$(basename $p) $(cat $p/comm 2>/dev/null) $(readlink $f)";; esac; done; done 2>/dev/null | sort -u

sect "enigma2 skin resolution and osd"
grep -E "config.osd.(alpha|dst_|xres|yres|resolution)|config.av.osd_alpha|config.skin.primary_skin" /etc/enigma2/settings 2>/dev/null | head -12
cat /proc/stb/fb/dst_width /proc/stb/fb/dst_height 2>/dev/null

sect "EGL / GLES offscreen probe (vu_egl_probe)"
chmod +x "$HERE/vu_egl_probe" 2>/dev/null  # tar does not always preserve the executable bit; make sure of it ourselves
if [ -x "$HERE/vu_egl_probe" ]; then
	"$HERE/vu_egl_probe" 2>&1
	echo "exit code: $?"
else
	echo "vu_egl_probe not found (or chmod +x failed) in $HERE"
fi

sect "Nexus client-join symbols (dynsym_dump - no nm/readelf needed on the box)"
# Confirmed from Broadcom's own nxclient.h/nexus_platform_client.h (see hbbtv2/headers/gb-nexus-headers): a process must call
# NxClient_Join() (modern, joins both the nexus driver AND the server app over IPC) or the older NEXUS_Platform_Join() /
# NEXUS_Platform_AuthenticatedJoin(NULL) (driver-only) BEFORE touching any Nexus-backed resource - and EGL on this platform is
# layered on Nexus surface/display objects (EGLNativeDisplayType is just an opaque void* on BROADCOM_PLATFORM, so EGL itself
# gives no clue). A second process calling eglInitialize/eglQueryString without ever joining would dereference NULL exactly like
# the crash reports show. These symbols could live in libnexus*.so, or be statically linked into the vendor EGL/GLES driver
# itself (libv3ddriver.so, libnxpl.so, ...) - so check every EGL-stack library found, not just libnexus*.
chmod +x "$HERE/dynsym_dump" 2>/dev/null
if [ -x "$HERE/dynsym_dump" ]; then
	CANDIDATE_LIBS=$(find /usr/lib /lib -maxdepth 2 \( -iname "libnexus*.so*" -o -iname "libv3d*.so*" -o -iname "libnxpl*.so*" \
		-o -iname "libnxclient*.so*" -o -iname "libEGL*.so*" -o -iname "libGLESv2*.so*" -o -iname "libbrcm*.so*" \) 2>/dev/null | sort -u)
	if [ -n "$CANDIDATE_LIBS" ]; then
		echo "$CANDIDATE_LIBS" | while read -r LIB; do
			echo "-- $LIB, symbols containing 'join' (NxClient_Join / NEXUS_Platform_Join / NEXUS_Platform_AuthenticatedJoin)"
			"$HERE/dynsym_dump" "$LIB" join 2>&1
			echo "-- same file, symbols containing 'init' (NEXUS_Platform_Init, NxClient init helpers)"
			"$HERE/dynsym_dump" "$LIB" init 2>&1
			echo "-- same file, symbols containing 'nxclient' or 'client'"
			"$HERE/dynsym_dump" "$LIB" client 2>&1
			echo "-- same file, symbols containing 'begl' (BEGL_RegisterMemoryInterface/DisplayInterface/SchedInterface - the vendor's own"
			echo "   EGL/GLES <-> Nexus platform-interface registration API, see hbbtv2/headers/gb-nexus-headers/EGL/begl_*platform.h and"
			echo "   private_nexus.h: report(7) showed NxClient_Join() succeeding but eglInitialize() still asserting 'Memory interface not"
			echo "   registered' at gmem_abstract.c:132 - begl_memplatform.h declares 'extern void BEGL_RegisterMemoryInterface(BEGL_MemoryInterface*)',"
			echo "   which matches that message exactly. If the driver EXPORTS this symbol (and its Display/Sched counterparts), the app is"
			echo "   expected to build the interface struct and call it; if not exported, it's implemented elsewhere (or by the app itself,"
			echo "   which would need Broadcom's own gmem_abstract.c - not present in the header dump we have - to do correctly)."
			"$HERE/dynsym_dump" "$LIB" begl 2>&1
			case "$LIB" in
			*libnxpl*)
				echo "-- $LIB, ALL symbols, unfiltered (report(9): libnxpl.so IMPORTS (undefined, value=0) BEGL_RegisterMemoryInterface/DisplayInterface/"
				echo "   SchedInterface from libv3ddriver.so, which exports real (non-zero) implementations of all three - i.e. libnxpl.so itself is"
				echo "   Broadcom's own working glue that builds a Nexus-backed BEGL_MemoryInterface and calls BEGL_RegisterMemoryInterface for you,"
				echo "   so the app almost certainly just has to call ONE libnxpl.so entry point, not implement gmem_abstract.c from scratch. The only"
				echo "   DEFINED (real) symbols found there so far via the 'client' filter are NXPL_CreateVideoWindowClient/NXPL_ReleaseVideoWindowClient/"
				echo "   NXPL_GetClientID - those look like the VIDEO-DECODE overlay path (parallel to this project's own dvbvideosink hole-punch quirk"
				echo "   on the Dreambox side), not the GLES/EGL graphics path this probe needs. libnxpl.so only has 153 dynamic symbols total (small,"
				echo "   cheap to dump whole) - this full, unfiltered list is to find whatever top-level 'create/init a GLES platform' entry point it"
				echo "   exports that isn't caught by the join/init/client/begl substring filters above (e.g. a name containing neither 'client' nor"
				echo "   any of the other filter words)."
				"$HERE/dynsym_dump" "$LIB" 2>&1
				;;
			esac
		done
	else
		echo "no libnexus*/libv3d*/libnxpl*/libnxclient*/libEGL*/libGLESv2*/libbrcm* found under /usr/lib or /lib"
	fi
else
	echo "dynsym_dump not found (or chmod +x failed) in $HERE"
fi

sect "end"
date
echo "report: $OUT"
echo "vu_probe: done, please send $OUT ($(wc -c <"$OUT") bytes)" >&3
