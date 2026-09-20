#!/bin/bash
# Patch 0005: WEBKIT_DISABLE_GL_FENCE opt-out for GL/EGL fences (vendor EGL crashes in glFlush after eglCreateSync).
set -euo pipefail
cd /home/alpha/wpe-src/wpewebkit-2.54.0
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-browser/wpewebkit/files

python3 <<'EOF'
def edit(path, old, new, count=1):
    s = open(path).read()
    n = s.count(old)
    assert n == count, "%s: expected %d occurrence(s) of anchor, found %d" % (path, count, n)
    open(path, "w").write(s.replace(old, new))
    print("edited", path)

p = "Source/WebCore/platform/graphics/egl/GLFence.cpp"

# 1. helper + include
edit(p, "namespace WebCore {\n\nWTF_MAKE_TZONE_ALLOCATED_IMPL(GLFence);\n",
     "#include <cstdlib>\n#include <cstring>\n\nnamespace WebCore {\n\nWTF_MAKE_TZONE_ALLOCATED_IMPL(GLFence);\n\n"
     "// Some vendor EGL/GLES drivers advertise EGL 1.5 but crash in glFlush() once an EGL fence sync has been\n"
     "// created (seen on Broadcom V3D set-top box drivers). Allow opting out; callers already fall back to a\n"
     "// synchronous CPU wait (GrSyncCpu::kYes / glFinish) when fences are unsupported.\n"
     "static bool fencesDisabledByEnvironment()\n{\n"
     "    static const bool disabled = [] {\n"
     "        const char* value = getenv(\"WEBKIT_DISABLE_GL_FENCE\");\n"
     "        return value && *value && strcmp(value, \"0\");\n"
     "    }();\n    return disabled;\n}\n")

# 2. isSupported
edit(p, "bool GLFence::isSupported(const GLDisplay& display)\n{\n",
     "bool GLFence::isSupported(const GLDisplay& display)\n{\n    if (fencesDisabledByEnvironment())\n        return false;\n\n")

# 3. create
edit(p, "std::unique_ptr<GLFence> GLFence::create(const GLDisplay& display)\n{\n#if HAVE(GL_FENCE)\n",
     "std::unique_ptr<GLFence> GLFence::create(const GLDisplay& display)\n{\n#if HAVE(GL_FENCE)\n    if (fencesDisabledByEnvironment())\n        return nullptr;\n\n")
EOF

P5="$LAYER/0005-GLFence-add-WEBKIT_DISABLE_GL_FENCE-opt-out.patch"
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] GLFence: add WEBKIT_DISABLE_GL_FENCE opt-out"
  echo
  echo "Broadcom V3D set-top box drivers advertise EGL 1.5 but crash inside glFlush() after"
  echo "eglCreateSync(EGL_SYNC_FENCE) (memcpy from a NULL pointer in the platform layer)."
  echo "Add an environment opt-out so GLFence::isSupported()/create() report no fence support;"
  echo "callers then use their existing synchronous fallback."
  echo
  echo "---"
  git diff --no-color
} > "$P5"
sed -n 1,50p "$P5"
git -c user.name=hbbtv2 -c user.email=noreply@localhost commit -qam "0005: GLFence env opt-out" && echo "committed in source tree"
