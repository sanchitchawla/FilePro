CC=gcc
CFLAGS=-ansi -Wall -W -pedantic -g

SRC = $(wildcard *.c) demo.c
BIN = $(patsubst %.c,%,$(SRC))

all: $(BIN)

demo1: demo1.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(BIN)

.PHONY: all clean
