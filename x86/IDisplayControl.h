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

#ifndef INTEL_UFO_HWC_IDISPLAY_CONTROL_H
#define INTEL_UFO_HWC_IDISPLAY_CONTROL_H

// #include <binder/IInterface.h>
// #include <binder/Parcel.h>

#include "IDisplayScalingControl.h"
#include "IDisplayOverscanControl.h"
#include "IDisplayModeControl.h"
#include "IColorControl.h"
#include "IDisplayBlankControl.h"


namespace intel {
namespace ufo {
namespace hwc {
namespace services {


using namespace android;


/**
 * Allows control of HDMI display
 */
class IDisplayControl : public IInterface
{
public:
    DECLARE_META_INTERFACE(DisplayControl);

    /// restore default control (overscan, scale, ...)
    virtual status_t restoreAllDefaults() = 0;

    virtual sp<IDisplayOverscanControl> getOverscanControl() = 0;
    virtual sp<IDisplayScalingControl> getScalingControl() = 0;
    virtual sp<IDisplayModeControl> getModeControl() = 0;
    virtual sp<IDisplayBlankControl> getBlankControl() = 0;

#ifdef EXPERIMENTAL
    ///
    virtual sp<IColorControl> getBrightnessControl() = 0;
    virtual sp<IColorControl> getContrastControl() = 0;
    virtual sp<IColorControl> getGammaControl() = 0;
    virtual sp<IColorControl> getHueControl() = 0;
    virtual sp<IColorControl> getSaturationControl() = 0;
#else
    enum {
        COLOR_BRIGHTNESS,
        COLOR_CONTRAST,
        COLOR_GAMMA,
        COLOR_SATURATION,
        COLOR_HUE,
    };
    virtual sp<IColorControl> getColorControl(int32_t param) = 0;
#endif

#ifdef EXPERIMENTAL
    /// switch into power safe mode (soft disconnect?)
    virtual status_t powerOff(int off) = 0;
#endif

};


/**
 */
class BnDisplayControl : public BnInterface<IDisplayControl>
{
public:
    virtual status_t onTransact(uint32_t, const Parcel&, Parcel*, uint32_t);
};



} // namespace services
} // namespace hwc
} // namespace ufo
} // namespace intel

#endif // INTEL_UFO_HWC_IDISPLAY_CONTROL_H
