/**
 * @file	backward_search.c
 * @brief	Implementation of backwards search.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include <string.h>
#include <stdlib.h>
#include "../../include/utils.h"
#include "../../include/c_array.h"
#include "../../include/structs.h"
#include "../../include/backward_search.h"
#include "../../include/wavelet_tree.h"

interval* backward_search(const wavelet_tree* bwt, const wavelet_tree* string, interval* target) {
	int i = 0, j = bwt->get_num_bits(bwt) - 1, index;
	unsigned int alphabet_length = bwt->get_alphabet_length(bwt) - 1;
	char* alphabet = bwt->get_alphabet(bwt), current;
	unsigned int* c_array = create_c_array(bwt, 0, 0, 0, 0);
	int upper, lower;

	for (int k = string->get_num_bits(string) - 1; k >= 0; k--) {
		if(j < i) {
			free(c_array);
			return NULL;
		}

		current = string->char_at(string, k);
		index = binary_search(alphabet, &current, sizeof(char), alphabet_length, 0);

		if (index < 0) {
			free(c_array);
			return NULL;
		}

		upper = bwt->rank(bwt, current, i, j) - 1;
		lower = bwt->rank(bwt, current, 0, i - 1);

		i = c_array[index] + lower;
		j = i + upper;
	}

	free(c_array);

	if (target == 0)
		target = malloc(sizeof(interval));

	target->i = i;
	target->j = j;

	return target;
}

interval* backward_search_interval(const wavelet_tree* bwt, const interval* inter, char c,
		interval* target) {
	unsigned int* c_array = create_c_array(bwt, 0, 0, 0, 0);
	char* alphabet = bwt->get_alphabet(bwt);

	int index = binary_search(alphabet, &c, sizeof(char), bwt->get_alphabet_length(bwt) - 1, 0);
	int i = c_array[index] + bwt->rank(bwt, c, 0, inter->i - 1);
	int j = i + bwt->rank(bwt, c, inter->i, inter->j) - 1;

	free(c_array);

	if (i > j) return NULL;

	if (target == 0)
		target = malloc(sizeof(interval));

	target->i = i;
	target->j = j;

	return target;
}
	
