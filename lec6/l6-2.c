#include <stdio.h>

int main(){

	int numbers[4] = {3,1,4,5};
	int* int_ptr = numbers;
	double* db_ptr = 0x0;

	printf("%p %p\n", numbers, &numbers); // & in array still means the address
	printf("%d %d\n",numbers[0], *int_ptr);

	// Difference between memory addresses down is 4 because int size is 4
	printf("%p %p %p\n", numbers, &numbers[1], &numbers[2]); 

	// Gives warning cos its not actually a pointer, right way to do is %d
	printf("%p %p %p\n", int_ptr[0], int_ptr[1], int_ptr[2]); 
	printf("%d %d %d\n", int_ptr[0], int_ptr[1], int_ptr[2]);

	printf("%p\n",int_ptr);
	printf("%p\n",int_ptr+1);
	printf("%p\n",int_ptr+2);
	printf("%p\n",int_ptr+ 2048);

	printf("%p\n",db_ptr);
	printf("%p\n",db_ptr+1);
	printf("%p\n",db_ptr+2);
	printf("%p\n",db_ptr+3);
	printf("%p\n",db_ptr+4);
	printf("%p\n",db_ptr+5);
	printf("%p\n",db_ptr+6);
	printf("%p\n",db_ptr+32);

	return 0;
}