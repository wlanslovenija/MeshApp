#include <jni.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "olsr_cmd.h"
#include "net_wlanlj_meshapp_OlsrNative.h"


JavaVM *cached_jvm;
jclass Class_C;
jmethodID MID_C_g;
pid_t olsrd_pid;

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *jvm, void *reserved) 
{
  {
     JNIEnv *env;
     jclass cls;
     cached_jvm = jvm;  /* cache the JavaVM pointer */
 
     if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_2)) {
         return JNI_ERR; /* JNI version not supported */
     }
     cls = (*env)->FindClass(env, "C");
     if (cls == NULL) {
         return JNI_ERR;
     }
     /* Use weak global ref to allow C class to be unloaded */
     Class_C = (*env)->NewWeakGlobalRef(env, cls);
     if (Class_C == NULL) {
         return JNI_ERR;
     }
     /* Compute and cache the method ID */
     MID_C_g = (*env)->GetMethodID(env, cls, "g", "()V");
     if (MID_C_g == NULL) {
         return JNI_ERR;
     }
     return JNI_VERSION_1_2;
 }
}

void olsr_start()
{
  pid_t pid = fork();

  if (pid == -1) {
    exit(1);
  }
  else if (pid == 0) {
    execlp("/data/local/bin/olsrd", "olsrd", NULL);
    _exit(1);
  }
  else {  
    olsrd_pid = pid; 
  }
}

void olsr_stop()
{
  kill(olsrd_pid, SIGKILL);
}

JNIEXPORT jint JNICALL
Java_net_wlanlj_meshapp_OlsrNative_start
(JNIEnv *env, jobject obj)
{
  olsr_start();
  return 0;
}


JNIEXPORT jint JNICALL
Java_net_wlanlj_meshapp_OlsrNative_stop 
(JNIEnv *env, jobject obj)
{
  olsr_stop();
  return 0;
}

