CC = gcc
CFLAGS = -Wall -O2 -g
LDFLAGS = -ljack -lm

SRCS += main.c
SRCS += sinus.c
SRCS += session.c

all:
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o cenk

clean:
	rm cenk
