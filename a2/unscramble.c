# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>


int cmpstringp(const void*  p1, const void* p2)
{

   return *(char*)p1 -  *(char*)p2;
}


void anagram(char* w){
	qsort(w, strlen(w), sizeof(char), cmpstringp);
}

void go(FILE* d, FILE* j, char* jum,char* dic , char* dic2 ){

	char* jumble = fgets(jum, 20, j); 
	char* dicline= fgets(dic, 30, d);

	int jlen, dlen;
	
	 
	while (jumble!=NULL){
		jlen = strlen(jumble) -1;
		anagram(jumble);
		printf("%s:",jumble );
		if (jumble[jlen] == '\n'){
			jumble[jlen] = '\0';
		}
		int count = 0;
		while (dicline!=NULL){
			dlen = strlen(dicline) -1;
			anagram(dicline);
			strcpy(dic2, dic);
			if (strcmp(dicline, jumble)){
				printf("%s ", dic);
				count++;

			}
			dicline= fgets(dic, 30, d);

		}
		if (count==0){
			printf("NO MATCHES\n");
		}
		else{
			printf("\n");
			
		}
		jumble = fgets(jum, 20, j);
	}

}


int main(int argc, char *argv[])
{

	if (argc!=3){
		return 1;
	}

	char *dname = argv[1];
	char *jname = argv[2];

	FILE *d = fopen(dname,"r");
	FILE *j = fopen(jname,"r");

	if (d == NULL || j == NULL) {
		printf("ERROR\n");
		exit(EXIT_FAILURE);
	}


	char jum[21]; 
	char dic[31];
	char dic2[31];

	go(d,j,jum,dic, dic2); /* Array passes pointer to another function */


	return 0;

}