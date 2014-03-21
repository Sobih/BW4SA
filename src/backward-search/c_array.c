
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../../include/c_array.h"
#include "../../include/utils.h"
#include "../../include/structs.h"
#include "../../include/backward_search.h"
#include "../../include/wavelet_tree.h"

unsigned int* create_c_array(const wavelet_tree* string, const interval* inter, const char* alphabet,
		unsigned int alphabet_length, unsigned int* target) {
	if (string == 0)
		return 0;

	unsigned int start = 0, end = UINT_MAX;

	if (inter) {
		start = inter->i;
		end = inter->j - 1;
	}

	if (!alphabet) {
		alphabet = string->get_alphabet(string);
		alphabet_length = string->get_alphabet_length(string);
	}

	if (target == 0)
		target = malloc((alphabet_length + 1) * sizeof(unsigned int));

	target[0] = 0;
	
	for(int i = 0; i < alphabet_length; i++) {
		//count number of occurrences of each character
		target[i + 1] = string->rank(string, alphabet[i], start, end);

		//add previous count to each number
		target[i + 1] += target[i];
	}
	
	return target;
}

alphabet_data* create_alphabet_interval(const interval* interval, const wavelet_tree* string, alphabet_data* target)
{
	int length = interval->j - interval->i + 1;
	char current;

	if (target == 0)
		target = malloc(sizeof(alphabet_data));

	target->length = 0;
	target->alphabet = realloc(target->alphabet, length * sizeof(char));
	target->alphabet[length - 1] = 0;

	for (int i = interval->i; i < interval->j; ++i) {
		current = string->char_at(string, i);

		if (binary_search(target, &current, sizeof(char), target->length, 0) < 0) {
			target->alphabet[target->length] = current;
			target->length++;
		}
	}

	quick_sort(target, target->length, sizeof(char));

	return target;
}
