#include "lsm9ds1.h"
#include "libi2c.h"

int set_odr(int fd, int odr)
{
  // This takes the odr value, 3 bits, and shifts it
  int shifted = (odr << 5) & 0xE0;

  // get the current CTRL_REG_1
  uint8_t ctrl_reg1;
  read_byte(fd,CTRL_REG1_G,&ctrl_reg1);

  // Set the ODR bits
  ctrl_reg1 |= shifted;

  // Write back CTRL_REG_1
  return write_byte(fd,CTRL_REG1_G,ctrl_reg1);
}

void get_gyro(int fd, struct g_data* data)
{
  // If the data pointer is null, return now
  if(!data)
    return;

  read_bytes(fd,OUT_X_L_G,(uint8_t*)data,6);
}

void get_accel(int fd, struct a_data* data)
{
  // If the data pointer is null, return now
  if(!data)
    return;

  read_bytes(fd,OUT_X_L_G,(uint8_t*)data,6);
}

void get_mag(int fd, struct m_data* data)
{
  // If the data is null, return now
  uint8_t old_slave = i2c_slave_addr;
  uint8_t new_slave = ((old_slave << 1) & 0x02) | 0x1C;
  set_slave(fd,new_slave);

  read_bytes(fd,OUT_X_L_M,(uint8_t*)data,6);

  set_slave(fd,old_slave);
}

int get_status(int fd)
{
  uint8_t stat;
  read_byte(fd,STATUS_REG1,&stat);
  return stat;
}

