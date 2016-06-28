
#include "registers.h"
#include "lsm9ds1.h"
#include "libi2c.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

int main() {

  // Setup the GPIO interface
  int i2c = open_i2c(1);

  // This is the 7 bit slave address we want to write to.
  // Range is 0x03 to 0x77
  // 0x6A is the slave address for the accelerometer and gyro on an LSM9DS1
  // with the SA0 line pulled low
  uint8_t addr = 0x6A;
  set_slave(i2c,addr);

  if(i2c == -1) // Something terrible has happened
  {
    perror("Failed to initialize i2c");
    return -1;
  }

  // Set the gyroscope and accelerometer output data rate to 1
  // 1 corresponds to 14.9 Hz. see datasheet for other values
  set_odr(i2c,3);

  // This loop continually reads the high byte of the accelerometer output
  // register
  int status;
  struct g_data data;
  while (1) {
    status = get_status(i2c);
    if(!(status & 0x02)) // No new gyro data
      continue;

    get_gyro(i2c,&data);
    printf("%d,%d,%d\n",data.x,data.y,data.z);
  }
}
