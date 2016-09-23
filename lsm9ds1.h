#ifndef LSM9DS1_H
#define LSM9DS1_H

#include <stdint.h>
#include "registers.h"

struct ga_data {
  int16_t gx;
  int16_t gy;
  int16_t gz;
  int16_t ax;
  int16_t ay;
  int16_t az;
};

struct m_data {
  int16_t x;
  int16_t y;
  int16_t z;
};

struct gam_data_float {
  float gx;
  float gy;
  float gz;
  float ax;
  float ay;
  float az;
  float mx;
  float my;
  float mz;
};

int get_status(int id);

int init_sensor(int fd);

void get_mag(int fd, struct m_data* data);
void get_gyro_accel(int fd, struct ga_data* data);
void convert(struct ga_data gdata, struct m_data mdata, struct gam_data_float* gamdata);

#endif

