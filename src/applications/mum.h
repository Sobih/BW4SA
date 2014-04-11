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
struct triplet;

/**
 * @brief	Initialization function for MUMs, so the callback can be done without having all BWTs as parameters.
 * @param	bwt1	The normal BWT of the first string.
 * @param	bwt2	The normal BWT of the second string.
 * @param	rbwt1	The BWT of the reverse of the first string.
 * @param	rbwt2	The BWT of the reverse of the second string.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void mum_initialize_bwts(struct wavelet_tree* bwt1, struct wavelet_tree* bwt2,
		struct wavelet_tree* rbwt1, struct wavelet_tree* rbwt2);

/**
 * @brief	Callback function given to double_iterate that determines if a substring is a MUM.
 * @param	node1	The intervals of a substring in the first string.
 * @param	node2	The intervals of a substring in the second string.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		Doesn't differentiate between the $-characters.
 */
void search_mums(struct substring* node1, struct substring* node2);

/**
 * @brief	Return the list of found MUMs as a list of triplet structs.
 * @return	List of found MUMs
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
struct triplet* get_mums();

/**
 * @brief	Returns the amount of MUMs found.
 * @return	The number of MUMs, i.e. the size of the list.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int get_mums_amount();

/**
 * @brief	Prints the indexes of the MUM in both strings, as well as the substring itself,
 * 			to stdout.
 * @param	string	The string that is to be searched inside the MUM.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_mums(char* string);

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
void mum_print_bit_vectors(char* string1, char* string2);

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
struct bit_vector** mum_make_bit_vectors(struct triplet* mapped_mums);

#endif /* MUM_H_ */
