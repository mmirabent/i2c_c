/*
 * Implementation for simple I2C Library
 */

#include "libi2c.h"
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

i2c::i2c(int adapter) {

  char filename[20];
  snprintf(filename, 19, "/dev/i2c-%d", adapter);
  file = open(filename, O_RDWR);
}

i2c::~i2c() { close(file); }

int i2c::set_slave(uint8_t address) {
  slave = address;
  return ioctl(file, I2C_SLAVE, address);
}

int i2c::write_byte(uint8_t reg, uint8_t byte) {
  uint8_t buffer[2];
  buffer[0] = reg;
  buffer[1] = byte;

  return write(file, buffer, 2);
}

int i2c::read_byte(uint8_t reg, uint8_t* byte) {
  struct i2c_msg* msgs = (struct i2c_msg*)malloc(sizeof(struct i2c_msg) * 2);

  msgs[0].addr = slave;
  msgs[0].flags = 0x00;
  msgs[0].len = 1;
  msgs[0].buf = &reg;

  msgs[1].addr = slave;
  msgs[1].flags = I2C_M_RD;
  msgs[1].len = 1;
  msgs[1].buf = byte;

  struct i2c_rdwr_ioctl_data data;
  data.msgs = msgs;
  data.nmsgs = 2;

  return ioctl(file, I2C_RDWR, &data);
}

int i2c::read_word(uint8_t reg, uint8_t* byte){return 0;}
