#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include "guilib.h"
#include "config.h"
#include "log.h"

const char *root_cmd = "su -c ";

int init(const char *path)
{
  /**
   * Set the file paths.
   */
  strcpy(platform_data_path, path);
  set_file_path(olsr_start_script, olsr_start_script_name);
  set_file_path(olsr_stop_script, olsr_stop_script_name);
  set_file_path(olsr_config_file, olsr_config_file_name);
  set_file_path(olsr_lock_file, olsr_lock_file_name);
  set_file_path(olsr_bin_file, olsr_bin_file_name);
  set_file_path(detect_adhoc_script, detect_adhoc_script_name);
  set_file_path(create_adhoc_script, create_adhoc_script_name);

  /**
   * Make scripts and binaries executable.
   */
  mode_t exec_mode = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH;
  
  chmod(olsr_start_script, exec_mode);
  chmod(olsr_stop_script, exec_mode);
  chmod(olsr_bin_file, exec_mode);
  chmod(detect_adhoc_script, exec_mode);
  chmod(create_adhoc_script, exec_mode);

  return 0;
}

int meshapp_start()
{
  /**
   * Configure the OLSR routing protocol.
   */
  if (configure_olsr_protocol() == -1) {
    guilib_syslog(GUILIB_LOG_ERROR, "Error! Failed to write OLSR config file %s: %s", olsr_config_file_name, strerror(errno));
    return -1;
  }
  
  guilib_syslog(GUILIB_LOG_INFO, "Wrote OLSR config file: %s", olsr_config_file);

  /**
   * Run the script to start the OLSR daemon.
   */
  strcpy(olsr_start_syscmd, root_cmd);
  strcat(olsr_start_syscmd, olsr_start_script);
  
  if (system(olsr_start_syscmd) != 0) {
    guilib_syslog(GUILIB_LOG_ERROR, "Error! \"%s\" returned non-zero exit status: %s", olsr_start_syscmd, strerror(errno));
    return -1;
  }
  
  guilib_syslog(GUILIB_LOG_INFO, "Command \"%s\" executed successfully.", olsr_start_syscmd);
  return 0;
}

int meshapp_stop()
{

  /**
   * Run the script to stop the OLSR daemon.
   */
  strcpy(olsr_stop_syscmd, root_cmd);
  strcat(olsr_stop_syscmd, olsr_stop_script);

  if (system(olsr_stop_syscmd) != 0) {
    guilib_syslog(GUILIB_LOG_ERROR, "Error! \"%s\" returned non-zero exit status: %s", olsr_stop_syscmd, strerror(errno));
    return -1;
  }
  						\
  guilib_syslog(GUILIB_LOG_INFO, "Command \"%s\" executed successfully.", olsr_stop_syscmd);
  return 0;
}
