
#include "net_wlanlj_meshapp_OlsrNative.h"
#include "../../../guilib/src/olsrd_config.h"

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_OlsrNative_startOlsrd
(JNIEnv *env, jclass class)
{
  return start_olsrd();
}

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_OlsrNative_stopOlsrd
(JNIEnv *env, jclass class)
{
  return stop_olsrd();
}

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_OlsrNative_generateConfigFile
(JNIEnv *env, jclass class)
{
  return generate_config_file();
}

