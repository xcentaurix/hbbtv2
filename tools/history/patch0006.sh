#!/bin/bash
# Patch 0006: read back only the damaged regions in the WPE shared-memory render target.
set -euo pipefail
cd /home/alpha/wpe-src/wpewebkit-2.54.0
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-browser/wpewebkit/files

python3 <<'PYEOF'
import re

H = "Source/WebKit/WebProcess/WebPage/CoordinatedGraphics/AcceleratedSurface.h"
C = "Source/WebKit/WebProcess/WebPage/CoordinatedGraphics/AcceleratedSurface.cpp"

def edit(path, old, new, count=1):
    s = open(path).read()
    n = s.count(old)
    assert n == count, "%s: expected %d occurrence(s) of anchor, found %d: %r" % (path, count, n, old[:70])
    open(path, "w").write(s.replace(old, new))
    print("edited", path)

# ---- header -------------------------------------------------------------------------------------------------
edit(H,
"        ~RenderTargetSHMImage();\n\n    private:\n        bool supportsExplicitSync() const override { return false; }\n        void didRenderFrame() override;\n\n        const Ref<WebCore::ShareableBitmap> m_bitmap;\n    };\n",
"        ~RenderTargetSHMImage();\n\n"
"#if ENABLE(DAMAGE_TRACKING)\n"
"        // What changed since this buffer was last filled; the read-back only has to fetch that.\n"
"        void setReadbackDamage(std::optional<WebCore::Damage>&& damage) { m_readbackDamage = WTF::move(damage); }\n"
"#endif\n\n"
"    private:\n        bool supportsExplicitSync() const override { return false; }\n        void didRenderFrame() override;\n\n"
"        const Ref<WebCore::ShareableBitmap> m_bitmap;\n"
"#if ENABLE(DAMAGE_TRACKING)\n        std::optional<WebCore::Damage> m_readbackDamage;\n#endif\n    };\n")

edit(H,
"        bool needsFineGrainedDamage() const { return m_platformWalksDamageRects || m_damageUsedForCompositing; }\n",
"        bool needsFineGrainedDamage() const\n        {\n"
"#if PLATFORM(GTK) || ENABLE(WPE_PLATFORM)\n"
"            // The shared-memory read-back fetches each damaged rect separately, so keep the rects exact.\n"
"            if (m_swapChain.type() == SwapChain::Type::SharedMemory)\n                return true;\n"
"#endif\n"
"            return m_platformWalksDamageRects || m_damageUsedForCompositing;\n        }\n")

# ---- didRenderFrame: hand over the target's damage before didPresent() resets it -----------------------------------
edit(C,
"#if ENABLE(DAMAGE_TRACKING)\n    m_damageTracker.didPresent(*m_target, targetContents);\n",
"#if ENABLE(DAMAGE_TRACKING)\n"
"#if PLATFORM(GTK) || ENABLE(WPE_PLATFORM)\n"
"    // Give a shared-memory target the damage accumulated since it was last filled, before didPresent()\n"
"    // resets that record, so its read-back can be limited to what changed. Without a record (new buffer,\n"
"    // or invalid contents) the target reads back the whole frame.\n"
"    if (m_swapChain.type() == SwapChain::Type::SharedMemory && targetContents != TargetContents::Invalid)\n"
"        static_cast<RenderTargetSHMImage&>(*m_target).setReadbackDamage(std::optional<Damage>(m_damageTracker.damageSinceTargetWasLastCurrent(*m_target)));\n"
"#endif\n"
"    m_damageTracker.didPresent(*m_target, targetContents);\n")

