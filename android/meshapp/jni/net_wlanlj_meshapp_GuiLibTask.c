/*-----------------------------------*\
 *  net_wlanlj_meshapp_GuiLibTask.c  *
\*-----------------------------------*/

#include "net_wlanlj_meshapp_GuiLibTask.h"

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_GuiLibTask_init
(JNIEnv *env, jclass class, jstring jpath)
{

  const char *path = (*env)->GetStringUTFChars(env, jpath, 0);
  int val = init(path);

  (*env)->ReleaseStringUTFChars(env, jpath, path);

  return val;
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

