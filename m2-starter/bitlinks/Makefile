CC=gcc
CFLAGS=-Wall -W -pedantic

all: driver

bitlinks.o: bitlinks.c
	$(CC) $(CFLAGS) -c -o $@ $<

driver: bitlinks.o bitdriver.c 
	$(CC) $(CFLAGS) -o $@ $^

memcheck: driver
	-valgrind --tool=memcheck --leak-check=yes ./driver

clean:
	rm bitlinks.o driver
