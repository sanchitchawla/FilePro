# include <stdio.h>
# include <string.h>
# include <stdlib.h>

int main(){

	int *number;
	float *tenFloats;
	char *word;

	number = (int *)malloc(10*sizeof(int)); // Size of one int
	//number = (int *)calloc(1, sizeof(int)); initialize to 0, 1 block
	//*number = 10;
	memset(number,0x77, 10*sizeof(int));

	// If you do this before malloc might give segmentation 
	// fault cos u dont have permission to access that chunk of memory
	printf("content: %d\n",*number); // Value 
	printf("location: %p\n", number); /* Location of value */
	printf("%p\n", &number); //Location of pointer

	tenFloats = (float *)malloc(10 * sizeof(float));
	tenFloats[5] = 10.0; // points to the 5th index equivalent to *

	word = (char *)malloc(5);
	strcpy(word,"wot8463956"); // That's more than 5 lmao, ,bug tho 
	free(number); // free space from malloc 
	number = NULL; // pls do this

	printf("content: %f\n",tenFloats[5]); 
	printf("location[5]: %p\n", &tenFloats[5]);
	printf("location index 0: %p\n", tenFloats);
	printf("location index 0: %p\n", &tenFloats);

}