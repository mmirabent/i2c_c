#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "euler.h"
#include "moving.h"

extern "C" {
  #include "registers.h"
  #include "lsm9ds1.h"
  #include "libi2c.h"
}

using namespace std;

int open_socket(char* ip);
void send_angles(int sock, Euler angle);

int main(int argc, char** argv) {
  int i2c = open_i2c(1);

  if(i2c == -1) {
    perror("Failed to initialize i2c");
    exit(1);
  }


  uint8_t addr = 0x6A;
  set_slave(i2c,addr);
  init_sensor(i2c);

  char* ip = NULL;
  if(argc > 1)
    ip = argv[1];
  int sock = open_socket(ip);

  struct ga_data gadata;
  struct m_data mdata;
  struct gam_data_float gamdata;
  Euler raw_angle;
  Euler avg_angle;


  //printf("ax,ay,az,mx,my,mz,Raw Phi, Raw Theta, Raw Psi, Filtered Phi, Filtered Theta, Filtered Psi\n");
  //printf("Raw Phi, Raw Theta, Raw Psi, Filtered Phi, Filtered Theta, Filtered Psi\n");

  while(1) {
    get_gyro_accel(i2c,&gadata);
    get_mag(i2c,&mdata);
    convert(gadata, mdata, &gamdata);
   // printf("%08.3f,%f,%f,%f,%f,%f,",gamdata.ax,gamdata.ay,gamdata.az,gamdata.mx,gamdata.my,gamdata.mz);
    raw_angle = eulercomp(gamdata.ax,gamdata.ay,gamdata.az,
                          gamdata.mx,gamdata.my,gamdata.mz);
    //printf("%08.3f,%08.3f,%08.3f,",raw_angle.phi*57.296, raw_angle.theta*57.296, raw_angle.psi*57.296);
    avg_angle = moving_avg(raw_angle);
    //printf("%08.3f,%08.3f,%08.3f\n",avg_angle.phi*57.296, avg_angle.theta*57.296, avg_angle.psi*57.296);
    send_angles(sock, avg_angle);

  }


}

void send_angles(int sock, Euler angle) {
  char message[28];
  sprintf(message, "%08.3f,%08.3f,%08.3f\n",angle.phi*57.296, angle.theta*57.296, angle.psi*57.296);

  write(sock, message, sizeof(message));
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
  memset(reinterpret_cast<char*>(&source_addr), 0, sizeof(source_addr));
  source_addr.sin_family = AF_INET;
  source_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  source_addr.sin_port = htons(0);

  // Name the socket
  if(bind(sock, reinterpret_cast<struct sockaddr*>(&source_addr), sizeof(source_addr)) < 0) {
    perror("Failed to bind socket");
    exit(5);
  }


  memset(reinterpret_cast<char*>(&dest_addr), 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(port);
  if(!ip) {
    dest_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  } else {
    struct in_addr dest_in_addr;
    inet_aton(ip, &dest_in_addr);
    dest_addr.sin_addr = dest_in_addr;
  }

  connect(sock, reinterpret_cast<struct sockaddr*>(&dest_addr), sizeof(dest_addr));
  return sock;
}

