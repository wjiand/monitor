#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "log.h"
#include "station.h"

zlog_category_t *o;

/*
 * Initialize zlog system
 */
int log_init(void)
{
  int ret = 0;
  char zlog_conf_path[256] = {0};

  //Get config file path
  strcpy(zlog_conf_path, main_path);
  strcat(zlog_conf_path, "/conf/zlog.conf");

  ret = zlog_init(zlog_conf_path);
  if(ret)
  {
    printf("zlog init failed!\n");
    return -1;
  }

  o = zlog_get_category("base");
  if(!o)
  {
    printf("zlog get category failed!\n");
    zlog_fini();
    return -1;
  }

  return ret;
}

/*
 * Uninitialize zlog system
 */
void log_exit(void)
{
  zlog_fini();
}


