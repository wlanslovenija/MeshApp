#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/system_properties.h>

#include "cutils/properties.h"
#include "net_wlanlj_meshapp_OlsrNative.h"

JNIEXPORT jstring JNICALL Java_net_wlanlj_meshapp_OlsrNative_getProp
(JNIEnv *env, jclass class, jstring name)
 {
 const char *nameString;
  nameString = (*env)->GetStringUTFChars(env, name, 0);

  char value[PROPERTY_VALUE_MAX];
  char *default_value;
  jstring jstrOutput;
  int length;
  
  // default_value = "undefined";
  //property_get(nameString, value, default_value);

  jstrOutput = (*env)->NewStringUTF(env, value);

  (*env)->ReleaseStringUTFChars(env, name, nameString);  

  return jstrOutput;
}

JNIEXPORT jint JNICALL Java_net_wlanlj_meshapp_OlsrNative_runCommand
(JNIEnv *env, jclass class, jstring cmd)
{
  const char *commandString;
  commandString = (*env)->GetStringUTFChars(env, cmd, 0);
  int exitcode = system(commandString); 
  (*env)->ReleaseStringUTFChars(env, cmd, commandString);  
  return (jint)exitcode;
}
