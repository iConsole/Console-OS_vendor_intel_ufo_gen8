/*===================== begin_copyright_notice ==================================

INTEL CONFIDENTIAL
Copyright 2013-2014
Intel Corporation All Rights Reserved.

The source code contained or described herein and all documents related to the
source code ("Material") are owned by Intel Corporation or its suppliers or
licensors. Title to the Material remains with Intel Corporation or its suppliers
and licensors. The Material contains trade secrets and proprietary and confidential
information of Intel or its suppliers and licensors. The Material is protected by
worldwide copyright and trade secret laws and treaty provisions. No part of the
Material may be used, copied, reproduced, modified, published, uploaded, posted,
transmitted, distributed, or disclosed in any way without Intel's prior express
written permission.

No license under any patent, copyright, trade secret or other intellectual
property right is granted to or conferred upon you by disclosure or delivery
of the Materials, either expressly, by implication, inducement, estoppel or
otherwise. Any license under such intellectual property rights must be express
and approved by Intel in writing.

File Name: libpavp.h
Abstract: PAVP library for Android - header file for external use.

Environment: Linux/Android

Notes:  

======================= end_copyright_notice ==================================*/

#ifndef _LIBPAVP_H_
#define _LIBPAVP_H_

#ifndef BASIC_TYPES_DEFINED
#include <cstdint>
typedef uint8_t     UINT8;
typedef uint8_t     BYTE;
typedef uint8_t*    PBYTE;
typedef uint16_t    UINT16;
typedef uint32_t    UINT32;
typedef uint32_t    ULONG;
typedef void*       PVOID;
typedef uint32_t*   PUINT;
typedef uint32_t    UINT;
typedef uint32_t    DWORD;
typedef uint32_t*   PDWORD;
#endif // BASIC_TYPES_DEFINED

/// \def INTERFACE_VERSION
/// The interface version the library was compiled with.
#define INTERFACE_VERSION 0x0D

class pavp_lib_session_impl;

class pavp_lib_session
{
public:

    /// \enum pavp_lib_session::pavp_lib_code
    /// Libpavp Error Codes
    /// @{
    enum pavp_lib_code
    {
        status_ok                     = 0x0,
        invalid_arg                   = 0x1,
        session_already_initialized   = 0x2,
        session_uninitialized         = 0x3,
        insufficient_memory           = 0x4,
        internal_error                = 0x5,
        not_implemented               = 0x6,
        pavp_not_supported            = 0x7,
        hdcp1_not_supported           = 0x8,
        hdcp2_not_supported           = 0x9,
        hdcp2_timeout                 = 0xa,
        operation_failed              = 0xb,
        api_version_mismatch          = 0xc,
        signature_verify_failed       = 0xd,
        pavp_lib_status_count         = 0xe
    };
    ///@}

    /// \enum pavp_lib_session::LSFCB_TYPE
    /// Type of message to send back to LSF
    /// @{
    enum LSFCB_TYPE
    {
        HDCP2RX_SUCCESS         = 0,
        HDCP2RX_ERROR           = 1,
        HDCP2RX_CLOSE_SOCKET    = 2,
    };
    ///@}

    /// \enum pavp_lib_session::hdcp2_content_stream_type
    /// HDCP2 Stream Types
    /// @{
    enum hdcp2_content_stream_type
    {
        content_stream_type0     = 0,   //!< May be transmitted by the HDCP repeater to all HDCP devices.
        content_stream_type1     = 1,   //!< Must not be transmitted by the HDCP repeater to HDCP 1.x-compliant devices and HDCP 2.0-compliant repeaters.
        max_content_stream_types = 2
    };
    ///@}

    /// \enum pavp_lib_session::pavp_type
    /// PAVP Session Types
    /// @{
    enum pavp_type
    {
        pavp_type_invalid   = 0x0,
        pavp_type_decode    = 0x1, //!< Decode session type
        pavp_type_transcode = 0x2, //!< Transcode session type
        pavp_type_widi      = 0x3  //!< Widi session type
    };
    ///@}

    /// \enum pavp_lib_session::pavp_mode
    /// PAVP Session Modes
    /// @{
    enum pavp_mode
    {
        pavp_mode_invalid         = 0x0,
        pavp_mode_lite            = 0x1, //!< Lite Mode                             [BYT+]
        pavp_mode_heavy           = 0x2, //!< Heavy Mode                            [BYT+]
        pavp_mode_iso_dec         = 0x3, //!< Isolated Decode Mode                  [BXT+]
        pavp_mode_stout           = 0x4, //!< Isolated Decode with Authenticated EU [Not supported]
        pavp_mode_thv_d           = 0x5, //!< Isolated Display/Threadville-Display  [Not supported]  
        pavp_mode_huc_guard       = 0x6  //!< HuC Signed cmd buff                   [Not supported]
    };
    ///@}

