#!/bin/bash
# Patch ORBPlatformLoader to honour ORB_PLATFORM_LIB (no hard-coded /usr/lib), keep it as a layer patch.
set -euo pipefail
cd /home/alpha/orb
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/orb/files
F=rdk/ORB/library/src/core/ORBPlatformLoader.cpp
git checkout -q -- "$F"
python3 - <<'EOF'
p = "rdk/ORB/library/src/core/ORBPlatformLoader.cpp"
s = open(p).read()
old_def = '#define ORB_PLATFORM_IMPL_LIBRARY_NAME "/usr/lib/libORBPlatformImpl.so"\n'
new_def = ('#include <cstdlib>\n\n'
           '#define ORB_PLATFORM_IMPL_LIBRARY_NAME "/usr/lib/libORBPlatformImpl.so"\n\n'
           '// Let the environment point at the platform library, so it does not have to live in /usr/lib.\n'
           'static const char *OrbPlatformLibraryName()\n{\n'
           '    const char *path = getenv("ORB_PLATFORM_LIB");\n'
           '    return (path && *path) ? path : ORB_PLATFORM_IMPL_LIBRARY_NAME;\n}\n')
assert s.count(old_def) == 1
s = s.replace(old_def, new_def)
old_open = 'm_lib = dlopen(ORB_PLATFORM_IMPL_LIBRARY_NAME, RTLD_LAZY);'
assert s.count(old_open) == 1
s = s.replace(old_open, 'm_lib = dlopen(OrbPlatformLibraryName(), RTLD_LAZY);')
open(p, "w").write(s)
print("patched", p)
EOF
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] ORBPlatformLoader: honour ORB_PLATFORM_LIB"
  echo
  echo "The platform library path was hard-coded to /usr/lib/libORBPlatformImpl.so. Allow the ORB_PLATFORM_LIB"
  echo "environment variable to override it, so a test or self-contained deployment need not write to /usr/lib."
  echo
  echo "---"
  git diff --no-color -- "$F"
} > "$LAYER/0001-ORBPlatformLoader-honour-ORB_PLATFORM_LIB.patch"
wc -l "$LAYER/0001-ORBPlatformLoader-honour-ORB_PLATFORM_LIB.patch"
