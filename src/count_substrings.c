/*
 * count_substrings.c
 *
 *  Created on: 21.1.2014
 *      Author: lvapaaka
 */

#include <stdlib.h>
#include <stdio.h>

int count_substrings(char* string, int string_length){
	char **substrings = calloc(100, string_length-1);
	int i,j,k,count = 0;
	for(i = 0; i < string_length;i++){
		for(j = 1; j < string_length-i +1;j++){
			for(k = 0;k < j;k++){
				printf("%c",string[i+k]);
			}
			printf("\n");
			count++;
			//if (!substrings.contains(string.substring(i,j){
			// substrings.add(substring)
			//substrings[count * (string_length-1)] = string[i];
			//string[j]
		}
	}
	free(substrings);
	return count;
}
