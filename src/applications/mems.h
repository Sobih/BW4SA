/**
 * @file	mems.h
 * @brief	A collection of functions for finding Maximal Exact Matches (=MEMs) using iterate.
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef MEMS_H_
#define MEMS_H_


#include "../utils/structs.h"
#include "../core/iterate.h"

struct parameter_struct;
struct iterator_state;

/**
 * @brief	A structure for storing the results of an iteration when finding
 * 			maximal exact matches.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct mem_results {
	triplet* data;
	unsigned int length;
	unsigned int allocated_length;
	void* params;
} mem_results;

/**
 * @brief	An initialization function that creates a parameter struct that
 * 			instructs iterate to search for maximal exact matches.
 * @param	strings		An array of pointers to strings that are to be
 * 						iterated over.
 * @param	max_number_mems
 * 						Number of slots of memory allocated for triplets. This number has
 * 						to be at least as large as expected number of MEMs.
 * @return				An initialized parameter struct ready to be passed
 * 						to iterate.
 * @author	Max Sandberg (REXiator), Topi Paavilainen
 * @bug		No known bugs.
 */
struct parameter_struct* initialize_for_mems(char** strings, int max_number_mems);

/**
 * @brief	Callback function given to double_iterate that determines if a substring is a MEM (Maximal Exact Match)
 * @param	state		The internal state of the iterator.
 * @param	results		A pointer to a region of memory containing the previous results of
 * 						this callback function. Can safely be cast to <code>mem_results</code>
 * 						if iterate was initialized using <code>initialize_for_mems()</code>.
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void search_mems(struct iterator_state* state, void* results);

/**
 * @brief	Prints the indexes of the MEM in both strings, as well as the substring itself,
 * 			to stdout.
 * @param	string		The string that is to be searched inside the MEM.
 * @param	results		Results of the iteration over a set of strings.
 * @param	state		The internal state of the iterator that performed the search.
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_mems(char* string, mem_results* results, iterator_state* state);

/**
 * @brief	Creates a list of two bit vectors based on the given strings, where marked bits
 * 			correspond to starting indexes of MEM's inside the strings.
 *
 * @param	results		The results of an iteration over a set of strings.
 * @param	state		Internal state of the iterator that performed the search.
 * @return 				Bit vectors with starts of MEMs marked.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
struct bit_vector** mem_make_bit_vectors(mem_results* results, struct iterator_state* state);

#endif /* MEMS_H_ */
