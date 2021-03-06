/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "SkTypes.h"
#if defined(SK_BUILD_FOR_MAC) || defined(SK_BUILD_FOR_IOS)

#include "SkCGUtils.h"
#include "SkData.h"
#include "SkImageGenerator.h"
#include "SkTemplates.h"

class SkImageGeneratorCG : public SkImageGenerator {
public:
    /*
     * Refs the data if an image generator can be returned.  Otherwise does
     * not affect the data.
     */
    static SkImageGenerator* NewFromEncodedCG(SkData* data);

protected:
    SkData* onRefEncodedData(
#ifdef SK_SUPPORT_GPU_REF_ENCODED_DATA
        GrContext* ctx
#endif
    ) override;

    bool onGetPixels(const SkImageInfo& info, void* pixels, size_t rowBytes, SkPMColor ctable[],
            int* ctableCount) override;

private:
    /*
     * Takes ownership of the imageSrc
     * Refs the data
     */
    SkImageGeneratorCG(const SkImageInfo& info, const void* imageSrc, SkData* data);

    SkAutoTCallVProc<const void, CFRelease> fImageSrc;
    sk_sp<SkData>                           fData;

    typedef SkImageGenerator INHERITED;
};

#endif //defined(SK_BUILD_FOR_MAC) || defined(SK_BUILD_FOR_IOS)
