
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/c_array.h"
#include "../../include/utils.h"
#include "../../include/backward_search.h"

#define MAX_ALPHABET_SIZE 30
/**
*@brief finds first index of given char from a string
**/
int get_index(const char* string, const char c)
{
	int i;
	for(i=0;i<strlen(string);i++){
		if(c == string[i]){
			return i;
		}
	}
	return -1;
}

/**
*@brief returns string of all characters in alphabet of the given word, ordered alphabetically
**/
char* get_alphabet(const char* string)
{
	int i;
	char* alphabet = calloc(MAX_ALPHABET_SIZE, sizeof(char));
	alphabet[0] = '\0';
	int alphabet_index = 0;
	
	int length = strlen(string);
	for(i=0;i<length;i++){
		if(get_index(alphabet, string[i]) == -1){
			alphabet[alphabet_index+1] = alphabet[alphabet_index];
			alphabet[alphabet_index] = string[i];
			alphabet_index++;
		}
	}
	quick_sort(alphabet, strlen(alphabet), sizeof(char));
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
	
	for(i=strlen(alphabet)-1; i>0;i--){
		c_array[i] = c_array[i-1];
	}
	c_array[0] = 0;
	
	free(alphabet);
	
	return c_array;
}

char* create_string_from_interval(const Interval* interval, char* string);

int* create_c_array_interval(const Interval* interval, char* bwt)
{
	char* substr = create_string_from_interval(interval, bwt);
	return create_c_array(substr);
}

char* create_alphabet_interval(const Interval* interval, char* bwt)
{
	char* substr = create_string_from_interval(interval, bwt);
	return get_alphabet(substr);
}

char* create_string_from_interval(const Interval* interval, char* string)
{
	int length = interval->j - interval->i + 1;
	char* substr = malloc(sizeof(char)*length +1);
	for(int k = 0; k<length; k++){
		substr[k] = string[interval->i+k];
	}
	substr[length] = '\0';
	return substr;
}

int get_char_index(const int* c_array, const char* alphabet, const char c)
{
	int i;
	for(i=0;i<strlen(alphabet);i++){
		if(alphabet[i] == c){
			return c_array[i];
		}
	}
	printf("NOTFOUND\n");
	return 0;
}

