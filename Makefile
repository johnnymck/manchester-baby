CC=g++ -std=gnu++0x
CFLAGS=-Wall -c

all:
	$(CC) baby.cpp baby.hpp -o baby
