#include <stdio.h>

void prefix_sum(int *a, int *b, int *c){

	int val_a = *a;
	int val_b = *b;
	int val_c = *c;

	int newval_b = val_a + val_b;
	int newval_c = newval_b + val_c;

	*b = newval_b;
	*c = newval_c;

}

int my_str_len(char *s){

	int i = 0;

	while (s[i] != '\0'){
		i++;
	}

	return i;

}

int main(){

	int a;
	int b;
	int c;
	int* a_ptr = &a;
	int* b_ptr = &b;
	int* c_ptr = &c;


	a = 3; b = 5; c = 10;

	printf("a=%d, b=%d, c=%d\n", a,b,c);

	prefix_sum(a_ptr,b_ptr,c_ptr);

	printf("a=%d, b=%d, c=%d\n", a,b,c);

	char *s = "smd";
	int len = my_str_len(s);

	printf("Length of string is %d\n", len );

	return 0;
}
