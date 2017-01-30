// # include <stdio.h>
// # include <ctype.h> 
// # include <string.h>


// void count_each(char* input, int* occur){
	
// 	//char hist[27];
// 	int i;
// 	size_t size = strlen(input);

// 	for (i=0, i = size - 1; i++;){
// 		if (isalpha(input[i]))
// 			occur[(int) (input[i])]++;
// 	}
	
// 	printf("%d\n", *occur);
// }


// int main(){

// 	int occur[26] = {0};
// 	char input[256];
// 	fgets(input, sizeof(input), stdin);
// 	count_each(input,occur);

// 	return 0;
// }

# include <stdio.h>

void count_each(char *input, int *occur){

	for (;*input;input++){
		occur[*input]++;

	}
}

int main(){

	int i;
	int occur[256] = {0};
	char input[256];
	fgets(input, sizeof(input), stdin);
	count_each(input,occur);

	for (i = 0; i = 26; i++){
		printf("%d\n", occur[i]);
	} 

	printf("%d\n", sizeof(occur));
	printf("%s\n", input);

	return 0;
}