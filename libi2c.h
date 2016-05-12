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
  int write_bytes(uint8_t, uint8_t* bytes, int num);
  int read_byte(uint8_t reg, uint8_t* byte);
  int read_bytes(uint8_t reg, uint8_t* bytes, int num);

private:
  int file;
  uint8_t slave;
};

#endif
