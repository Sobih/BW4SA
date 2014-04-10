/**
 * @file	iterate.c
 * @brief	Implementation of the core of the library.
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator),
 * 			Paula Lehtola
 * @bug		No known bugs.
 */

#include "iterate.h"
#include "backward_search.h"
#include "rbwt.h"
#include "c_array.h"
#include "s_to_bwt.h"
#include "substring_stack.h"
#include "../../include/utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define END_STRING '$'

/**
 * @brief 	A function that determines if given interval in given reverse BWT is right maximal.
 * @param 	runs	Runs-vector of a reverse BWT.
 * @param 	inter 	The interval that is to be checked.
 * @return 			<code>1</code> if the interval is right maximal, <code>0</code> otherwise.
 * @author 	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug 	No known bugs.
 */
int is_reverse_interval_right_maximal(bit_vector* runs,
		interval* inter) {
	return runs->rank(runs, (inter->i) + 1, inter->j) > 0 ? 1 : 0;
}

/**
 * @brief	Updates the interval in the BWT of the reverse of the string
 * @param	inter			The current interval in the reverse BWT.
 * @param	normal			The current interval in the normal BWT.
 * @param	alphabet		The alphabet used by both BWT's.
 * @param	alphabet_length	The length of the alphabet.
 * @param	c_array			The c-array used in the interval of the BWT's.
 * @param	c				The current extension character.
 * @param	target			The structure in which the results should be stored.
 * 							If <code>NULL</code>, a new structure will be allocated
 * 							and returned.
 * @return 					An updated interval-struct of the BWT of the
 * 							reverse of the string.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
interval* update_reverse_interval(interval* inter, interval* normal,
		const char* alphabet, unsigned int alphabet_length, const int* c_array,
		const char c, interval* target) {

	if (target == 0)
		target = malloc(sizeof(interval));

	int index_in_c_array = binary_search(alphabet, &c, sizeof(char),
			alphabet_length, 0);
	int char_index = c_array[index_in_c_array];
	target->i = inter->i + char_index;

	//length of the reverse interval is same as length of the normal interval
	int normal_j = normal->j;
	int normal_i = normal->i;

	int new_j = target->i + (normal_j - normal_i);
	target->j = new_j;
	return target;
}

/**
 * @brief 	Creates a substring-struct from the parameters.
 * @param 	normal 	The interval of the substring in the normal BWT.
 * @param 	reverse The interval of the substring in the BWT of the reverse
 * 					of the string.
 * @param 	length 	Length of the substring.
 * @param	target	The structure in which the data should be stored. If
 * 					<code>NULL</code>, a new struct will be allocated and
 * 					returned.
 * @return			A pointer to an initialized substring-struct.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
substring* create_substring(interval* normal, interval* reverse, int length,
		substring* target) {
	if (target == 0)
		target = malloc(sizeof(substring));

	int normal_i = normal->i;
	int normal_j = normal->j;

	target->normal.i = normal_i;
	target->normal.j = normal_j;

	target->reverse.i = reverse->i;
	target->reverse.j = reverse->j;

	target->length = length;

	return target;
}

void* single_iterate(iterator_state* state, void (*callback)(iterator_state* state, void* results),
		void* result) {
	wavelet_tree* bwt = state->bwts, *reverse_bwt = state->reverse_bwts;
	bit_vector* reverse_runs = state->runs_vectors;
	substring_stack* stack = state->stacks;
	unsigned int* c_array = state->c_arrays[0];
	interval* normal = state->normals, *reverse = state->reverses;
	alphabet_data* alpha_data = state->alpha_datas;

	int bwt_length = bwt->get_num_bits(bwt), i;

	//Initialize first intervals. In the start both intervals are the whole bwt
	normal.i = 0;
	normal.j = bwt_length - 1;
	reverse.i = 0;
	reverse.j = bwt_length - 1;

	//create starting substring
	substring* substr = create_substring(normal, reverse, 0, 0);
	substring* temp, *new_substring = state->current;

	while (1) {
		if (substr == NULL)
			break;

		//if size of the interval is 1, it cannot be a right-maximal string
		//if(substr->normal->i == substring->normal->j) continue;

		// Determine characters that precede the interval
		alpha_data = create_alphabet_interval(&substr->normal, bwt, alpha_data);

		c_array = create_c_array(bwt, &substr->normal, 0, 0, c_array);

		for (i = 0; i < alpha_data->length; i++) {
			state->current_extension = alpha_data->alphabet[i];

			normal = backward_search_interval(bwt, &substr->normal,
					state->current_extension, normal);

			reverse = update_reverse_interval(&substr->reverse, normal,
					alpha_data->alphabet, alpha_data->length, c_array,
					state->current_extension, reverse);

			if (is_reverse_interval_right_maximal(reverse_runs, reverse)) {
				new_substring = create_substring(normal, reverse, substr->length + 1,
						new_substring);

				// callback function pointers
				callback(state, result);
				push(stack, new_substring);

				state->prev = create_substring(new_substring->normal, new_substring->reverse,
						new_substring->length, state->prev);
			}
		}

		temp = pop(stack);

		if (temp == NULL)
			break;

		substr = create_substring(&temp->normal, &temp->reverse, temp->length,
				substr);
	}

	return result;
}

/**
 * @brief	Combines the intersection of the two alphabets into one common alphabet.
 * @param	alpha_data1		The data for the first alphabet.
 * @param	alpha_data2		The data for the second alphabet.
 * @param	common_alphabet	The c-string where the result should be stored.
 * @return					The intersection of the combined alphabets.
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
alphabet_data* combine_alphabets_intersection(alphabet_data* alpha_data1,
		alphabet_data* alpha_data2, alphabet_data* common_alphabet_data) {
	char* alphabet1 = alpha_data1->alphabet;
	char* alphabet2 = alpha_data2->alphabet;
	char* common_alphabet = common_alphabet_data->alphabet;
	int index1 = 0;
	int index2 = 0;
	int common_index = 0;
	if (alphabet1[index1] == END_STRING) {
		index1++;
	}
	if (alphabet2[index2] == END_STRING) {
		index2++;
	}
	while (index1 < alpha_data1->length && index2 < alpha_data2->length) {
		if (alphabet1[index1] == alphabet2[index2]) {
			common_alphabet[common_index] = alphabet1[index1];
			common_index++;
			index1++;
			index2++;
		} else if (alphabet1[index1] > alphabet2[index2]) {
			index2++;
		} else if (alphabet1[index1] < alphabet2[index2]) {
			index1++;
		} else {
			printf("THE IMPOSSIBLR HAPPENED");
		}
	}
	common_alphabet[common_index] = '\0';

	common_alphabet_data->alphabet = common_alphabet;
	common_alphabet_data->length = common_index;

	return common_alphabet_data;
}

void* double_iterate(iterator_state* state, void (*callback)(iterator_state* state, void* results),
		void* result) {

	wavelet_tree* bwt1 = &state->bwts[0], *bwt2 = &state->bwts[1];
	wavelet_tree* rev_bwt1 = &state->reverse_bwts[0], *rev_bwt2 = &state->reverse_bwts[1];
	bit_vector* rev_runs1 = &state->runs_vectors[0], *rev_runs2 = &state->runs_vectors[1];
	substring_stack* stack1 = &state->stacks[0], *stack2 = &state->stacks[1];
	unsigned int* c_array1 = state->c_arrays[0], *c_array2 = state->c_arrays[1];
	interval* normal1 = &state->normals[0], *normal2 = &state->normals[1];
	interval* reverse1 = &state->reverses[0], *reverse2 = &state->reverses[1];
	alphabet_data* alpha_data1 = &state->alpha_datas[0], *alpha_data2 = &state->alpha_datas[1];
	alphabet_data* common_alphabet = state->common_alphabets;

	int bwt_length1 = bwt1->get_num_bits(bwt1), bwt_length2 = bwt2->get_num_bits(bwt2), i;

	//Initialize first intervals. In the start both intervals are the whole bwt
	normal1->i = 0;
	normal1->j = bwt_length1 - 1;
	reverse1->i = 0;
	reverse1->j = bwt_length1 - 1;

	normal2->i = 0;
	normal2->j = bwt_length2 - 1;
	reverse2->i = 0;
	reverse2->j = bwt_length2 - 1;

	//create starting substring
	substring* new_substring1 = &state->current[0], *substring1 = create_substring(normal1,
			reverse1, 0, 0);

	substring* new_substring2 = &state->current[1], *substring2 = create_substring(normal2,
			reverse2, 0, 0);

	substring* temp;

	while (1) {
		//if size of the interval is 1, it cannot be a right-maximal string
		//if(substring->normal->i == substring->normal->j) continue;

		// Determine characters that precede the interval
		alpha_data1 = create_alphabet_interval(&substring1->normal, bwt1,
				alpha_data1);
		alpha_data2 = create_alphabet_interval(&substring2->normal, bwt2,
				alpha_data2);

		c_array1 = create_c_array(bwt1, &substring1->normal, 0, 0, c_array1);
		c_array2 = create_c_array(bwt2, &substring2->normal, 0, 0, c_array2);

		common_alphabet = combine_alphabets_intersection(alpha_data1,
				alpha_data2, common_alphabet);

		for (i = 0; i < common_alphabet->length; i++) {
			state->current_extension = common_alphabet->alphabet[i];

			//print_node(substring1->normal);
			//printf("letter added to the left: %c \n", common_alphabet[i]);
			normal1 = backward_search_interval(bwt1, &substring1->normal,
					state->current_extension, normal1);

			if (normal1 == NULL)
				continue;

			//print_node(substring2->normal);
			normal2 = backward_search_interval(bwt2, &substring2->normal,
					state->current_extension, normal2);

			if (normal2 == NULL)
				continue;

			reverse1 = update_reverse_interval(&substring1->reverse, normal1,
					alpha_data1->alphabet, alpha_data1->length, c_array1,
					state->current_extension, reverse1);

			reverse2 = update_reverse_interval(&substring2->reverse, normal2,
					alpha_data2->alphabet, alpha_data2->length, c_array2,
					state->current_extension, reverse2);

			new_substring1 = create_substring(normal1, reverse1,
					substring1->length + 1, new_substring1);

			new_substring2 = create_substring(normal2, reverse2,
					substring2->length + 1, new_substring2);

			// callback function pointers
			callback(state, result);

			push(stack1, new_substring1);
			push(stack2, new_substring2);

			create_substring(new_substring1->normal, new_substring1->reverse,
					new_substring1->length, &state->prev[0]);

			create_substring(new_substring2->normal, new_substring2->reverse,
					new_substring2->length, &state->prev[1]);
		}

		temp = pop(stack1);

		if (temp == NULL)
			break;

		substring1 = create_substring(&temp->normal, &temp->reverse,
				temp->length, substring1);

		temp = pop(stack2);

		if (temp == NULL)
			break;

		substring2 = create_substring(&temp->normal, &temp->reverse,
				temp->length, substring2);
	}

	return result;
}

iterator_state* iterate(parameter_struct* parameters) {
	if (parameters == 0 ||
			parameters->callback == 0 ||
			parameters->strings == 0)
		return 0;

	iterator_state* state = malloc(sizeof(iterator_state));

	switch (parameters->iterate_type) {
	case MUM: //do the same as for mem
	case MEM:
		//initialize iterator state
		state->bwts = malloc(2 * sizeof(wavelet_tree));
		state->bwts[0] = *s_to_BWT(parameters->strings[0]);
		state->bwts[1] = *s_to_BWT(parameters->strings[1]);

		state->reverse_bwts = malloc(2 * sizeof(wavelet_tree));
		state->reverse_bwts[0] = *reverse_bwt(parameters->strings[0]);
		state->reverse_bwts[1] = *reverse_bwt(parameters->strings[1]);

		state->runs_vectors = malloc(2 * sizeof(bit_vector));
		state->runs_vectors[0] = *create_runs_vector(&state->reverse_bwts[0], 0);
		state->runs_vectors[1] = *create_runs_vector(&state->reverse_bwts[1], 0);

		state->stacks = malloc(2 * sizeof(substring_stack));
		state->stacks[0] = *create_stack(10);
		state->stacks[1] = *create_stack(10);

		int length = state->bwts->get_alphabet_length(state->bwts) + 1;
		state->c_arrays = malloc(2 * sizeof(unsigned int*));
		state->c_arrays[0] = malloc(length * sizeof(unsigned int));
		state->c_arrays[1] = malloc(length * sizeof(unsigned int));

		state->common_alphabets = malloc(sizeof(alphabet_data));
		state->common_alphabets->alphabet = malloc((state->bwts[0].get_alphabet_length(&state->bwts[0]) +
				state->bwts[1].get_alphabet_length(&state->bwts[1]) + 1) * sizeof(char));

		state->alpha_datas = malloc(2 * sizeof(alphabet_data));
		state->normals = malloc(2 * sizeof(interval));
		state->reverses = malloc(2 * sizeof(interval));
		state->current = malloc(2 * sizeof(substring));
		state->prev = malloc(2 * sizeof(substring));

		parameters->ret_data = double_iterate(state, parameters->callback, parameters->ret_data);

		//free all resources
		/*free_wavelet_tree(&state->bwts[0]);
		free_wavelet_tree(&state->bwts[1]);

		free_wavelet_tree(&state->reverse_bwts[0]);
		free_wavelet_tree(&state->reverse_bwts[1]);

		free_bit_vector(&state->runs_vectors[0]);
		free_bit_vector(&state->runs_vectors[1]);

		free_substring_stack(&state->stacks[0]);
		free_substring_stack(&state->stacks[1]);

		free(state->normals);
		free(state->reverses);
		free(state->current);
		free(state->prev);
		free(state->alpha_datas[0]->alphabet);
		free(state->alpha_datas[1]->alphabet);
		free(state->alpha_datas[0]);
		free(state->alpha_datas[1]);
		free(state->c_arrays[0]);
		free(state->c_arrays[1]);
		free(state->c_arrays);
		free(state->common_alphabets[0]);
		free(state->common_alphabets);*/

		break;
	case DOT_TREE: //do the same as for max repeats
	case MAX_REPEATS: //do the same as default
	default:
		//initialize iterator state
		state->bwts = s_to_BWT(parameters->strings[0]);
		state->reverse_bwts = reverse_bwt(parameters->strings[0]);
		state->runs_vectors = create_runs_vector(state->reverse_bwts, 0);
		state->stacks = create_stack(10);
		state->alpha_datas = malloc(sizeof(alphabet_data));
		state->normals = malloc(sizeof(interval));
		state->reverses = malloc(sizeof(interval));
		state->current = malloc(sizeof(substring));
		state->prev = malloc(sizeof(substring));
		state->c_arrays = malloc(sizeof(unsigned int*));
		state->c_arrays[0] = malloc((state->bwts->get_alphabet_length(state->bwts) + 1) *
						sizeof(unsigned int));

		state->common_alphabets = 0;

		parameters->ret_data = single_iterate(state, parameters->callback, parameters->ret_data);

		//free all resources
		/*free_wavelet_tree(state->bwts);
		free_wavelet_tree(state->reverse_bwts);
		free_bit_vector(state->runs_vectors);
		free_substring_stack(state->stacks);
		free(state->normals);
		free(state->reverses);
		free(state->current);
		free(state->prev);
		free(state->c_arrays);
		free(state->alpha_datas->alphabet);
		free(state->alpha_datas);*/

		break;
	}

	//free(state);

	return state;
}
