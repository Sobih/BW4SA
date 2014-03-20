/**
 * @file	wavelet_tree.h
 * @brief	An implementation of a standard wavelet tree-structure.
 *
 * This file contains the implementation of a standard wavelet tree-
 * structure. A wavelet tree allows for better compression of strings
 * and better performance on rank-queries (~ O (log n), n = size of
 * alphabet), and thus much improved performance for the program
 * overall.
 *
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef WAVELET_TREE_H_
#define WAVELET_TREE_H_

#include "bit_vector.h"

/**
 * @brief	A simple struct for storing a node of a wavelet tree.
 *
 * This struct stores all the necessary data of a node inside a
 * wavelet tree, including the bit vector, the alphabet used and
 * locations of its children (if any).
 *
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct wavelet_node {
	char* string;
	bit_vector vector;
	char* alphabet;
	unsigned int alphabet_length;
	unsigned int children[2];
} wavelet_node;

/**
 * @brief	A struct for storing a wavelet tree.
 *
 * This structure stores all the nodes of a wavelet tree, as well
 * as function pointers to operations possible on the tree. Such
 * operations include length of the root node, rank and char at.
 *
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct wavelet_tree {
	unsigned int (*get_num_bits) (const struct wavelet_tree* tree);
	unsigned int (*get_alphabet_length) (const struct wavelet_tree* tree);
	int (*rank) (const struct wavelet_tree* node, char c, int start, int end);
	char (*char_at) (const struct wavelet_tree* node, int index);

	unsigned int num_nodes;
	wavelet_node* nodes;
} wavelet_tree;

/**
 * @brief	An algorithm that creates a wavelet tree from a string.
 *
 * This algorithm recursively creates a wavelet tree from the string
 * supplied as parameter.
 *
 * @param	string	The string of characters from which a wavelet
 * 					tree is to be constructed.
 * @return			A structure containing the wavelet tree, or
 * 					NULL if the string is uninitialized.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
wavelet_tree* create_wavelet_tree(const char* string);

/**
 * @brief	Frees the memory used by an entire wavelet tree.
 *
 * This algorithm frees an entire wavelet tree. It also frees
 * the alphabet used by the wavelet tree, but leaves the
 * original string from which the tree was created intact.
 *
 * @param	tree	The wavelet tree to be freed.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void free_wavelet_tree(wavelet_tree* tree);

#endif /* WAVELET_TREE_H_ */
