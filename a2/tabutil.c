# include <stdio.h>
# include <string.h>
# include <ctype.h>

int main(int argc, char const *argv[])
{
	
	if (strcmp(argv[1], "-d") ==0){
		printf("Do -d");
	}

	if (strcmp(argv[1], "-e") ==0){
		printf("Do -e");
	}
	return 0;
}