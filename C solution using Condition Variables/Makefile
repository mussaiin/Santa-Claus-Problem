CC = gcc
CFLAGS = -g -Wall -Wno-int-to-void-pointer-cast

INCLUDES = -I/usr/local/include
LFLAGS=
LIBS = -lpthread

SRCS = santaclaus.c semaphore.c

OBJS = $(SRCS:.c=.o)

.PHONY: depend clean

all: santaclaus 

santaclaus: santaclaus.o semaphore.o
	$(CC) $(CFLAGS) $(INCLUDES) -o santaclaus santaclaus.o semaphore.o $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
