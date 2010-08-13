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

#include "wpa_ctrl.h"
#include "wifi_config.h"

static struct wpa_ctrl *control_connection;

static const char *local_socket_dir = "/data/misc/wifi/wpa_supplicant";

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
  fprintf(stdout, "%s\n", message);
}


static void wpa_print_scan_results(void) 
{
  char command = "SCAN_RESULTS";
  char buffer[4096];
  size_t length;
  int ret;
  
  if (control_connection == NULL) {
    fprintf(stderr, "Error: Not connected to wpa_supplicant: %s", strerror(errno));
    return;
  }
  
  length = sizeof(buffer) - 1;
  ret = wpa_ctrl_request(control_connection, command, strlen(command), buffer, &length, wpa_message_callback);

  if (ret == -2) {
    fprintf(stderr, "'%s' command timed out.", command);
    return;
  }
  else if (ret < 0) {
    fprintf(stderr, "'%s' command failed: %s", command, strerror(errno));
    return;
  }
  
  buffer[length] = '\0';
  fprintf(stdout, "%s", buffer);
  
  return;
}

int main(int argc, char *argv[])
{
  control_connection = wpa_open_control_connection(local_socket_dir);
  wpa_print_scan_results();
  wpa_close_control_connection();
  return 0;
}
