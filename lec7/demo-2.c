# include <stdio.h>


int main(){


	/* Arrays vs Pointers are not really the same */ 

	int numbers[10];
	int numbers2[10];

	int* int_ptr;

	int_ptr = numbers;
	numbers = numbers2; // I hate you!!
	

}
