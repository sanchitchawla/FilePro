# include <stdio.h>

int main(){
	int mat[4][4];

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			printf(" %p ", &mat[i][j]);
		}
		printf("\n");
	}
	// contiguous chunk for efficiency 
	return 0;
}