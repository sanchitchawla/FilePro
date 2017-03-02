all: disasTest

disasTest: disas
	gcc disas.o disasTest.c -o disasTest
disas:
	gcc disas.c -c

clean:
	rm disas.o disasTest