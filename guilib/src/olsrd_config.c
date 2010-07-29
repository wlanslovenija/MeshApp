#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include "olsrd_config.h"

void generate_olsr_config_file(void)
{

  const char *config_file = strncat(etc_path, config_file_name, strlen(config_file_name));
 
  FILE *cnf = fopen(config_file, "w");

  if (cnf != NULL) {

    fprintf(cnf,"#\n"
	    "# OLSR.org routing daemon config file\n"
	    "#\n"
	    "# Lines starting with # are discarded.\n"
	    "#\n"
	    "# This file was written automatically by MeshApp.\n"
	    "#\n"
	    "###\n"
	    "# BASIC CONFIG\n"
	    "###\n"
	    "# Run OLSR in the background by setting DebugLevel to 0.\n"
	    "DebugLevel \t 0\n"
	    "IpVersion \t 4\n"
	    "# Prevents multiple instances of OLSR from running at once.\n"
	    "LockFile \t \"/data/data/net.wlanlj.meshapp/tmp/olsrd.lock\"\n"
	    "FIBMetric \t \"flat\"\n"
	    "ClearScreen \t yes\n"
	    "# Allow OLSR to run without specifying an interface.\n"
	    "AllowNoInt \t yes\n"
	    "# Disable Hysteresis, enabled by default.\n"
	    "UseHysteresis \t no\n"
	    "# Interval between polling network interface for config changes.\n"
	    "NicChgsPollInt \t 3.0\n"
	    "# How much information about neighbors to send in TC msgs.\n"
	    "# Setting 2 tells OLSRD to send info about all neighbors.\n"
	    "TcRedundancy \t 2\n"
	    "MprCoverage \t 3\n"
	    "Hna4\n"
	    "{\n"
	    "\t # Internet gateway\n"
	    "\t # 0.0.0.0 \t 0.0.0.0\n"
	    "}\n"
	    "IpcConnect\n"
	    "{\n"
	    "\t # Set number of simultaneous IPC connections to allow\n"
	    "\t # This disables IPC\n"
	    "\t MaxConnections 0\n"
	    "\t # Hosts permitted for IPC connect\n"
	    "\t Host \t 127.0.0.1\n"
	    "}\n"
	    "###\n"
	    "# PLUGINS\n"
	    "###\n"
	    "LoadPlugin \"/data/data/net.wlanlj.meshapp/lib/olsrd_txtinfo.so.0.1\"\n"
	    "{\n"
	    "\t PlParam \t \"Accept\" \t \"127.0.0.1\"\n"
	    "\t # PlParam \t \"Accept\" \t \"0.0.0.0\"\n"
	    "}\n"
	    "###\n"
	    "# NETWORK INTERFACE\n"
	    "###\n"
	    "Interface \"tiwlan0\"\n"
	    "{\n"
	    "\t Mode \"mesh\"\n"
	    "}\n");
  }
  fclose(cnf);
  return;
}

int adhoc_mode()
{

  return 0;
  
  // return execl("/system/bin/sh", "/data/data/net.wlanlj.meshapp/bin/adhoc_mode", NULL);

 
}

int run_olsrd()
{

  // const char *run_path = "/bin/run_olsrd";
  // const char *bin_file = strncat(data_path, run_path, strlen(run_path));

  // generate_olsr_config_file();
  adhoc_mode();
  return 0;

  //  return execl("/system/bin/sh", "data/data/net.wlanlj.meshapp/bin/run_olsrd", NULL); 
}

int kill_olsrd()
{

  return 0;
 
  // return execl("/system/bin/sh", "data/data/net.wlanlj.meshapp/bin/kill_olsrd", NULL);
  
}

