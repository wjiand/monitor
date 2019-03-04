#ifndef _SYSMGT_H
#define _SYSMGT_H

typedef struct {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  long utc_seconds;
  long launch_time;
  int timing;
} tm_t;

typedef struct {
  unsigned int freq;
  float util;
} cpu_t;

typedef struct {
  unsigned int total;
  unsigned int free;
  unsigned int available;
  float util;
} mem_t;

typedef struct {
  float in_rom_total;
  float in_rom_free;
  float in_rom_util;
  float ex_rom_total;
  float ex_rom_free;
  float ex_rom_util;
} disk_t;

typedef struct {
  tm_t time;
  cpu_t cpu;
  mem_t mem;
  disk_t disk;
} system_t;

#endif  //_SYSMGT_H

