#ifndef _CONFIG_H
#define _CONFIG_H

#define BUFSIZE 128

char platform_data_path[BUFSIZE];

char olsr_start_script[BUFSIZE];

char olsr_stop_script[BUFSIZE];

char olsr_config_file[BUFSIZE];

char olsr_lock_file[BUFSIZE];

char olsr_bin_file[BUFSIZE];

char detect_adhoc_script[BUFSIZE];

char create_adhoc_script[BUFSIZE];

char olsr_start_syscmd[BUFSIZE];

char olsr_stop_syscmd[BUFSIZE];

typedef struct adhoc_network {
  char ssid[32];
  char bssid[18];
  char key_mgnt[8];
  int priority;
  int mode;
} adhoc_network;

/**
 * Sets platform-specific absolute paths of files needed by GuiLib.
 *
 * @param path_buf is a char array that the absolute path is copied into.
 * @param platform_data_path is a string provided by the platform, this is the "prefix" to the absolute path, 
 * @param file_name is a string pointing to the relative location or name of the file, this is the "suffix" to the absolute path,
 *
 * @return the absolute path of the file, stored in path_buf.
 */
char *set_file_path(char path_buf[], const char *file_name); 


/**
 * Writes the configuration file for OLSR routing protocol.
 *
 * @return 0 on success, -1 on failure.
 */
int configure_olsr_protocol(void);


/**
 * Scans for wireless ad-hoc networks.
 *
 * @return The number of detected ad-hoc networks if any are available, -1 otherwise.
 */
int detect_adhoc_network(void);


/**
 * Creates an ad-hoc network.
 *
 * @param adhoc_network is the structure defining the network to create.
 *
 * @return 0 on success, -1 on failure.
 */
int configure_adhoc_network(adhoc_network network);

#endif
