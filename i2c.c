
#include "registers.h"
#include "libi2c.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

int main() {

  // Setup the GPIO interface
  wiringPiSetupSys();

  // This is the 7 bit slave address we want to write to.
  // Range is 0x03 to 0x77
  // 0x6A is the slave address for the accelerometer and gyro on an LSM9DS1
  // with the SA0 line pulled low
  int addr = 0x6A;
  int i2c = wiringPiI2CSetup(addr);

  if(i2c == -1) // Something terrible has happened
  {
    perror("Failed to initialize i2c");
    return -1;
  }

  // 0x10 is the gyroscope control register. Setting this register will turn
  // on both the gyro and accelerometer
  uint8_t reg = 0x10;
  uint8_t data = 1 << 5;

  wiringPiI2CWriteReg8(i2c,reg,data);

  // This loop continually reads the high byte of the accelerometer output
  // register
  int buf;
  reg = OUT_X_L_G;
  while (1) {
    //i2cdev.read_byte(reg,buf);
    buf = wiringPiI2CReadReg8(i2c,reg);
    printf("0x%X\n", buf); // Print the register
    struct timespec fifty_ms = (struct timespec){0,50*1000*1000};
    nanosleep(&fifty_ms,NULL);
  }
}
