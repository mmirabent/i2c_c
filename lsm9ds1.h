#ifndef LSM9DS1_H
#define LSM9DS1_H

#include <stdint.h>
#include "registers.h"

/* These are the values for the full scale settings for Gyroscope,
 * Accelerometer and Magnetometer in that order */
#define FS_G_VAL 1
#define FS_XL_VAL 2
#define FS_M_VAL 2

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

struct ga_data_float {
    float gx;
    float gy;
    float gz;
    float ax;
    float ay;
    float az;
};

struct m_data_float {
    float x;
    float y;
    float z;
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
void get_gyro_accel(int fd, struct ga_data* data, struct ga_data_float* fdata);

#endif

