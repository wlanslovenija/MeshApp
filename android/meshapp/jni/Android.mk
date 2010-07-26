LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := guilib
LOCAL_SRC_FILES := net_wlanlj_meshapp_GuiLibTask.c
LOCAL_STATIC_LIBRARIES := libguilib

include $(BUILD_SHARED_LIBRARY)