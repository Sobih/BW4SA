/**
 * @file	bwt_to_s.h
 * @brief	Implementation of the function to convert BWT back to an original string.
 * @author	Paula Lehtola, Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "../../include/backward_search.h"
#include "../../include/structs.h"
#include "../../include/wavelet_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* bwt_to_s(const wavelet_tree* bwt)
{
	long n = bwt->get_num_bits(bwt);
	char* string = malloc(n * sizeof(char));
	interval inter = (interval) {.i = 0, .j = 0};

	for (int k = 1; k < n; k++) {
		string[n - k - 1] = bwt->char_at(bwt, inter.i);
		backward_search_interval(bwt, &inter, string[n - k - 1], &inter);
	}

	string[n - 1] = 0;

	return string;
}
