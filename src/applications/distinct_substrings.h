/*
 * count_substrings.h
 *
 *  Created on: 21.1.2014
 *      Author: pklehtol
 */

#ifndef DISTINCT_SUBSTRINGS_H_
#define DISTINCT_SUBSTRINGS_H_


int lcp(char* string1, char* string2);

char **create_suffixes(char *string);

int compare_pairs(char *strings[], int len);

int distinct_substrings(char *string);

#endif /* DISTINCT_SUBSTRINGS_H_ */
