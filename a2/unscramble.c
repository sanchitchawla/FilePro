# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>
int cmpstringp(const void *p1, const void *p2)
{

   return strcmp(* (char * const *) p1, * (char * const *) p2);
}


void anagram(char* w){
	qsort(w, strlen(w), sizeof(char*), cmpstringp);
}


int main(int argc, char const *argv[])
{
	if (argc!=3){
		return 1;
	}


	return 0;
}