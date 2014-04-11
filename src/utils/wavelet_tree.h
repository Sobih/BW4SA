/**
 * @file	wavelet_tree.h
 * @brief	An implementation of a standard wavelet tree-structure.
 *
 * This file contains the implementation of a standard wavelet tree-
 * structure. A wavelet tree allows for better compression of strings
 * and better performance on rank-queries, and thus much improved
 * performance for the program overall.
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
	/**
	 * @brief	Returns the number of bits used by the bit vector of the root node
	 * 			(= length of the string from which the tree was created).
	 * @param	tree	The tree for which the length should be determined.
	 * @return			Returns the length of the original string.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	unsigned int (*get_num_bits) (const struct wavelet_tree* tree);

	/**
	 * @brief	Returns the length of the alphabet used by the root node.
	 * @param	tree	The tree for which the alphabet length should be determined.
	 * @return			The length of the alphabet.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	unsigned int (*get_alphabet_length) (const struct wavelet_tree* tree);

	/**
	 * @brief	Returns the alphabet used by the root node.
	 * @param	tree	The tree whose alphabet is to be returned.
	 * @return			The alphabet used by the root node of the tree.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	char* (*get_alphabet) (const struct wavelet_tree* tree);

	/**
	 * @brief	Counts the number of occurrences of a character inside an
	 * 			interval of the string used to create the tree.
	 * @param	tree	The tree for which the count should be done.
	 * @param	c		The character to be counted.
	 * @param	start	The starting index of the count.
	 * @param	end		The ending index of the count.
	 * @return			The number of occurrences of character <code>c</code>
	 * 					between indices start and end inside the wavelet tree.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	int (*rank) (const struct wavelet_tree* tree, char c, int start, int end);

	/**
	 * @brief	Returns the character at index <code>index</code> inside the
	 * 			original string.
	 * @param	tree	The wavelet tree for which the character should be
	 * 					determined.
	 * @param	index	The index of the character to be determined.
	 * @return			The character at index <code>index</code> inside
	 * 					the tree, or <code>NULL</code> if index > length of
	 * 					string or index < 0.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	char (*char_at) (const struct wavelet_tree* tree, int index);

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

void free_wavelet_tree_internals(wavelet_tree* tree);

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
