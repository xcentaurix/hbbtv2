#!/bin/bash
set -euo pipefail
cd /home/alpha/openvix/build-enviroment
L=meta-hbbtv2
mkdir -p "$L/conf" "$L/recipes-browser/wpewebkit"

cat > "$L/conf/layer.conf" <<'EOF'
BBPATH .= ":${LAYERDIR}"
BBFILES += "${LAYERDIR}/recipes-*/*/*.bb ${LAYERDIR}/recipes-*/*/*.bbappend"

BBFILE_COLLECTIONS += "hbbtv2"
BBFILE_PATTERN_hbbtv2 := "^${LAYERDIR}/"
BBFILE_PRIORITY_hbbtv2 = "9"

LAYERDEPENDS_hbbtv2 = "core openembedded-layer webkit"
LAYERSERIES_COMPAT_hbbtv2 = "wrynose"
EOF

cat > "$L/recipes-browser/wpewebkit/wpewebkit_%.bbappend" <<'EOF'
# HbbTV 2.0 experiment: minimal WPE WebKit for a box with only the vendor
# EGL/GLES2 (no DRM/GBM, no Wayland). Goal of step 1: render a page into a
# buffer through the WPE Platform API headless platform.

# OpenViX opts out of the "opengl" distro feature distro-wide (every box uses a
# vendor EGL), so features_check would skip this recipe. Bypass it for wpewebkit
# only instead of flipping a distro-wide feature, which would rebuild much of
# the image.
REQUIRED_DISTRO_FEATURES = ""

PACKAGECONFIG = "dfg-jit jit remote-inspector unified-builds woff2 wpe-platform wpe-platform-headless"

# WebKit compile jobs are memory hungry (unified builds: several GB each).
PARALLEL_MAKE = "-j 4"
EOF

find "$L" -type f | sort

cd builds/openvix/developer/dm900/conf
[ -f bblayers.conf.pre-wpe ] || cp bblayers.conf bblayers.conf.pre-wpe
if ! grep -q meta-hbbtv2 bblayers.conf; then
  sed -i 's#^BBLAYERS = "#BBLAYERS = "/home/alpha/openvix/build-enviroment/meta-hbbtv2 /home/alpha/openvix/build-enviroment/meta-webkit #' bblayers.conf
fi
grep '^BBLAYERS' bblayers.conf | cut -c1-240
