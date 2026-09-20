SUMMARY = "Headless WPE WebKit smoke test (HbbTV 2.0 experiment)"
DESCRIPTION = "Loads a test page in the WPE Platform API headless display and writes a snapshot, \
to check that WPE renders on a box with only a vendor EGL/GLES2."
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://wpe_shot.c"

S = "${UNPACKDIR}"

DEPENDS = "wpewebkit glib-2.0 libsoup"

inherit pkgconfig

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} ${S}/wpe_shot.c -o ${B}/wpe_shot \
        $(pkg-config --cflags --libs wpe-webkit-2.0 wpe-platform-headless-2.0)
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/wpe_shot ${D}${bindir}/wpe_shot
}
