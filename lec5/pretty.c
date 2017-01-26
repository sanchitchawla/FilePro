#include <stdio.h>



int main(int argc, char const *argv[])
{
	char lang_name[11]; // cos string max 10 but special marker at 11 
	int count; 
	while (scanf("%s %d", lang_name, &count)>0) {
		printf("%s %d", lang_name ,count ); 
	
	}
	return 0;

}