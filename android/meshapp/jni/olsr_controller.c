#include <jni.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "olsr_cmd.h"
#include "net_wlanlj_meshapp_OlsrNative.h"

pid_t olsrd_pid;

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

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_OlsrNative_start
(JNIEnv *env, jobject obj)
{
  olsr_start();
  return 0;
}


JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_OlsrNative_stop 
(JNIEnv *env, jobject obj)
{
  olsr_stop();
  return 0;
}

