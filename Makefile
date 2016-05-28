CC=clang
CFLAGS=-g -O -std=gnu11 -Weverything -pedantic -I/usr/local/include
LDFLAGS=-L/use/local/libs -lwiringPi

i2c : i2c.c 

