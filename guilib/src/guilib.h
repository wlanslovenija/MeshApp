/*------------*\
 *  guilib.h  *
\*------------*/

/**
 * Definitions
 */

#define MAX_PATH_LENGTH 128
#define SLEEP_DURATION 5


/**
 * Function Prototypes 
 */

int init(const char *path);

int meshapp_start(void);

int meshapp_stop(void);

void generate_olsr_config_file(const char *cfg);

void android_log_error(const char *m);

void android_log_info(const char *m);
