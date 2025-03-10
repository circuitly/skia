/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkPictureShader_DEFINED
#define SkPictureShader_DEFINED

#include "include/core/SkTileMode.h"
#include "src/shaders/SkShaderBase.h"
#include <atomic>

class SkArenaAlloc;
class SkBitmap;
class SkPicture;

/*
 * An SkPictureShader can be used to draw SkPicture-based patterns.
 *
 * The SkPicture is first rendered into a tile, which is then used to shade the area according
 * to specified tiling rules.
 */
class SkPictureShader : public SkShaderBase {
public:
    static sk_sp<SkShader> Make(sk_sp<SkPicture>, SkTileMode, SkTileMode, SkFilterMode,
                                const SkMatrix*, const SkRect*);

#if SK_SUPPORT_GPU
    std::unique_ptr<GrFragmentProcessor> asFragmentProcessor(const GrFPArgs&) const override;
#endif
#ifdef SK_GRAPHITE_ENABLED
    void addToKey(const skgpu::graphite::KeyContext&,
                  skgpu::graphite::PaintParamsKeyBuilder*,
                  skgpu::graphite::PipelineDataGatherer*) const override;
#endif

    SkPictureShader(sk_sp<SkPicture>, SkTileMode, SkTileMode, SkFilterMode, const SkRect*);

protected:
    SkPictureShader(SkReadBuffer&);
    void flatten(SkWriteBuffer&) const override;
    bool appendStages(const SkStageRec&, const MatrixRec&) const override;
    skvm::Color onProgram(skvm::Builder*, skvm::Coord device, skvm::Coord local, skvm::Color paint,
                          const SkMatrixProvider&, const SkMatrix* localM, const SkColorInfo& dst,
                          skvm::Uniforms* uniforms, SkArenaAlloc* alloc) const override;

#ifdef SK_ENABLE_LEGACY_SHADERCONTEXT
    Context* onMakeContext(const ContextRec&, SkArenaAlloc*) const override;
#endif

private:
    SK_FLATTENABLE_HOOKS(SkPictureShader)

    sk_sp<SkShader> rasterShader(const SkMatrix&,
                                 SkColorType dstColorType,
                                 SkColorSpace* dstColorSpace,
                                 const SkSurfaceProps& props) const;

    sk_sp<SkPicture>    fPicture;
    SkRect              fTile;
    SkTileMode          fTmx, fTmy;
    SkFilterMode        fFilter;

    using INHERITED = SkShaderBase;
};

#endif // SkPictureShader_DEFINED
