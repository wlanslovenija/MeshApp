/*------------*\
 *  guilib.h  *
\*------------*/

#define BUFSIZE 256

/**
 * Global Variables
 */

const char *working_dir;

const char *olsr_init_script_path;

const char *olsr_kill_script_path;

/**
 * Function Prototypes 
 */

int init(const char *jni_path);

int meshapp_start(void);

int meshapp_stop(void);
