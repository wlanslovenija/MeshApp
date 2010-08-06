/*---------*\
 *  log.c  *
\*---------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "log.h"

void android_log_error(const char *error)
{
  __android_log_print(ANDROID_LOG_ERROR, "guilib", "Error! %s: %s", error, strerror(errno));

  return;
}

void android_log_info(const char *info)
{
  __android_log_write(ANDROID_LOG_INFO, "guilib", info);

  return;
}
