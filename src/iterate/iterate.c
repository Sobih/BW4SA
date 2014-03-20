#include "../../include/bit_vector.h"
#include "../../include/iterate.h"
#include "../../include/rbwt.h"
#include "../../include/backward_search.h"
#include "../../include/c_array.h"
#include "../../include/maximal_repeats.h"
#include "../../include/wavelet_tree.h"
#include "../../include/utils.h"
#include "../bwt/s_to_bwt.h"
#include "substring_stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bit_vector* create_runs_vector(const wavelet_tree* string, bit_vector* target) {
	if (target == 0)
		target = malloc(sizeof(bit_vector));

	unsigned int length = string->get_num_bits(string);
	init_bit_vector(target, length);

	target->mark_bit(target, 0);
	for (int i = 1; i < length; i++)
		if (string->char_at(string, i - 1) != string->char_at(string, i))
			target->mark_bit(target, i);

	return target;
}

int is_reverse_interval_right_maximal(bit_vector* runs, interval* interval) {
	return runs->rank(runs, (interval->i)+1, interval->j) > 0 ? 1 : 0;
}

/**
 * Updates the interval in the BWT of the reverse of the string
 * @param reverse-BWT interval of the mother node
 * @param updated BWT interval in this node
 * @param alphabet in the interval
 * @param array C of the interval
 * @param extension character
 * @return a new updated Interval struct in the BWT of the reverse of the string
 */
interval* update_reverse_interval(interval* inter, interval* normal, const char* alphabet,
		unsigned int alphabet_length, const int* c_array, const char c, interval* target) {

	if (target == 0)
		target = malloc(sizeof(interval));

	int char_index = c_array[binary_search(alphabet, &c, sizeof(char), alphabet_length, 0)];
	target->i = inter->i + char_index;

	//length of the reverse interval is same as length of the normal interval
	target->j = target->i + (normal->j - normal->i);
	return target;
}

/**
 * @brief Creates a substring struct from interval and length.
 * @param interval in normal BWT
 * @param interval in the BWT of the reverse of the string
 * @param length of substring
 *
 * @return pointer to a new substring struct
 */
substring* create_substring(interval* normal, interval* reverse, int length)
{
	substring* target = malloc(sizeof(substring));

	target->normal.i = normal->i;
	target->normal.j = normal->j;

	target->reverse.i = reverse->i;
	target->reverse.j = reverse->j;

	target->length = length;

	return target;
}

void iterate(char* string, void (*callback)(substring* substr)) {

	wavelet_tree* bwt = s_to_BWT(string), *rev_bwt = reverse_bwt(string);
	bit_vector* reverse_runs = create_runs_vector(rev_bwt, 0);
	substring_stack* stack = create_stack(10);
	int bwt_length = bwt->get_num_bits(bwt), i, alphabet_length = bwt->get_alphabet_length(bwt);
	unsigned int* c_array = malloc((alphabet_length + 1) * sizeof(unsigned int));
	char* alphabet = malloc((alphabet_length + 1) * sizeof(char));

	// WARNING WARNING, NOT GOOD
	max_repeats_initialize_bwt(bwt);

	//Initialize first intervals. In the start both intervals are the whole bwt
	interval* normal = &((interval) {.i = 0, .j = bwt_length - 1});
	interval* reverse = &((interval) {.i = 0, .j = bwt_length - 1});

	//create starting substring
	substring* new_substring, *substring = create_substring(normal, reverse, 0);

	while (1) {
		if (substring == NULL)
			break;

		//if size of the interval is 1, it cannot be a right-maximal string
		//if(substring->normal->i == substring->normal->j) continue;

		// Determine characters that precede the interval
		alphabet = create_alphabet_interval(substring->normal, bwt, alphabet);
		c_array = create_c_array(bwt, substring->normal, 0, 0, c_array);
		alphabet_length = strlen(alphabet);

		for(i = 0; i < alphabet_length; i++) {
			interval* normal = backward_search_interval(bwt, substring->normal, alphabet[i], normal);
			interval* reverse = update_reverse_interval(substring->reverse, normal, alphabet, alphabet_length,
					c_array, alphabet[i], reverse);

			if(is_reverse_interval_right_maximal(reverse_runs, reverse)) {
				new_substring = create_substring(normal, reverse, substring->length + 1);
				// callback function pointers
				callback(new_substring);
				push(stack, new_substring);
			}
		}

		free(substring);

		substring = pop(stack);
	}

	free(c_array);
	free(alphabet);
}

/*
void iterate_for_tree_drawing(char* string, void (*callback)(substring* substr, substring* prev_substr, char c)) {

	unsigned char* bwt = s_to_BWT(string);
	bit_vector* runs = create_runs_vector(string);

	substring_stack* stack = create_stack(10);

	//Initialise first intervals. In the start both intervals are the whole bwt
	Interval* normal = &((Interval ) { .i = 0, .j = strlen(bwt) - 1 } );
	Interval* reverse = &((Interval ) { .i = 0, .j = strlen(bwt) - 1 } );

	//create starting substring
	substring* start = &((substring) { .normal = normal, .reverse = reverse, .length = 0 });

	push(stack, start);
	substring* new_substring;
	substring* substring;

	while (1) {
		substring = pop(stack);

		if (substring == NULL)
			break;

		//if size of the interval is 1, it cannot be a right-maximal string
		//if(substring->normal->i == substring->normal->j) continue;

		// Determine characters that precede the interval
		char* alphabet = create_alphabet_interval(substring->normal, bwt);
		int* c_array = create_c_array_interval(substring->normal, bwt);

		int i;
		for (i = 0; i < strlen(alphabet); i++) {

			Interval* normal = backward_search_interval(bwt, substring->normal,
					alphabet[i]);
			Interval* reverse = update_reverse_interval(substring->reverse,substring->normal,
					normal, bwt, alphabet[i]);

			if (is_reverse_interval_right_maximal(runs, reverse)) {
				new_substring = create_substring(normal, reverse, substring->length + 1);
				// callback function pointers
				callback(new_substring, substring, alphabet[i]);
				push(stack, new_substring);
			} else {
				free(normal);
				free(reverse);
			}
		}
		free(alphabet);
		free(c_array);
	}
}
*/
