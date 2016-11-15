CC=clang
CXX=clang++
CXXFLAGS=-g -std=gnu++11 -Weverything -pedantic
CFLAGS=-g -std=gnu11 -Weverything -pedantic 

main : main.cpp moving.o euler.o moving.o lsm9ds1.o libi2c.o

i2c : i2c.c libi2c.o lsm9ds1.o

libi2c.o : libi2c.c libi2c.h

lsm9ds1.o : lsm9ds1.c lsm9ds1.h

euler.o : euler.cpp euler.h

moving.o : moving.cpp moving.h

clean :
	rm -rf *.o i2c main

remake : clean i2c

.PHONY : clean remake

