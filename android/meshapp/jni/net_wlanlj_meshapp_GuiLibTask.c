
#include "net_wlanlj_meshapp_GuiLibTask.h"
#include "../../../guilib/src/olsrd_config.h"

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_GuiLibTask_startOlsrd
(JNIEnv *env, jclass class)
{
  if (run_olsrd() == -1)
    return -1;
  else
    return 0;
}

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_GuiLibTask_stopOlsrd
(JNIEnv *env, jclass class)
{
  if (kill_olsrd() == -1)
    return -1;
  else
    return 0;
}
