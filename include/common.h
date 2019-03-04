#ifndef _COMMON_H
#define _COMMON_H

#include <errno.h>

typedef enum {
  sig_interrupt,
  pwr_off,
} signal_t;

typedef enum {
  normal;
  abnormal;
} state_t;

#endif  //_COMMON_H

