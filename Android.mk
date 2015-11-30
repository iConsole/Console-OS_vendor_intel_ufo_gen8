LOCAL_PATH := $(call my-dir)

ifeq ($(strip $(UFO_ENABLE_GEN)),gen8)
ifeq ($(USE_INTEL_UFO_DRIVER),true)
ifneq ($(BOARD_HAVE_GEN_GFX_SRC),true)

include $(LOCAL_PATH)/$(TARGET_ARCH)/gen8.mk

endif # BOARD_HAVE_GEN_GFX_SRC
endif # USE_INTEL_UFO_DRIVER
endif # UFO_ENABLE_GEN
