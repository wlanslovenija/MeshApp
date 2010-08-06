/*-----------------------------------*\
 *  net_wlanlj_meshapp_GuiLibTask.c  *
\*-----------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "net_wlanlj_meshapp_GuiLibTask.h"

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_GuiLibTask_init
(JNIEnv *env, jclass class, jstring jPath)
{
  int ret;
  const char *path;
  path = (*env)->GetStringUTFChars(env, jPath, NULL);
  
  if (path == NULL) {
    return NULL;
  }
  
  ret = init(path);
  (*env)->ReleaseStringUTFChars(env, jPath, path);
  
  return ret;
}

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_GuiLibTask_start
(JNIEnv *env, jclass class)
{
  return meshapp_start();
}

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_GuiLibTask_stop
(JNIEnv *env, jclass class)
{
  return meshapp_stop();
}

