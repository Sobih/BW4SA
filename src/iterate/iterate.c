#include "../../include/bit_vector.h"
#include "../../include/iterate.h"
#include "../../include/rbwt.h"
#include "../../include/backward_search.h"
#include "../../include/c_array.h"
#include "../bwt/s_to_bwt.h"
#include "substring_stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bit_vector* create_runs_vector(char* string) {
	char* rbwt = reverse_bwt(string);
	bit_vector* runs = malloc(sizeof(bit_vector));
	init_bit_vector(runs, strlen(rbwt));

	runs->mark_bit(runs, 0);
	for (int i = 1; i < strlen(rbwt); i++) {
		if (rbwt[i - 1] != rbwt[i]) {
			runs->mark_bit(runs, i);
		}
	}
	return runs;
}

void print_bit_vec(bit_vector* bitvec, int length) {
	for (int i = 0; i < length; i++) {
		if (bitvec->is_bit_marked(bitvec, i)) {
			printf("%d", 1);
		} else {
			printf("%d", 0);
		}
	}
	printf("\n");
}

int is_reverse_interval_right_maximal(bit_vector* runs, Interval* interval) {
	if (interval->i >= interval->j)
		return 0;

	if (runs->rank_interval(runs, (interval->i) + 1, interval->j) > 0) {
		return 1;
	} else
		return 0;
}

Interval* update_reverse_interval(Interval* old_reverse, Interval* old_normal, Interval* normal,
		char* bwt, const char c);

substring* create_substring(Interval* normal, Interval* reverse, int length);

void iterate(char* string, void (*callback)(substring* substr)) {

	unsigned char* bwt = s_to_BWT(string);
	bit_vector* runs = create_runs_vector(string);

	print_bit_vec(runs, strlen(bwt));
	substring_stack* stack = create_stack(10);

	//Initialise first intervals. In the start both intervals are the whole bwt
	Interval* normal = &((Interval ) { .i = 0, .j = strlen(bwt) - 1 } );
	Interval* reverse = &((Interval ) { .i = 0, .j = strlen(bwt) - 1 } );

	//create starting substring
	substring* start = create_substring(normal, reverse, 0);

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

//		printf("c-array: ");
//		for(int i = 0; i<strlen(alphabet);i++){
//			printf("%d ", c_array[i]);
//		}
//		printf("\n");
//
//		printf("alphabet: ");
//			for(int i = 0; i<strlen(alphabet);i++){
//				printf("%c ", alphabet[i]);
//			}
//		printf("\n");

		int i;
		for (i = 0; i < strlen(alphabet); i++) {

			Interval* normal = backward_search_interval(bwt, substring->normal,
					alphabet[i]);
			Interval* reverse = update_reverse_interval(substring->reverse,substring->normal,
					normal, bwt, alphabet[i]);
//			printf("for loop: normal i = %d, normal j = %d, reverse i = %d, reverse j = %d\n", normal->i, normal->j, reverse->i, reverse->j);
//			printf("substring is r-maximal? %d\n",is_reverse_interval_right_maximal(runs, reverse));

			if (is_reverse_interval_right_maximal(runs, reverse)) {
//				printf("right_maximal found\n");
				new_substring = create_substring(normal, reverse,
						substring->length + 1);
				// callback function pointers
				callback(new_substring);
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

/**
 * Updates the interval in the BWT of the reverse of the string
 * @param reverse-BWT interval of the mother node
 * @param updated BWT interval in this node
 * @param alphabet in the interval
 * @param array C of the interval
 * @param extension character
 * @return a new updated Interval struct in the BWT of the reverse of the string
 */
Interval* update_reverse_interval(Interval* old_reverse, Interval* old_normal, Interval* normal,
		char* bwt, const char c) {

	char* alphabet = create_alphabet_interval(old_normal, bwt);
	int* c_array = create_c_array_interval(old_normal, bwt);
//
//	printf("original reverse's i = %d, j = %d\n", old_reverse->i, old_reverse->j);
//
//	printf("c-array: ");
//	for (int i = 0; i < strlen(alphabet); i++) {
//		printf("%d ", c_array[i]);
//	}
//	printf("\n");
//
//	printf("alphabet: ");
//	for (int i = 0; i < strlen(alphabet); i++) {
//		printf("%c ", alphabet[i]);
//	}
//	printf("\n");

	Interval* updated = malloc(sizeof(Interval));
	int i = old_reverse->i;
	int j = old_reverse->j;

	int char_index = get_char_index(c_array, alphabet, c);
	//printf("%c's index in c is %d\n", c, char_index);

	updated->i = i + char_index;

	updated->j = updated->i + (normal->j - normal->i);
	/**if(index_in_c == strlen(alphabet) - 1){
	 updated->j = j;
	 } else {
	 updated->j = c_array[index_in_c + 1] - 1;
	 }**/

	return updated;
}

/**
 * @brief Creates a substring struct from interval and length.
 * @param interval in normal BWT
 * @param interval in the BWT of the reverse of the string
 * @param length of substring
 *
 * @return pointer to a new substring struct
 */
substring* create_substring(Interval* normal, Interval* reverse, int length) {
	substring* new_substring = malloc(sizeof(substring));
	new_substring->normal = normal;
	new_substring->reverse = reverse;
	new_substring->length = length;
	return new_substring;
}

