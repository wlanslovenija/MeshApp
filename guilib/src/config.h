/*------------*\
 *  config.h  *
\*------------*/

/**
 * Global Variables
 */

const char *olsr_config_file_path;

const char *olsr_lock_file_path;

const char *wlan_interface;

/**
 * Function Prototypes
 */

int generate_olsr_config_file(void);
