/*
 * count_substrings.h
 *
 *  Created on: 21.1.2014
 *      Author: pklehtol
 */

#ifndef DISTINCT_SUBSTRINGS_H_
#define DISTINCT_SUBSTRINGS_H_



int lcp(char* string1, char* string2);

void swap_strings(char **a, char **b);

void quicksort(char *strings[], int len);

int compare_pairs(char *strings[], int len);

char **create_suffixes(char *string);

int distinct_substrings(char *string);

#endif /* DISTINCT_SUBSTRINGS_H_ */
