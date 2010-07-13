
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *data_path;
FILE *config_file;
void generate_config_file();

void generate_config_file()
{		       
  const char *debug_level = "DebugLevel";
  int debug_value = 0;

  const char *ip_version = "IpVersion";
  int ip_value = 4;

  const char *interface = "Interface";
  const char *interface_value = "wlan0";
  
  data_path = "/data/data/net.wlanlj.meshapp/etc";
  if (chdir(data_path) == 0) 
    {
      if ((config_file = fopen("olsrd.conf", "w")) != NULL) 
	{
	  fprintf(config_file, "%s %d\n", debug_level, debug_value);
	  fprintf(config_file, "%s %d\n", ip_version, ip_value);
	  fprintf(config_file, "%s %c\n %s\n %c", interface, '{', interface_value, '}');
	  exit(0);
	}
      else
	{
	  printf(stderr, "Could not open olsrd.conf");
	  exit(1);
	}
    }
  else
    {
      printf(stderr, "could not chdir() to specified directory");
      exit(1);
    }
}
  
  

  

 
