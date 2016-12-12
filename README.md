# Magic Motion Sensor Watch Software

## Overview

The software is comprised of the I2C library, the LSM9DS1 module, the Filter and
the main program file that ties these things together.

## I2C Library

The I2C Library is comprised of the libi2c.h and libi2c.c files. These files
depend on the linux kernel headers being installed, as well as the linux i2c
driver being installed. Note that for the MMSW, these are preinstalled as part
of the custom image for the PiTFT touchscreen. In order to use the library, you
must first open the I2C bus with the `open_i2c(int bus)` function. The function
will return a file descriptor for the opened I2C Bus. This will be passed to the
other functions in the library. When you are done using the bus, you should
close the descriptor with `close(int fd)`. The bus argument is used to select an
I2C Bus. Note that on the raspberry pi, there are two I2C busses, but only the
second bus, bus 1, is used for the sensor. The other is reserved.

Once the bus is opened, the `set_slave(int fd, uint8_t addr)` function can be
used to set the slave to talk to. Once a slave address is set, you can use
`write_bytes()` or `read_bytes()` to write or read multiple bytes. The
`write_bytes()` function performs a "burst mode" write. The `read_bytes()`
function performs a "burst mode" read.

## LSM9DS1 Module

This library consists of the lsm9ds1.c and lsm9ds1.h files, as well as the
registers.h file. The registers.h file contains a list of register addresses for
interesting and useful registers on the LSM9DS1. The lsm9ds1.c and .h files
define structures and methods for setting up the sensor for data collection and
actually collecting data. An example of how to use this module can be seen in
i2c.c or main.cpp. The important thing to note here is that gyroscope and
accelerometer data are collected with one function call and magnetometer data
with another. This is due to the magnetometer being at a different I2C address
and thus needing a seperate I2C read command. If the magnetometer data is not
needed, you can simply not call the `get_mag()` function. The `convert()`
function converts the raw 16 bit sign integer data from the sensor to floating
point data. Gyroscope data is read in degrees per second, accelerometer data is
in g's and magnetometer data is in milligauss(I think). The conversion is done
by multiplying the raw integer by the full scale value of each sensor and then dividing by
2^15 - 1. This has the effect of converting to the actual measurement of each
sensor. The full scale values are defined in lsm9ds1.c and are set upon
initialization of the sensor in the `init_sensor()` routine. Note that you need
only change the variables at the top of the function in order to change the
desired full scale value and output data rate. These values are from the LSM9DS1
datasheet, and are the actual bits set in the `CTRL_REG1_G`, `CTRL_REG6_XL`,
`CTRL_REG1_M`, and `CTRL_REG2_M` registers. More info in the LSM9DS1 datasheet. 

## i2c.c and main.cpp

Included are two programs that can be used to extract data from the sensor. The
`i2c.c` program was written first and used for most of the development of the
sensor module and i2c library. The program runs an infinite loop, displaying
raw, unfiltered data from all nine axes in the terminal. The data is comma
sepperated and suitable for generating a comma separated values file. The first
line of output contains a header for easy importing into spreadsheet software
such as MS Excel, or for importing into Matlab or Python for further processing.
This is the program used to generate the raw data that the filter design team
used to design the kalman and moving average filter. Running the program is as
simple as compiling it with `make i2c` and then running it with either `./i2c`
to display to the terminal, or `./i2c > data.csv` which redirects this output to
a file called `data.csv`. To quit the program, simply hit Ctrl-C on the
keyboard. Note that the last line will most likely be truncated because of
killing the program with Ctrl-C.

The `main.cpp` file is the program used during the demonstration itself, and it
is a bit more sofisticated. It can be compiled by running `make` with out any
arguments, and run with `./main`. It takes a single command line argument in the
form of an IPv4 address in quad-dotted decimal format, for example,
`192.168.0.1`. This IP address is where the program will send the filtered data.
If no IP address is supplied, the program uses the loopback address `127.0.0.1`
as a default. Filtered data comes in the form of an Euler angle, comprised of
three individual angles, pitch, roll, and yaw. In addition, unfiltered
acelerometer and gyroscope data is sent as well. The data is sent as UDP packets
to UDP Port 9001. The packets contain a string representation of the Euler angle
and the individual raw measurements of the accellerometer and gyroscope. This
data can be seen simply by pointing the program to a computer running this
netcat command `nc -lu 9001`. This command sets netcat to listen for data coming
in on UDP port 9001. For the purposes of the demonstration, we had Alain, a
student in the OpenHID lab add some code to an Unreal powered 3d game that would
listen to this port, and we pointed the software on the watch at the computer
running the game. The output format can easily be changed, as the output is
split into it's own function, the `send_angles()` function.

filtering is handled by two files, the `euler.cpp` file and the `moving.cpp` file.
These define functions for converting from raw measurements to euler angles, and
for filtering said euler angles. At this time, only the moving average filter is
implemented, but it should be a relatively simply task to integrate any other
filter. One would just have to add another `.cpp` and `.h` file for the new filter,
and change the `main` function in `main.cpp`. Specifically, the line where
`avg_angle - moving_avg(raw_angle)` would need to be changed to call the desired
filtering funciton.

