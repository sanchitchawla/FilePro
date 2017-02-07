# include <stdio.h>
# include <stdlib.h>
# define index(r,c) ((r*10)+c)
int main(){

	// top level array 2d array 

	int **arr;

	arr = (int **)malloc(5* sizeof(int *)); // initialize 2d array 

	for (int i = 0; i < 5; i++){
		arr[i] = (int *)malloc(10 * sizeof(int)); // initialize each array
	}

	arr[0][1] = 10;
	arr[0][5] = 20;
	arr[1][0] = 30;

	// arr[4][3] = 40;
	*(*(arr + 4) + 3) = 40;

	// free(arr);
	// arr = NULL; DONT DO THIS

	for (int i = 0; i < 5;i++){
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;

	int *arr2;
	arr2 = (int *)malloc(5*10*sizeof(int));

	// arr2[3][2] = 10;-t
	
	arr2[index[3,2]] = 10;

}