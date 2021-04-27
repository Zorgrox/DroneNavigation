# CSCI3081 lab01 makefile

CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: main.o
	$(CC) $(LFLAGS) main.o -o lab02.out

main.o : main.cc
	$(CC) $(CFLAGS) main.cc

clean:
	\rm *.o *.*~ lab02.out
