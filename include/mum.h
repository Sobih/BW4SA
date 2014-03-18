/*
 * mum.h
 *
 *  Created on: 26.2.2014
 *      Author: lvapaaka
 */

#ifndef MUM_H_
#define MUM_H_

#include "iterate.h"

typedef struct triplet_struct {
	unsigned int pos1;
	unsigned int pos2;
	unsigned int length;
} triplet;

/**
 * @brief	Initialization function for mums, so the callback can be done without having all BWTs as parameters.
 * @param	bwt1			The normal BWT of the first string
 * @param	bwt2			The normal BWT of the second string
 * @param	rbwt1			The BWT of the reverse of the first string
 * @param	rbwt2			The BWT of the reverse of the second string
 * @bug		No known bugs.
 */
void mum_initialize_bwts(char* bwt1,char* bwt2, char* rbwt1, char* rbwt2);

/**
 * @brief	Callback function given to double_iterate that determines if a substring is a MUM (Maximal Unique match)
 * @param	node1			The intervals of a substring in the first string
 * @param	node2			The intervals of a substring in the second string
 * @bug		Doesn't differentiate between the $-characters
 */
void search_mums(substring* node1, substring* node2);

/**
 * @brief	Return the list of found MUMs as a list of triplet structs.
 * @return	List of found MUMs
 * @bug		No known bugs.
 */
triplet* get_mums();

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

#endif /* MUM_H_ */
