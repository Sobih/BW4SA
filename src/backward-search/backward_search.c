
#include <string.h>
#include <stdlib.h>
#include "../../include/utils.h"
#include "../../include/c_array.h"
#include "../../include/backward_search.h"
#include "../../include/wavelet_tree.h"

interval* backward_search(const wavelet_node* bwt, const wavelet_node* string)
{
	bit_vector* bwt_vec = bwt->vector, *str_vec = string->vector;
	int i = 0, j = bwt_vec->length * 32 - bwt_vec->filler_bits - 1, k, index;
	char* alphabet = bwt->alphabet, current;
	int* c_array = create_c_array(bwt);

	for(k = str_vec->length * 32 - str_vec->filler_bits - 1; k >= 0; k--) {
		if(j < i)
			return NULL;

		current = string->char_at(string, k);
		index = binary_search(alphabet, &current, 0, string->alphabet_length - 1, sizeof(char));
		i = index + bwt->rank(bwt, current, i);
		j = index + bwt->rank(bwt, current, j) - 1;
	}

	interval* new_interval = malloc(sizeof(interval));
	new_interval->i = i;
	new_interval->j = j;

	return new_interval;		
}

interval* backward_search_interval(const wavelet_node* bwt, const interval* interval, char c) {
	int* c_array = create_c_array(bwt);
	char* alphabet = bwt->alphabet;

	int index = binary_search(alphabet, &c, 0, bwt->alphabet_length - 1, sizeof(char));
	int i = index + bwt->rank(bwt, c, interval->i);
	int j = index + bwt->rank(bwt, c, interval->j) - 1;

	if (i > j) return NULL;

	struct inter* new_interval = calloc(1, sizeof(struct inter));
	new_interval->i = i;
	new_interval->j = j;

	return new_interval;
}
	
