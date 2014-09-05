/*
 * new_ui.c
 *
 *  Created on: 2.7.2014
 *      Author: sobih
 */
#include "new_ui.h"

void print_new_choices()
{
	printf("Welcome to the Glfbabot-BWT program!\n");
	printf("Operations:\n");
	printf("Print K-mers count: 1 Kmer_Length FILE_NAME\n");
	printf("Kmer Kernel: 2 Kmer_Length FILE_NAME\n");
}

void new_ui(int argc, char** argv){
	int command=atoi(argv[1]);
	if(command==1){
		int kmerlen=atoi(argv[2]);
		char *input=readFile(argv[3]);
		char** strings = malloc(sizeof(char*));
		strings[0] = input;
		int nKmers=strlen(input)+1-kmerlen;
		printf("Number of kmers= %i\n",nKmers);
		clock_t tStart=clock();
		iterator_state* state = initialize_iterator(strings, 1);
		single_iterate_test(state, &count_kmers, &nKmers, kmerlen);
		printf("Number of unique kmers= %i\n", nKmers);
		clock_t tEnd=clock();
		printf("The running time is %.2f Seconds. \n",((double)(tEnd - tStart)/(CLOCKS_PER_SEC)));
		free_iterator_state(state);
		free(strings);
	}else if(command==2){
		int kmerlen=atoi(argv[2]);
		char *input1= readFile(argv[3]);
		if(input1==0)
			return;
		char *input2= readFile(argv[4]);
		if(input2==0)
			return;
		char** strings = malloc(sizeof(char*));
		strings[0] = input1;
		strings[1] = input2;
		printf("Kmer Length= %i\n",kmerlen);
		printf("Sequence 1 Length= %i , sequence is %s\n",strlen(input1), input1);
		printf("Sequence 2 Length= %i , sequence is %s\n",strlen(input2), input2);
		clock_t tStart=clock();
		iterator_state* state =initialize_iterator(strings,2);
		state->threshold =0;
		kmer_kernel* kernel=initialize_kmer_kernel(strlen(input1), strlen(input2),kmerlen);
		double_iterate_test(state, &update_kmer_kernel, kernel);
		compute_kmer_kernel(kernel);
		clock_t tEnd=clock();
		printf("The running time is %.2f Seconds. \n",((double)(tEnd - tStart)/(CLOCKS_PER_SEC)));
		free_iterator_state(state);
		free(strings);
	}else{
		printf("Unknown Command.\n");
		return;
	}
}


char* readFile(char* fileName){
	FILE *file = fopen( fileName, "r" );
	if ( file == 0 ){
		 printf( "Could not open file\n" );
		 return 0;
	}
	fseek(file, 0, SEEK_END);
	long fsize = ftell(file)-1;
	printf("Sequence Length= %i\n",fsize);
	fseek(file, 0, SEEK_SET);
	char* input= malloc(fsize+1);
	fread(input, fsize, 1, file);
	fclose(file);
	return input;
}
