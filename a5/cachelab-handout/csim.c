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
typedef struct Cache Cache;


struct Line
{
	int valid;
	long long tag;
	int lastUsed;
	char* byte;
};

struct Set
{
	Line *lines;
	
};

struct Cache
{
	int S;
	int s;
	int E;
	int B;
	int b;
	Set* sets;

	int evicts;
	int misses;
	int  hits; 
};


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

int evict(Set set, Cache cuch, int* UL){

	int numlines = cuch.E;
	int minUsedi = 0;
	int maxU = set.lines->lastUsed;
	int minU = set.lines->lastUsed;
	Line line;

	for (int i = 1; i < numlines; i++){

		line = set.lines[i];

		if (minU > line.lastUsed){
			minUsedi = i;
			minU = line.lastUsed;
		}

		if (maxU < line.lastUsed){
			maxU = line.lastUsed;
		}

	}

	UL[0] = minU;
	UL[1] = maxU;
	return minUsedi;
}

int emptyLine(Set set, Cache cuch){

	int numlines = cuch.E;
	Line line;

	for (int i = 0; i < numlines; i++){
		line = set.lines[i];

		if (line.valid == 0){
			return i;
		}
	}

	return 0;
}

void setmem(Cache** cuch, int E, int ps){

	((*cuch)->sets) = (Set *)malloc(ps * sizeof(Set));

	for (int i = 0; i < ps; i++){

		(*cuch)->sets[i].lines = (Line*)malloc(ps* sizeof(Line));

		for (int k = 0; k < E; k++){
			(*cuch)->sets[i].lines[k].lastUsed = 0;
			(*cuch)->sets[i].lines[k].valid = 0;
			(*cuch)->sets[i].lines[k].tag   = 0;

		}

	}

}

void freemem(Cache** cuch, int E, int ps){
	// Free Everything you malloc
	
	for (int i = 0;i < ps; i++){
		for (int k = 0; k < E; k++){

			(*cuch)->sets[i].lines[k].valid = 0;
			(*cuch)->sets[i].lines[k].tag   = 0;
			(*cuch)->sets[i].lines[k].lastUsed = 0;

		}

		free((*cuch)->sets[i].lines);
	}
	free((*cuch)->sets);
}

Cache* sim(Cache* cuch, unsigned long long address) {
	
	int cache_full = 1;
	int num_lines = cuch->E;
	int prev_hits = cuch->hits;
	int tag_size = (64 - (cuch->s + cuch->b));
	unsigned long long input = address >> (cuch->s + cuch->b);
	unsigned long long temp = address << (tag_size);
	unsigned long long setIndex = temp >> (tag_size + cuch->b);
	Set query_set = cuch->sets[setIndex];

	for (int i = 0; i < num_lines; i++){

		Line line = query_set.lines[i];

		//printf("valid %d tag %lld input%lld %d \n", line.valid, line.tag, input, i);

		if (line.valid){
			if (line.tag == input){
				line.lastUsed++;
				cuch->hits++;
				query_set.lines[i] = line;
			}

		}

		else if (!(line.valid) && cache_full){
				cache_full = 0;
		}

	}

	if (prev_hits == cuch->hits){
		cuch->misses++;
	}
	else{
		return cuch;
	}

	int* UL = (int*)malloc(2* sizeof(int));
	int minUsedi = evict(query_set, *cuch, UL); 

	if (cache_full){
		cuch->evicts++;
		query_set.lines[minUsedi].tag = input;	
		query_set.lines[minUsedi].lastUsed   = UL[1] + 1;

	}

	else{
		int EI = emptyLine(query_set, *cuch);
		query_set.lines[EI].tag   = input;
		query_set.lines[EI].valid = 1;
		query_set.lines[EI].lastUsed = UL[1] + 1;

	}
	free(UL);

	return cuch;

}

int main(int argc, char **argv)
{

	int op = 0;
	int h = -1;
	int v = -1;
	char* t = NULL;

	Cache* cuch = (Cache*)malloc(sizeof(Cache));

	while ((op = getopt(argc, argv,"hvs:E:b:t:")) != -1) {
        switch (op) {
            case 's' : cuch->s = atoi(optarg);
                break;
			case 'E' : cuch->E = atoi(optarg);
				break;
			case 'b' : cuch->b = atoi(optarg); 
				break;
			case 't' : t = optarg;
				break;
			case 'h' : usage();
				exit(2);
				break;
			case 'v' : v = 1;
				break;
             default: usage(); 
                 exit(EXIT_FAILURE);
        }
    }

    minput(cuch->s, cuch->E, cuch->b, t, h ,v);

    if (access(t, F_OK) == -1){
    	printf("%s: No such file or directory\n", t);
    	exit(EXIT_FAILURE);
    }

    int ps = pow(2,cuch->s);
    setmem(&(cuch), cuch->E, ps);

    FILE* read = fopen(t,"r");

    unsigned long long addr;
    unsigned int size;
    char cmd;

    cuch->hits   = 0;
    cuch->evicts = 0;
    cuch->misses = 0;
    while(!feof(read)){
    	if (fscanf(read, " %c %llx,%d", &cmd, &addr, &size) == 3){
    		switch(cmd){
    			case 'I' : 
    				break;
    			case 'L': 
    				cuch = sim(cuch, addr);
    				break;
    			case 'S' : 
    				cuch = sim(cuch, addr);
    				break;
    			case 'M' : 
    				cuch = sim(cuch, addr);
    				cuch = sim(cuch, addr);
    				break;
    			default:
    				break;
    		}
    	}

    }

    printSummary(cuch->hits, cuch->misses, cuch->evicts);
    freemem(&(cuch),cuch->E, cuch->s);
    fclose(read);

    return 0;
}