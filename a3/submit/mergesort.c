/* Name: Sanchit Chawla 
 * ID: 5780642 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

void merge(Entry *output, Entry *L, int nL, Entry *R, int nR) {

	int k = 0;
    int i = 0;
    int j = 0;

    while(k < nL+nR){

    	if ((i < nL && (L+i)->data < (R+j)->data) || j>= nR){

    		(output+k)->data = ((L+i)->data);
    		(output+k)->name = ((L+i)->name);
    		i++;

    	}
    	else{

    		(output+k)->data = ((R+j)->data);
    		(output+k)->name = ((R+j)->name);
    		j++;

    	}
    	k++;
    }
}

void merge_sort(Entry *entries, int n) {

	if (n>1){
		Entry* temp = (Entry*)malloc(n*sizeof(Entry));

		int Rs = n / 2;
		int Ls = n - Rs;

		Entry* R = (Entry*)malloc(Rs*sizeof(Entry));
		Entry* L = (Entry*)malloc(Ls*sizeof(Entry));

		for (int i = 0; i < n; i++){

			if (i< Ls){
				(L + i)->data = (entries+i)->data;
				(L + i)->name = (entries+i)->name;
			}

			else{
				(R - Ls + i)->data = (entries+i)->data;
				(R - Ls + i)->name = (entries+i)->name;
			}

		}


		merge_sort(L,Ls);
		merge_sort(R,Rs);
		
		merge(temp,L,Ls,R,Rs);

		for (int j = 0; j < n; j++){
			(entries+j)->data = (temp+j)->data;
			(entries+j)->name = (temp+j)->name;
		}

		free(R);
		free(L);
		free(temp);

	}

	

}

/*
TEST: ./mergesort < test.in
OUTPUT:
1 lsdfjl
2 ghijk
3 ksdljf
5 abc
6 def
*/

int main(void) {
    
    int n;
    scanf("%d", &n);
    Entry* entry = (Entry*)malloc(n*sizeof(Entry));

    char* name;

    for (int i = 0; i < n; i++){

    	name = (char*)malloc(MAX_NAME_LENGTH);
    	int each;

    	scanf("%d %s", &each,name);

    	(entry+i)->data = each;
    	(entry+i)->name = name;
    }

    merge_sort(entry,n);

    for (int j = 0; j < n; j++){
    	printf("%d %s\n", ((entry+j)->data), (entry+j)->name);
    	free((entry+j)->name);
    }

    free(entry);

}
