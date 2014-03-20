
#include <string.h>
#include <stdlib.h>
#include "../../include/utils.h"
#include "../../include/c_array.h"
#include "../../include/backward_search.h"
#include "../../include/wavelet_tree.h"

interval* backward_search(const wavelet_tree* bwt, const wavelet_tree* string) {
	int i = 0, j = bwt->get_num_bits(bwt) - 1, k, index;
	unsigned int alphabet_length = bwt->get_alphabet_length(bwt) - 1;
	char* alphabet = bwt->get_alphabet(bwt), current;
	unsigned int* c_array = create_c_array(bwt);

	for(k = string->get_num_bits(string) - 1; k >= 0; k--) {
		if(j < i)
			return NULL;

		current = string->char_at(string, k);
		index = binary_search(alphabet, &current, 0, alphabet_length, sizeof(char));

		if (index < 0)
			return NULL;

		i = c_array[index] + bwt->rank(bwt, current, 0, i - 1);
		j = i + bwt->rank(bwt, current, i, j) - 1;
	}

	interval* new_interval = malloc(sizeof(interval));
	new_interval->i = i;
	new_interval->j = j;

	return new_interval;		
}

interval* backward_search_interval(const wavelet_tree* bwt, const interval* interval, char c) {
	int* c_array = create_c_array(bwt);
	char* alphabet = bwt->get_alphabet(bwt);

	int index = binary_search(alphabet, &c, 0, bwt->get_alphabet_length(bwt) - 1, sizeof(char));
	int i = index + bwt->rank(bwt, c, 0, interval->i - 1);
	int j = i + bwt->rank(bwt, c, interval->i, interval->j) - 1;

	if (i > j) return NULL;

	struct interval* new_interval = malloc(sizeof(struct interval));
	new_interval->i = i;
	new_interval->j = j;

	return new_interval;
}
	