    /// \enum pavp_lib_session::key_type
    /// PAVP Key Types
    /// @{
    enum  key_type
    {
        pavp_key_decrypt    = 1,    //!< Decrypt key.
        pavp_key_encrypt    = 2,    //!< Encrypt key.
        pavp_key_both       = 4,    //!< Decrypt and encrypt key.
    };
    ///@}

    /// \enum pavp_lib_session::hdcp_capability
    /// HDCP capability of host and any connected display
    /// Adapted directly from Widevine MDRM Security Integration Guide for CENC
    /// @{
    typedef enum {
        HDCP_CAP_NO_HDCP_NO_SECURE_DATA_PATH = 0x0,  //!< HDCP is unsupported, local display is not secure
        HDCP_CAP_HDCP_10                     = 0x1,  //!< HDCP1.x is supported by host and display
        HDCP_CAP_HDCP_20                     = 0x2,  //!< HDCP2.0 is supported by host and display
        HDCP_CAP_HDCP_21                     = 0x3,  //!< HDCP2.1 is supported by host and display
        HDCP_CAP_HDCP_22                     = 0X4,  //!< HDCP2.2 is supported by host and display
        HDCP_CAP_NO_HDCP_SECURE_DATA_PATH    = 0xff, //!< HDCP is not supported, local display is secure
    } hdcp_capability_type;
    ///@}

    /// \enum pavp_lib_session::pavp_cek_operation
    /// PAVP CEK Key operations
    /// @{
    enum  pavp_cek_operation_type
    {
        pavp_cek_no_op          = 0x0,     //!< Invalid CEK Op
        pavp_sec_set_cek        = 0x1,     //!< Set CEK in SEC/ME
        pavp_sec_get_cek        = 0x2,     //!< Get CEK blob from SEC/ME
        pavp_gpu_rotate_cek     = 0x3,     //!< Rotate CEK and Inject into GPU
        pavp_sec_invalidate_cek = 0x4      //!< Invalidate CEK in ME/SEC.
    };
    ///@}

    /// \typedef pavp_lib_session::pavp_lib_version
    /// Libpavp Version Number
    typedef UINT32 pavp_lib_version;

    /// \typedef pavp_lib_session::PFNWIDIAGENT_HDCPSENDMESSAGE
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       A callback function used to send data to the wireless receiver.
    /// \param       hWiDiHandle    [in] Not used in Android, reserved.
    /// \param       pData          [in] a caller-allocated input buffer containing an HDCP2 message.
    /// \param       uiDataLen      [in] The size of the data in the buffer pointed to by pData. 
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    typedef pavp_lib_code (*PFNWIDIAGENT_HDCPSENDMESSAGE)
    (
        PVOID    hWiDiHandle,
        PVOID    pData,
        UINT32   uiDataLen
    );

    /// \typedef pavp_lib_session::PFNWIDIAGENT_HDCPRECEIVEMESSAGE
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       A callback function used to receive data from the wireless receiver.
    /// \param       hWiDiHandle        [in] Not used in Android, reserved.
    /// \param       pData              [in/out] a caller-allocated input buffer to be filled with the received HDCP2 message.
    /// \param       uiDataLen          [in] The size of the buffer pointed to by pData. 
    /// \param       pReceivedDataLen   [out] If pData was null, returns size required to receive the next message.
    ///                                       If pData was not null, returns the size of the data written to pData.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    typedef pavp_lib_code (*PFNWIDIAGENT_HDCPRECEIVEMESSAGE)
    (
        PVOID   hWiDiHandle,
        PVOID   pData,
        UINT32  uiDataLen,
        PUINT   pReceivedDataLen
    );

