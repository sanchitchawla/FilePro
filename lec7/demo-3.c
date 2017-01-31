# include <stdio.h>

int factorial(int n){

	int ans = 1;
	for (int i = 1;i <= n;i++){
		ans*=i;
	}
	return ans;
}

int main(){
	int n;
	scanf("%d\n", &n); // write to address
	int nfac = factorial(n);
	printf("factorial of %d = %d\n",n, nfac);
}