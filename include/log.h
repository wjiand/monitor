#ifndef _LOG_H
#define _LOG_H

#include "../zlog/zlog.h"

extern zlog_category_t *o;


int  log_init(void);
void log_exit(void);

#endif //_LOG_H

