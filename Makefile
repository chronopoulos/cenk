CC = gcc
CFLAGS = -Wall -O2 -g
LDFLAGS = -ljack -lm

SRCS += main.c
SRCS += session.c
SRCS += sinus.c
SRCS += bong.c
SRCS += common.c

all:
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o cenk

clean:
	rm cenk
