CC = gcc
CFLAGS = -g -Wall
COMP_LIBS = -lm

all: $(patsubst %.c, %.out, $(wildcard *.c))

%.out: %.c Makefile
	$(CC) $(CFLAGS) $< -o $@ $(COMP_LIBS)

clean:
	rm -f *.out

