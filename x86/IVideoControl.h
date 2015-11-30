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

#ifndef INTEL_UFO_HWC_IVIDEO_CONTROL_H
#define INTEL_UFO_HWC_IVIDEO_CONTROL_H

#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace intel {
namespace ufo {
namespace hwc {
namespace services {


using namespace android;

class IVideoResolutionListener;

/**
 * Allows control of Video processing
 */
class IVideoControl : public IInterface
{
public:
    DECLARE_META_INTERFACE(VideoControl);

    // The control enables a the protected video subsystem to control when to replace any
    // encrypted content with a default bitmap (usually black).

    // Each buffer has metadata associated with it that identifies how that buffer was encrypted.
    // This metadata is managed by Gralloc and queried every frame by the HWC.
    // The intel_ufo_bo_datatype_t structure contains these three fields
    //    uint32_t is_encrypted;
    //    uint32_t pavp_session_id;
    //    uint32_t pavp_instance_id;
    // If the buffer's is_encrypted field is non zero, the HWC will check on every frame whether
    // that particular sessionID and instanceID pair have been enabled.
    // If it is, the HWC will pass the buffer to the kernel to display.
    // If it isn't, the HWC will replace the buffer with a default image (usually black).
    // Many sessions can be enabled at any time, but only one instanceID for any session will be enabled.

    // Enable the display of encrypted buffers with the specified sessionID and instanceID.
    // This will take effect from the next composed frame.
    // Any previously enabled instanceID will be disabled (replaced by the default image)
    virtual status_t enableEncryptedSession( uint32_t sessionID, uint32_t instanceID ) = 0;

    // Disable specific encrypted session.
    // This call will trigger the HWC to remove any encrypted buffers with the specified sessionID
    // from the screen and replace with a default image.
    // The function will block until the screen no longer contains any encrypted data with this session.
    // This should be called by any subsystem that knows that a specific encrypted video session is about to
    // become invalid.
    virtual status_t disableEncryptedSession( uint32_t sessionID ) = 0;

    // Disable all protected sessions.
    // This call will trigger the HWC to remove any encrypted buffers from the screen and replace
    // with a default image.
    // The function will block until the screen no longer contains any encrypted data with any session.
    // This should be called by any subsystem that knows that all encrypted video sessions are about to
    // become invalid.
    virtual status_t disableAllEncryptedSessions( ) = 0;

    // Return whether or not the specified session/instance is enabled.
    virtual bool isEncryptedSessionEnabled( uint32_t sessionID, uint32_t instanceID ) = 0;

    // Register VPP listener
    virtual status_t registerVideoResolutionListener( const sp<IVideoResolutionListener> &vppServiceListener ) = 0;

    // Unregister VPP listener
    virtual status_t unregisterVideoResolutionListener( const sp<IVideoResolutionListener> &vppServiceListener ) = 0;

    enum EDisplayId
    {
        eWired    = 0,
        eWireless = 1,
    };

    enum EDisplayStatus
    {
        eInsecure = 0,
        eSecure   = 1,
    };

    // Update the protection status of a display.
    virtual status_t updateStatus( EDisplayId display, EDisplayStatus status ) = 0;

    // Hint provided by the application about the global optimization mode for the driver
    enum EOptimizationMode
    {
        eNormal,
        eVideo,
        eCamera,
    };
    virtual status_t setOptimizationMode(EOptimizationMode mode) = 0;
};

/**
 */
class BnVideoControl : public BnInterface<IVideoControl>
{
public:
    virtual status_t onTransact(uint32_t, const Parcel&, Parcel*, uint32_t);
};

} // namespace services
} // namespace hwc
} // namespace ufo
} // namespace intel

#endif // INTEL_UFO_HWC_IVIDEO_CONTROL_H
