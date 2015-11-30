/*
 * INTEL CONFIDENTIAL
 *
 * Copyright 2013-2014
 * Intel Corporation All Rights Reserved.
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


#ifndef INTEL_UFO_HWC_IDIAGNOSTIC_H
#define INTEL_UFO_HWC_IDIAGNOSTIC_H

#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <utils/String8.h>
#include <utils/Flattenable.h>
#include <utils/Timers.h>
#include <hardware/hwcomposer.h>
#include <ufo/gralloc.h>

namespace intel {
namespace ufo {
namespace hwc {
namespace services {

using namespace android;

class IDiagnostic : public IInterface
{
public:
    DECLARE_META_INTERFACE(Diagnostic);

    // This class is shared with the validation team. Take care when changing it that
    // the validation tests understand how we have changed this.
    enum
    {
        eLogTruncated = 101,   // Status to indicate log entries have been overwritten
    };

    virtual status_t readLogParcel(android::Parcel* reply) = 0;

    // Debug API
    virtual void enableDisplay(uint32_t d) = 0;
    virtual void disableDisplay(uint32_t d, bool bBlank) = 0;
    virtual void maskLayer(uint32_t d, uint32_t layer, bool bHide) = 0;
    virtual void dumpFrames(uint32_t d, int32_t frames, bool bSync) = 0;
};

class BnDiagnostic : public android::BnInterface<IDiagnostic>
{
public:
    BnDiagnostic()
    {
    }

    virtual ~BnDiagnostic()
    {
    }

    virtual status_t onTransact(uint32_t, const Parcel&, Parcel*, uint32_t);
};

}   // services
}   // hwc
}   // ufo
}   // intel

#endif // INTEL_UFO_HWC_IDIAGNOSTIC_H
