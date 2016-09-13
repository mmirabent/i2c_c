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
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

uint8_t i2c_slave_addr;

int open_i2c(int bus) {
  char filename[20];
  snprintf(filename, 19, "/dev/i2c-%d", bus);
  return open(filename, O_RDWR);
}

int set_slave(int fd, uint8_t address) {
  i2c_slave_addr = address;
  return ioctl(fd, I2C_SLAVE, address);
}

int write_byte(int fd, uint8_t reg, uint8_t byte) {
  uint8_t buf[2];
  buf[0] = reg;
  buf[1] = byte;

  return (int)write(fd, buf, 2);
}

int write_bytes(int fd, uint8_t reg, uint8_t* bytes, size_t count) {
  uint8_t* buffer = malloc(count+1);
  buffer[0] = reg;
  memcpy(buffer+1,bytes,count);

  int ret = (int)write(fd,buffer,count+1);
  free(buffer);
  return ret;
}

int read_byte(int fd, uint8_t reg, uint8_t* byte) {
  return read_bytes(fd,reg,byte,1);
}

int read_bytes(int fd, uint8_t reg, uint8_t* bytes, size_t num) {

  struct i2c_msg* msgs = malloc(sizeof(struct i2c_msg)*(num+1));

  msgs[0].addr = i2c_slave_addr;
  msgs[0].flags = 0x00;
  msgs[0].len = 1;
  msgs[0].buf = &reg;

  msgs[1].addr = i2c_slave_addr;
  msgs[1].flags = I2C_M_RD;
  msgs[1].len = (uint16_t)num;
  msgs[1].buf = bytes;

  struct i2c_rdwr_ioctl_data data;
  data.msgs = msgs;
  data.nmsgs = 2;

  int ret = ioctl(fd, I2C_RDWR, &data);
  free(msgs);
  return ret;
}