    /// \typedef pavp_lib_session::PFNWIDIAGENT_LSFCALLBACK
    /// \brief       A callback function used to send events to the Widi Agent for HDCP2 Rx
    /// \param       pWiDiHandle    [in] Handle to the Widi agent. Passed as input in hdcp2_rx_create_and_authenticate()
    /// \param       uiCbType       [in] Event type. Takes value from enum pavp_hdcp2_rx_cb_event
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    typedef pavp_lib_code (*PFNWIDIAGENT_LSFCALLBACK)
    (
       PVOID        pWiDiHandle,
       LSFCB_TYPE   uiCbType
    );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Initializes the libary.
    /// \param       interface_version          [in] Should be set to INTERFACE_VERSION.
    /// \param       pavp_lib_session_instance  [out] The library session object to be used for using this library.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    static pavp_lib_code pavp_lib_init(
        pavp_lib_version    interface_version,
        pavp_lib_session    **pavp_lib_session_instance);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Destroy resources allocated for the libary use. Must be called if a successful pavp_lib_init call has been made.
    /// \param       pavp_lib_session_instance  [in] The library session object to be destroyed.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    static pavp_lib_code pavp_lib_cleanup(pavp_lib_session *pavp_lib_session_instance);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Allows direct communication with the SEC FW. This function can be used for DRM initialization and key exchange.
    /// \par         Details:
    /// \li          This function can be called any time after pavp_lib_init().
    /// \param       pInput     [in] The SEC command to be sent.
    /// \param       ulInSize   [in] The size of the SEC command to be sent.
    /// \param       pOutput    [out] A buffer to contain the SEC response.
    /// \param       ulOutSize  [in] The SEC response buffer size.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code sec_pass_through(
        PBYTE pInput,
        ULONG ulInSize,
        PBYTE pOutput,
        ULONG ulOutSize);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Provides an HDCP System Renewability Message.
    /// \par         Details:
    /// \li          The SRM's digital signature will be verified and revoked KSVs will be extracted to check during activation of HDCP1.
    /// \li          Can be called when using either HDCP1 or HDCP2, but must be called before activation or authentication.
    /// \param       srm_data       [in] Binary data that contains revoked KSVs formatted according to the HDCP specification.
    /// \param       srm_data_size  [in] The size of the binary data.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code hdcp_set_srm(UINT8* srmData, UINT32 srmDataSize);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Returns the HDCP support of the host and any connected display.
    /// \par         This method conforms to the return values specified by the Widevine MDRM Security Integration Guide for CENC. 
    ///              See pavp_lib_session::hdcp_capability_type for possible values.
    /// \param       current [out]  current returns the HDCP capability successfully negotioated by the host to a display
    /// \param       maximum [out]  maximum returns the maximum supported HDCP capibility of the host
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code hdcp_get_capability(UINT8 *current, UINT8 *maximum);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Enables HDCP1 and creates a PAVP session and initializes the required private variables.
    /// \par         Details:
    /// \li          This must be called when the host process needs to create a session for protected decoding.
    /// \li          If any digital outputs are enabled, this function will also attempt to activate HDCP1.x on them.
    /// \li          If this is called, hdcp2_create() will be unavailable until pavp_destroy_session() is called.
    /// \li          This call will fail if hdcp2_create() was already called (PAVP and HDCP2 library usages 
    /// \li          are mutually exclusive).
    /// \param       session_mode [in, optional] Indicates the session mode to be created (default: pavp_mode_heavy).
    /// \param       session_type [in, optional] Indicates whether the session type to be created is decode,transcode or Widi
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code pavp_create_session(
        pavp_mode session_mode = pavp_mode_heavy,
        pavp_type session_type = pavp_type_decode);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Returns the app ID of the PAVP session created by the library.
    /// \par         Details:
    /// \li          This call fails if no PAVP session has been created.
    /// \li          If the call failed, app_id value is undefined.
    /// \param       app_id [out] The created PAVP session app ID.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code pavp_get_app_id(UINT& app_id);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Releases the PAVP session and all resources allocated in pavp_create_session().
    /// \par         Details:
    /// \li          Can be called if for any reason PAVP needs to be recreated without re-creating a pavp_lib_session object.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code pavp_destroy_session();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Reports whether the PAVP session is alive at the hardware level.
    /// \par         Details:
    /// \li          If the session is not alive, the host application should immediately halt playback, destroy the current session and create a new one.
    /// \param       bIsAlive   [out] If the returned status is status_ok, bIsAlive will be true if the PAVP session is alive, false otherwise.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code pavp_is_session_alive(bool *bIsAlive);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Sets the steam key to be used with the previouly created PAVP session.
    /// \par         Details:
    /// \li          If the session is not alive, the host application should immediately halt playback, destroy the current session and create a new one.
    /// \param       key_type               [in] The key type to set (decrypt/encrypt/both).
    /// \param       encrypted_decrypt_key  [in] Encrpted decrypt key to set (ignored if the requested key type is encrypt only).
    /// \param       encrypted_encrypt_key  [in] Encrpted encrypt key to set (ignored if the requested key type is decrypt only).
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code pavp_set_stream_key(
        key_type    key_type,
        DWORD       encrypted_decrypt_key[4],
        DWORD       encrypted_encrypt_key[4]);
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Releases HDCP2 usage. Frees all resources associated with HDCP2.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code hdcp2_destroy();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       An optional call for HDCP2.1+. Allows the player to set certain restrictions on the HDCP topology.
    /// \param       content_stream_type    [in] A stream type for the content being played.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code hdcp2_set_stream_types(hdcp2_content_stream_type content_stream_type);
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Rerforms the full HDCP2.x AKE between the wireless adapter and Widi Transmitter (SEC).
    /// \par         Details:
    /// \li          The send and receive callbacks will not be cached and will only be used within the scope of this function call.
    /// \li          Therefore the caller does not need to guarantee the validity of the function pointers afterwards.
    /// \li          This call will fail if pavp_create_session() was already called (PAVP and HDCP2 library usages are mutually exclusive).
    /// \param       pSend      [in] A callback function to send a message to the wireless adapter.
    /// \param       pReceive   [in] A callback function to receive a response from the wireless adapter.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code hdcp2_create_and_authenticate(
        PFNWIDIAGENT_HDCPSENDMESSAGE    pSend,
        PFNWIDIAGENT_HDCPRECEIVEMESSAGE pReceive);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Recreates hdcp2 session without hdcp re-authorization
    /// \par         Details:
    /// \li          This API to recreate hdcp session when the rest of the hdcp states are already authorized.
    ///              This is a mechanism for app to recover hdcp session retaining authetication states.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code hdcp2_recreate();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Rerforms the full HDCP2.x RX flow LIBPAVP handles HOTPLUGs and passing topology info around.
    /// \par         Details:
    /// \li          This call is asynchronous and will immediately spawn 2 threads 1 for responding to messages
    /// \li          1 for the HDCP1 HOTPLUG events.  It will use "pLSFcb" to signal HDCP2 RX SUCESS, ERROR, or
    /// \li          CLOSE_SOCKET messages.
    /// \li
    /// \li          If HDCP2RX_ERROR or HDCP2RX_CLOSE_SOCKET is signaled LIBPAVP will implicitly call hdcp2_rx_destroy(...)
    /// \li          It won't hurt if LSF also calls hdcp2_rx_destroy(...), LSF should call hdcp2_rx_destroy(...) and
    /// \li          make sure they can get back pavp_lib_session::status_ok, if they get status_ok LSF will
    /// \li          be able to call this function once more.
    /// \li
    /// \param       pSend      [in] A callback function to send a message to the wireless adapter.
    /// \param       pReceive   [in] A callback function to receive a response from the wireless adapter.
    /// \param       pLSFcb     [in] A callback function to notify LSF asynchronously of SUCCESS/ERROR/CLOSE_SOCKET
    /// \param       pLSFHandle [in] Pointer to LSF handle which needs to be passed back when we invoke pLSFcb.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code hdcp2_rx_create_and_authenticate(
            PFNWIDIAGENT_HDCPSENDMESSAGE    pSend,
            PFNWIDIAGENT_HDCPRECEIVEMESSAGE pReceive,
            PFNWIDIAGENT_LSFCALLBACK        pLSFcb,
            PVOID                           pLSFHandle);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Destroys HDCP2 RX session and any state LIBPAVP maintains for HDCP2 RX session.
    /// \li
    /// \li          Can be called at any time after hdcp2_rx_create_and_authenticate has been called.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code hdcp2_rx_destroy();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Decrypts an uncompressed image and blts data to a protected surface.
    ///              NOTE: DecryptionBlt is enabled for Debug and Release-Internal drivers only becuse it was not verified yet on Android.
    ///
    /// \param       pIV            [in] The IV + counter that was used to encrypt the surface (128 bit = 4 DWORDS). 
    /// \param       src_resource   [in] The source resource which contains the AES encrypted data. The surface is an RGB surface.
    /// \param       dst_Resource   [out] The Destination resource. This resource will contain the serpent encrypted data. It should be allocated by the caller.
    /// \param       size   [in] The size of the src buffer.
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code decryption_blt(
        const DWORD(&iv)[4],
        const BYTE* const src, 
        BYTE* const dest,
        const size_t size);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Encrypts an uncompressed clear surface, to pass back to the application. 
    ///              Adding this function "declaration but disabling definition" in release driver will remove qualms for running P4 release-internal 
    ///              driver on release OTC build. 
    /// \param       src_resource   [in] The source resource which contains the clear data. 
    /// \param       dst_Resource   [out] The Destination resource. This resource will contain the encrypted data. It should be allocated by the caller.
    /// \param       width  [in] The width of the surface in Bytes.
    /// \param       height [in] The height of the surface in Bytes (pay attention that for NV12 the height(Bytes) = 1.5*height(Pixel)).
    /// \return     status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code encryption_blt(
        PBYTE   src_resource,
        PBYTE   dst_Resource,
        DWORD   width,
        DWORD   height);

    //HSW Android WideVine Stuff
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Start HSW WideVine connection status heart beat message.
    /// \par         Details:
    /// \li          This function should be called after set entitlement key and before first video process frame.
    ///              Algorithm -
    ///              - App -
    ///              check_connection_status_heart_beat()
    ///              first_video_process_frame()
    ///              while playback
    ///                 for i = 1 to 100
    ///                     do nothing
    ///                 check_connection_status_heart_beat()
    ///              end while
    ///              - Driver -
    ///              Call Get WideVine Nonce (It is different from regular gent nonce)
    ///              Program Nonce to GPU and Get Connection Status
    ///              Verify Connection Status and return T/F if HDCP alive 
    ///              - Firmware -
    ///              Wait for Connection Status before Xscripting first Video Frame
    ///              Receive request for connection status and verify
    ///              Start counter till 100 frames
    ///                 Process video frames
    ///              if on 100th frame and connection status is not received then stop doing Xscripting 
    ///              
    /// \param       bStartCSHeartBeat  [out] True if heart beat status is ok, false otherwise.
    /// 
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code check_connection_status_heart_beat(bool *bCSHeartBeatStatus);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Start HSW WideVine crypto init dma message.
    /// \par         Details:
    /// \li          This function should be called to get handle to DMA message.
    /// \param       pMessage   [in] The message to be sent to FW for allocating DMA resources.
    /// \param       msg_length [in] pMessage length.
    /// \param       handle     [out] An SGL handle to be used for accessing the DMA resources.
    /// 
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code oem_crypto_init_dma(
        UINT8   *pMessage,
        UINT32  msg_length,
        UINT32  *handle);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       Start HSW WideVine crypto uninit dma message.
    /// \par         Details:
    /// \li          This function should be called to free handle to DMA message.
    /// \param       handle  [in] The SGL handle previously returned from oem_crypto_init_dma.
    ///
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code oem_crypto_uninit_dma(UINT32 *handle);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief       This call does the CEK Injection operations based on cek_op.
    /// \par         Details: 
    /// \li          After ProcessVideoFrame, OMX calls this API to inject the CEK.
    /// \param       key_op [in] can take 2 different values:
    ///              pavp_sec_set_cek     Inject first CEK into ME/SEC. 
    ///              pavp_sec_get_cek     Get CEK from ME/SEC. 
    ///              pavp_gpu_rotate_cek  Rotate and Inject CEK [Non-First CEK]. OMX passes this flag 
    ///                                   to rotate/inject a new CEK into GPU. 
    ///                                   No putput returned so app sets key_blob_out = NULL
    ///                                   This flag translates to SetStreamKey.
    ///              Key Rotation sequence
    ///              The OMX can rotate/change the cek key periodically after every couple of frames.
    ///              (X)Y implies X encrypted with Y
    ///              (CEK0)Kb,(Kb)CEK0 --> CEK0 is injected into GPU
    ///              (Kb)CEK0,(CEK1)Kb --> CEK1 is injected into GPU
    ///              so on...
    ///              pavp_sec_invalidate_cek   : Invalidates CEK in SEC
    ///                                          This flag transaltes to AccessME ie sec_pass_thru.
    /// \param       key_blob_in  [in]  Input key blob
    /// \param       key_blob_out [out] Output key blob
    /// \param       ulInSize     [in]  key_blob_in size
    //  \param       ulOutSize    [out] key_blob_out size
    /// \return      status_ok on success, error codes on failure.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    pavp_lib_code pavp_cek_operation(
        pavp_cek_operation_type cek_op,
        PBYTE                   key_blob_in,
        ULONG                   ulInSize,
        PBYTE                   key_blob_out,
        ULONG                   ulOutSize);

protected:

    pavp_lib_session(pavp_lib_code& rc);
    ~pavp_lib_session();

private:

    // Default constructor, copy constructor and assignment operator should not be used.
    pavp_lib_session& operator=(const pavp_lib_session& other);
    pavp_lib_session(const pavp_lib_session& other);
    pavp_lib_session_impl* m_PavpLibSessionImpl;
        
};

#endif
