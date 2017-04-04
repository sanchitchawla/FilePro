all: driver

explosion: explosion.c
	gcc -Wall -pedantic -O -c explosion.c

driver: explosion driver.c
	gcc -Wall -pedantic -o driver driver.c explosion.o

memcheck: driver
	-valgrind --tool=memcheck --leak-check=yes ./driver

clean:
	rm explosion.o driver
