/*
 * Simple I2C communication library
 */

#ifndef MM_I2C_H
#define MM_I2C_H

#include <stdint.h>
#include <stddef.h>

extern uint8_t i2c_slave_addr;

int open_i2c(int bus);
int set_slave(int fd, uint8_t address);
int write_byte(int fd, uint8_t reg, uint8_t byte);
int write_bytes(int fd, uint8_t reg, uint8_t* bytes, size_t count);
int read_byte(int fd, uint8_t reg, uint8_t* byte);
int read_bytes(int fd, uint8_t reg, uint8_t* bytes, size_t num);

#endif
