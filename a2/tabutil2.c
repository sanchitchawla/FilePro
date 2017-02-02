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

void spaces_tab(){
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

int main(int argc, char const *argv[]){

    int n = atoi(argv[2]);
    
    if (strcmp(argv[1], "-d") ==0){
        tab_spaces(n);
    }
    else if (strcmp(argv[1], "-e") ==0){
        printf("Do -e");
    }

    return 0;
}