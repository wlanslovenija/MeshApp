#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "wpa_ctrl.h"
#include "config.h"
#include "log.h"

struct wpa_ctrl *control_connection;

static const char *local_socket_dir = "/data/misc/wifi/sockets";
static const char *local_socket_prefix = "wpa_ctrl_";

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
	    "Hna4\n"
	    "{\n"
	    "\t # Internet gateway\n"
	    "\t # 0.0.0.0 \t 0.0.0.0\n"
	    "}\n"
	    "Interface \"%s\"\n"
	    "{\n"
	    "\t Mode \"mesh\"\n"
	    "}\n", olsr_lock_file, "tiwlan0");
    fclose(cnf);
    return 0;
}

void wpa_close_control_connection(void) {
  if (control_connection == NULL) 
    return;
  
  wpa_ctrl_close(control_connection);
  
  control_connection = NULL;
}

struct wpa_ctrl *wpa_open_control_connection(const char *wpa_directory)
{
  if (wpa_directory == NULL) {
    return NULL;
  }
  
  if (control_connection != NULL) {
    wpa_close_control_connection();
  }
  
  control_connection = wpa_ctrl_open(wpa_directory);
  return control_connection;
}

void wpa_message_callback(char *message, size_t length) 
{
  guilib_syslog(GUILIB_LOG_INFO, "%s\n", message);
}

void wpa_print_scan_results() 
{
  char command = "SCAN_RESULTS";
  char buffer[4096];
  size_t length;
  int ret;
  
  if (control_connection == NULL) {
    guilib_syslog(GUILIB_LOG_ERROR, "Error: Not connected to wpa_supplicant: %s", strerror(errno));
    return;
  }
  
  length = sizeof(buffer) - 1;
  ret = wpa_ctrl_request(control_connection, command, strlen(command), buffer, &length, wpa_message_callback);

  if (ret == -2) {
    guilib_syslog(GUILIB_LOG_ERROR, "'%s' command timed out.", command);
    return;
  }
  else if (ret < 0) {
    guilib_syslog(GUILIB_LOG_ERROR, "'%s' command failed: %s", command, strerror(errno));
    return;
  }
  
  buffer[length] = '\0';
  guilib_syslog(GUILIB_LOG_INFO, "%s", buffer);
  
  return;
}
