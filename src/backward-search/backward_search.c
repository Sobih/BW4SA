
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/c_array.h"
#include "../../include/structs.h"
/*
 * backward_search.c
 *
 *  Created on: 30.1.2014
 *      Author: lvapaaka
 */

int rank(const int index, const char c, const char* string){
	int i, count = 0;
	if(index <= 0){
		return 0;
	}

	for(i = index - 1; i >= 0; i--){
		if(string[i] == c){
			count++;
		}
	}
	return count;
}

Interval* backward_search(const char* bwt, const char* string)
{
	int i = 0;
	int j = strlen(bwt)-1;
	char* alphabet = get_alphabet(bwt);
	int* c_array = create_c_array(bwt);
	int k;
	for(k = strlen(string)-1; k>=0; k--){
		if(j<i){
			return NULL;
		}
		i = get_char_index(c_array, alphabet, string[k])+rank(i, string[k], bwt);
		j = get_char_index(c_array, alphabet, string[k])+rank(j+1, string[k], bwt)-1;
	}
	Interval* new_interval = malloc(sizeof(Interval));
	new_interval->i = i;
	new_interval->j = j;
	return new_interval;		
}

Interval* backward_search_interval(const char* bwt, Interval* interval, const char c){
	int* c_array = create_c_array(bwt);
	char* alphabet = get_alphabet(bwt);
	int i = interval->i;
	int j = interval->j;
	i = get_char_index(c_array, alphabet, c)+rank(i, c, bwt);
	j = get_char_index(c_array, alphabet, c)+rank(j+1, c, bwt)-1;
	if(i > j){
		return NULL;
	}
	Interval* new_interval = malloc(sizeof(Interval));
	new_interval->i = i;
	new_interval->j = j;
	return new_interval;
}
	
