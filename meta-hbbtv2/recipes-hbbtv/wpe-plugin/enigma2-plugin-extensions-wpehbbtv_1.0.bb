SUMMARY = "HbbTV 2.0 for enigma2 (WPE WebKit + Open Red Button)"
DESCRIPTION = "Runs HbbTV applications on top of enigma2: wpe_fb renders them with WPE WebKit onto the framebuffer, the Open Red \
Button engine provides the HbbTV/OIPF objects, and <video> plays on the hardware video plane through dvbvideosink. The plugin \
forwards the remote control to the application and hands the decoder over from the live service and back."
AUTHOR = "xcentaurix"
HOMEPAGE = "https://github.com/xcentaurix/hbbtv2"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

# wpe_fb.c is shared with the bring-up tools in wpe-shot/, the test pages with the ORB recipe: use them from where they are
FILESEXTRAPATHS:prepend := "${THISDIR}/../wpe-shot/files:${THISDIR}/../orb/files:"

SRC_URI = " \
    file://wpe_fb.c \
    file://WPEHbbTV/__init__.py \
    file://WPEHbbTV/plugin.py \
    file://WPEHbbTV/keymap.xml \
    file://run_wpe.sh \
    file://fonts.conf \
    file://orb_hello.html \
    file://video_test.html \
"

S = "${UNPACKDIR}"

# wpewebkit: the browser engine and its headers; orb: the engine, orb_host.h and the libraries wpe_fb is linked against
DEPENDS = "wpewebkit orb glib-2.0 libsoup"
# wpe_fb loads the web process extension and the platform library of ORB by path (dlopen), which the shared library dependencies do not show.
# No "enigma2" here: it is always there on a box, and bitbake would build everything a package runtime-depends on (a whole enigma2 build).
RDEPENDS:${PN} = "orb"

inherit pkgconfig

PLUGINDIR = "${libdir}/enigma2/python/Plugins/Extensions/WPEHbbTV"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} -Wall ${S}/wpe_fb.c -o ${B}/wpe_fb \
        -I${STAGING_INCDIR}/orb \
        $(pkg-config --cflags --libs wpe-webkit-2.0 wpe-platform-2.0 libsoup-3.0 gio-2.0 glib-2.0) \
        -lORBHost -lm
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/wpe_fb ${D}${bindir}/wpe_fb

    install -d ${D}${PLUGINDIR}/pages
    install -m 0644 ${S}/WPEHbbTV/__init__.py ${D}${PLUGINDIR}/__init__.py
    install -m 0644 ${S}/WPEHbbTV/plugin.py ${D}${PLUGINDIR}/plugin.py
    install -m 0644 ${S}/WPEHbbTV/keymap.xml ${D}${PLUGINDIR}/keymap.xml
    install -m 0755 ${S}/run_wpe.sh ${D}${PLUGINDIR}/run_wpe.sh
    install -m 0644 ${S}/fonts.conf ${D}${PLUGINDIR}/fonts.conf
    install -m 0644 ${S}/orb_hello.html ${D}${PLUGINDIR}/pages/orb_hello.html
    install -m 0644 ${S}/video_test.html ${D}${PLUGINDIR}/pages/video_test.html
}

FILES:${PN} = "${bindir}/wpe_fb ${PLUGINDIR}"

pkg_postinst:${PN}() {
#!/bin/sh
echo "***********************************"
echo "*          WPE HbbTV 2.0          *"
echo "*   WPE WebKit + Open Red Button  *"
echo "*               by                *"
echo "*           xcentaurix            *"
echo "***********************************"
echo ""
echo "Plugin successfully installed."
echo "Please restart Enigma2 now!"
exit 0
}

pkg_postrm:${PN}() {
#!/bin/sh
# what is left after the files are gone: compiled python. Not on an upgrade, which runs this with something else than "remove".
if [ "$1" = "remove" ]; then
	rm -rf $D${libdir}/enigma2/python/Plugins/Extensions/WPEHbbTV > /dev/null 2>&1
fi
exit 0
}
