#ifndef _GUILIB_H
#define _GUILIB_H

const char *olsr_start_script_name = "/bin/olsr_start";

const char *olsr_stop_script_name = "/bin/olsr_stop";

const char *olsr_bin_file_name = "/bin/olsrd";

const char *olsr_config_file_name = "/tmp/olsrd.conf";

const char *olsr_lock_file_name = "/tmp/olsrd.lock";

const char *olsr_pid_file_name = "/tmp/olsrd.pid";

const char *detect_adhoc_script_name = "/bin/detect_adhoc";

const char *create_adhoc_script_name = "/bin/create_adhoc_network";

/**
 * Initializes the platform-specific components to GuiLib.
 *
 * @param platform_data_path is a string passed from the platform pointing the the path where MeshApp should store its data.
 *
 * @return 0 on success, < 0 on failure.
 */
int init(const char *path);


/**
 * Platform interface for starting MeshApp functionality provided by GuiLib.
 *
 * @return 0 on success, < 0 on failure.
 */
int meshapp_start(void);


/**
 * Platform interface for stopping MeshApp functionality provided by GuiLib.
 *
 * @return 0 on success, < 0 on failure.
 */
int meshapp_stop(void);


/**
 * Writes the output of %id to the syslog for debugging.
 */
void get_uid(void);


#endif
