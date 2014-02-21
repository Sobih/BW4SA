/**
 * @file	wavelet_tree.c
 * @brief	Implementation of the wavelet tree-structure.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include "../../include/utils.h"
#include "../../include/wavelet_tree.h"

/**
 * @brief	The implementation for the rank query on a wavelet tree.
 *
 * The rank query on a wavelet tree works by recursively doing a rank
 * function on a child of the current node based on if the character
 * has been encoded as a 0 or a 1 in the current node. If <code>index</code>
 * is larger than the size of the bit vector, the rank operation will
 * be done for the entire length of the vector.
 *
 * @param	node	The node on which the rank query is to be started.
 * @param	c		The character for which the rank is to be found.
 * @param	index	The index up to which the rank query is going to
 * 					be made inside the bit vector.
 * @return			Returns the number of occurrences of character
 * 					<code>c</code> in a string up to <code>index</code>.
 * @see		bit_vector.c#rank_query
 * @see		bit_vector.c#rank_query_interval
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int wavelet_rank_query(const wavelet_node* node, char c, int index) {
	if (index < 0)
		return 0;

	if (index > node->vector->length * 32 - node->vector->filler_bits)
		index = node->vector->length * 32 - node->vector->filler_bits;

	//determine rank
	int rank = node->vector->rank(node->vector, index);
	int half_length = (node->alphabet_length / 2) - 1;
	int child = 0, i = binary_search(node->alphabet, &c, 0, half_length >= 0 ? half_length : 0, sizeof(char));

	//not found in lower half of alphabet = marked as 0 = inverse rank
	if (i < 0 || i > node->alphabet_length) {
		rank = index - rank;
		child = 1;
	}

	//query a child, or return rank if leaf node
	if (node->children[child] != 0)
		return node->rank(node->children[child], c, rank);

	return rank;
}

/**
 * @brief	Returns the character at a certain index inside a wavelet tree.
 * @param	node	The root of the (sub)tree that is to be searched.
 * @param	index	The index of the character that is to be identified.
 * @return			The found character at the location.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char wavelet_char_at(const wavelet_node* node, int index) {
	if (index < 0 || node == 0)
		return 0;

	int vec_length = node->vector->length * 32 - node->vector->filler_bits;

	if (index > vec_length)
		index = vec_length;

	//node isn't leaf
	if (node->children[0] != 0) {
		int child = node->vector->is_bit_marked(node->vector, index) == 0 ? 1 : 0;
		int rank = node->vector->rank(node->vector, index);

		//subtract wrongly marked bits from index and recurse
		index -= child == 0 ? index - rank : rank;

		return node->char_at(node->children[child], index);
	}

	//alphabet length = 1
	if (node->alphabet_length == 1)
		return node->alphabet[0];

	return node->vector->is_bit_marked(node->vector, index) == 0 ? node->alphabet[1] : node->alphabet[0];
}

/**
 * @brief	A simple function for initializing the values in a wavelet node.
 * @param	node			The node that is to be initialized.
 * @param	string			The string used by the node.
 * @param	alphabet		Half of the alphabet used by the string of the node.
 * @param	alphabet_length	Length of the alphabet.
 * @param 	parent			The parent node of the node to be initialized.
 * @return					An initialized wavelet node.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
wavelet_node* init_node(wavelet_node* node, const char* string, const char* alphabet,
		unsigned int alphabet_length, wavelet_node* parent) {
	node->alphabet = (char*) alphabet;
	node->alphabet_length = alphabet_length;
	node->string = (char*) string;
	node->vector = 0;
	node->parent = parent;
	node->children = calloc(2, sizeof(wavelet_node*));
	node->rank = &wavelet_rank_query;
	node->char_at = &wavelet_char_at;

	return node;
}

/**
 * @brief	Constructs a bit vector based on the alphabet of the node.
 *
 * This algorithm creates a bit vector with every character in the alphabet
 * of the node marked as a 1 inside the bit vector and all other characters
 * marked as 0.
 *
 * @param	string			The string for which a bit vector is created.
 * @param	alphabet		The alphabet used by the string.
 * @param	alphabet_length	The length of the alphabet used by the string.
 * @return					Returns an initialized bit vector based on the
 * 							string and alphabet supplied as parameters, or
 * 							NULL if either string is uninitialized or the
 * 							vector couldn't be initialized.
 * @see		bit_vector.h
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
bit_vector* create_bit_vector(const char* string, const char* alphabet, unsigned int alphabet_length) {
	if (string == 0 || alphabet == 0)
		return 0;

	bit_vector* vector = calloc(1, sizeof(bit_vector));
	unsigned int length = strlen(string);

	//init bit vector
	if ((vector = init_bit_vector(vector, length)) == 0)
		return 0;

	//mark all chars that are in alphabet
	for (int i = 0; i < length; ++i) {
		int index = binary_search(alphabet, string + i, 0, alphabet_length - 1, sizeof(char));

		//binary search on alphabet for current char, and if found, mark bit at
		//same location in vector as current char in string
		if (index >= 0 && index < alphabet_length)
			vector->mark_bit(vector, i);
	}

	return vector;
}

/**
 * @brief	Splits a string into two substrings.
 *
 * This algorithm splits a string into two substrings by taking all the
 * 0-marked characters in the bit vector of the parent and putting them in
 * one string and the 1-marked characters into another string.
 *
 * @param	parent	The parent node from which a new set of substrings
 * 					should be determined.
 * @return			An array of the two constructed substrings.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char** determine_substrings(const wavelet_node* parent) {
	bit_vector* vector = parent->vector;
	unsigned int num_bits = strlen(parent->string);

	char** string_arr = calloc(2, sizeof(char*));

	//determine length of substrings
	unsigned int left = vector->rank(vector, num_bits) + 1;
	unsigned int right = num_bits - left + 2;

	//allocate substrings
	string_arr[0] = calloc(left, sizeof(char));
	string_arr[1] = calloc(right, sizeof(char));

	left = 0; right = 0;

	//create substrings
	for (int i = 0; i < num_bits; ++i) {
		//marked bit = append to first substring
		if (vector->is_bit_marked(vector, i)) {
			string_arr[0][left] = parent->string[i];
			left++;
		}
		//unmarked bit = append to second substring
		else {
			string_arr[1][right] = parent->string[i];
			right++;
		}
	}

	//append null-markers to end of both substrings
	string_arr[0][left] = 0;
	string_arr[1][right] = 0;

	return string_arr;
}

/**
 * @brief	Recursively creates children for a node.
 *
 * This algorithm populates the wavelet tree. It takes an initialized
 * node as parameter for which it creates a bit vector and any possible
 * children. If children are created, it will recursively call itself
 * for the children. Otherwise it will return the node supplied as
 * parameter.
 *
 * @param	node	The node for which a bit vector and children is
 * 					to be created.
 * @return			The initialized node with possible children created.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
wavelet_node* create_children(wavelet_node* node) {
	//determine bitvector of node
	unsigned int left_length = node->alphabet_length / 2;
	node->vector = create_bit_vector(node->string, node->alphabet, left_length > 0 ? left_length : 1);

	//alphabet can still be split
	if (node->alphabet_length > 2) {
		//allocate children
		wavelet_node* children = calloc(2, sizeof(wavelet_node));
		wavelet_node* left_child = &children[0];
		wavelet_node* right_child = &children[1];

		//determine length of alphabet for both children
		unsigned int right_length = node->alphabet_length - left_length;

		//determine substrings for children
		char** substrings = determine_substrings(node);

		//recursively create children of left child
		left_child = init_node(left_child, substrings[0], node->alphabet, left_length, node);
		node->children[0] = left_child;
		create_children(left_child);

		//recursively create children of right child
		right_child = init_node(right_child, substrings[1], node->alphabet + left_length, right_length, node);
		node->children[1] = right_child;
		create_children(right_child);

		free(substrings);
	}

	//alphabet small enough = no children
	else {
		node->children[0] = 0;
		node->children[1] = 0;
	}

	return node;
}

wavelet_node* create_wavelet_tree(const char* string) {
	if (string == 0)
		return 0;

	//allocate the root node
	wavelet_node* root = calloc(1, sizeof(wavelet_node));

	//determine the alphabet and its length
	char* alphabet = determine_alphabet(string);
	unsigned int alphabet_length = strlen(alphabet);
	quick_sort(alphabet, alphabet_length, sizeof(char));

	//init root and populate tree
	root = init_node(root, string, alphabet, alphabet_length, 0);
	root = create_children(root);

	return root;
}

void free_wavelet_tree(wavelet_node* node) {
	if (node == NULL)
		return;

	//free alphabet, since it only has one allocation throughout the tree
	free(node->alphabet);

	free_subtree(node);
}

void free_subtree(wavelet_node* node) {
	if (node == NULL)
		return;

	//set parent's connection to this node to NULL
	if (node->parent != 0) {
		if (node->parent->children[0] == node)
			node->parent->children[0] = NULL;
		else if (node->parent->children[1] == node)
			node->parent->children[1] = NULL;
	}

	//free bitvector and string first
	free(node->vector);
	free(node->string);

	//recursively call children
	free_subtree(node->children[0]);
	free_subtree(node->children[1]);

	//free entire struct
	free(node);
}
