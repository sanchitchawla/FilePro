# include <stdio.h>

# define mult(x,y) ((x)*(y)) // can't use space between mult and (x,y)
# define MAX_LEN 40


int main(){

	int c = mult(4,7);
	printf("c = %d\n", c);

	int a[MAX_LEN];

	return 0;
}