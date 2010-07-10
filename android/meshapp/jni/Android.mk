LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := guilib

LOCAL_SRC_FILES := net_wlanlj_meshapp_OlsrNative.c

include $(BUILD_SHARED_LIBRARY)