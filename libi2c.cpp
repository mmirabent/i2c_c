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
#include <cstring>

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

int i2c::write_bytes(uint8_t reg, uint8_t* bytes, int num) {
  uint8_t* buffer = new uint8_t[num+1];
  buffer[0] = reg;
  memcpy(buffer+1,bytes,num);

  int ret = write(file,buffer,num+1);
  delete buffer;
  return ret;
}

int i2c::read_byte(uint8_t reg, uint8_t* byte) {
  return read_bytes(reg,byte,1);
}

int i2c::read_bytes(uint8_t reg, uint8_t* bytes, int num){
  struct i2c_msg* msgs = new struct i2c_msg[num+1];

  msgs[0].addr = slave;
  msgs[0].flags = 0x00;
  msgs[0].len = 1;
  msgs[0].buf = &reg;

  msgs[1].addr = slave;
  msgs[1].flags = I2C_M_RD;
  msgs[1].len = num;
  msgs[1].buf = bytes;

  struct i2c_rdwr_ioctl_data data;
  data.msgs = msgs;
  data.nmsgs = 2;

  int ret = ioctl(file, I2C_RDWR, &data);
  delete[] msgs;
  return ret;
}

