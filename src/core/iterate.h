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

/**
 * @brief	Unsigned int typedefed as the type of iterate that is to be performed.
 * @author	Max Sandberg (REXiator)
 */
typedef 	unsigned int	iterate_t;

/**
 * @brief	A structure for storing the internal state of an iterator.
 * @author	Max Sandberg (REXiator)
 */
typedef struct iterator_state {
	/**
	 * @brief	The number of strings that the iterator is iterating over.
	 */
	unsigned int num_strings;
	/**
	 * @brief	The current extension character in the iteration process.
	 */
	char current_extension;
	/**
	 * @brief	All BWT's used by this iterator.
	 */
	struct wavelet_tree* bwts;
	/**
	 * @brief	All BWT's of the reversed strings used by this iterator.
	 */
	struct wavelet_tree* reverse_bwts;
	/**
	 * @brief	All runs vectors used by this iterator.
	 */
	struct bit_vector* runs_vectors;
	/**
	 * @brief	All runs vectors of the reverse strings used by this iterator.
	 */
	struct bit_vector* reverse_runs_vectors;
	/**
	 * @brief	All substring stacks used by this iterator.
	 */
	struct substring_stack* stacks;
	/**
	 * @brief	Current alphabets over intervals inside the BWT's.
	 */
	struct alphabet_data* alpha_datas;
	/**
	 * @brief	The common alphabet shared by all strings. <code>NULL</code> if
	 * 			only one string.
	 */
	struct alphabet_data* common_alphabet;
	/**
	 * @brief	All the intervals on the BWT's that are used in this iteration by the
	 * 			iterator.
	 */
	struct interval* normals;
	/**
	 * @brief	All the intervals on the reverse BWT's that are used in this iteration
	 * 			by the iterator.
	 */
	struct interval* reverses;
	/**
	 * @brief	All the substrings that have been found in this iteration step.
	 */
	struct substring* current;
	/**
	 * @brief	All the substrings that have been found in the previous iteration step.
	 */
	struct substring* prev;
	/**
	 * @brief	All the c-arrays used by the iterator in this iteration.
	 */
	unsigned int** c_arrays;
	/**
	 * @brief	Length of the shortest string the callback function will process
	 */
	int threshold;

	/**
	 * A 128 bit vector represents the ASCII letters.
	 */
	struct alphabet_bit_vector* alpha_bit_vectors;

	struct alphabet_data* union_alphabet;

} iterator_state;

/**
 * @brief	A struct for storing the parameters given to iterate.
 * @author	Max Sandberg (REXiator)
 */
typedef struct parameter_struct {
	iterate_t iterate_type;
	void (*callback) (iterator_state* state, void* results);
	void* ret_data;
	char** strings;
	int threshold;
} parameter_struct;

/**
 * @brief	Initializes the iterator's internal state.
 * @param	strings		A list of pointers to strings that are to be iterated over.
 * @param	num_strings	The number of strings inside the list.
 * @return				An initialized <code>iterator_state</code>-pointer.
 * @see		#iterator_state
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
iterator_state* initialize_iterator(char** strings, unsigned int num_strings);

/**
 * @brief	Frees an <code>iterator_state</code>-structure and all it's resources.
 * @param	state	The structure to be freed.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void free_iterator_state(iterator_state* state);

/**
 * @brief	Frees a <code>parameter_struct</code>-structure and all it's resources,
 * 			except for the return data.
 * @param	params	The structure to be freed.
 * @author	Max Sandberg (REXiator)
 * @bug		Throws errors if strings have not been allocated on the heap.
 */
void free_parameter_struct(parameter_struct* params);

/**
 * @brief	The main iteration function.
 *
 * Determines what kind of iterate-function to call based on the parameters sent
 * to it. Should always be initialized using one of the initialization-functions
 * found in any of the files in the <code>applications</code>-folder.
 *
 * @param	parameters	The parameters used to determine what kind of iteration
 * 						to perform.
 * @return				The internal state of the iterator after the iteration
 * 						is done.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
iterator_state* iterate(parameter_struct* parameters);

/**
 * @brief 	A function for iterating through right maximal substrings of a string.
 *
 * Creates a BWT of a string and iterates through substrings of it. If the substring is right
 * maximal, the callback function given as parameter will be called on the substring.
 *
 * @param 	state 		The internal variables used by the iteration function.
 * @param 	callback 	Function pointer to a callback function that is to be called on each
 * 						right maximal substring.
 * @param	result		A pointer to a region of memory where the callback-function can
 * 						store its results.
 * @return				Returns a pointer to the results of the iteration process.
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void* single_iterate(iterator_state* state, void (*callback)(iterator_state* state, void* results),
		void* result);


void* single_iterate_test(iterator_state* state, void (*callback)(iterator_state* state, void* results),
		void* result, int kmerLength);
/**
 * @brief	A function for simultaneously iterating over two strings.
 * @param	state		The internal variables used by the iteration function.
 * @param	callback	The callback function to be called whenever matching substrings
 * 						inside both strings are found to be right maximal.
 * @param	result		A pointer to a region of memory where the callback-function can
 * 						store its results.
 * @return				Returns a pointer to the results of the iteration process.
 * @see		#iterate
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void* double_iterate(iterator_state* state, void (*callback)(iterator_state* state, void* results),
		void* result);

int is_interval_maximal(struct bit_vector* runs, struct interval* inter);

#endif
