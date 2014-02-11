
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/c_array.h"
#include "../../include/utils.h"

#define MAX_ALPHABET_SIZE 20
/**
*@brief finds first index of given char from a string
**/
int get_index(const char* string, const char c)
{
	int i;
	for(i=0;i<strlen(string);i++){
		//printf("gettind index. i: %d \n",i);
		if(c == string[i]){
			printf("returning %d \n", i);
			return i;
		}
		//printf("loop cycle done. i:%d\n",i);
	}
	return -1;
}

/**
*@brief returns string of all characters in alphabet of the given word, ordered alphabetically
**/
char* get_alphabet(const char* string)
{
	printf("starting c alphabet\n");
	int i;
	char* alphabet = calloc(MAX_ALPHABET_SIZE, sizeof(char));
	alphabet[0] = '\0';
	int alphabet_index = 0;
	
	printf("starting loop \n");

	int length = strlen(string);
	for(i=0;i<length;i++){
		//printf("index i: %d and alphabet_index: %d \n", i,alphabet_index);
		if(get_index(alphabet, string[i]) == -1){
			printf("Moving letter by one \n");
			alphabet[alphabet_index+1] = alphabet[alphabet_index];
			printf("adding letter to alphabet \n");
			alphabet[alphabet_index] = string[i];
			printf("incrementing index \n");
			alphabet_index++;
			printf("alphabet index is: %d \n", alphabet_index);
		}
	}
	printf("finished loop");
	quick_sort(alphabet, strlen(alphabet), sizeof(char));
	printf("returning alphabet\n");
	return alphabet;
}

int* create_c_array(const char* string)
{
	int i;
	char* alphabet = get_alphabet(string);
	int* c_array = calloc(strlen(alphabet), sizeof(int));
	
	for(i=0;i<strlen(string);i++){
		int index = get_index(alphabet, string[i]);
		c_array[index] += 1;
	}
	for(i=0;i<strlen(alphabet)-1;i++){
		c_array[i+1] = c_array[i+1] + c_array[i];
	}
	
	for(i=strlen(alphabet); i>0;i--){
		c_array[i] = c_array[i-1];
	}
	c_array[0] = 0;
	
	free(alphabet);
	
	return c_array;
}

