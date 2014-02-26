#include "../../include/bit_vector.h"
#include "../../include/iterate.h"
#include "../../include/rbwt.h"
#include "../../include/backward_search.h"
#include "../../include/c_array.h"
#include "../../include/utils.h"
#include "../../include/mum.h"
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

int is_reverse_interval_right_maximal(bit_vector* runs, Interval* interval) {
	if (interval->i >= interval->j)
		return 0;

	if (runs->rank_interval(runs, (interval->i) + 1, interval->j) > 0) {
		return 1;
	} else
		return 0;
}

Interval* update_reverse_interval(Interval* old_reverse, Interval* old_normal,
		Interval* normal, char* bwt, const char c);

substring* create_substring(Interval* normal, Interval* reverse, int length);

void iterate(char* string, void (*callback)(substring* substr)) {

	unsigned char* bwt = s_to_BWT(string);
	bit_vector* runs = create_runs_vector(string);

	substring_stack* stack = create_stack(10);

	//Initialise first intervals. In the start both intervals are the whole bwt
	Interval* normal = &((Interval ) { .i = 0, .j = strlen(bwt) - 1 } );
	Interval* reverse = &((Interval ) { .i = 0, .j = strlen(bwt) - 1 } );

	//create starting substring
	substring* start = &((substring ) { .normal = normal, .reverse = reverse,
					.length = 0 } );

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
			Interval* reverse = update_reverse_interval(substring->reverse,
					substring->normal, normal, bwt, alphabet[i]);

			if (is_reverse_interval_right_maximal(runs, reverse)) {
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
Interval* update_reverse_interval(Interval* old_reverse, Interval* old_normal,
		Interval* normal, char* bwt, const char c) {

	//create c-array and alphabet from the old normal-bwt interval
	char* alphabet = create_alphabet_interval(old_normal, bwt);
	int* c_array = create_c_array_interval(old_normal, bwt);

	//initialise new interval to be created
	Interval* updated = malloc(sizeof(Interval));
	int i = old_reverse->i;
	int j = old_reverse->j;

	int char_index = get_char_index(c_array, alphabet, c);

	updated->i = i + char_index;

	//length of the reverse interval is same as length of the normal interval
	updated->j = updated->i + (normal->j - normal->i);
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

void double_iterate(char* string1, char* string2,
		void (*callback)(substring* substr1, substring* substr2)) {

	unsigned char* bwt1 = s_to_BWT(string1);
	bit_vector* runs1 = create_runs_vector(string1);

	unsigned char* bwt2 = s_to_BWT(string2);
	bit_vector* runs2 = create_runs_vector(string2);

	mum_initialize_bwts(bwt1, bwt2, reverse_bwt(string1), reverse_bwt(string2));

	printf("%s %s %s %s \n", string1,bwt1,string2,bwt2);

	substring_stack* stack1 = create_stack(10);
	substring_stack* stack2 = create_stack(10);

	//stack1 = init_stack_with_substring(string1, bwt1, stack1);
	Interval* start_normal1 = &((Interval ) { .i = 0, .j = strlen(bwt1) - 1 } );
	Interval* start_reverse1 = &((Interval ) { .i = 0, .j = strlen(bwt1) - 1 } );

	//create starting substring
	substring* start1 = &((substring ) { .normal = start_normal1, .reverse = start_reverse1,
					.length = 0 } );

	push(stack1, start1);
	//stack2 = init_stack_with_substring(string2, bwt2, stack2);
	Interval* start_normal2 = &((Interval ) { .i = 0, .j = strlen(bwt2) - 1 } );
	Interval* start_reverse2 = &((Interval ) { .i = 0, .j = strlen(bwt2) - 1 } );

	//create starting substring
	substring* start2 = &((substring ) { .normal = start_normal2, .reverse = start_reverse2,
					.length = 0 } );

	push(stack2, start2);

	substring* new_substring1;
	substring* new_substring2;
	substring* substring1;
	substring* substring2;

	Interval* normal1;
	Interval* reverse1;
	Interval* normal2;
	Interval* reverse2;

	while (1) {
		substring1 = pop(stack1);
		substring2 = pop(stack2);

		if (substring1 == NULL) {
			break;
		}
		if (substring2 == NULL) {
			break;
		}
		// Determine characters that precede the interval

		char* alphabet1 = create_alphabet_interval(substring1->normal, bwt1);
		int* c_array1 = create_c_array_interval(substring1->normal, bwt1);

		char* alphabet2 = create_alphabet_interval(substring2->normal, bwt2);
		int* c_array2 = create_c_array_interval(substring2->normal, bwt2);

		// Determine common alphabet. Very unoptimized.
		char alphabets[strlen(alphabet1) + strlen(alphabet2)];
		strcpy(alphabets, alphabet1);
		strcat(alphabets, alphabet2);

		char* common_alphabet = determine_alphabet(alphabets);

		int i;
		for (i = 0; i < strlen(common_alphabet); i++) {
			if(common_alphabet[i] == '$'){
				continue;
			}
			normal1 = backward_search_interval(bwt1, substring1->normal,
					common_alphabet[i]);
			if (normal1 == NULL) {
				continue;
			}
			reverse1 = update_reverse_interval(substring1->reverse,
					substring1->normal, normal1, bwt1, common_alphabet[i]);

			normal2 = backward_search_interval(bwt2, substring2->normal,
					common_alphabet[i]);
			if (normal2 == NULL) {
				continue;
			}
			reverse2 = update_reverse_interval(substring2->reverse,
					substring2->normal, normal2, bwt2, common_alphabet[i]);

			new_substring1 = create_substring(normal1, reverse1,
					substring1->length + 1);
			new_substring2 = create_substring(normal2, reverse2,
					substring2->length + 1);
			// callback function pointers
			callback(new_substring1, new_substring2);
			push(stack1, new_substring1);
			push(stack2, new_substring2);
		}
	}
}
