#ifndef _GUILIB_H
#define _GUILIB_H

const char *olsr_start_script_name = "/bin/olsr_start";

const char *olsr_stop_script_name = "/bin/olsr_stop";

const char *olsr_bin_file_name = "/bin/olsrd";

const char *olsr_config_file_name = "/tmp/olsrd.conf";

const char *olsr_lock_file_name = "/tmp/olsrd.lock";

const char *olsr_pid_file_name = "/tmp/olsrd.pid";

const char *wificonfig_bin_file_name = "/bin/wificonfig";

const char *scan_results_file_name = "/tmp/scan_results.log";

/**
 * Initializes the platform-specific components to GuiLib.
 *
 * @param platform_data_path is a string passed from the platform pointing the the path where MeshApp should store its data.
 *
 * @return 0 on success, < 0 on failure.
 */
int guilib_init(const char *path);

/**
 * High level controller for guilib.
 *
 * @return 0 on success, < 0 on failure.
 */
int guilib_start(void);

/**
 * Platform interface for stopping MeshApp functionality provided by GuiLib.
 *
 * @return 0 on success, < 0 on failure.
 */
int guilib_stop(void);

/**
 * Run the wificonfig program to scan for ad-hoc networks.
 *
 * @return number of detected ad-hoc networks on success, < 0 on failure.
 */
int wifi_scan(void);

/**
 * Start the OLSR daemon.
 *
 * @return 0 on success, < 0 on failure.
 */
int olsrd_start(void);

/**
 * Stop the OLSR daemon.
 *
 * @return 0 on success, < 0 on failure.
 */
int olsrd_stop(void);

/**
 * Remove temporary files created by guilib.
 */
void clean_temp_files(char *file_path);

/**
 * Writes the output of %id to the syslog for debugging.
 */
void get_uid(void);


#endif
