all: disasTest

disasTest: disas.o disasTest.c
	gcc disas.o disasTest.c -o disasTest

disas.o: disas.c
	gcc disas.c -c

clean:
	rm disas.o disasTest