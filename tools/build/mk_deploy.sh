#!/bin/bash
# Assemble a self-contained WPE test deployment for the DM900 (private prefix, nothing system-wide).
set -uo pipefail
SP=/mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad
RT=/home/alpha/wpe-test/pkg/rt
T=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp
COMP=$T/sysroots-components/cortexa15hf-neon-vfpv4
D=/home/alpha/wpe-test/deploy
rm -rf "$D"; mkdir -p "$D/lib" "$D/libexec/wpe-webkit-2.0" "$D/lib/wpe-webkit-2.0/injected-bundle" "$D/bin" "$D/fonts"

# names of libs already on the box (from `ls /lib /usr/lib`)
grep -E "\.so" "$SP/boxlibs.txt" | tr -d '\r' | sort -u > /tmp/box_names.txt

cp "$RT/usr/lib/libWPEWebKit-2.0.so.1.11.3" "$D/lib/libWPEWebKit-2.0.so.1"
# The helper-process dir is compiled in with no env override. Patch the PRIVATE copy to a same-length
# path under /tmp (a symlink to the deployed helpers is created by env.sh) so nothing under /usr is touched.
python3 - "$D/lib/libWPEWebKit-2.0.so.1" <<'PYEOF'
import sys
p = sys.argv[1]
old = b"/usr/libexec/wpe-webkit-2.0\x00"
new = b"/tmp/wpe-libexec/wpekit-2.0\x00"
assert len(old) == len(new), (len(old), len(new))
data = open(p, "rb").read()
n = data.count(old)
assert n == 1, "expected exactly one occurrence, found %d" % n
open(p, "wb").write(data.replace(old, new))
print("patched libexec path in private lib copy (1 occurrence)")
PYEOF
cp "$RT/usr/libexec/wpe-webkit-2.0/WPEWebProcess" "$RT/usr/libexec/wpe-webkit-2.0/WPENetworkProcess" "$D/libexec/wpe-webkit-2.0/"
cp "$RT/usr/lib/wpe-webkit-2.0/injected-bundle/libWPEInjectedBundle.so" "$D/lib/wpe-webkit-2.0/injected-bundle/"

queue=("$D/lib/libWPEWebKit-2.0.so.1" "$D/libexec/wpe-webkit-2.0/WPEWebProcess" "$D/libexec/wpe-webkit-2.0/WPENetworkProcess" "$D/lib/wpe-webkit-2.0/injected-bundle/libWPEInjectedBundle.so")
declare -A have
have["libWPEWebKit-2.0.so.1"]=1
notfound=()
i=0
while [ $i -lt ${#queue[@]} ]; do
  f=${queue[$i]}; i=$((i+1))
  for n in $(readelf -d "$f" 2>/dev/null | grep NEEDED | sed 's/.*Shared library: \[//; s/\]//'); do
    [ -n "${have[$n]:-}" ] && continue
    if grep -qxF "$n" /tmp/box_names.txt; then have[$n]=box; continue; fi
    src=$(find "$COMP" \( -type f -o -type l \) -name "$n" 2>/dev/null | head -1)
    if [ -z "$src" ]; then have[$n]=missing; notfound+=("$n"); continue; fi
    cp -L "$src" "$D/lib/$n"; have[$n]=added
    queue+=("$D/lib/$n")
  done
done

echo "== added (not on box):"
for n in "${!have[@]}"; do [ "${have[$n]}" = added ] && echo "$(stat -c %s "$D/lib/$n") $n"; done | sort -n | awk '{printf "%9d %s\n",$1,$2}'
echo "== on box (not shipped): $(for n in "${!have[@]}"; do [ "${have[$n]}" = box ] && echo $n; done | wc -l)"
echo "== NOT FOUND anywhere: ${notfound[*]:-none}"

# minimal fontconfig setup (box has no fontconfig): use whatever fonts exist on the box
cat > "$D/fonts.conf" <<'EOF'
<?xml version="1.0"?>
<!DOCTYPE fontconfig SYSTEM "fonts.dtd">
<fontconfig>
  <dir>/usr/share/fonts</dir>
  <dir>/media/hdd/wpe-test/fonts</dir>
  <cachedir>/tmp/wpe-fontconfig-cache</cachedir>
</fontconfig>
EOF

cat > "$D/env.sh" <<'EOF'
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
EOF

chmod +x "$D/libexec/wpe-webkit-2.0/"*
echo "== total deploy size"; du -sh "$D"
echo "== confirm WEBKIT_EXEC_PATH / INJECTED_BUNDLE env names exist in the lib"
strings -a "$D/lib/libWPEWebKit-2.0.so.1" | grep -E "^(WEBKIT_EXEC_PATH|WEBKIT_INJECTED_BUNDLE_PATH|WEBKIT_SKIA_ENABLE_CPU_RENDERING|WEBKIT_DISABLE_SANDBOX_THIS_IS_DANGEROUS|WPE_DISPLAY)$" | sort -u
