#include "net_wlanlj_meshapp_OlsrNative.h"

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_OlsrNative_startOlsr
  (JNIEnv *, jobject);
{
  return 0;
}

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_OlsrNative_stopOlsr
  (JNIEnv *, jobject);
{
  return 1;
}
