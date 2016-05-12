CXX=g++
CXXFLAGS=-g -O -std=c++11 -Wall -pedantic

i2c : i2c.cpp libi2c.o

libi2c.o : libi2c.cpp

