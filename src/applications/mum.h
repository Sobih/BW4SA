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

struct bit_vector;
struct parameter_struct;
struct iterator_state;
struct triplet;

/**
 * @brief	A structure for storing the results of an iteration when finding
 * 			maximal unique matches.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct mum_results {
	triplet* data;
	unsigned int length;
	unsigned int allocated_length;
} mum_results;

/**
 * @brief	An initialization function that creates a parameter struct that
 * 			instructs iterate to search for maximal unique matches.
 * @param	strings		An array of pointers to strings that are to be
 * 						iterated over.
 * @return				An initialized parameter struct ready to be passed
 * 						to iterate.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
struct parameter_struct* initialize_for_mums(char** strings);

/**
 * @brief	Callback function given to double_iterate that determines if a substring is a MUM.
 * @param	state		The internal state of the iterator.
 * @param	results		A pointer to a region of memory containing the previous results of
 * 						this callback function. Can safely be cast to <code>mum_results</code>
 * 						if iterate was initialized using <code>initialize_for_mums()</code>.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		Doesn't differentiate between the $-characters.
 */
void search_mums(struct iterator_state* state, void* results);

/**
 * @brief	Prints the indexes of the MUM in both strings, as well as the substring itself,
 * 			to stdout.
 * @param	string		The string that is to be searched inside the MUM.
 * @param	results		Results of the iteration over a set of strings.
 * @param	state		The internal state of the iterator that performed the search.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_mums(char* string, mum_results* results, struct iterator_state* state);

/**
 * @brief	Prints the bit vectors of the strings which show where MUMs occur to stdout.
 *
 * Every time a MUM is found, the BWT index of the MUM is marked on both strings' bit vectors.
 *
 * @param	string1		The first string for which a bit vector is to be printed.
 * @param	string2		The first string for which a bit vector is to be printed.
 * @param	results		The results of the iteration over the two strings.
 * @param	state		Internal state of the iterator that performed the search.
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
 * @param	results		The results of an iteration over a set of strings.
 * @param	state		Internal state of the iterator that performed the search.
 * @return 				Bit vectors with starts of MUMs marked.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
struct bit_vector** mum_make_bit_vectors(mum_results* results, struct iterator_state* state);

#endif /* MUM_H_ */
