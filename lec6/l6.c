#include <stdio.h>



void swap(int *x, int *y){

	int temp = *x;
	*x =  *y;
	*y = temp;
	 
}

int main(){

	// C is pass by value
	int number; // an int 
	int* int_ptr; // a pointer to an int 

	int_ptr = &number; // set int_ptr to point to value of value of number
	number = 5;
	printf("%d %d\n",number, *int_ptr );

	*int_ptr = 6;  // if remove * will get segmentation error
	printf("%d %d\n",number, *int_ptr ); 

	number = 7;
	printf("%d %d\n",number, *int_ptr );

	int a = 3;
	int b = 5;

	printf("a=%d, b=%d\n", a,b);

	swap(&a,&b);
	printf("a=%d, b=%d\n", a,b);

	return 0;
}