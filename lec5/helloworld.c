#include <stdio.h>

int main()
{	int a,b;

	printf("Hello, World!\n");
	printf("Name %s, Number %d, Float %15.3f\n", "FilePro", 3, 2.7184 );
	
	printf("a: ");
	scanf("%d", &a);
	printf("b: " );
	scanf("%d", &b);

	printf("a + b: %d\n",a+b );

	return 0; /* hwat is this m8 (also if we use -ansi 
	we can use "//" for comments )*/ 

}