# ---- the read-back itself ------------------------------------------------------------------------------------
s = open(C).read()
start = s.index("void AcceleratedSurface::RenderTargetSHMImage::didRenderFrame()\n{")
end = s.index("\n}\n", start) + 3
new_fn = r'''void AcceleratedSurface::RenderTargetSHMImage::didRenderFrame()
{
    const IntSize size = m_bitmap->size();
    const unsigned rowBytes = m_bitmap->bytesPerRow();
    uint8_t* pixels = m_bitmap->mutableSpan().data();
    const IntRect fullRect { { }, size };

    // Reading a rendered frame back from the GPU can be extremely slow on some set-top-box drivers (about
    // 14 MB/s with the Broadcom V3D driver), which caps a full-frame read-back at a few frames per second.
    // The swap chain already records, per buffer, what changed since that buffer was last filled, so fetch
    // only that. No record (a new buffer, or a full repaint) means the whole frame.
    Vector<IntRect, 1> rects;
    bool partial = false;
#if ENABLE(DAMAGE_TRACKING)
    if (m_readbackDamage && m_readbackDamage->mode() != Damage::Mode::Full) {
        partial = true;
        for (const auto& rect : m_readbackDamage->rectsForPainting()) {
            auto clipped = intersection(rect, fullRect);
            if (!clipped.isEmpty())
                rects.append(clipped);
        }
    }
    m_readbackDamage = std::nullopt;
#endif
    if (!partial)
        rects.append(fullRect);

    static const bool logReadback = getenv("WEBKIT_SHM_READBACK_LOG");
    static const bool verifyReadback = getenv("WEBKIT_SHM_READBACK_VERIFY");

    // Read one rect of the rendered frame into `base`, a buffer laid out like the shared bitmap.
    auto readRect = [&](const IntRect& rect, uint8_t* base) {
        const int width = rect.width();
        const int height = rect.height();
        if (m_surface->useSkia()) {
            if (!m_skiaSurface)
                return;
            SkImageInfo info = SkImageInfo::Make(width, height, SkColorType::kBGRA_8888_SkColorType, SkAlphaType::kPremul_SkAlphaType);
            auto* destination = base + static_cast<size_t>(rect.y()) * rowBytes + static_cast<size_t>(rect.x()) * 4;
            if (m_surface->usesGL()) {
                GLContext::ScopedGLContextCurrent scopedCurrent(*PlatformDisplay::sharedDisplay().skiaGLContext());
                m_skiaSurface->readPixels(info, destination, rowBytes, rect.x(), rect.y());
            } else
                m_skiaSurface->readPixels(info, destination, rowBytes, rect.x(), rect.y());
            return;
        }

        if (!rect.x() && width == size.width() && rowBytes == static_cast<unsigned>(width) * 4) {
            // Full-width band: the rows are contiguous in the bitmap, read straight into it.
            glReadPixels(0, rect.y(), width, height, GL_BGRA, GL_UNSIGNED_BYTE, base + static_cast<size_t>(rect.y()) * rowBytes);
            return;
        }

        Vector<uint8_t> scratch(static_cast<size_t>(width) * height * 4);
        glReadPixels(rect.x(), rect.y(), width, height, GL_BGRA, GL_UNSIGNED_BYTE, scratch.mutableSpan().data());
        for (int row = 0; row < height; ++row) {
            memcpy(base + static_cast<size_t>(rect.y() + row) * rowBytes + static_cast<size_t>(rect.x()) * 4,
                scratch.span().data() + static_cast<size_t>(row) * width * 4, static_cast<size_t>(width) * 4);
        }
    };

    const auto startTime = MonotonicTime::now();
    int64_t pixelsRead = 0;
    for (const auto& rect : rects) {
        readRect(rect, pixels);
        pixelsRead += static_cast<int64_t>(rect.width()) * rect.height();
    }

    if (logReadback) {
        const auto totalPixels = static_cast<int64_t>(size.width()) * size.height();
        WTFLogAlways("[shm-readback] %s: %zu rect(s), %lld px (%.1f%% of the frame), %.1f ms", partial ? "partial" : "full", rects.size(),
            static_cast<long long>(pixelsRead), 100.0 * pixelsRead / std::max<int64_t>(1, totalPixels), (MonotonicTime::now() - startTime).milliseconds());
    }

    if (verifyReadback && partial) {
        // Debug aid: read the whole frame again and compare it with what the partial read-backs left in the bitmap.
        Vector<uint8_t> reference(static_cast<size_t>(rowBytes) * size.height());
        readRect(fullRect, reference.mutableSpan().data());
        size_t badRows = 0;
        int firstBadRow = -1;
        for (int row = 0; row < size.height(); ++row) {
            if (memcmp(pixels + static_cast<size_t>(row) * rowBytes, reference.span().data() + static_cast<size_t>(row) * rowBytes, static_cast<size_t>(size.width()) * 4)) {
                if (firstBadRow < 0)
                    firstBadRow = row;
                ++badRows;
            }
        }
        WTFLogAlways("[shm-readback] verify: %s (%zu of %d rows differ from a full read-back, first at row %d)", badRows ? "MISMATCH" : "ok", badRows, size.height(), firstBadRow);
    }
}
'''
s = s[:start] + new_fn + s[end:]
open(C, "w").write(s)
print("replaced RenderTargetSHMImage::didRenderFrame")
PYEOF

P6="$LAYER/0006-WPE-SHM-read-back-only-the-damaged-regions.patch"
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] WPE: read back only the damaged regions in the shared-memory render target"
  echo
  echo "glReadPixels() from a GPU render target is extremely slow on some set-top-box drivers"
  echo "(~14 MB/s on Broadcom V3D: ~270 ms for a 1280x720 frame), which caps the shared-memory"
  echo "transport at ~3.7 fps whatever the content. The swap chain already records per buffer what"
  echo "changed since that buffer was last filled (SwapChainDamageTracker), so hand that record to the"
  echo "shared-memory target and read back only those rects. New buffers and full repaints still read"
  echo "back the whole frame. Debug switches: WEBKIT_SHM_READBACK_LOG=1 (log path/area/time) and"
  echo "WEBKIT_SHM_READBACK_VERIFY=1 (compare against a full read-back)."
  echo
  echo "---"
  git diff --no-color
} > "$P6"
wc -l "$P6"
git -c user.name=hbbtv2 -c user.email=noreply@localhost commit -qam "0006: SHM partial read-back" && echo "committed in source tree"
