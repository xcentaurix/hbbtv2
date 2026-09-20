#!/bin/bash
# Patch 0004: handle PlatformDisplay::Type::Default on WPE (SHM frames, surfaceless GL target).
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

# 1. the enum value must exist on WPE
edit("Source/WebCore/platform/graphics/PlatformDisplay.h",
     "#if PLATFORM(GTK) || OS(ANDROID)\n        Default,\n#endif\n",
     "#if PLATFORM(GTK) || PLATFORM(WPE) || OS(ANDROID)\n        Default,\n#endif\n")

# 2. GL target: the default display supports surfaceless contexts, use the surfaceless target
edit("Source/WebCore/platform/graphics/egl/GLContext.cpp",
     "    case PlatformDisplay::Type::Surfaceless:\n        return GLContext::Target::Surfaceless;\n",
     "    case PlatformDisplay::Type::Surfaceless:\n        return GLContext::Target::Surfaceless;\n"
     "#if PLATFORM(WPE) && !OS(ANDROID)\n    case PlatformDisplay::Type::Default:\n        return GLContext::Target::Surfaceless;\n#endif\n")

# 3. frame transport: no dma-buf on this display, deliver frames through shared memory
edit("Source/WebKit/WebProcess/WebPage/CoordinatedGraphics/AcceleratedSurface.cpp",
     "#if USE(GBM)\n    case PlatformDisplay::Type::GBM:\n        if (display.eglExtensions().EXT_image_dma_buf_import) {\n",
     "#if PLATFORM(WPE) && !OS(ANDROID)\n    case PlatformDisplay::Type::Default:\n        m_type = Type::SharedMemory;\n        break;\n#endif\n"
     "#if USE(GBM)\n    case PlatformDisplay::Type::GBM:\n        if (display.eglExtensions().EXT_image_dma_buf_import) {\n")
EOF

P4="$LAYER/0004-WPE-handle-PlatformDisplay-Type-Default.patch"
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] WPE: handle PlatformDisplay::Type::Default"
  echo
  echo "Follow-up to enabling PlatformDisplayDefault for WPE: the Type::Default enum"
  echo "value was GTK/Android only, so define it for WPE too, use the surfaceless GL"
  echo "target for it (the default display supports surfaceless contexts), and deliver"
  echo "frames through shared memory (no dma-buf export on such displays)."
  echo
  echo "---"
  git diff --no-color
} > "$P4"
cat "$P4" | sed -n 1,60p

git -c user.name=hbbtv2 -c user.email=noreply@localhost commit -qam "0004: WPE handle PlatformDisplay::Type::Default" && echo "committed in source tree"
