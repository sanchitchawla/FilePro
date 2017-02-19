# include <stdio.h>
# include <stdlib.h>
# define MYPI 3.14


const double PI = 3.14;

int main(){
	
	double r  = 10;
	int y = 7;
	int x = 6;

	int* ip = &x;
	const int* cip = &x; // this reference 
						//cant be changed 

	int * const cp = &x;
	//cp = &y cant do this 

	printf("area = %f\n", MYPI*r*r);

}