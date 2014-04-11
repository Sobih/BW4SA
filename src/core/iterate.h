/**
 * @file	iterate.h
 * @brief	The core of the entire library.
 *
 * This file contains all functions for iterating through strings and
 * collecting data on the strings.
 *
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator),
 * 			Paula Lehtola
 * @bug		No known bugs.
 */

#ifndef ITERATE_H_
#define ITERATE_H_

#define		MAX_REPEATS		0
#define		MUM				1
#define		MEM				2
#define		DOT_TREE		3

struct substring;
struct wavelet_tree;
struct bit_vector;
struct substring_stack;
struct alphabet_data;
struct interval;

typedef 	unsigned int	iterate_t;

typedef struct iterator_state {
	unsigned int num_strings;
	char current_extension;
	struct wavelet_tree* bwts;
	struct wavelet_tree* reverse_bwts;
	struct bit_vector* runs_vectors;
	struct bit_vector* reverse_runs_vectors;
	struct substring_stack* stacks;
	struct alphabet_data* alpha_datas;
	struct alphabet_data* common_alphabet;
	struct interval* normals, *reverses;
	struct substring* current, *prev;
	unsigned int** c_arrays;
} iterator_state;

typedef struct parameter_struct {
	iterate_t iterate_type;
	void (*callback) (iterator_state* state, void* results);
	void* ret_data;
	char** strings;
} parameter_struct;

iterator_state* initialize_iterator(char** strings, unsigned int num_strings);

void free_iterator_state(iterator_state* state);

void free_parameter_struct(parameter_struct* params);

iterator_state* iterate(parameter_struct* parameters);

/**
 * @brief 	A function for iterating through right maximal substrings of a string.
 *
 * Creates a BWT of a string and iterates through substrings of it. If the substring is right
 * maximal, the callback function given as parameter will be called on the substring.
 *
 * @param 	string 		C-string to be iterated over.
 * @param 	callback 	Function pointer to a callback function that is to be called on each
 * 						right maximal substring.
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void* single_iterate(iterator_state* state, void (*callback)(iterator_state* state, void* results),
		void* result);

/**
 * @brief	A function for simultaneously iterating over two strings.
 * @param	string1		The first c-string to be iterated over.
 * @param	string2		The second c-string to be iterated over.
 * @param	callback	The callback function to be called whenever matching substrings
 * 						inside both strings are found to be right maximal.
 * @see		#iterate
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void* double_iterate(iterator_state* state, void (*callback)(iterator_state* state, void* results),
		void* result);

#endif
