/*------------*\
 *  guilib.c  *
\*------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <android/log.h>

#include "guilib.h"

const char* meshapp_dir = "/data/data/net.wlanlj.meshapp";

static const char *msg_tag = "GuiLib -> guilib";

int init(const char *path)
{
  path = meshapp_dir;

  if (chdir(path) != 0) {
    android_log_error("chdir() with non-zero exit status");
    return -1;
  } else {
    android_log_info("set guilib working directory to specified path");
    return 0;
  }
}

int meshapp_start()
{

  generate_olsr_config_file("tmp/olsrd.conf");

  if (system("su -c /data/data/net.wlanlj.meshapp/bin/olsrd_init") != 0) {
    android_log_error("failed to run olsrd");
    return -1;
  } else {
    android_log_info("started olsrd");
    return 0;
  }
}
  

int meshapp_stop()
{
  if (system("su -c /data/data/net.wlanlj.meshapp/bin/olsrd_kill") != 0) {
    android_log_error("failed to kill olsrd");
    return -1;
  } else {
    android_log_info("killed olsrd");  
    return 0;
  }
}

void generate_olsr_config_file(const char *file_name)
{
  FILE *cnf = fopen(file_name, "w");

  if (cnf != NULL) {
    fprintf(cnf,"#\n"
	    "# OLSR.org routing daemon config file\n"
	    "#\n"
	    "# This file was written automatically by MeshApp.\n"
	    "#\n"
	    "DebugLevel \t 5\n"
	    "IpVersion \t 4\n"
	    "LockFile \t \"/data/data/net.wlanlj.meshapp/tmp/olsrd.lock\"\n"
	    "FIBMetric \t \"flat\"\n"
	    "ClearScreen \t yes\n"
	    "AllowNoInt \t yes\n"
	    "UseHysteresis \t no\n"
	    "NicChgsPollInt \t 3.0\n"
	    "TcRedundancy \t 2\n"
	    "MprCoverage \t 3\n"
	    "Hna4\n"
	    "{\n"
	    "\t # Internet gateway\n"
	    "\t # 0.0.0.0 \t 0.0.0.0\n"
	    "}\n"
	    "#IpcConnect\n"
	    "#{\n"
	    "#\t MaxConnections 0\n"
	    "#\t Host \t 127.0.0.1\n"
	    "#}\n"
	    "#LoadPlugin \"lib/olsrd_txtinfo.so.0.1\"\n"
	    "#{\n"
	    "#\t PlParam \t \"Accept\" \t \"127.0.0.1\"\n"
	    "#\t # PlParam \t \"Accept\" \t \"0.0.0.0\"\n"
	    "#}\n"
	    "Interface \"tiwlan0\"\n"
	    "{\n"
	    "\t Mode \"mesh\"\n"
	    "}\n");

    fclose(cnf);
    android_log_info("Wrote olsrd.conf");

  } else {
    android_log_error("Failed to write olsrd.conf");
    _exit(EXIT_FAILURE);
  }

  return;
}


void android_log_error(const char *msg)
{

  __android_log_print(ANDROID_LOG_ERROR, msg_tag, "Error! %s: %s", msg, strerror(errno));

  return;
}

void android_log_info(const char *msg)
{
  __android_log_write(ANDROID_LOG_INFO, msg_tag, msg);

  return;

}
