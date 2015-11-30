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

#ifndef INTEL_UFO_HWC_ICOLOR_CONTROL_H
#define INTEL_UFO_HWC_ICOLOR_CONTROL_H

#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace intel {
namespace ufo {
namespace hwc {
namespace services {


using namespace android;


/**
 * Allows tuning display color
 */
class IColorControl : public IInterface
{
public:
    DECLARE_META_INTERFACE(ColorControl);

    virtual status_t restoreDefault() = 0;
    virtual status_t getColorParam(int32_t *value, int32_t *startvalue, int32_t *endvalue) = 0;
    virtual status_t setColorParam(int32_t value) = 0;
};


/**
 */
class BnColorControl : public BnInterface<IColorControl>
{
public:
    virtual status_t onTransact(uint32_t, const Parcel&, Parcel*, uint32_t);
};


} // namespace services
} // namespace hwc
} // namespace ufo
} // namespace intel

#endif // INTEL_UFO_HWC_IDISPLAY_CONTROL_H
