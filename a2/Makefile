# Makefile by Peter Son Struschka
CC=gcc
CFLAGS=-ansi -Wall -W -pedantic

all: vert_hist tabutil life unscramble

vert_hist:
	$(CC) $(CFLAGS) -o vert_hist vert_hist.c

tabutil:
	$(CC) $(CFLAGS) -o tabutil tabutil.c

life:
	$(CC) -Wall -W -pedantic -o life life_engine.c life_driver.c

unscramble:
	$(CC) -Wall -W -pedantic -g -o unscramble unscramble.c

clean:
	$(RM) vert_hist tabutil life unscramble

.PHONY: all vert_hist tabutil life unscramble clean
