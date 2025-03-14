/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkJpegDecoderMgr_DEFINED
#define SkJpegDecoderMgr_DEFINED

#include "include/codec/SkCodec.h"
#include "include/private/SkEncodedInfo.h"
#include "include/private/base/SkNoncopyable.h"
#include "src/codec/SkJpegPriv.h"
#include "src/codec/SkJpegUtility.h"

extern "C" {
    #include "jpeglib.h"
}

class SkStream;

class JpegDecoderMgr : SkNoncopyable {
public:

    /*
     * Print a useful error message and return false
     */
    bool returnFalse(const char caller[]);

    /*
     * Print a useful error message and return a decode failure
     */
    SkCodec::Result returnFailure(const char caller[], SkCodec::Result result);

    /*
     * Create the decode manager
     * Does not take ownership of stream
     */
    JpegDecoderMgr(SkStream* stream);

    /*
     * Initialize decompress struct
     * Initialize the source manager
     */
    void  init();

    /*
     * Returns true if it successfully sets outColor to the encoded color,
     * and false otherwise.
     */
    bool getEncodedColor(SkEncodedInfo::Color* outColor);

    /*
     * Free memory used by the decode manager
     */
    ~JpegDecoderMgr();

    /*
     * Get the skjpeg_error_mgr in order to set an error return jmp_buf
     */
    skjpeg_error_mgr* errorMgr() { return &fErrorMgr; }

    /*
     * Get function for the decompress info struct
     */
    jpeg_decompress_struct* dinfo() { return &fDInfo; }

private:

    jpeg_decompress_struct fDInfo;
    skjpeg_source_mgr      fSrcMgr;
    skjpeg_error_mgr       fErrorMgr;
    jpeg_progress_mgr      fProgressMgr;
    bool                   fInit;
};

#endif
