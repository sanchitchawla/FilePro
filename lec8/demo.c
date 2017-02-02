# include <stdio.h>


int main(int argc, char const *argv[]){

	FILE *fin = fopen(argv[1],"r");

	int running_sum = 0;
	int line_count = 0;

	while (!feof(fin)){
		int data_point;
		fscanf(fin,"%d", &data_point);//scan and write to address of datapoint 
		running_sum += data_point;
		line_count++;
	}

	fclose(fin);

	FILE *fin2 = fopen(argv[2], "w");


	fprintf(fin2,"Average is %f\n", (double) running_sum / line_count);
	fclose(fin2);

	return 0;
}