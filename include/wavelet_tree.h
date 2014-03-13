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
 * wavelet tree. The tree is a linked structure, so traversal of
 * the tree is possible in normal (root -> leaf) and reverse
 * (leaf -> root) order thanks to every node storing their respective
 * children and parent. Every node also contains a pointer to a
 * rank-function for the wavelet tree for ease of access.
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

typedef struct wavelet_tree {
	unsigned int (*get_num_bits) (const struct wavelet_tree* tree);
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
 * @return			The root of the constructed wavelet tree, or
 * 					NULL if the string is uninitialized.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
wavelet_tree* create_wavelet_tree(const char* string);

/**
 * @brief	Frees the memory used by an entire wavelet tree.
 *
 * This algorithm frees an entire wavelet tree. It also frees
 * the alphabet used by the wavelet tree, and since the pointer
 * to the alphabet is shared by all nodes this algorithm should
 * not be called on any node but the root.
 *
 * @param	root	The root of the wavelet tree.
 * @see		#free_subtree
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void free_wavelet_tree(wavelet_tree* tree);

/**
 * @brief	Frees a wavelet (sub)tree.
 *
 * This algorithm frees a wavelet node and all of it's
 * descendants. It does not free the alphabet used by the
 * wavelet tree, so this algorithm can safely be used on any
 * node inside a wavelet tree without damaging the remaining
 * tree.
 *
 * @param	node	The root of the subtree that is to be freed.
 * @see		#free_wavelet_tree
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void free_subtree(wavelet_tree* tree, unsigned int node);

#endif /* WAVELET_TREE_H_ */
