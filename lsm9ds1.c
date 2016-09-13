#include "lsm9ds1.h"
#include "libi2c.h"

int init_sensor(int fd)
{
    uint8_t ctrl_reg1_g = ODR_G(4) | FS_G(1);
    uint8_t ctrl_reg2_g = 0x00;
    uint8_t ctrl_reg3_g = 0x00;
    uint8_t ctrl_reg4 = ZEN_G | YEN_G | XEN_G;
    uint8_t ctrl_reg5_xl = ZEN_XL | YEN_XL | XEN_XL;
    uint8_t ctrl_reg6_xl = ODR_XL(4) | FS_XL(2);
    uint8_t ctrl_reg7_xl = 0x00;
    uint8_t ctrl_reg8 = BDU | IF_ADD_INC;

    write_byte(fd, CTRL_REG1_G, ctrl_reg1_g);
    write_byte(fd, CTRL_REG2_G, ctrl_reg2_g);
    write_byte(fd, CTRL_REG3_G, ctrl_reg3_g);
    write_byte(fd, CTRL_REG4, ctrl_reg4);
    write_byte(fd, CTRL_REG5_XL, ctrl_reg5_xl);
    write_byte(fd, CTRL_REG6_XL, ctrl_reg6_xl);
    write_byte(fd, CTRL_REG7_XL, ctrl_reg7_xl);
    write_byte(fd, CTRL_REG8, ctrl_reg8);

    uint8_t old_slave = i2c_slave_addr;
    uint8_t new_slave = ((old_slave << 1) & 0x02) | 0x1C;
    set_slave(fd,new_slave);

    uint8_t ctrl_reg1_m = TEMP_COMP | OM_M(3) | DO_M(7);
    uint8_t ctrl_reg2_m = 0x00;
    uint8_t ctrl_reg3_m = MD_M(0);
    uint8_t ctrl_reg4_m = OMZ(3);
    uint8_t ctrl_reg5_m = BDU_M;

    write_byte(fd, CTRL_REG1_M, ctrl_reg1_m);
    write_byte(fd, CTRL_REG2_M, ctrl_reg2_m);
    write_byte(fd, CTRL_REG3_M, ctrl_reg3_m);
    write_byte(fd, CTRL_REG4_M, ctrl_reg4_m);
    write_byte(fd, CTRL_REG5_M, ctrl_reg5_m);

    set_slave(fd,old_slave);

    return 0;
}

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

