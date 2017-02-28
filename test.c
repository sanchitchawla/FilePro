# include <stdio.h>


void print_len(int a[]){
	printf("%d\n", sizeof(a)/sizeof(int));
}

int main(){
	int x[] = {1,2,4,8,16,32};
	print_len(x);
}