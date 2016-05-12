/*
 * Simple I2C communication library
 */

#ifndef MM_I2C_H
#define MM_I2C_H

#include <cstdint>

class i2c {
public:
  i2c(int adapter);
  ~i2c();

  int set_slave(uint8_t address);

  int write_byte(uint8_t reg, uint8_t byte);
  int read_byte(uint8_t reg, uint8_t* byte);
  int read_word(uint8_t reg, uint8_t* byte);

private:
  int file;
  uint8_t slave;
};

#endif
