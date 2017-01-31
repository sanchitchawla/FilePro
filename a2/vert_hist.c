
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void count_each( int* occur){
	
	char input = getchar();

	while (input != EOF){

		if (isalpha(input)){
			input= tolower(input);
			occur[(input - 'a')]++;
		}
		input = getchar();
	}


}

void draw_hist(int* occur){

	int max = 0;

	for (int i = 0; i < 26; i++){

		if (occur[i] > max){
			max = occur[i];
		}
	}

	printf("\n");

	for (int j = max; j > 0; j--){
		for (int k = 0; k < 26; k++){
			if (occur[k] < j){
				printf(" ");
			}
			else{
				printf("*");
			}
		}
		printf("\n");

	}
	printf("abcdefghijklmnopqrstuvwxyz\n");

}

int main(){

	int occur[26] = {0};
	count_each(occur);
	draw_hist(occur);

	return 0;
}