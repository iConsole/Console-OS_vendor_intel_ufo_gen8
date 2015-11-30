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

#ifndef __IVIDEO_RESOLUTION_LISTENER_H__
#define __IVIDEO_RESOLUTION_LISTENER_H__

#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <utils/Vector.h>

namespace intel {
namespace ufo {
namespace hwc {
namespace services {

using namespace android;

struct VideoBufferInfo
{
    uint32_t    width;
    uint32_t    height;
    uint32_t    colorFormat;
    uint32_t    transform;
};

class IVideoResolutionListener : public IInterface
{
public:
    DECLARE_META_INTERFACE( VideoResolutionListener );

public:
    // flink is a unique id associated with display frame buffer.
    // Can be obtained with Gralloc get buffer info call - buffer_info.name.
    // For disable call (enableVpp=false) - other parameters are irrelevant.
    virtual void onPreferredVideoResolution( int32_t flinkName, const VideoBufferInfo &vppBufferInfo, int32_t enableVpp ) = 0;
};

class BnVideoResolutionListener : public BnInterface<IVideoResolutionListener>
{
public:
    virtual status_t onTransact( uint32_t, const Parcel&, Parcel*, uint32_t );
};

} // namespace services
} // namespace hwc
} // namespace ufo
} // namespace intel

#endif /* __IVIDEO_RESOLUTION_LISTENER_H__ */
