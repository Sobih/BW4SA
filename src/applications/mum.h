/*
 * mum.h
 *
 *  Created on: 26.2.2014
 *      Author: lvapaaka
 */

#ifndef MUM_H_
#define MUM_H_

struct substring;
struct bit_vector;
struct wavelet_tree;
struct triplet;

/**
 * @brief	Initialization function for mums, so the callback can be done without having all BWTs as parameters.
 * @param	bwt1			The normal BWT of the first string
 * @param	bwt2			The normal BWT of the second string
 * @param	rbwt1			The BWT of the reverse of the first string
 * @param	rbwt2			The BWT of the reverse of the second string
 * @bug		No known bugs.
 */
void mum_initialize_bwts(struct wavelet_tree* bwt1, struct wavelet_tree* bwt2,
		struct wavelet_tree* rbwt1, struct wavelet_tree* rbwt2);

/**
 * @brief	Callback function given to double_iterate that determines if a substring is a MUM (Maximal Unique match)
 * @param	node1			The intervals of a substring in the first string
 * @param	node2			The intervals of a substring in the second string
 * @bug		Doesn't differentiate between the $-characters
 */
void search_mums(struct substring* node1, struct substring* node2);

/**
 * @brief	Return the list of found MUMs as a list of triplet structs.
 * @return	List of found MUMs
 * @bug		No known bugs.
 */
struct triplet* get_mums();

/**
 * @brief	Return the amount of MUMs found.
 * @return	The number of MUMs, i.e. the size of the list.
 * @bug		No known bugs.
 */
int get_mums_amount();

/**
 * @brief	Prints the indexes the MUM occurs in both strings and the substring itself.
 * @bug		No known bugs.
 */
void print_mums(char* string);

/**
 * @brief	Prints the bit vectors of the strings which show where MUMs occur.
 *
 * Every time a MUM is found, the BWT index of the MUM is marked on both strings' bit vectors.
 *
 * @bug		No known bugs.
 */
void mum_print_bit_vectors(char* string1, char* string2);

/**
 * @brief	Makes and returns a list of two bit vectors, corresponding to the given strings.
 *
 * Takes in a list of triplets where the positions have been updated to point to the original string.
 *
 * @param	mapped_mums		A triplet list where the indexes have been mapped to the original strings.
 * @return 	Bit vectors with starts of MUMs marked.
 *
 * @bug		No known bugs.
 */
struct bit_vector** mum_make_bit_vectors(struct triplet* mapped_mums);

#endif /* MUM_H_ */
