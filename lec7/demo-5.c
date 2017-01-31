# include <stdio.h>

void fun(int a){
	printf("Value of a is %d\n",a );
}

int add(int a, int b){return a+b;}

int sub(int a, int b){return a-b;}

int mult(int a, int b){return a*b;}

int main(){

	void (*fun_ptr)(int) = &fun;

	(*fun_ptr)(10); // run the function fun with number 10 

	// int (*add_ptr)(int, int) = &add;

	// int (*mult_ptr)(int, int) = &mult;

	// int (*sub_ptr)(int, int) = &sub;

	int (*fun_ptr_arr[])(int, int) = {&add, &sub, &mult};
	char* names[] = {"add", "subtract", "multiply"};

	int a = 5, b = 10;

	for (int i = 0; i < 3; i++){
		printf("%s: %d\n",names[i],(*fun_ptr_arr[i])(a,b));
	}

	printf("%ld\n", sizeof(names));
} 