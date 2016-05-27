
#include "libi2c.h"
#include "registers.h"
#include <cstdio>
#include <unistd.h>

int main() {

  i2c i2cdev(1);

  // This is the 7 bit slave address we want to write to.
  // Range is 0x03 to 0x77
  // 0x6A is the slave address for the accelerometer and gyro on an LSM9DS1
  // with the SA0 line pulled low
  int addr = 0x6A;
  i2cdev.set_slave(addr);

  // 0x10 is the gyroscope control register. Setting this register will turn
  // on both the gyro and accelerometer
  uint8_t reg = 0x10;
  uint8_t data = 1 << 5;
  i2cdev.write_byte(reg,data);

  // This loop continually reads the high byte of the accelerometer output
  // register
  uint8_t* buf = new uint8_t;
  reg = 0x28;
  while (1) {
    i2cdev.read_byte(reg,buf);
    printf("0x%X\n", *buf); // Print the register
    usleep(50 * 1000); // sleep for 50 ms
  }
}
