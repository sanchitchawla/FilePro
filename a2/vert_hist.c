# include <stdio.h>
# include <ctype.h> 
# include <string.h>

// int* count_each(char *input){

// 	int* occur[256] = {0};
// 	int i;
// 	size_t size = strlen(input);

// 	for (i=0, i = size - 1; i++;){
// 		if (isalpha(input[i]))
// 			occur[(int) (input[i])]++;
// 	}

// 	return occur;

// }

void count_each(char* input, int* occur){
	
	//char hist[27];
	int i;
	size_t size = strlen(input);

	for (i=0, i = size - 1; i++;){
		if (isalpha(input[i]))
			occur[(int) (input[i])]++;
	}
	printf("%d\n", *occur);
}

int main(){

	int occur[26] = {0};
	char input[256];
	fgets(input, sizeof(input), stdin);
	count_each(input,occur);

	return 0;


}