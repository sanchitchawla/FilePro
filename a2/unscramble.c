# include <stdio.h>
# include <stdlib.h>
# include <string.h>


int cmpstringp(const void*  p1, const void* p2){

   return *(char*)p1 - *(char*)p2;
}



void go(FILE* d, FILE* j, char* jum,char* dic , char* dic2 ){

	int jlen, dlen;
	 
	while (fgets(jum, 20, j)!=NULL){

		jlen = strlen(jum) - 1;

		if (jum[jlen] == '\n'){
			jum[jlen] = '\0';
		}
		else{
			jlen++;

		}

		printf("%s:",jum);
		qsort(jum, strlen(jum), sizeof(char), cmpstringp);
		int count = 0;

		while (fgets(dic, 30, d)!=NULL){
			dlen = strlen(dic) - 1;

			if (dic[dlen] == '\n'){
				dic[dlen] = '\0';
			}
			else{
				dlen++;
			}



			if (dlen==jlen){
				strcpy(dic2, dic);
				qsort(dic, strlen(dic), sizeof(char), cmpstringp);

				if (strcmp(dic, jum)==0){
					printf(" %s", dic2);
					count++;

				}

			}

			

			if (dic==NULL){
				break;
			}
			
		}

		if (count==0){
			printf(" NO MATCHES\n");
		}

		else{
			printf("\n");
			
		}

		rewind(d);
	}

	fclose(d);
	fclose(j);

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