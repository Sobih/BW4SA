/**
 * @file	utils.c
 * @brief	Implementation of the utility-algorithms.
 * @see		utils.h
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "utils.h"
#include "bit_vector.h"
#include "wavelet_tree.h"
#include "structs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief	Simple swap-function.
 *
 * Swaps the position of two entries in an array.
 *
 * @param	arr			Pointer to the array is to be manipulated.
 * @param	entry_size	Size of the entries that are to be swapped.
 * @param	i			Index of the first entry.
 * @param	j			Index of the second entry.
 * @see		utils.h#quick_sort
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void swap(void* arr, unsigned int entry_size, int i, int j, void* swap_area) {
	memcpy(swap_area, (arr + (j * entry_size)), entry_size);
    memcpy((arr + (j * entry_size)), (arr + (i * entry_size)), entry_size);
    memcpy((arr + (i * entry_size)), swap_area, entry_size);
}

/**
 * @brief	The implementation of the quicksort-algorithm.
 * @param	arr			Pointer to the array that is to be sorted.
 * @param	entry_size	Size of the individual entries in the array.
 * @param	a			Index to the first entry to be sorted.
 * @param	b			Index to the last entry to be sorted.
 * @see		utils.h#quick_sort
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void quicksort(void* arr, unsigned int entry_size, unsigned int a,
		unsigned int b, void* swap_area) {

    if (a >= b)
        return;

    void* key = (arr + (a * entry_size));
    int i = a + 1, j = b;

    while (i < j) {
        while (i < j && memcmp((arr + (j * entry_size)), key, entry_size) >= 0)
        	--j;

        while (i < j && memcmp((arr + (i * entry_size)), key, entry_size) <= 0)
        	++i;

        if (i < j)
            swap(arr, entry_size, i, j, swap_area);
    }

    if (memcmp((arr + (a * entry_size)), (arr + (i * entry_size)), entry_size) > 0) {
        swap(arr, entry_size, a, i, swap_area);
        quicksort(arr, entry_size, a, i - 1, swap_area);
        quicksort(arr, entry_size, i + 1, b, swap_area);
    }

    // there is no left-hand-side
    else
        quicksort(arr, entry_size, a + 1, b, swap_area);
}

void quick_sort(void* arr, unsigned int arr_size, unsigned int entry_size) {
	if (arr == 0 || arr_size == 0 || entry_size == 0)
		return;

	void* tmp = malloc(entry_size);
	quicksort(arr, entry_size, 0, arr_size - 1, tmp);
	free(tmp);
}

void print_bits(unsigned int mask) {
	unsigned int size = sizeof(unsigned int);
	unsigned int max_pow = 1 << (size * 8 - 1);

	for (int i = 0; i < size * 8; ++i) {
		// print last bit and shift left.
	    printf("%u", mask & max_pow ? 1 : 0);
	    mask = mask << 1;
	}
}

/**
 * @brief	Simple swap-function.
 *
 * Swaps the position of two strings in an array.
 *
 * @param	a	Pointer to a pointer to a string to be swapped.
 * @param	b	Pointer to a pointer to another string to be swapped.
 * @see		utils.h#string_quick_sort
 * @author	Paula Lehtola, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void string_swap(char** a, char** b) {
	char* tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * @brief	Quicksort for an array of strings.
 * @param	strings 	Array of pointers to strings.
 * @param	a			Index of the first entry to be sorted.
 * @param	b			index of the last entry to be sorted.
 * @see		utils.h#quick_sort
 * @author	Paula Lehtola, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void string_quicksort(char** strings, unsigned int a, unsigned int b) {
	if (a >= b)
		return;

	const char* key = strings[a];
	int i = a+1, j = b;

	while (i < j) {
		while (i < j && strcmp(strings[j], key) >= 0)
			j--;

		while (i < j && strcmp(strings[i], key) <= 0)
			i++;

		if (i < j)
			string_swap(strings+i, strings+j);
	}

	if (strcmp(strings[a],strings[i]) > 0) {
		string_swap(strings+a, strings+i);
		string_quicksort(strings, a, i-1);
		string_quicksort(strings, i+1, b);
	} else {
		string_quicksort(strings, a+1, b);
	}

}

void string_quick_sort(char **strings, unsigned int arr_size) {
	if (strings == 0 || arr_size == 0)
		return;

	string_quicksort(strings, 0, arr_size-1);

}

char* determine_alphabet(const char* string) {
	int chars_left = 10, alphabet_size = 0;
	unsigned int size = strlen(string);
	char* alphabet;

	if ((alphabet = calloc(chars_left, sizeof(char))) == 0)
		return 0;

	int exists;

	for (int i = 0; i < size; ++i) {
		exists = 0;

		for (int j = 0; j < alphabet_size; ++j) {
			//break if character already in alphabet
			if (strncmp(string + i, alphabet + j, 1) == 0) {
				exists = 1;
				break;
			}
		}

		//character doesn't exist in alphabet, insert it
		if (!exists) {

			if (chars_left == 0) {
				//expand alphabet array
				chars_left = 10;

				if ((alphabet = realloc(alphabet, alphabet_size + chars_left)) == 0)
					//realloc failed, return NULL
					return 0;
			}

			//add to alphabet
			chars_left--;
			alphabet[alphabet_size] = *(string + i);
			alphabet_size++;
		}
	}

	//add null-marker
	if (chars_left == 0)
		//expand alphabet array
		if ((alphabet = realloc(alphabet, alphabet_size + 1)) == 0)
			//realloc failed, return NULL
			return 0;

	//add to alphabet
	alphabet[alphabet_size] = 0;

	return alphabet;
}

int binary_search(const void* arr, const void* key, unsigned int entry_size,
		int max, int min) {

	//not viable indexes
	if (max < 0 || min < 0)
		return -1;

	//(sub)set empty
	if (max < min)
		return -1;

	//(sub)set has size 1
	if (max == min)
		return memcmp(arr + (min * entry_size), key, entry_size) == 0 ? min : -1;

	int mid = min + ((max - min) / 2), comparison = memcmp(arr + (mid * entry_size), key, entry_size);

	//key is in lower subset
	if (comparison > 0)
		return binary_search(arr, key, entry_size, mid - 1, min);

	//key is in upper subset
	if (comparison < 0)
		return binary_search(arr, key, entry_size, max, mid + 1);

	return mid;
}

void print_bit_vector(bit_vector* vector) {
	if (vector == 0) {
		printf("\t(NULL)\n");
		return;
	}

	printf("\tVector length: %u\n", vector->length);
	printf("\tVector bits: %u\n", vector->get_length(vector));

	for (int i = 0; i < vector->length; ++i) {
		printf("\t%u, ", vector->vector[i]);
		print_bits(vector->vector[i]);
		printf("\n");
	}

	printf("\tFiller bits: %u\n", vector->filler_bits);
}

void print_wavelet_node(wavelet_node* node) {
	if (node == 0)
		return;

	printf("\tBit vector:\n");
	if (&node->vector != 0)
		print_bit_vector(&node->vector);
	else
		printf("\t(NULL)\n");
	printf("\tString: %s\n", node->string);
	printf("\tAlphabet length: %u\n", node->alphabet_length);
	printf("\tAlphabet: ");

	for (int i = 0; i < node->alphabet_length; ++i)
		printf("%c", node->alphabet[i]);

	printf("\n");
}

void print_wavelet_tree(wavelet_tree* tree) {
	int counter = 1, j;
	wavelet_node** node_list = calloc(1, sizeof(wavelet_node*)), ** next;
	node_list[0] = &tree->nodes[0];

	for (int depth = 0; counter > 0; depth++) {
		next = calloc(2 * counter, sizeof(wavelet_node*));
		j = 0;

		printf("\n#################################################\n");
		printf("Nodes at depth %d\n\n", depth);

		for (int i = 0; i < counter; ++i) {
			print_wavelet_node(node_list[i]);
			printf("\n");

			//not leaf, add children for next round
			if (node_list[i]->children[0] > 0) {
				next[j] = &tree->nodes[node_list[i]->children[0]];
				next[j + 1] = &tree->nodes[node_list[i]->children[1]];
				j += 2;
			}
		}

		counter = j;

		free(node_list);
		node_list = next;

		printf("\n");
	}

	free(node_list);
}

char* substring_from_string(char* string, int position, int length) {
	char* pointer;
	int i;
	int pointer_index = 0;

	pointer = malloc(length + 1);

	for (i = position; i < position + length; i++) {
		pointer[pointer_index] = string[i];
		pointer_index++;
	}
	pointer[pointer_index] = '\0';

	return pointer;
}

bit_vector* create_runs_vector(const wavelet_tree* string, bit_vector* target) {
	if (target == 0)
		target = malloc(sizeof(bit_vector));

	unsigned int length = string->get_num_bits(string);
	init_bit_vector(target, length);

	target->mark_bit(target, 0);
	for (int i = 1; i < length; i++)
		if (string->char_at(string, i - 1) != string->char_at(string, i))
			target->mark_bit(target, i);
	target->compute_rank_support(target);
	return target;
}


substring* create_dummy_substring(substring* target) {
	if (target == 0){
		target = malloc(sizeof(substring));
		target->string=malloc(2);
	}

	target->normal.i = 0;
	target->normal.j = -1;

	target->reverse.i = 0;
	target->reverse.j = -1;
	target->length = 0;
//	target->string[0]='_';
//	target->string[1]='\0';
	target->string[0]='\0';
	return target;
}

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
interval* create_reverse_interval(interval* current_reverse, interval* new_normal, const unsigned int* c_array,
		int index_in_c_array, interval* target) {
	if (target == 0)
		target = malloc(sizeof(interval));
	int char_index = c_array[index_in_c_array];
	target->i = current_reverse->i + char_index;
	target->j = target->i + (new_normal->j - new_normal->i);
	return target;
}

interval* update_reverse_interval(interval* inter, interval* normal,
		const char* alphabet, unsigned int alphabet_length, const int* c_array,
		const char c, interval* target) {

	if (target == 0)
		target = malloc(sizeof(interval));

	int index_in_c_array = binary_search(alphabet, &c, sizeof(char),
			alphabet_length, 0);
	int char_index = c_array[index_in_c_array];

	target->i = inter->i + char_index;
//	printf("Char=%c , Index in C_array=%i ,value=%i  ,FWD interval=[%i,%i]\n", c,index_in_c_array, char_index,inter->i ,inter->j );

	//length of the reverse interval is same as length of the normal interval
	int normal_j = normal->j;
	int normal_i = normal->i;

	int new_j = target->i + (normal_j - normal_i);
	target->j = new_j;
	return target;
}


void printBinary(unsigned int* input, int length){
	int INT_BITS=sizeof(int)*8;
	if(length==0)
			return ;
	int size=length*INT_BITS;
	unsigned char* binary=malloc(size+1);
	int i=0;
	int shift=INT_BITS;
	for(i=0;i<length;i++){
		int j=0;
		int c=input[i];
		for(j=0;j<INT_BITS;j++){
			int binaryIdx=(i*INT_BITS)+j;
			binary[binaryIdx]=((c>>shift++%INT_BITS)&1)==1 ?'1':'0';
		}
	}
	binary[size]='\0';
	printf("Binary is %s\n",binary);
}
