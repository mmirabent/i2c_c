
#include "registers.h"
#include "lsm9ds1.h"
#include "libi2c.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int open_socket(char* ip);

int main(int argc, char** argv) {

  char* ip = argc > 1 ? argv[1] : NULL;

  // Setup the GPIO interface
  int i2c = open_i2c(1);

  if(i2c == -1) // Something terrible has happened
  {
    perror("Failed to initialize i2c");
    return -1;
  }

  // This is the 7 bit slave address we want to write to.
  // Range is 0x03 to 0x77
  // 0x6A is the slave address for the accelerometer and gyro on an LSM9DS1
  // with the SA0 line pulled low
  uint8_t addr = 0x6A;
  set_slave(i2c,addr);

  // See lsm9ds1.c for exact values set to control registers
  init_sensor(i2c);

  struct ga_data gadata;
  struct m_data mdata;
  struct gam_data_float gamdata;

  printf("gyro_x,gyro_y,gyro_z,accel_x,accel_y,accel_z,mag_x,mag_y,mag_z\n");
  
  int sock = open_socket(ip);
  char* message;

  while (1) {

    get_gyro_accel(i2c,&gadata);
    get_mag(i2c,&mdata);
    convert(gadata, mdata, &gamdata);
    sprintf("%f,%f,%f,%f,%f,%f,%f,%f,%f\n",gamdata.gx,gamdata.gy,gamdata.gz,gamdata.ax,gamdata.ay,gamdata.az,gamdata.mx,gamdata.my,gamdata.mz);
  }
}

int open_socket(char* ip) {
  struct sockaddr_in source_addr, dest_addr;
  uint16_t port = 9001;
  int sock;

  printf("Using port %d\n", port);

  // Get a socket
  if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Cannot create socket");
    exit(4);
  }

  // Set the contents of the struct to zero
  memset((char*)&source_addr, 0, sizeof(source_addr));
  source_addr.sin_family = AF_INET;
  source_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  source_addr.sin_port = htons(0);

  // Name the socket
  if(bind(sock, (struct sockaddr*)&source_addr, sizeof(source_addr)) < 0) {
    perror("Failed to bind socket");
    exit(5);
  }

  struct in_addr dest_in_addr;
  if(!ip)
    ip = "127.0.0.1";
  inet_aton(ip, &dest_in_addr);


  memset((char*)&dest_addr, 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_addr.s_addr = dest_in_addr;
  dest_addr.sin_port = htons(port);

  connect(sock, (struct sockaddr*)&dest_addr, sizeof(dest_addr));

  return sock;
}
