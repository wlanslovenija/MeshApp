/*-------------------------------------------*\
 *              olsrd.config.h               *
\*-------------------------------------------*/


/**
 * Global Variables 
 */

const char *bin_path = "/data/data/net.wlanlj.meshapp/bin/";
const char *tmp_path = "/data/data/net.wlanlj.meshapp/tmp/";

const char *config_file_name = "olsrd.conf";
const char *lock_file_name = "olsrd.lock";

const char *start_script_name = "run_olsrd";
const char *stop_script_name = "kill_olsrd";
const char *adhoc_mode_script_name = "adhoc_mode";

/**
 * Function Prototypes 
 */

static void generate_olsr_config_file(void);

int adhoc_mode(void);

int run_olsrd(void);

int kill_olsrd(void);
