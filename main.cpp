#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "euler.h"
#include "moving.h"

extern "C" {
  #include "registers.h"
  #include "lsm9ds1.h"
  #include "libi2c.h"
}

using namespace std;

int main() {
  int i2c = open_i2c(1);

  if(i2c == -1) {
    perror("Failed to initialize i2c");
    exit(1);
  }



  uint8_t addr = 0x6A;
  set_slave(i2c,addr);

  init_sensor(i2c);
  struct ga_data gadata;
  struct m_data mdata;
  struct gam_data_float gamdata;
  Euler raw_angle;
  Euler avg_angle;



  //printf("ax,ay,az,mx,my,mz,Raw Phi, Raw Theta, Raw Psi, Filtered Phi, Filtered Theta, Filtered Psi\n");
  printf("ax,ay,az,mx,my,mz,Raw Phi, Raw Theta, Raw Psi, Filtered Phi, Filtered Theta, Filtered Psi\n");

  while(1) {
    get_gyro_accel(i2c,&gadata);
    get_mag(i2c,&mdata);
    convert(gadata, mdata, &gamdata);
   // printf("%08.3f,%f,%f,%f,%f,%f,",gamdata.ax,gamdata.ay,gamdata.az,gamdata.mx,gamdata.my,gamdata.mz);
    raw_angle = eulercomp(gamdata.ax,gamdata.ay,gamdata.az,
                          gamdata.mx,gamdata.my,gamdata.mz);
    printf("%08.3f,%08.3f,%08.3f,",raw_angle.phi*57.296, raw_angle.theta*57.296, raw_angle.psi*57.296);
    avg_angle = moving_avg(raw_angle);
    printf("%08.3f,%08.3f,%08.3f\n",avg_angle.phi*57.296, avg_angle.theta*57.296, avg_angle.psi*57.296);

  }


}

