#!/bin/bash

HOST_SYSTEM=linux-x86
PYTHON=/usr/bin/python

ANDROID_SDK_PATH=~/android/android-sdk-linux_86
ANDROID_NDK_PATH=~/android/android-ndk-r4b

ADB=$ANDROID_SDK_PATH/tools/adb
OBJDUMP=$ANDROID_NDK_PATH/build/prebuilt/$HOST_SYSTEM/arm-eabi-4.2.1/bin/arm-eabi-objdump

MESHAPP_ROOT_DIR=~/code/meshapp
MESHAPP_GUILIB_DEBUG_LIB=$MESHAPP_ROOT_DIR/android/meshapp/libs/armeabi/libguilib.so

PARSE_STACK_SCRIPT=parse_stack.py

$ADB logcat -d > data/logcat.txt
$OBJDUMP -S $MESHAPP_GUILIB_DEBUG_LIB > data/guilib.asm

$PYTHON $PARSE_STACK_SCRIPT data/guilib.asm data/logcat.txt

#EOF


