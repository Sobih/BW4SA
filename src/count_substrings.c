/*
 * count_substrings.c
 *
 *  Created on: 21.1.2014
 *      Author: lvapaaka & & pklehtol
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int count_substrings(char* string, int string_length){
	//char **substrings = calloc(100, string_length-1);
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
	//free(substrings);
	return count;
}
/** longest common prefix
 * @return how long is the lcp */
int lcp(char *string1, char *string2, int s1_length, int s2_length) {
	int i, string_length, lcp_length = 0;

	string_length = s1_length < s2_length ? s1_length : s2_length;

	for (i = 0; i < string_length; i++) {

		if (string1[i] == string2[i]) {
			lcp_length++;
		} else break;
	}

	return lcp_length;
}


void swap_strings(char **a, char **b) {
	char *tmp = *a;
	*a = *b;
	*b = tmp;
}

/* reference: http://stackoverflow.com/questions/19612152/quicksort-string-array-in-c*/
void quicksort(char *strings[], int len) {
	int i, pivot = 0;

	if (len <= 1) return;

	// swap a randomly selected value to the last node
	swap_strings(strings+((int)rand() % len), strings+len-1);

	for (i = 0; i < len-1; i++) {
		if (strcmp(strings[i], strings[len-1]) < 0) {
			swap_strings(strings+i, strings+pivot++);
		}
	}

	swap_strings(strings+pivot, strings+len-1);

	quicksort(strings, pivot++);
	quicksort(strings+pivot, len-pivot);
}

int compare_pairs(char *strings[], int len) {
	int i, count = 1;
	char *a, *b;

	quicksort(strings, len);

	for (i = 1; i < len; i++) {
		a = strings[i-1];
		b = strings[i];
		count += strlen(b) - lcp(a, b, strlen(a), strlen(b));
	}

	return count;
}

char **create_suffixes(char *string) {
	char **suffixes, *substr;
	int i, j;

	suffixes = calloc(strlen(string), sizeof(char));

	for (i = 0; i < strlen(string); i++) {
		substr = "";
		for (j = i; j < strlen(string); j++) {
			substr += string[j];

		}
		suffixes[i] = substr;
	}

	return **suffixes;

}





