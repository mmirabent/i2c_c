CXX=g++
CXXFLAGS=-g -O -std=c++11 -Wall -pedantic -I/usr/local/include
LDFLAGS=-L/use/local/libs -lwiringPi

i2c : i2c.cpp libi2c.o

libi2c.o : libi2c.cpp

