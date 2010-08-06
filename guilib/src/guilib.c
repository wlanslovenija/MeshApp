/*------------*\
 *  guilib.c  *
\*------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include "log.h"
#include "config.h"
#include "guilib.h"

char olsr_config_buf[BUFSIZE];
char olsr_lock_buf[BUFSIZE];
char olsr_init_buf[BUFSIZE];
char olsr_kill_buf[BUFSIZE];
char olsr_bin_buf[BUFSIZE];

char syscmd_start[BUFSIZE];
char syscmd_stop[BUFSIZE];

const char *olsr_bin_file_path;

const char *root_cmd = "su -c ";

mode_t exec_mode = S_ISUID | S_ISGID | S_ISVTX | S_IXUSR | S_IXUSR | S_IROTH | S_IXOTH;

int init(const char *path)
{
  strcpy(olsr_bin_buf, path);
  olsr_bin_file_path = strcat(olsr_bin_buf, "/bin/olsrd");
  chmod(olsr_bin_file_path, exec_mode);
  android_log_info(olsr_bin_file_path);

  strcpy(olsr_init_buf, path);
  olsr_init_script_path = strcat(olsr_init_buf, "/bin/olsrd_init");
  chmod(olsr_init_script_path, exec_mode);
  android_log_info(olsr_init_script_path);

  strcpy(olsr_kill_buf, path);
  olsr_kill_script_path = strcat(olsr_kill_buf, "/bin/olsrd_kill");
  chmod(olsr_kill_script_path, exec_mode);
  android_log_info(olsr_kill_script_path);

  strcpy(olsr_config_buf, path);
  olsr_config_file_path = strcat(olsr_config_buf, "/tmp/olsrd.conf"); 
  android_log_info(olsr_config_file_path);

  strcpy(olsr_lock_buf, path);
  olsr_lock_file_path = strcat(olsr_lock_buf, "/tmp/olsrd.lock");
  android_log_info(olsr_lock_file_path);

  return 0;
}

int meshapp_start()
{
  if (generate_olsr_config_file() == -1) {
    android_log_error("failed to write olsrd.conf");
    return -1;
  }

  android_log_info("wrote olsrd.conf");

  strcpy(syscmd_start, root_cmd);
  strcat(syscmd_start, olsr_init_script_path);
  android_log_info(syscmd_start);
  
  if (system(syscmd_start) != 0) {
    android_log_error("failed to run olsrd");
    return -1;
  }

    android_log_info("started olsrd");

    return 0;
}
  

int meshapp_stop()
{
  strcpy(syscmd_stop, root_cmd);
  strcat(syscmd_stop, olsr_kill_script_path);
  android_log_info(syscmd_stop);

  if (system(syscmd_stop) != 0) {
    android_log_error("failed to kill olsrd");
    return -1;
  }
 
  android_log_info("killed olsrd"); 
 
  return 0;
}
