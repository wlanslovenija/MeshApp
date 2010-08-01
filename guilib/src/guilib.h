/*------------*\
 *  guilib.h  *
\*------------*/

/**
 * Global Variables 
 */

const char *data_dir_path;

const char *config_file_name = "tmp/olsrd.conf";
const char *lock_file_name = "tmp/olsrd.lock";

/*
const char *start_script = "bin/run_olsrd";
const char *stop_script = "bin/kill_olsrd";
const char *adhoc_mode_script = "bin/adhoc_mode";
*/

/**
 * Function Prototypes 
 */

int init(const char *path);

int meshapp_start(void);

int meshapp_stop(void);

int generate_olsr_config_file(void);

int adhoc_mode(void);

int run_olsrd(void);

int kill_olsrd(void);
