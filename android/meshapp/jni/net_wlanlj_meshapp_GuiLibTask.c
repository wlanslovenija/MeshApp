#include "net_wlanlj_meshapp_GuiLibTask.h"

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_GuiLibTask_startOlsrd
(JNIEnv *env, jclass class)
{
  return run_olsrd();
}

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_GuiLibTask_stopOlsrd
(JNIEnv *env, jclass class)
{
  return kill_olsrd();
}

