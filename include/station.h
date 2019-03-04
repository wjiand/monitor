#ifndef _STATION_H
#define _STATION_H

typedef struct {
  state_t state;
} receiver_t;

typedef struct {
  int number;
  receiver_t no_1;
  receiver_t no_2;
  receiver_t no_3;
  receiver_t no_4;
} receivers_t;

typedef struct {
  float value;
  float threshold;
} value_t;

typedef struct {
  int speed;
  int grade;
} fan_t;

typedef struct {
  value_t temperature;
  value_t humidity;
  fan_t fan;
} sensor_t;

typedef struct {
  state_t state;
} door_t;

typedef struct {
  char id[64];
  char part_number[64];
  char version[64];
  int input_vol;
  int output_vol;
  int battery_vol;
  int mode;
  state_t input_state;
  state_t battery_state;
  state_t state;
} ups_t;

typedef struct {
  state_t state;
  state_t input_state;
} inverter_t;

typedef struct {
  ups_t ups;
  inverter_t inverter;
} power_t;

typedef struct {
  char system[32];
  char application[32];
  char hardware[32];
} version_t;

typedef struct {
  char id[64];
  version_t version;
  system_t system;
} monitor_t;

typedef struct {
  monitor_t   monitor;
  receivers_t receivers;
  sensor_t    dev_sensor;
  sensor_t    pwr_sensor;
  door_t      door;
  power_t     power;
} station_t;


extern char main_path[];

#endif  //_STATION_H
