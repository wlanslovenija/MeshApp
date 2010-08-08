#include <stdio.h>
#include <syslog.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/select.h>
#include <android/log.h>

#include "log.h"

void guilib_openlog(const char *ident)
{
#ifndef ANDROID
  openlog(ident, LOG_PID | LOG_ODELAY, LOG_DAEMON);
  setlogmask(LOG_UPTO(LOG_INFO));
#endif
  return;
}

void guilib_syslog(int level, const char *format, ...)
{

  int linux_level;
  va_list arglist;

  switch (level) {
  case (GUILIB_LOG_INFO):
#ifdef ANDROID
    linux_level = ANDROID_LOG_INFO;
#else
    linux_level = LOG_INFO;
#endif
    break;
  case (GUILIB_LOG_ERROR):
#ifdef ANDROID
    linux_level = ANDROID_LOG_ERROR;
#else
    linux_level = LOG_ERR;
#endif
    break;
  default:
    return;
  }

  va_start(arglist, format);
#ifdef ANDROID
  __android_log_vprint(linux_level, "guilib", format, arglist);
#else
  vsyslog(linux_level, format, arglist);
#endif
  va_end(arglist);

  return;
}
    
  
  
    
