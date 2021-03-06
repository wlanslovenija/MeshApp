#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "config.h"
#include "log.h"


char *set_file_path(char file_path[], const char *file_name)
{
  strcpy(file_path, platform_data_path);
  file_path = strcat(file_path, file_name);
  return file_path;
}

int configure_olsr_protocol(void)
{
  FILE *cnf = fopen(olsr_config_file, "w");

  if (cnf == NULL)
    return -1;
  else
    fprintf(cnf,"#\n"
	    "# OLSR.org config file\n"
	    "DebugLevel \t 0\n"
	    "IpVersion \t 4\n"
	    "LockFile \t \"%s\"\n"
	    "FIBMetric \t \"flat\"\n"
	    "ClearScreen \t yes\n"
	    "AllowNoInt \t yes\n"
	    "UseHysteresis \t no\n"
	    "NicChgsPollInt \t 3.0\n"
	    "TcRedundancy \t 2\n"
	    "MprCoverage \t 3\n"
	    "Interface \"%s\"\n"
	    "{\n"
	    "\t Mode \"mesh\"\n"
	    "}\n", olsr_lock_file, "tiwlan0");
    fclose(cnf);
    return 0;
}
