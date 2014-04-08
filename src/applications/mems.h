/*
 * mems.h
 *
 *  Created on: 3.4.2014
 *      Author: lvapaaka
 */

#ifndef MEMS_H_
#define MEMS_H_

struct substring;
struct bit_vector;
struct wavelet_tree;
struct alphabet_data;


/**
 * @brief	Initialization function for mems, so the callback can be done without having all BWTs as parameters.
 * @param	bwt1			The normal BWT of the first string
 * @param	bwt2			The normal BWT of the second string
 * @param	rbwt1			The BWT of the reverse of the first string
 * @param	rbwt2			The BWT of the reverse of the second string
 * @bug		No known bugs.
 */
void mem_initialize_bwts(struct wavelet_tree* bwt1, struct wavelet_tree* bwt2,
		struct wavelet_tree* rbwt1, struct wavelet_tree* rbwt2);

/**
 * @brief	Callback function given to double_iterate that determines if a substring is a MEM (Maximal Exact Match)
 * @param	node1			The intervals of a substring in the first string
 * @param	node2			The intervals of a substring in the second string
 * @bug		Doesn't differentiate between the $-characters
 */
void search_mems(struct substring* node1, struct substring* node2);

/**
 * @brief	Return the list of found MEMs as a list of triplet structs.
 * @return	List of found MEMs
 * @bug		No known bugs.
 */
struct triplet* get_mems();

/**
 * @brief	Return the amount of MEMs found.
 * @return	The number of MEMs, i.e. the size of the list.
 * @bug		No known bugs.
 */
int get_mems_amount();

/**
 * @brief	Prints the indexes the MUM occurs in both strings and the substring itself.
 * @bug		No known bugs.
 */
void print_mems(char* string);

#endif /* MEMS_H_ */
