#include "../../include/bit_vector.h"
#include "../../include/iterate.h"
#include "../../include/rbwt.h"
#include "../../include/backward_search.h"
#include "../../include/c_array.h"
#include "../../include/utils.h"
#include "../../include/mum.h"
#include "../../include/maximal_repeats.h"
#include "../../include/structs.h"
#include "../../include/wavelet_tree.h"
#include "../../include/utils.h"
#include "../bwt/s_to_bwt.h"
#include "substring_stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

inline int is_reverse_interval_right_maximal(bit_vector* runs,
		interval* interval) {
	return runs->rank(runs, (interval->i) + 1, interval->j) > 0 ? 1 : 0;
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
interval* update_reverse_interval(interval* inter, interval* normal,
		const char* alphabet, unsigned int alphabet_length, const int* c_array,
		const char c, interval* target) {

	if (target == 0)
		target = malloc(sizeof(interval));

	int char_index = c_array[binary_search(alphabet, &c, sizeof(char),
			alphabet_length, 0)];
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
substring* create_substring(interval* normal, interval* reverse, int length,
		substring* target) {
	if (target == 0)
		target = malloc(sizeof(substring));

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
	//printf("Bwt, reverse bwt, reverse runs and stack created\n");
	int bwt_length = bwt->get_num_bits(bwt), i, alphabet_length =
			bwt->get_alphabet_length(bwt);
	unsigned int* c_array = malloc((alphabet_length + 1) * sizeof(unsigned int));
	alphabet_data* alpha_data = malloc(sizeof(alphabet_data));
	alpha_data->alphabet = malloc((alphabet_length + 1) * sizeof(char));

	// WARNING WARNING, NOT GOOD
	max_repeats_initialize_bwt(bwt);
	//printf("Max repeats initialized\n");

	//Initialize first intervals. In the start both intervals are the whole bwt
	interval* normal = &((interval ) { .i = 0, .j = bwt_length - 1 } );
	interval* reverse = &((interval ) { .i = 0, .j = bwt_length - 1 } );

	//printf("Intervals initialized\n");

	//create starting substring
	substring* new_substring = 0, *substring = create_substring(normal, reverse,
			0, 0);

	//printf("Substrings created.\n");

	while (1) {
		if (substring == NULL)
			break;

		//if size of the interval is 1, it cannot be a right-maximal string
		//if(substring->normal->i == substring->normal->j) continue;

		// Determine characters that precede the interval
		alpha_data = create_alphabet_interval(&substring->normal, bwt,
				alpha_data);

		//printf("Alphabet determined: %s. Length: %d\n", alpha_data->alphabet, alpha_data->length);

		c_array = create_c_array(bwt, &substring->normal, 0, 0, c_array);

		/*printf("C-array created: ");

		for (int i = 0; i < alpha_data->length; ++i)
			printf("%u, ", c_array[i]);

		printf("\n");*/

		alphabet_length = alpha_data->length;

		for (i = 0; i < alphabet_length; i++) {
			normal = backward_search_interval(bwt, &substring->normal,
					alpha_data->alphabet[i], normal);
			reverse = update_reverse_interval(&substring->reverse,
					normal, alpha_data->alphabet, alphabet_length, c_array,
					alpha_data->alphabet[i], reverse);

			//printf("normal and reverse updated\n");

			if (is_reverse_interval_right_maximal(reverse_runs, reverse)) {
				//printf("Reverse is right maximal\n");
				new_substring = create_substring(normal, reverse,
						substring->length + 1, new_substring);
				// callback function pointers
				callback(new_substring);
				push(stack, new_substring);
				//printf("Reverse pushed to stack\n");
			}
		}

		substring = pop(stack);
	}

	free(c_array);
	free(alpha_data->alphabet);
	free(alpha_data);
	free_stack(stack);
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

void double_iterate(char* string1, char* string2,
		void (*callback)(substring* substr1, substring* substr2)) {

	wavelet_tree* bwt1 = s_to_BWT(string1), *rev_bwt1 = reverse_bwt(string1);
	wavelet_tree* bwt2 = s_to_BWT(string1), *rev_bwt2 = reverse_bwt(string1);
	bit_vector* reverse_runs1 = create_runs_vector(rev_bwt1, 0);
	bit_vector* reverse_runs2 = create_runs_vector(rev_bwt2, 0);
	substring_stack* stack1 = create_stack(10);
	substring_stack* stack2 = create_stack(10);
	int bwt_length1 = bwt1->get_num_bits(bwt1), i, alphabet_length1 =
			bwt1->get_alphabet_length(bwt1);
	int bwt_length2 = bwt2->get_num_bits(bwt2), alphabet_length2 =
			bwt2->get_alphabet_length(bwt2);
	unsigned int* c_array1 = malloc(
			(alphabet_length1 + 1) * sizeof(unsigned int));
	unsigned int* c_array2 = malloc(
			(alphabet_length2 + 1) * sizeof(unsigned int));
	alphabet_data* alpha_data1 = malloc(sizeof(alphabet_data));
	alpha_data1->alphabet = malloc((alphabet_length1 + 1) * sizeof(char));

	alphabet_data* alpha_data2 = malloc(sizeof(alphabet_data));
	alpha_data2->alphabet = malloc((alphabet_length2 + 1) * sizeof(char));

	char* common_alphabet = malloc((alphabet_length2 + alphabet_length1 + 1) * sizeof(char));

	// WARNING WARNING, NOT GOOD
	mum_initialize_bwts(bwt1, bwt2, rev_bwt1, rev_bwt2);

	//Initialize first intervals. In the start both intervals are the whole bwt
	interval* normal1 = &((interval ) { .i = 0, .j = bwt_length1 - 1 } );
	interval* reverse1 = &((interval ) { .i = 0, .j = bwt_length1 - 1 } );

	interval* normal2 = &((interval ) { .i = 0, .j = bwt_length2 - 1 } );
	interval* reverse2 = &((interval ) { .i = 0, .j = bwt_length2 - 1 } );

	//create starting substring
	substring* new_substring1 = 0, *substring1 = create_substring(normal1,
			reverse1, 0, 0);

	substring* new_substring2 = 0, *substring2 = create_substring(normal2,
			reverse2, 0, 0);

	while (1) {
		if (substring1 == NULL)
			break;

		if (substring2 == NULL)
			break;

		//if size of the interval is 1, it cannot be a right-maximal string
		//if(substring->normal->i == substring->normal->j) continue;

		// Determine characters that precede the interval
		alpha_data1 = create_alphabet_interval(&substring1->normal, bwt1,
				alpha_data1);
		alpha_data2 = create_alphabet_interval(&substring2->normal, bwt2,
				alpha_data2);
		c_array1 = create_c_array(bwt1, &substring1->normal, 0, 0, c_array1);
		c_array2 = create_c_array(bwt2, &substring2->normal, 0, 0, c_array2);

		char alphabets[alpha_data1->length + alpha_data2->length];
		strcpy(alphabets, alpha_data1->alphabet);
		strcat(alphabets, alpha_data2->alphabet);

		common_alphabet = determine_alphabet(alphabets);
		int common_alphabet_length = strlen(common_alphabet);

		for (i = 0; i < common_alphabet_length; i++) {
			interval* normal1 = backward_search_interval(bwt1,
					&substring1->normal, common_alphabet[i], normal1);
			if (normal1 == NULL) {
				continue;
			}
			interval* normal2 = backward_search_interval(bwt2,
					&substring2->normal, common_alphabet[i], normal2);
			if (normal2 == NULL) {
				continue;
			}
			interval* reverse1 = update_reverse_interval(&substring1->reverse,
					normal1, alpha_data1->alphabet, alphabet_length1, c_array1,
					common_alphabet[i], reverse1);
			interval* reverse2 = update_reverse_interval(&substring2->reverse,
					normal2, alpha_data2->alphabet, alphabet_length2, c_array2,
					common_alphabet[i], reverse2);

			new_substring1 = create_substring(normal1, reverse1,
					substring1->length + 1, new_substring1);
			new_substring2 = create_substring(normal2, reverse2,
					substring2->length + 1, new_substring2);
			// callback function pointers
			callback(new_substring1, new_substring2);
			push(stack1, new_substring1);
			push(stack2, new_substring2);
		}

		substring1 = pop(stack1);
		substring2 = pop(stack2);
	}

	free(c_array1);
	free(c_array2);
	free(alpha_data1->alphabet);
	free(alpha_data1);
	free_stack(stack1);
	free(alpha_data2->alphabet);
	free(alpha_data2);
	free_stack(stack2);
	free(common_alphabet);
}
