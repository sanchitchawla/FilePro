# include <stdio.h>
# include <stdlib.h>
# include <string.h>



void hist(FILE* f, char* w, char* ans){

	while (fgets(w, 15, f)!=NULL){

		int len = strlen(w)-1 ;
		ans[len]++;

	}
}


int main(int argc, char  *argv[])
{
	if (argc!=2){
		return 1;
	}


	char* name = argv[1];

	FILE* f = fopen(name,"r");

	char w[16]; 

	char ans[15];

	hist(f,w, ans);

	int count =0;


	for (int i = 0; i < 15; i++){
		if (ans[i]!=0){
			count++;
			printf("Rank %d: length %d sees %d word(s)\n", count,i,ans[i]);
		}
		
	}

	return 0;
}

