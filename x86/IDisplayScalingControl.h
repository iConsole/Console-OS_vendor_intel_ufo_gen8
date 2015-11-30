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

#ifndef INTEL_UFO_HWC_IDISPLAY_SCALING_CONTROL_H
#define INTEL_UFO_HWC_IDISPLAY_SCALING_CONTROL_H

#include <binder/IInterface.h>
#include <binder/Parcel.h>


namespace intel {
namespace ufo {
namespace hwc {
namespace services {


using namespace android;


/**
 * Allows control of HDMI scaling for content
 * that does not match the native display resolution.
 */
class IDisplayScalingControl : public IInterface
{
public:
    DECLARE_META_INTERFACE(DisplayScalingControl);

    enum EScalingMode
    {
        SCALE_CENTRE  = 0,  // Present the content centred at 1:1 source resolution.
        SCALE_STRETCH,      // Do not preserve aspect ratio - scale to fill the display without cropping.
        SCALE_FIT,          // Preserve aspect ratio - scale to closest edge (may be letterboxed or pillarboxed).
        SCALE_FILL,         // Preserve aspect ratio - scale to fill the display (may crop the content).
        SCALE_MAX_ENUM      // End of enum.
    };

    /// Set scaling to one of EScalingMode.
    // Returns OK if succesful.
    virtual status_t setScaling(EScalingMode eScalingMode) = 0;

    // Get last set scaling.
    // Returns OK if succesful.
    // Returns INVALID_OPERATION if scaling has not been set and eScalingMode is untouched.
    virtual status_t getScaling(EScalingMode *eScalingMode) = 0;
};


/**
 */
class BnDisplayScalingControl : public BnInterface<IDisplayScalingControl>
{
public:
    virtual status_t onTransact(uint32_t, const Parcel&, Parcel*, uint32_t);
};


} // namespace services
} // namespace hwc
} // namespace ufo
} // namespace intel

#endif // INTEL_UFO_HWC_IDISPLAY_SCALING_CONTROL_H
