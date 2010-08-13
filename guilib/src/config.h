#ifndef _CONFIG_H
#define _CONFIG_H

#define BUFSIZE 128

char platform_data_path[BUFSIZE];

char olsr_start_script[BUFSIZE];

char olsr_stop_script[BUFSIZE];

char olsr_config_file[BUFSIZE];

char olsr_lock_file[BUFSIZE];

char olsr_pid_file[BUFSIZE];

char olsr_bin_file[BUFSIZE];

char olsr_start_syscmd[BUFSIZE];

char olsr_stop_syscmd[BUFSIZE];

/**
 * Sets platform-specific absolute paths of files needed by GuiLib.
 *
 * @param path_buf is a char array that the absolute path is copied into.
 * @param platform_data_path is a string provided by the platform, this is the "prefix" to the absolute path, 
 * @param file_name is a string pointing to the relative location or name of the file, this is the "suffix" to the absolute path,
 *
 * @return the absolute path of the file, stored in path_buf.
 */
char *set_file_path(char buf[], const char *file); 


/**
 * Writes the configuration file for OLSR routing protocol.
 *
 * @return 0 on success, -1 on failure.
 */
int configure_olsr_protocol(void);

#endif
