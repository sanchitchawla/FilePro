# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>


void tab_spaces(int n) {
	char in = getchar();
	int i=0;
    while (in!= EOF) {
        if (in == '\t') {
            while (i < n) {
                putchar(' ');
                i++;
            }
            i = 0;
        } else {
            putchar(in);
        }
        in = getchar();
    }

}

void spaces_tab(int n){
	char in = getchar();
	int i=0;

    while (in!= EOF) {
        if (in == ' ') {
            i++; 
        } 
        else if (i!=0 && in!=' '){
            while (i!=0){

                putchar(' ');
                i--;
            }
            putchar(in);
        }
        else {
            i=0;
            putchar(in); 
        }

        if (i==n){
            putchar('\t');
            i=0;
        }
        in = getchar();
    }
	
}

int main(int argc, char const *argv[]){
    int n;

    if (argc!=3){
        return 1;
    }

	n = atoi(argv[2]);
	
	if (strcmp(argv[1], "-d") ==0){
		tab_spaces(n);
	}
	else if (strcmp(argv[1], "-e") ==0){
        spaces_tab(n);
	}

	return 0;
}