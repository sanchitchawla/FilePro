# include <stdio.h>

/* About pointers */

int main(){

	/* Size would be 8 bytes cos it holds 2 ints (each 4) */
	unsigned int a[2] = {0x12345678, 0xabcdef01};

	unsigned char *x = (unsigned char *)&a; /* only the a[0] */ 
	printf("start of a : %p\n", &a);

	printf("locations of a[0], a[1] %p %p\n",&a[0],&a[1]);
	printf("locations of a, a+1 %p %p\n",a,a+1);

	/* & means location of */ 
	printf("locations of x, x+1, x+2 %p %p %p\n", x, x+1, x+2);
	printf("locations of x[0], x[1], x[2] %p %p %p\n", &x[0], &x[1], &x[2]);

	printf("value of a %x\n",a[0] );

	printf("values of x[0], x[1], x[2], x[3] %x, %x , %x, %x\n", 
	x[0], x[1], x[2], x[3]); /* prints out in reverse order cos Little endian*/


	unsigned char b[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0x1a, 0xbc, 0xde};
	unsigned int *y = (unsigned int *) &b; /* so just b[0] */

	printf("start of b: %p\n", &b);
	printf("locations of b[0] --- b[7]: \n");
	for (int i = 0; i < 8; i++){
		printf("%p\n", &b[i]);
	}

	/* it's 4 apart cos its int (size 4) */
	printf("locations of y[0], y[1]: %p, %p\n", &y[0], &y[1]); 
	printf("value of y[0], y[1]: %x, %x\n", y[0], y[1]);




}