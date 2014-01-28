/*
 * count_substrings.c
 *
 *  Created on: 21.1.2014
 *      Author: pklehtol
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>




/** longest common prefix
 * @return how long is the lcp */
int lcp(char *string1, char *string2) {
	int i, string_length, lcp_length = 0;
	int s1_length = strlen(string1);
	int s2_length = strlen(string2);
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
void quicksort(char **strings, int len) {
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
	int i, count = strlen(strings[0]);
	char *a, *b;

	for (i = 1; i < len; i++) {
		a = strings[i-1];
		b = strings[i];
		count += strlen(b) - lcp(a, b);
	}

	return count;
}

char **create_suffixes(char *string) {
	int len = strlen(string);	
	char **suffixes;
	int i;	

	suffixes = calloc(len+1, len+1);

	for (i = 0; i < len; i++) {
		suffixes[i] = &(string[i]);
	}

	return suffixes;
}

int distinct_substrings(char *string) {
	int res;

	char **suffixes = create_suffixes(string);
	quicksort(suffixes, strlen(string));
	res = compare_pairs(suffixes, strlen(string));

	free(suffixes);

	return res;
}



