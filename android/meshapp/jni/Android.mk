#--------------#
#  Android.mk  #
#--------------#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := guilib
LOCAL_SRC_FILES := net_wlanlj_meshapp_GuiLibTask.c
LOCAL_LDLIBS := -llog

LOCAL_STATIC_LIBRARIES := libguilib-static
LOCAL_SHARED_LIBRARIES := libwpa_client
#LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

include $(BUILD_SHARED_LIBRARY)