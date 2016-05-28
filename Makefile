CC=clang
CFLAGS=-g -O -std=gnu11 -Weverything -pedantic -I/usr/local/include
LDFLAGS=-L/use/local/libs -lwiringPi

i2c : i2c.c libi2c.o

libi2c.o : libi2c.c libi2c.h

