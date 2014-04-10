/**
 * @file	mum.h
 * @brief	A collection of functions for manipulating maximal unique matches (MUMs)
 * 			found during iteration.
 * @see		iterate.h
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef MUM_H_
#define MUM_H_

struct substring;
struct bit_vector;
struct wavelet_tree;
struct parameter_struct;
struct iterator_state;

typedef struct mum_results {
	triplet* data;
	unsigned int length;
	unsigned int allocated_length;
} mum_results;

/**
 * @brief	A simple structure for storing the starting indices of a MUM inside
 * 			two BWTs and the length of the MUM.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct triplet {
	unsigned int pos1;
	unsigned int pos2;
	unsigned int length;
} triplet;

struct parameter_struct* initialize_for_mums(char** strings);

/**
 * @brief	Callback function given to double_iterate that determines if a substring is a MUM.
 * @param	node1	The intervals of a substring in the first string.
 * @param	node2	The intervals of a substring in the second string.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		Doesn't differentiate between the $-characters.
 */
void search_mums(struct iterator_state* state, void* results);

/**
 * @brief	Prints the indexes of the MUM in both strings, as well as the substring itself,
 * 			to stdout.
 * @param	string	The string that is to be searched inside the MUM.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_mums(char* string, mum_results* results, struct iterator_state* state);

/**
 * @brief	Prints the bit vectors of the strings which show where MUMs occur to stdout.
 *
 * Every time a MUM is found, the BWT index of the MUM is marked on both strings' bit vectors.
 *
 * @param	string1	The first string for which a bit vector is to be printed.
 * @param	string2	The first string for which a bit vector is to be printed.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void mum_print_bit_vectors(char* string1, char* string2, mum_results* results, struct iterator_state* state);

/**
 * @brief	Creates a list of two bit vectors based on the given strings, where marked bits
 * 			correspond to starting indexes of MUM's inside the strings.
 *
 * Takes in a list of triplets where the positions have been updated to point to
 * the original string.
 *
 * @param	mapped_mums		A triplet list where the indexes have been mapped to the
 * 							original strings.
 * @return 					Bit vectors with starts of MUMs marked.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
struct bit_vector** mum_make_bit_vectors(mum_results* results, struct iterator_state* state);

#endif /* MUM_H_ */
