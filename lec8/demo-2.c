# include <stdio.h>
# include <string.h>

int main(){

	char* name = "George Washington";

	char* cptr = name;

	// int n = strlen(name);

	// for (int i = 0; i < n; i++){
	// 	printf("%c\n", name[i]);
	// }

	while (*cptr){ // could also use NULL or \0 or 0
		printf("%c\n", *cptr);
		cptr++;
	}
}