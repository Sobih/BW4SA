/**
 * @file	bwt_to_s.h
 * @brief	A function to convert BWT back to an original string. 
 *
 * @author	Paula Lehtola, Lassi Vapaakallio
 * @bug		No known bugs
 */


#include "../../include/backward_search.h"
#include "../../include/wavelet_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief A function to convert a BWT of a string back to an original string.
 *
 * This function takes a BWT of a string as an input and converts it back to the original string  
 * (without $)
 *
 * @param bwt		The bwt of a string
 * @return string	The original string
 * @author 			Paula Lehtola, Lassi Vapaakallio
 * @bug				No known bugs
 */

char* bwt_to_s(const wavelet_tree* bwt)
{
	long n = bwt->get_num_bits(bwt) - 1;
	char* string = malloc(n * sizeof(char));
	int k;	
	interval inter = (interval) {.i = 0, .j = 0};

	for (k = 1; k <= n; k++) {
		string[n-k] = bwt->char_at(bwt, inter.i);
		backward_search_interval(bwt, &inter, string[n-k], &inter);
	}

	return string;
}
