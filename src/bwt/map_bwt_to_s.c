/*
 * map_bwt_to_s.c
 *
 *  Created on: 27.2.2014
 *      Author: lvapaaka
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/c_array.h"
#include "../../include/utils.h"
#include "../../include/wavelet_tree.h"

int* map_create_suffix_array_from_bwt(const wavelet_tree* bwt)
{
	int string_length = bwt->get_num_bits(bwt), interval = 0, index;
	int* suffix_array = malloc(sizeof(int) * string_length);

	unsigned int* c_array = create_c_array(bwt, 0, 0, 0, 0);
	char* alphabet = bwt->get_alphabet(bwt), current;
	int c_value = 0, alphabet_length = bwt->get_alphabet_length(bwt);

	for(int i = string_length - 1; i >= 0; i--) {
		suffix_array[interval] = i;
		current = bwt->char_at(bwt, interval);
		index = binary_search(alphabet, &current, sizeof(char), alphabet_length, 0);
		interval = c_array[index] + bwt->rank(bwt, current, 0, interval - 1);
	}

	return suffix_array;
}
