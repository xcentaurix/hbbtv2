# source this:  . /media/hdd/wpe-test/env.sh
W=/media/hdd/wpe-test
export LD_LIBRARY_PATH=$W/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}
# libWPEWebKit here is patched to look for its helpers in /tmp/wpe-libexec/wpekit-2.0 (tmpfs, gone on reboot)
mkdir -p /tmp/wpe-libexec
[ -e /tmp/wpe-libexec/wpekit-2.0 ] || ln -s $W/libexec/wpe-webkit-2.0 /tmp/wpe-libexec/wpekit-2.0
export WEBKIT_INJECTED_BUNDLE_PATH=$W/lib/wpe-webkit-2.0/injected-bundle
export FONTCONFIG_FILE=$W/fonts.conf
export XDG_RUNTIME_DIR=/tmp/wpe-runtime
export HOME=/tmp/wpe-home
mkdir -p "$XDG_RUNTIME_DIR" "$HOME" /tmp/wpe-fontconfig-cache
chmod 700 "$XDG_RUNTIME_DIR"
# The Dreambox vendor EGL crashes in glFlush() once an EGL fence sync exists (patch 0005 adds this opt-out)
export WEBKIT_DISABLE_GL_FENCE=1
# one-line switches you can export before running:
#   WEBKIT_SKIA_ENABLE_CPU_RENDERING=1   force CPU painting
#   WEBKIT_DISABLE_SANDBOX_THIS_IS_DANGEROUS=1   (no bubblewrap here anyway)
