/*
 * Implementation for simple I2C Library
 */

#include "libi2c.h"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

int set_slave(int fd, int address) {
  return ioctl(fd, I2C_SLAVE, address);
}
