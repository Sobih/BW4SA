
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../../include/c_array.h"
#include "../../include/utils.h"
#include "../../include/backward_search.h"
#include "../../include/wavelet_tree.h"

unsigned int* create_c_array(const wavelet_tree* string, const interval* inter, const char* alphabet,
		unsigned int alphabet_length, unsigned int* target) {
	if (string == 0)
		return 0;

	if (!alphabet) {
		alphabet = string->get_alphabet(string);
		alphabet_length = string->get_alphabet_length(string);
		printf("Alphabet: %s, length: %d\n", alphabet, alphabet_length);
	}

	unsigned int start = 0, end = INT_MAX;

	if (inter) {
		start = inter->i;
		end = inter->j;
		alphabet_data* data = create_alphabet_interval(inter, string, 0);
		alphabet = data->alphabet;
		alphabet_length = data->length;
		free(data);
		printf("Interval! %d, %d\n", inter->i, inter->j);
		printf("New alphabet: %s, length: %d\n", alphabet, alphabet_length);
	}

	unsigned int* ret;

	if (target == 0) {
		ret = malloc((alphabet_length + 1) * sizeof(unsigned int));
		printf("ASDASDASDSADASDASDASD");
	}
	else ret = target;

	printf("String: %s\n", string->nodes[0].string);

	ret[0] = 0;
	


	for(int i = 0; i < alphabet_length - 1; i++) {
		//count number of occurrences of each character
		ret[i + 1] = string->rank(string, alphabet[i], start, end);

		printf("Char: %c, Start: %u, End: %u\n", alphabet[i], start, end);
		printf("Rank: %u\n", ret[i + 1]);

		//add previous count to each number
		ret[i + 1] += ret[i];

		printf("Final number: %d\n", ret[i + 1]);
	}
	
	printf("target[0]: %u\n", ret[0]);

	return ret;
}

alphabet_data* create_alphabet_interval(const interval* interval, const wavelet_tree* string, alphabet_data* target)
{
	int length = interval->j - interval->i + 1;
	printf("Length: %d\n", length);
	char* current = malloc(sizeof(char));
	alphabet_data* ret;

	if (target == 0) {
		target = malloc(sizeof(alphabet_data));
		target->alphabet = malloc(length * sizeof(char));
	}
	else {
		//ret = target;
		target->alphabet = realloc(ret->alphabet, length * sizeof(char));
	}

	target->length = 0;
	target->alphabet[length - 1] = 0;

	for (int i = interval->i; i <= interval->j; ++i) {
		*current = string->char_at(string, i);

		printf("Current char: %c\n", *current);
		printf("Current length: %d\n", target->length);

		if (binary_search(target->alphabet, current, sizeof(char), target->length, 0) < 0) {
			printf("Char not found in alphabet! Adding %c\n", *current);
			target->alphabet[target->length] = *current;
			target->length++;
		}
	}

	target->alphabet[target->length] = 0;

	quick_sort(target->alphabet, target->length, sizeof(char));

	return target;
}
