#ifndef LSM9DS1_REG_H
#define LSM9DS1_REG_H

// Accelerometer Registers

#define ACT_THS 0x04
#define ACT_DUR 0x05
#define INT_GEN_CFG_XL 0x06
#define INT_GEN_THS_X_XL 0x07
#define INT_GEN_THS_Y_XL 0x08
#define INT_GEN_THS_Z_XL 0x09
#define INT_GEN_DUR_XL 0x0A 
#define REFERENCE_G 0x0B 
#define INT1_CTRL 0x0C 
#define INT2_CTRL 0x0D 
#define WHO_AM_I 0x0F 

#define CTRL_REG1_G 0x10 
#define ODR_G(X) ((X & 0x07) << 5)
#define FS_G(X) ((X & 0x03) << 3)
#define BW_G(X) (X & 0x03)

#define CTRL_REG2_G 0x11
#define OUT_SEL(X) (X & 0x03)

#define CTRL_REG3_G 0x12 
#define LP_MODE 0x80
#define HP_EN 0x40
#define HPCF_G(X) (X & 0x0F)

#define ORIENT_CFG_G 0x13 
#define INT_GEN_SRC_G 0x14 
#define OUT_TEMP_L 0x15 
#define OUT_TEMP_H 0x16 
#define STATUS_REG1 0x17 
#define OUT_X_L_G 0x18 
#define OUT_X_H_G 0x19 
#define OUT_Y_L_G 0x1A 
#define OUT_Y_H_G 0x1B 
#define OUT_Z_L_G 0x1C 
#define OUT_Z_H_G 0x1D 

#define CTRL_REG4 0x1E 
#define XEN_G 0x08
#define YEN_G 0x10
#define ZEN_G 0x20

#define CTRL_REG5_XL 0x1F
#define DEC(X) ((X & 0x03) << 6)
#define XEN_XL 0x08
#define YEN_XL 0x10
#define ZEN_XL 0x20

#define CTRL_REG6_XL 0x20 
#define ODR_XL(X) ((X & 0x07) << 5)
#define FS_XL(X) ((X & 0x03) << 3)
#define BW_SCAL_ODR 0x04
#define BW_XL(X) (X & 0x03)

#define CTRL_REG7_XL 0x21
#define HR 0x80
#define DCF(X) ((X & 0x03) << 5)
#define FDS 0x04

#define CTRL_REG8 0x22 
#define BDU 0x40
#define IF_ADD_INC 0x04

#define CTRL_REG9 0x23 
#define CTRL_REG10 0x24
#define INT_GEN_SRC_XL 0x26
#define STATUS_REG2 0x27
#define OUT_X_L_XL 0x28
#define OUT_X_H_XL 0x29
#define OUT_Y_L_XL 0x2A
#define OUT_Y_H_XL 0x2B
#define OUT_Z_L_XL 0x2C
#define OUT_Z_H_XL 0x2D
#define FIFO_CTRL 0x2E
#define FIFO_SRC 0x2F
#define INT_GEN_CFG_G 0x30
#define INT_GEN_THS_XH_G 0x31
#define INT_GEN_THS_XL_G 0x32
#define INT_GEN_THS_YH_G 0x33
#define INT_GEN_THS_YL_G 0x34
#define INT_GEN_THS_ZH_G 0x35
#define INT_GEN_THS_ZL_G 0x36
#define INT_GEN_DUR_G 0x37

// Magnetometer Registers

#define OFFSET_X_REG_L_M 0x05
#define OFFSET_X_REG_H_M 0x06
#define OFFSET_Y_REG_L_M 0x07
#define OFFSET_Y_REG_H_M 0x08
#define OFFSET_Z_REG_L_M 0x09
#define OFFSET_Z_REG_H_M 0x0A
#define WHO_AM_I_M 0x0F

#define CTRL_REG1_M 0x20
#define TEMP_COMP 0x80
#define OM_M(X) ((X & 0x03) << 5)
#define DO_M(X) ((X & 0x07) << 2)
#define FAST_ODR 0x02

#define CTRL_REG2_M 0x21
#define FS_M(X) ((X & 0x03) << 5)

#define CTRL_REG3_M 0x22
#define MD_M(X) (X & 0x03)

#define CTRL_REG4_M 0x23
#define OMZ(X) ((X & 0x03) << 2)

#define CTRL_REG5_M 0x24
#define BDU_M 0x40

#define STATUS_REG_M 0x27
#define OUT_X_L_M 0x28
#define OUT_X_H_M 0x29
#define OUT_Y_L_M 0x2A
#define OUT_Y_H_M 0x2B
#define OUT_Z_L_M 0x2C
#define OUT_Z_H_M 0x2D
#define INT_CFG_M 0x30
#define INT_SRC_M 0x31
#define INT_THS_L_M 0x32
#define INT_THS_H_M 0x33

#endif

