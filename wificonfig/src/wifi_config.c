#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <android/log.h>

#include "wpa_ctrl.h"
#include "wifi_config.h"
#include "log.h"

#define MODE_DISABLED   0
#define MODE_ENABLED    1

static struct wpa_ctrl *control_connection;

//static const char *local_socket_dir = "/data/misc/wifi/wpa_supplicant";

static void wpa_close_control_connection(void) {
  if (control_connection == NULL) 
    return;
  
  wpa_ctrl_close(control_connection);
  
  control_connection = NULL;
}

static struct wpa_ctrl *wpa_open_control_connection(const char *wpa_directory)
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

static void wpa_message_callback(char *message, size_t length) 
{
  android_syslog(ANDROID_LOG_INFO, "%s\n", message);
}


static void wpa_print_scan_results(void) 
{
  char command = "SCAN_RESULTS";
  char buffer[4096];
  FILE *wpa_scan_file = fopen("/data/data/net.wlanlj.meshapp/tmp/scan_results.log", "w");
  size_t length;
  int ret;
  
  if (control_connection == NULL) {
    android_syslog(ANDROID_LOG_ERROR, "Error: Not connected to wpa_supplicant: %s", strerror(errno));
    return;
  }
  
  length = sizeof(buffer) - 1;
  ret = wpa_ctrl_request(control_connection, command, strlen(command), buffer, &length, wpa_message_callback);

  if (ret == -2) {
    android_syslog(ANDROID_LOG_ERROR, "'%s' command timed out.", command);
    return;
  }
  else if (ret < 0) {
    android_syslog(ANDROID_LOG_ERROR, "'%s' command failed: %s", command, strerror(errno));
    return;
  }
  
  if (wpa_scan_file == NULL) {
    buffer[length] = '\0';
    android_syslog(ANDROID_LOG_INFO, "%s", buffer);
  } else {
    buffer[length] = '\0';
    fprintf(wpa_scan_file, "%s", buffer);
    fclose(wpa_scan_file);
  }
  return;
}

void start_scan(void)
{
  control_connection = wpa_open_control_connection("/data/misc/wifi/sockets/wpa_ctrl_1109-2");
  wpa_print_scan_results();
  wpa_close_control_connection();
  return;
}

int main(int argc, char *argv[])
{

  int c;
  int scan_mode = MODE_ENABLED;
  int config_mode = MODE_DISABLED;

  
  while ((c = getopt(argc, argv, "sc:")) != -1)
    switch (c)
      {
      case 's':
	scan_mode = MODE_ENABLED;
	break;
      case 'c':
	config_mode = MODE_ENABLED;
	break;
      case '?':
	android_syslog(ANDROID_LOG_ERROR, "Invalid option: %c", optopt);
	return -1;
      default:
	abort();
      }

  if (scan_mode == MODE_ENABLED || config_mode == MODE_ENABLED)
    start_scan();

  return 0;
}
