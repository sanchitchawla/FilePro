// ID : 5780642 
// Name: Sanchit Chawla

#include "cachelab.h"
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

struct Line
{
	int valid;
	int tag;
	int bytes:
	int b;
	char* cacheme;
};

struct Set
{
	int numoflines;
	Line *lines;
	
};

void strcp(char **t, char *optarg){
	*t = malloc(sizeof(char) * strlen(optarg) + 1); 
}

void trace(char* file){

	FILE* f = fopen(file, "r");
	char lines[256];

	while (fgets(lines, sizeof(lines), f)){
		printf("%s\n", lines);
	}

	fclose(f);
}

void usage(){
	printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n");
	printf("Options:\n");
	printf("  %-12s %s\n", "-h", "Print this help message.");
	printf("  %-12s %s\n", "-v", "Optional verbose flag.");
	printf("  %-12s %s\n", "-s <num>", "Number of set index bits.");
	printf("  %-12s %s\n", "-E <num>", "Number of lines per set.");
	printf("  %-12s %s\n", "-b <num>", "Number of block offset bits.");
	printf("  %-12s %s\n", "-t <file>", "Trace file.\n");
	printf("Examples:\n");
	printf("  %s\n", "linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace");
	printf("  %s\n", "linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace");
}

void minput(int s, int E, int b, char *t, int h, int v){

	if (h == 1){
		usage();
	}

	if (s == -1 || b == -1 || E == -1 || t == NULL){

		int ne, ns, nt, nb, tots = 0;

		if (s == -1){
			tots++;
			ns = 1;
		}
		if (b == -1){
			tots++;
			nb = 1;
		}
		if (t!=NULL){
			free(t);
		}
		else{
			tots++;
			nt = 1;
		}

		if (tots > 1){
			printf("Missing required command line argument\n");
		}
		else if(tots == 1){
			printf("%s\n", t);
			printf("Options require an argument --");
			if (ns == 1){
				printf("\'%c\'", 's');
			}
			else if (ne == 1){
				printf("\'%c\'", 'E');
			}
			else if (nb == 1){
				printf("\'%c\'", 'b');
			}
			else if (nt == 1){
				printf("\'%c\'", 't');
			}
		}

		if (h != 1){
			usage();
		}
	exit(EXIT_FAILURE);

	}


}

int main()
{

	int s, E, b, h, v, op;
	char *t;
	op = 0;
	s = -1;
	E = -1;
	b = -1;
	h = -1;
	v = -1;
	t = NULL;

	while ((op = getopt(argc, argv,"hvs:E:b:t:")) != -1) {
        switch (op) {
            case 's' : s = atoi(optarg);
                break;
			case 'E' : E = atoi(optarg);
				break;
			case 'b' : b = atoi(optarg); 
				break;
			case 't' : strcp(&t,optarg);
				break;
			case 'h' : h = 1;
				break;
			case 'v' : v = 1;
				break;
             default: usage(); 
                 exit(EXIT_FAILURE);
        }
    }

    minput(s, E, b, t, h ,v);

    if (access(t, F_OK) == -1){
    	printf("%s: No such file or directory\n", t);
    	exit(EXIT_FAILURE);
    }

    if (v == 1){
    	trace(t);
    }

    return 0;
}
 