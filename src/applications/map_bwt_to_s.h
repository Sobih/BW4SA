/**
 * @file	map_bwt_to_s.h
 * @brief	A function for mapping BWTs to suffix arrays.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef MAP_BWT_TO_S_H_
#define MAP_BWT_TO_S_H_

struct wavelet_tree;

/**
 * @brief	A function for mapping BWTs to suffix arrays.
 * @param	bwt		The BWT of a string, represented as a wavelet tree.
 * @return			A suffix array.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int* map_create_suffix_array_from_bwt(const struct wavelet_tree* bwt);

#endif /* MAP_BWT_TO_S_H_ */
