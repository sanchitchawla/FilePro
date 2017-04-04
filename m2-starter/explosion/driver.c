#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "explosion.h"

#define Ntest 3
#define L 80

int main(int argc, char **argv) {
    char testcases[Ntest][L];
    char solutions[Ntest][L];

    strcpy(testcases[0], "hello");
    strcpy(solutions[0], "hello");

    strcpy(testcases[1], "world!");
    strcpy(solutions[1], "wwoorrlldd!!");

    strcpy(testcases[2], "1234567890");
    strcpy(solutions[2], "111222333444555666777888999000");

    char *s;
    for (int i=0;i<Ntest;i++) {
      printf("Checking case#%d: explode(%s,%d)\n", i, testcases[i],i+1);
        s = explode(testcases[i], i+1);
        printf("Your output: %s\n", s);
        printf("Expected output: %s\n", solutions[i]);
        assert(strcmp(s, solutions[i]) == 0);
        free(s);
    }

    return 0;
}
