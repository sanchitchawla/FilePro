// ID : 5780642 
// Name: Sanchit Chawla

#include "cachelab.h"
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


typedef struct Line Line;
typedef struct Set Set;


struct Line
{
	int valid;
	int tag;
	int bytes;
	int b;
	char* cacheme;
};

struct Set
{
	int numoflines;
	Line *lines;
	
};

struct Cache
{
	int S;
	int s;
	int E;
	int B;
	int b;
	set* sets;
};


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

		int ne = 0; int ns = 0; int nt = 0;
		int nb = 0; int tots = 0;

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

void setmem(Set **sets, int E, int b, int s){

	int ps = pow(2, s);
	int pb = pow(2, b);
	*sets = (Set *)malloc(ps * sizeof(Set));

	for (int i = 0; i < ps; i++){

		(*sets[i]).numoflines = E;
		(*sets[i]).lines = (Line*)malloc(E* sizeof(Line));

		for (int k = 0; i < E; k++){
			(*sets[i]).lines[k].valid = 0;
			(*sets[i]).lines[k].tag = 0;
			(*sets[i]).lines[k].bytes = pb;
			(*sets[i]).lines[k].b = b;
			(*sets[i]).lines[k].cacheme = (char*)malloc(pb* sizeof(char));
		}
	}

}

void freemem(Set **sets, int E, int b, int s){
	// Free Everything you malloc

	int ps = pow(2,s);
	
	for (int i = 0;i < ps; i++){
		for (int k = 0; k < E; k++){

			(*sets[i]).lines[k].valid = 0;
			(*sets[i]).lines[k].tag = 0;
			(*sets[i]).lines[k].bytes = 0;
			(*sets[i]).lines[k].b = 0;
			free((*sets[i]).lines[k].cacheme);

		}

		(*sets[i]).numoflines = 0;
		free((*sets[i]).lines);
	}
	free(*sets);
}


int main(int argc, char **argv)
{

	int op = 0;
	int s = -1;
	int E = -1;
	int b = -1;
	int h = -1;
	int v = -1;
	char* t = NULL;

	Cache cuch = (Cache)malloc(sizeof(Cache));

	while ((op = getopt(argc, argv,"hvs:E:b:t:")) != -1) {
        switch (op) {
            case 's' : s = atoi(optarg);
                break;
			case 'E' : E = atoi(optarg);
				break;
			case 'b' : b = atoi(optarg); 
				break;
			case 't' : t = optarg;
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

    else{
    	cuch.
    	setmem(cuch.sets, E, b, s);
    }

    if (v == 1){
    	trace(t);
    }




    return 0;
}
 