#ifndef LSM9DS1_H
#define LSM9DS1_H

#include <stdint.h>
#include "registers.h"

struct g_data {
  int16_t x;
  int16_t y;
  int16_t z;
};

struct a_data {
  int16_t x;
  int16_t y;
  int16_t z;
};

struct m_data {
  int16_t x;
  int16_t y;
  int16_t z;
};

int set_hpf_reference(int id, int ref);
int set_odr(int id, int odr);
int set_fsg(int id, int fs);
int get_temp(int id);
int get_status(int id);

int init_sensor(int fd);

void get_gyro(int fd, struct g_data* data);
void get_accel(int fd, struct a_data* data);
void get_mag(int fd, struct m_data* data);

#endif

