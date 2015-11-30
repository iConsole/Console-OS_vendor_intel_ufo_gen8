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

#ifndef INTEL_UFO_HWC_IDISPLAY_OVERSCAN_CONTROL_H
#define INTEL_UFO_HWC_IDISPLAY_OVERSCAN_CONTROL_H

#include <binder/IInterface.h>
#include <binder/Parcel.h>


namespace intel {
namespace ufo {
namespace hwc {
namespace services {


using namespace android;


/**
 * Allows control of HDMI overscan
 */
class IDisplayOverscanControl : public IInterface
{
public:
    DECLARE_META_INTERFACE(DisplayOverscanControl);

    enum
    {
        MAX_OVERSCAN = 100,     // The limit of the control parameters are +/-MAX_OVERSCAN inclusive.
        RANGE        = 15,      // RANGE describes the % of the display size a max control setting will adjust by.
    };

    /// Set overscan in the range +/-MAX_OVERSCAN inclusive.
    // -ve : zoom/crop the image  (increase display overscan).
    // +ve : shrink the image (decrease display overscan).
    virtual status_t setOverscan(int32_t xoverscan, int32_t yoverscan) = 0;
    // Get last set overscan.
    // Returns INVALID_OPERATION if overscan has not been set and xoverscan/yoverscan are untouched.
    virtual status_t getOverscan(int32_t *xoverscan, int32_t *yoverscan) = 0;
};


/**
 */
class BnDisplayOverscanControl : public BnInterface<IDisplayOverscanControl>
{
public:
    virtual status_t onTransact(uint32_t, const Parcel&, Parcel*, uint32_t);
};


} // namespace services
} // namespace hwc
} // namespace ufo
} // namespace intel

#endif // INTEL_UFO_HWC_IDISPLAY_OVERSCAN_CONTROL_H
