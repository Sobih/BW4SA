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
#include "substring_stack.h"
#include "s_to_bwt.h"
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

void* single_iterate(iterator_state* state, void (*callback)(iterator_state* state, void* results),
		void* result) {
	wavelet_tree* bwt = &state->bwts[0], *reverse_bwt = &state->reverse_bwts[0];
	bit_vector* reverse_runs = &state->reverse_runs_vectors[0];
	substring_stack* stack = &state->stacks[0];
	unsigned int* c_array = state->c_arrays[0];
	interval* normal = &state->normals[0], *reverse = &state->reverses[0];
	alphabet_data* alpha_data = &state->alpha_datas[0];

	int bwt_length = bwt->get_num_bits(bwt), i;

	//Initialize first intervals. In the start both intervals are the whole bwt
	normal->i = 0;
	normal->j = bwt_length - 1;
	reverse->i = 0;
	reverse->j = bwt_length - 1;

	//create starting substring
	substring* substr = create_substring(normal, reverse, 0, 0);
	substring* temp, *new_substring = state->current;

	//printf("Variables initialized, commencing iteration\n");

	while (1) {
		if (substr == NULL)
			break;

		//if size of the interval is 1, it cannot be a right-maximal string
		//if(substr->normal->i == substring->normal->j) continue;

		// Determine characters that precede the interval
		alpha_data = create_alphabet_interval(&substr->normal, bwt, alpha_data);

		//printf("Created alphabet interval\n");

		c_array = create_c_array(bwt, &substr->normal, 0, 0, c_array);

		//printf("Created C-array\n");

		for (i = 0; i < alpha_data->length; i++) {
			state->current_extension = alpha_data->alphabet[i];

			normal = backward_search_interval(bwt, &substr->normal,
					state->current_extension, normal);

			//printf("Updated normal interval\n");

			reverse = update_reverse_interval(&substr->reverse, normal,
					alpha_data->alphabet, alpha_data->length, c_array,
					state->current_extension, reverse);

			//printf("Updated reverse interval\n");

			//printf("Alphabet length: %d\n", alpha_data->length);

			if (is_reverse_interval_right_maximal(reverse_runs, reverse)) {
				//printf("Found right maximal\n");

				new_substring = create_substring(normal, reverse, substr->length + 1,
						new_substring);

				/*printf("New substring:\n");
				printf("\tNormal: %d.%d\n", normal->i, normal->j);
				printf("\tReverse: %d.%d\n", reverse->i, reverse->j);
				printf("\tLength: %d\n", new_substring->length);*/

				// callback function pointers
				callback(state, result);
				push(stack, new_substring);

				//printf("Callbacked and pushed\n");

				state->prev = create_substring(&new_substring->normal, &new_substring->reverse,
						new_substring->length, state->prev);

				//printf("Updated as prev in state\n");
			}
		}

		temp = pop(stack);

		if (temp == NULL)
			break;

		substr = create_substring(&temp->normal, &temp->reverse, temp->length,
				substr);

		//printf("New substring popped\n");
	}

	free(substr);

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
	bit_vector* rev_runs1 = &state->reverse_runs_vectors[0], *rev_runs2 = &state->reverse_runs_vectors[1];
	substring_stack* stack1 = &state->stacks[0], *stack2 = &state->stacks[1];
	unsigned int* c_array1 = state->c_arrays[0], *c_array2 = state->c_arrays[1];
	interval* normal1 = &state->normals[0], *normal2 = &state->normals[1];
	interval* reverse1 = &state->reverses[0], *reverse2 = &state->reverses[1];
	alphabet_data* alpha_data1 = &state->alpha_datas[0], *alpha_data2 = &state->alpha_datas[1];
	alphabet_data* common_alphabet = state->common_alphabet;

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

			create_substring(&new_substring1->normal, &new_substring1->reverse,
					new_substring1->length, &state->prev[0]);

			create_substring(&new_substring2->normal, &new_substring2->reverse,
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

	free(substring1);
	free(substring2);

	return result;
}

iterator_state* initialize_iterator(char** strings, unsigned int num_strings) {
	iterator_state* state = malloc(sizeof(iterator_state));

	state->num_strings = num_strings;
	state->bwts = malloc(num_strings * sizeof(wavelet_tree));
	state->reverse_bwts = malloc(num_strings * sizeof(wavelet_tree));
	state->runs_vectors = malloc(num_strings * sizeof(bit_vector));
	state->reverse_runs_vectors = malloc(num_strings * sizeof(bit_vector));
	state->stacks = malloc(num_strings * sizeof(substring_stack));
	state->alpha_datas = malloc(num_strings * sizeof(alphabet_data));
	state->normals = malloc(num_strings * sizeof(interval));
	state->reverses = malloc(num_strings * sizeof(interval));
	state->current = malloc(num_strings * sizeof(substring));
	state->prev = malloc(num_strings * sizeof(substring));
	state->c_arrays = malloc(num_strings * sizeof(unsigned int*));

	unsigned int common_alpha_length = 1;

	wavelet_tree* tree;
	bit_vector* vector;
	substring_stack* stack;

	for (int i = 0; i < num_strings; ++i) {
		state->alpha_datas[i].alphabet = 0;

		tree = s_to_bwt(strings[i]);
		memcpy(&state->bwts[i], tree, sizeof(wavelet_tree));
		free(tree);

		tree = reverse_bwt(strings[i]);
		memcpy(&state->reverse_bwts[i], tree, sizeof(wavelet_tree));
		free(tree);

		vector = create_runs_vector(&state->bwts[i], 0);
		memcpy(&state->runs_vectors[i], vector, sizeof(bit_vector));
		free(vector);

		vector = create_runs_vector(&state->reverse_bwts[i], 0);
		memcpy(&state->reverse_runs_vectors[i], vector, sizeof(bit_vector));
		free(vector);

		stack = create_stack(10);
		memcpy(&state->stacks[i], stack, sizeof(substring_stack));
		free(stack);

		state->c_arrays[i] = malloc((state->bwts->get_alphabet_length(&state->bwts[i]) + 1) *
				sizeof(unsigned int));

		common_alpha_length += state->bwts->get_alphabet_length(&state->bwts[i]);
	}

	if (num_strings > 1) {
		state->common_alphabet = malloc(sizeof(alphabet_data));
		state->common_alphabet->alphabet = malloc(common_alpha_length * sizeof(char));
	}
	else
		state->common_alphabet = 0;

	/*printf("State initialized:\n");
	printf("\tNum strings: %u\n", state->num_strings);
	printf("\tBwts:");
	for (int i = 0; i < num_strings; ++i) {
		printf(" ");

		for (int j = 0; j < state->bwts[i].get_num_bits(&state->bwts[i]); ++j)
			printf("%c", state->bwts[i].char_at(&state->bwts[i], j));
	}
	printf("\n\tReverse bwts:");
	for (int i = 0; i < num_strings; ++i) {
		printf(" ");

		for (int j = 0; j < state->reverse_bwts[i].get_num_bits(&state->reverse_bwts[i]); ++j)
			printf("%c", state->reverse_bwts[i].char_at(&state->reverse_bwts[i], j));
	}
	printf("\n\tRuns vectors:\n");
	for (int i = 0; i < num_strings; ++i)
		print_bit_vector(&state->runs_vectors[i]);*/

	return state;
}

void free_parameter_struct(parameter_struct* params) {
	free(params->ret_data);

	switch (params->iterate_type) {
	case MUM: //do the same as for MEM
	case MEM:
		free(params->strings[0]);
		free(params->strings[1]);
		break;
	case DOT_TREE: //do the same as for MAX_REPEATS
	case MAX_REPEATS: //do the same as default
	default:
		//free(params->strings[0]);
		break;
	}

	free(params->strings);
}

void free_iterator_state(iterator_state* state) {
	for (int i = 0; i < state->num_strings; ++i) {
		free_wavelet_tree_internals(&state->bwts[i]);
		free_wavelet_tree_internals(&state->reverse_bwts[i]);
		free(state->stacks[i].array);
		free(state->runs_vectors[i].vector);
		free(state->reverse_runs_vectors[i].vector);
		free(state->alpha_datas[i].alphabet);
		free(state->c_arrays[i]);
	}

	free(state->normals);
	free(state->reverses);
	free(state->current);
	free(state->prev);
	free(state->alpha_datas);
	free(state->c_arrays);
	free(state->common_alphabet);
	free(state->stacks);
	free(state->runs_vectors);
	free(state->reverse_runs_vectors);
	free(state->bwts);
	free(state->reverse_bwts);

	free(state);
}

iterator_state* iterate(parameter_struct* parameters) {
	if (parameters == 0 ||
			parameters->callback == 0 ||
			parameters->strings == 0)
		return 0;

	iterator_state* state;

	switch (parameters->iterate_type) {
	case MUM: //do the same as for mem
	case MEM:
		//initialize iterator state for using double iterate
		state = initialize_iterator(parameters->strings, 2);
		state->threshold = parameters->threshold;

		parameters->ret_data = double_iterate(state, parameters->callback, parameters->ret_data);

		//free all resources
		/*free_wavelet_tree(&state->bwts[0]);
		free_wavelet_tree(&state->bwts[1]);

		free_wavelet_tree(&state->reverse_bwts[0]);
		free_wavelet_tree(&state->reverse_bwts[1]);

		free_bit_vector(&state->runs_vectors[0]);
		free_bit_vector(&state->runs_vectors[1]);

		free_stack(&state->stacks[0]);
		free_stack(&state->stacks[1]);

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
		//initialize iterator state for using single iterate
		state = initialize_iterator(parameters->strings, 1);
		state->threshold = parameters->threshold;
		parameters->ret_data = single_iterate(state, parameters->callback, parameters->ret_data);

		//free all resources
		/*free_wavelet_tree(state->bwts);
		free_wavelet_tree(state->reverse_bwts);
		free_bit_vector(state->runs_vectors);
		free_stack(state->stacks);
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
