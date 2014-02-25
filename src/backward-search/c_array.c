
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../../include/c_array.h"
#include "../../include/utils.h"
#include "../../include/backward_search.h"
#include "../../include/wavelet_tree.h"

unsigned int* create_c_array(const wavelet_node* string, const interval* inter, const char* alphabet,
		unsigned int alphabet_length)
{
	if (string == 0)
		return 0;

	unsigned int start = 0, end = UINT_MAX;

	if (inter) {
		start = inter->i;
		end = inter->j - 1;
	}

	if (!alphabet) {
		alphabet = string->alphabet;
		alphabet_length = string->alphabet_length;
	}

	unsigned int* c_array = malloc((alphabet_length + 1) * sizeof(unsigned int));
	c_array[0] = 0;
	
	for(int i = 0; i < alphabet_length; i++) {
		//count number of occurrences of each character
		c_array[i + 1] = string->rank(string, alphabet[i], start, end);

		//add previous count to each number
		c_array[i + 1] += c_array[i];
	}
	
	return c_array;
}

char* create_alphabet_interval(const interval* interval, const wavelet_node* string)
{
	unsigned int length = interval->j - interval->i + 1;
	char* alphabet = calloc(length, sizeof(char));
	unsigned int counter = 0;
	char current;

	for (int i = interval->i; i < interval->j; ++i) {
		current = string->char_at(string, i);

		if (binary_search(alphabet, &current, sizeof(char), length) < 0) {
			alphabet[counter] = current;
			counter++;
			quick_sort(alphabet, counter, sizeof(char));
		}
	}

	return alphabet;
}
