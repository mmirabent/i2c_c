#include "lsm9ds1.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>

int set_odr(int fd, int odr)
{
  // This takes the odr value, 3 bits, and shifts it
  int shifted = (odr << 5) & 0xE0;

  // get the current CTRL_REG_1
  int ctrl_reg1 = wiringPiI2CReadReg8(fd,CTRL_REG1_G);

  // Set the ODR bits
  ctrl_reg1 |= shifted;

  // Write back CTRL_REG_1
  return wiringPiI2CWriteReg8(fd,CTRL_REG1_G,ctrl_reg1);
}

void get_gyro(int fd, struct g_data* data)
{
  // If the data pointer is null, return now
  if(!data)
    return;

  // These will hold the individual bytes read from the device
  int x_h,x_l,y_h,y_l,z_h,z_l;

  // Read the high and low bytes
  // A note, this is probably not the most efficient way to do this as every
  // read statement is a seperate I2C transaction. It's probably not worth it
  // but you can get even faster throughput(theoretically) if you omit the stop
  // and start conditions. In order to do that, however, we'd have to revert to
  // using raw ioctl() calls. So we'll cross that bridge if/when we get there

  x_l = wiringPiI2CReadReg8(fd,OUT_X_L_G);
  x_h = wiringPiI2CRead(fd);
  y_l = wiringPiI2CRead(fd);
  y_h = wiringPiI2CRead(fd);
  z_l = wiringPiI2CRead(fd);
  z_h = wiringPiI2CRead(fd);

  // Store the data in the data opject
  data->x = x_l | (x_h << 8);
  data->y = y_l | (y_h << 8);
  data->z = z_l | (z_h << 8);
}

void get_accel(int fd, struct a_data* data)
{
  // If the data pointer is null, return now
  if(!data)
    return;

  // These will hold the individual bytes read from the device
  int x_h,x_l,y_h,y_l,z_h,z_l;

  // Read the high and low bytes
  // A note, this is probably not the most efficient way to do this as every
  // read statement is a seperate I2C transaction. It's probably not worth it
  // but you can get even faster throughput(theoretically) if you omit the stop
  // and start conditions. In order to do that, however, we'd have to revert to
  // using raw ioctl() calls. So we'll cross that bridge if/when we get there

  x_l = wiringPiI2CReadReg8(fd,OUT_X_L_XL);
  x_h = wiringPiI2CRead(fd);
  y_l = wiringPiI2CRead(fd);
  y_h = wiringPiI2CRead(fd);
  z_l = wiringPiI2CRead(fd);
  z_h = wiringPiI2CRead(fd);

  // Store the data in the data opject
  data->x = x_l | (x_h << 8);
  data->y = y_l | (y_h << 8);
  data->z = z_l | (z_h << 8);
}

int get_status(int fd)
{
  return wiringPiI2CReadReg8(fd,STATUS_REG1);
}

