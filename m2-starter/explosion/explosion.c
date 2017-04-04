/*
 * NAME: Sanchit Chawla
 * ID: 5780642
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char *explode(char * s, int k) {

	int n = strlen(s);

	char *fin = (char *)malloc((n*k));

	int count = 0;

	for (int i = 0; i < n; i++){

	 for (int j = 0; j < k; j++){
	 	fin[count] = s[i];
	 	count++;
	 }

	}
	return fin;
}