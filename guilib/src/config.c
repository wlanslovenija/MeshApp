/*------------*\
 *  config.c  *
\*------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "config.h"

int generate_olsr_config_file(void)
{
  FILE *cnf = fopen(olsr_config_file_path, "w");

  wlan_interface = "tiwlan0";

  if (cnf == NULL)
    return -1;
  else
    fprintf(cnf,"#\n"
	    "# OLSR.org config file\n"
	    "DebugLevel \t 5\n"
	    "IpVersion \t 4\n"
	    "LockFile \t \"%s\"\n"
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
	    "Interface \"%s\"\n"
	    "{\n"
	    "\t Mode \"mesh\"\n"
	    "}\n", olsr_lock_file_path, wlan_interface);
    fclose(cnf);
    return 0;
}
