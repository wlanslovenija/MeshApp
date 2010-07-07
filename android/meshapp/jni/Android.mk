LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := guilib

LOCAL_SRC_FILES := olsr_controller.c

include $(BUILD_SHARED_LIBRARY)