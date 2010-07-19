
/* Global Variables */

static const char *config_file = "/data/data/net.wlanlj.meshapp/tmp/olsrd.conf";
static const char *lock_file = "/data/data/net.wlanlj.meshapp/tmp/olsrd-ipv4.lock";


/* Function Prototypes  */

int generate_config_file(void);

int get_olsr_pid(void);
	
int start_olsrd(void);

int stop_olsrd(void);			 
