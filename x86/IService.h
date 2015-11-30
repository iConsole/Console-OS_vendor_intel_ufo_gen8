/*
 * INTEL CONFIDENTIAL
 *
 * Copyright 2013-2015 Intel Corporation All Rights Reserved.
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

#ifndef INTEL_UFO_HWC_ISERVICE_H
#define INTEL_UFO_HWC_ISERVICE_H

#include <binder/IInterface.h>
#include <binder/Parcel.h>

#define INTEL_HWC_SERVICE_NAME "hwc.info"

namespace android {
    class String8;
};

namespace intel {
namespace ufo {
namespace hwc {
namespace services {

class IDiagnostic;
class IDisplayControl;
class IVideoControl;

using namespace android;

/** Maintenance interface to control HWC activity.
 */
class IService : public IInterface
{
public:
    DECLARE_META_INTERFACE(Service);

    virtual sp<IDisplayControl> getDisplayControl(uint32_t display) = 0;
    virtual sp<IDiagnostic>     getDiagnostic() = 0;
    virtual sp<IVideoControl>   getVideoControl() = 0;

    virtual String8             getHwcVersion() = 0;
    virtual void                dumpOptions( void ) = 0;
    virtual status_t            setOption( String8 option, String8 optionValue ) = 0;
    virtual status_t            enableLogviewToLogcat() = 0;


};


/**
 */
class BnService : public BnInterface<IService>
{
public:
    virtual status_t onTransact(uint32_t, const Parcel&, Parcel*, uint32_t);
};

} // namespace services
} // namespace hwc
} // namespace ufo
} // namespace intel

#endif // INTEL_UFO_HWC_ISERVICE_H
