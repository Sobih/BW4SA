/*
 * count_substrings.h
 *
 *  Created on: 21.1.2014
 *      Author: lvapaaka
 */

#ifndef COUNT_SUBSTRINGS_H_
#define COUNT_SUBSTRINGS_H_

int count_substrings(char* string, int string_length);

int lcp(char* string1, char* string2,  int s1_length, int s2_length);

void swap_strings(char **a, char **b);

void quicksort(char *strings[], int len);

int compare_pairs(char *strings[], int len);

char **create_suffixes(char *string);

int distinct_substrings(char *string);

#endif /* COUNT_SUBSTRINGS_H_ */
