#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    // file holds the file handle for the i2c device
    int file;
    
    // Adapter number, in our case, it's always 1
    int adapter_nr = 1;

    // Holds the filename, we fill this with snprintf
    char filename[20];
    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);

    // Call the open syscall on the /dev/i2c-1 file with the O_RDWR mode
    file = open(filename, O_RDWR);

    // If that didn't work, exit
    if(file < 0) {
        perror("Couldn't open i2c device");
        exit(1);
    }

    // This is the 7 bit slave address we want to write to.
    // Range is 0x03 to 0x77
    // 0x6A is the slave address for the accelerometer and gyro on an LSM9DS1
    // with the SA0 line pulled low
    int addr = 0x6A;

    // This ioctl sets the slave address, which makes writing subsequent
    // commands to the slave easier If that didn't work, the ioctl returns a
    // negative number and we exit
    if(ioctl(file, I2C_SLAVE,addr) < 0) {
        perror("Could not set slave device");
        exit(2);
    }

    // 0x10 is the gyroscope control register. Setting this register will turn
    // on both the gyro and accelerometer
    __u8 reg = 0x10;
    char buf[10];

    buf[0] = reg;
    buf[1] = 1<<5; // The value turns on the slowest ODR possible

    if(write(file,buf,2) != 2 ) // Write the control register
    {
        // write failed
        perror("Write failed");
    }

    // This loop continually reads the high byte of the accelerometer output
    // register
    while(1)
    {
        buf[0] = 0x28; // X axis acellerometer high byte
        if(write(file, buf, 1) != 1) { // Tell the which register to read
            // Read failed
            perror("Write  failed");
        }
        if(read(file,buf,1) != 1) { // Read the register
            perror("Read failed");
        }
        else {
            printf("0x%X\n",buf[0]); // Print the register
        }
        usleep(50*1000); // sleep for 50 ms
    }
}

