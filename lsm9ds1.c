#include "lsm9ds1.h"
#include "libi2c.h"

static int fs_g;
static int fs_a;
static int fs_m;

int init_sensor(int fd)
{
    uint8_t fsg = 1;
    uint8_t fsa = 2;
    uint8_t fsm = 0;
    uint8_t odr_ga = 4;
    uint8_t odr_m = 7;

    uint8_t ctrl_reg1_g = (uint8_t)(ODR_G(odr_ga) | FS_G(fsg));
    uint8_t ctrl_reg2_g = 0x00;
    uint8_t ctrl_reg3_g = 0x00;
    uint8_t ctrl_reg4 = ZEN_G | YEN_G | XEN_G;
    uint8_t ctrl_reg5_xl = ZEN_XL | YEN_XL | XEN_XL;
    uint8_t ctrl_reg6_xl = (uint8_t)(ODR_XL(odr_ga) | FS_XL(fsa));
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

    uint8_t ctrl_reg1_m = (uint8_t)(TEMP_COMP | OM_M(3) | DO_M(odr_m));
    uint8_t ctrl_reg2_m = (uint8_t)FS_M(fsm);
    uint8_t ctrl_reg3_m = MD_M(0);
    uint8_t ctrl_reg4_m = OMZ(3);
    uint8_t ctrl_reg5_m = BDU_M;

    write_byte(fd, CTRL_REG1_M, ctrl_reg1_m);
    write_byte(fd, CTRL_REG2_M, ctrl_reg2_m);
    write_byte(fd, CTRL_REG3_M, ctrl_reg3_m);
    write_byte(fd, CTRL_REG4_M, ctrl_reg4_m);
    write_byte(fd, CTRL_REG5_M, ctrl_reg5_m);

    set_slave(fd,old_slave);
    
    switch(fsa) {
        case 0:
            fs_a = 2;
            break;
        case 1:
            fs_a = 16;
            break;
        case 2:
            fs_a = 4;
            break;
        case 3:
            fs_a = 8;
            break;
    }

    switch(fsg) {
        case 0:
            fs_g = 254;
            break;
        case 1:
            fs_g = 100;
            break;
        case 2:
            fs_g = 0;
            break;
        case 3:
            fs_g = 2000;
            break;
    }

    switch(fsm) {
        case 0:
            fs_m = 4;
            break;
        case 1:
            fs_m = 8;
            break;
        case 2:
            fs_m = 12;
            break;
        case 3:
            fs_m = 16;
            break;
    }

    return 0;
}

void convert(struct ga_data gdata, struct m_data mdata, struct gam_data_float* gamdata)
{
    gamdata->gx = gdata.gx*fs_g/(float)32767;
    gamdata->gy = gdata.gy*fs_g/(float)32767;
    gamdata->gz = gdata.gz*fs_g/(float)32767;
    gamdata->ax = gdata.ax*fs_a/(float)32767;
    gamdata->ay = gdata.ay*fs_a/(float)32767;
    gamdata->az = gdata.az*fs_a/(float)32767;
    gamdata->mx = mdata.x*fs_m/(float)32767;
    gamdata->my = mdata.y*fs_m/(float)32767;
    gamdata->mz = mdata.z*fs_m/(float)32767;
}

void get_gyro_accel(int fd, struct ga_data* data)
{
    if(!data)
        return;

    read_bytes(fd, OUT_X_L_G,(uint8_t*)data,12);
}

void get_mag(int fd, struct m_data* data)
{
  // If the data is null, return now
  uint8_t old_slave = i2c_slave_addr;
  uint8_t new_slave = ((old_slave << 1) & 0x02) | 0x1C;
  set_slave(fd,new_slave);

  read_bytes(fd,OUT_X_L_M,(uint8_t*)data,6);
  data->x *= -1;

  set_slave(fd,old_slave);
}

int get_status(int fd)
{
  uint8_t stat;
  read_byte(fd,STATUS_REG1,&stat);
  return stat;
}

