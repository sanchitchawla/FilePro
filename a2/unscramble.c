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

void go(FILE* d, FILE* j, char* jum,char* dic, char* dic2 ){


	char jumble = fgets(jum, strlen(jum), d);
	char dicline    = fgets(dic, strlen(dic), j);
	//printf("%s : %s",*jumble, *dic);

	while (jumble!='\0'){
		while (dicline!='\0'){
			if (qsort(jumble)==qsort(dicline)){
				printf("%s: %s \n",jumble, dic);
			}

		}
	}


}


int main(int argc, char const *argv[])
{

	if (argc!=3){
		return 1;
	}

	char *dname = argv[1];
	char *jname = argv[2];

	FILE *d = fopen(dname,"r");
	FILE *j = fopen(jname,"r");

	char jum[21];
	char dic[31];
	char dic2[31];

	go(d,j,jum,dic, dic2); /* Array passes pointer to another function */


	return 0;

}