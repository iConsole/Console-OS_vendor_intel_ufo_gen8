/*
 * INTEL CONFIDENTIAL
 *
 * Copyright 2013 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related to the
 * source code ("Material") are owned by Intel Corporation or its suppliers or
 * licensors. Title to the Material remains with Intel Corporation or its suppliers
 * and licensors. The Material contains trade secrets and proprietary and confidential
 * information of Intel or its suppliers and licensors. The Material is protected by
 * worldwide copyright and trade secret laws and treaty provisions. No part of the
 * Material may be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intels prior express
 * written permission.
 *
 * No license under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or delivery
 * of the Materials, either expressly, by implication, inducement, estoppel
 * or otherwise. Any license under such intellectual property rights must be
 * express and approved by Intel in writing.
 *
 */

#ifndef INTEL_UFO_HWC_IDISPLAY_MODE_CONTROL_H
#define INTEL_UFO_HWC_IDISPLAY_MODE_CONTROL_H

#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace intel {
namespace ufo {
namespace hwc {
namespace services {


using namespace android;


/**
 * Allows change of HDMI display mode.
 */
class IDisplayModeControl : public IInterface
{
public:
    DECLARE_META_INTERFACE(DisplayModeControl);

    struct Info
    {
        uint32_t width;
        uint32_t height;
        uint32_t refresh;
        uint32_t flags;
        uint32_t ratio;

        enum {
            FLAG_NONE           = 0,
            FLAG_PREFERRED      = 1 << 0,
            FLAG_SECURE         = 1 << 1,
            FLAG_INTERLACED     = 1 << 2,
            FLAG_CURRENT        = 1 << 4,
        };
    };

    /// Enumerations for common aspect ratios
    /// Any ratio can be supported, with the upper 16 bits containing one dimension,
    /// the lower 16 bits contains the lower dimension
    enum {
        ASPECT_RATIO_ANY    = 0x00000000,
        ASPECT_RATIO_4_3    = 0x00040003,
        ASPECT_RATIO_16_9   = 0x00100009,
    };

    /// restore default mode
    virtual status_t restorePreferredMode() = 0;

    /// query all available modes
    virtual Vector<Info> getAvailableModes() = 0;

    /// get current mode
    virtual status_t getMode(uint32_t *width, uint32_t *height, uint32_t *refresh, uint32_t *flags, uint32_t *ratio) = 0;

    /// set mode
    virtual status_t setMode(uint32_t width, uint32_t height, uint32_t refresh, uint32_t flags, uint32_t ratio) = 0;

#ifdef EXPERIMENTAL
    // scaling
    enum {
        SCALE_KEEP_ASPECT_RATIO = 0,
        SCALE_CENTER            = 1,
        SCALE_FULLSCREEN        = 2,
    };
    virtual status_t getScaleMode(uint32_t *scale) = 0;
    virtual status_t setScaleMode(uint32_t scale) = 0;
#endif
};



/**
 */
class BnDisplayModeControl : public BnInterface<IDisplayModeControl>
{
public:
    virtual status_t onTransact(uint32_t, const Parcel&, Parcel*, uint32_t);
};


} // namespace services
} // namespace hwc
} // namespace ufo
} // namespace intel

#endif // INTEL_UFO_HWC_IDISPLAY_MODE_CONTROL_H
