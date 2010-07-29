
/* Global Variables */

static const char *config_file = "/data/data/net.wlanlj.meshapp/etc/olsrd.conf";

/* Function Prototypes  */

static void generate_olsr_config_file(void);

int adhoc_mode(void);

int run_olsrd(void);

int kill_olsrd(void);
