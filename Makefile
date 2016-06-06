CC=clang
CFLAGS=-g -O -std=gnu11 -Weverything -pedantic -I/usr/local/include
LDFLAGS=-L/use/local/libs -lwiringPi

i2c : i2c.c libi2c.o lsm9ds1.o

libi2c.o : libi2c.c libi2c.h

lsm9ds1.o : lsm9ds1.c lsm9ds1.h

