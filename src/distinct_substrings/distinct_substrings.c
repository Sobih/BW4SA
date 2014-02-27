/**
 * @file 	distinct_substrings.c
 * @brief 	counts distincts substrings
 * @see 	distinct_substrings.h 
 * @author 	Paula Lehtola
 * @bug 	No known bugs.

 */


#include "../../include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




/** 
 * @brief 	longest common prefix
 * @param 	*string1 	char pointer to the first string to compare
 * @param 	*string2 	har pointer to the second string to compare
 * @return 	how long is the lcp 
 * @see 	distinct_substrings.h#lcp
 * @author 	Paula Lehtola
 * @bug 	No known bugs.
 */
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


/**
 * @brief 	creates an array with a pointer to every suffix of a string
 * @param 	*string		char pointer to a string 
 * @return 	a pointer array of suffixes
 * @see		distinct_substrings.h#create_suffixes
 * @author	Paula Lehtola
 * @bug		No known bugs.
 */

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

/**
 * @brief 	compares lexicographically adjacent strings to determine amount of distinct substrings for each suffix
 * @param 	*strings[] 	an array of pointers of lexicographically ordered suffixes
 * @param	len			the length of the array
 * @return 	count of distinct substrings
 * @see		distinct_substrings.h#compare_pairs
 * @author	Paula Lehtola
 * @bug		No known bugs.
 */
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

/**
 * @brief	collects together functions needed to count distinct substrings
 * @param	*string		pointer to string whose distinct substrings are to be counted
 * @return	amount of distinct substrings
 * @see		distinct_substrings.h#distinct_substrings
 * @author	Paula Lehtola
 * @bug		No known bugs.
 */

int distinct_substrings(char *string) {
	int res;
	int len = strlen(string);
	char **suffixes = create_suffixes(string);
	string_quick_sort(suffixes, len);
	res = compare_pairs(suffixes, len);

	free(suffixes);

	return res;
}



