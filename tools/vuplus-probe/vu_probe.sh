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
ls /usr/lib/libEGL* >/dev/null 2>&1 || echo "(no /usr/lib/libEGL*)"

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
if [ -x "$HERE/vu_egl_probe" ]; then
	"$HERE/vu_egl_probe" 2>&1
	echo "exit code: $?"
else
	echo "vu_egl_probe not found or not executable in $HERE (chmod +x vu_egl_probe)"
fi

sect "end"
date
echo "report: $OUT"
echo "vu_probe: done, please send $OUT ($(wc -c <"$OUT") bytes)" >&3
