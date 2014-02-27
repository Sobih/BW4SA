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
int wavelet_rank_query(const wavelet_tree* tree, unsigned int curr_node, char c, int start, int end) {
	wavelet_node* node = (wavelet_node*) &tree->nodes[curr_node];

	//determine rank
	int end_rank = node->vector.rank(&node->vector, start, end);
	int half_length = (node->alphabet_length / 2) - 1;
	int child = 0, i = binary_search(node->alphabet, &c, sizeof(char), half_length >= 0 ? half_length : 0, 0);

	//if leaf node, return rank
	if (&tree[node->children[child]] == 0)
		return (i < 0 || i > node->alphabet_length) ? end - start + 1 - end_rank : end_rank;

	//determine rank for 0 -> start of vector
	int start_rank = start > 0 ? node->vector.rank(&node->vector, 0, start - 1) : 0;

	//not found in lower half of alphabet = marked as 0 = inverse rank
	if (i < 0 || i > node->alphabet_length) {
		end = end - end_rank - start_rank;
		start = start - start_rank;
		child = 1;
	}
	else {
		end = end - (end - start - end_rank) - (start > 0 ? start + 1 - start_rank : 0);
		start = start - (start - start_rank);
	}

	//recurse to a child
	return wavelet_rank_query(tree, node->children[child], c, start, end);
}

int wavelet_root_rank_query(const wavelet_tree* tree, char c, int start, int end) {
	if (start < 0 || end < 0 || start > end)
		return 0;

	if (end >= tree->get_num_bits(tree))
		end = tree->get_num_bits(tree) - 1;

	return wavelet_rank_query(tree, 0, c, start, end);
}

/**
 * @brief	Returns the character at a certain index inside a wavelet tree.
 * @param	node	The root of the (sub)tree that is to be searched.
 * @param	index	The index of the character that is to be identified.
 * @return			The found character at the location.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char wavelet_char_at(const wavelet_tree* tree, unsigned int curr_node, int index) {
	wavelet_node* node = (wavelet_node*) &tree->nodes[curr_node];

	//node isn't leaf
	if (node->children[0] != 0) {
		int child = node->vector.is_bit_marked(&node->vector, index) == 0 ? 1 : 0;
		int rank = node->vector.rank(&node->vector, 0, index);

		//subtract wrongly marked bits from index and recurse
		index -= child == 0 ? index - rank + 1 : rank;

		return wavelet_char_at(tree, node->children[child], index);
	}

	//alphabet length = 1
	if (node->alphabet_length == 1)
		return node->alphabet[0];

	return node->vector.is_bit_marked(&node->vector, index) == 0 ? node->alphabet[1] : node->alphabet[0];
}

char wavelet_root_char_at(const wavelet_tree* tree, int index) {
	if (index < 0 || index > tree->get_num_bits(tree))
		return 0;

	return wavelet_char_at(tree, 0, index);
}

unsigned int get_num_bits_tree(const wavelet_tree* tree) {
	return tree->nodes[0].vector.get_length(&tree->nodes[0].vector);
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
		unsigned int alphabet_length) {
	node->alphabet = (char*) alphabet;
	node->alphabet_length = alphabet_length;
	node->string = (char*) string;

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
bit_vector* create_bit_vector(bit_vector* vector, const char* string, const char* alphabet,
		unsigned int alphabet_length) {

	if (string == 0 || alphabet == 0)
		return 0;

	unsigned int length = strlen(string);

	//init bit vector
	if ((vector = init_bit_vector(vector, length)) == 0)
		return 0;

	//mark all chars that are in alphabet
	for (int i = 0; i < length; ++i) {
		int index = binary_search(alphabet, string + i, sizeof(char), alphabet_length - 1, 0);

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
char** determine_substrings(const wavelet_tree* tree, unsigned int parent, char** string_arr) {
	bit_vector* vector = (bit_vector*) &tree->nodes[parent].vector;
	unsigned int num_bits = vector->get_length(vector);

	//determine length of substrings
	unsigned int left = vector->rank(vector, 0, num_bits) + 1;
	unsigned int right = num_bits - left + 2;

	//allocate substrings
	string_arr[0] = malloc(left * sizeof(char));
	string_arr[1] = malloc(right * sizeof(char));

	left = 0; right = 0;

	//create substrings
	for (int i = 0; i < num_bits; ++i) {
		//marked bit = append to first substring
		if (vector->is_bit_marked(vector, i)) {
			string_arr[0][left] = tree->char_at(tree, i);
			left++;
		}
		//unmarked bit = append to second substring
		else {
			string_arr[1][right] = tree->char_at(tree, i);
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
int create_children(wavelet_tree* tree, unsigned int curr_node, unsigned int next,
		bit_vector* vec, char** strings) {
	wavelet_node* node = &tree->nodes[curr_node];

	//determine bitvector of node
	unsigned int left_length = node->alphabet_length / 2;
	node->vector = *create_bit_vector(vec, node->string, node->alphabet, left_length > 0 ? left_length : 1);

	//alphabet can still be split
	if (node->alphabet_length > 2) {
		//determine length of alphabet for both children
		unsigned int right_length = node->alphabet_length - left_length;

		//determine substrings for children
		strings = determine_substrings(tree, curr_node, strings);

		//recursively create children of left child
		wavelet_node* next_child = &tree->nodes[next];
		next_child = init_node(next_child, strings[0], node->alphabet, left_length);
		node->children[0] = next;
		next = create_children(tree, next, next + 1, vec, strings);

		//recursively create children of right child
		next_child = &tree->nodes[next];
		next_child = init_node(next_child, strings[1], node->alphabet + left_length, right_length);
		node->children[1] = next;
		return create_children(tree, next, next + 1, vec, strings);
	}

	//alphabet small enough = no children
	else {
		node->children[0] = 0;
		node->children[1] = 0;
		return next;
	}
}

wavelet_tree* create_wavelet_tree(const char* string) {
	if (string == 0)
		return 0;

	//determine the alphabet and its length
	char* alphabet = determine_alphabet(string);
	unsigned int alphabet_length = strlen(alphabet);
	quick_sort(alphabet, alphabet_length, sizeof(char));

	//allocate and initialize the tree
	wavelet_tree* tree = malloc(sizeof(wavelet_tree));
	tree->num_nodes = alphabet_length;
	//tree->nodes = malloc(tree->num_nodes * sizeof(wavelet_node));
	tree->char_at = &wavelet_root_char_at;
	tree->get_num_bits = &get_num_bits_tree;
	tree->rank = &wavelet_root_rank_query;

	//init temporary bit vector and string array
	bit_vector* vec = malloc(sizeof(bit_vector));
	vec = init_bit_vector(vec, 1);
	char** strings = calloc(2, sizeof(char*));

	//init root and populate tree
	init_node(&tree->nodes[0], string, alphabet, alphabet_length);
	create_children(tree, 0, 1, vec, strings);

	//free temporary variables
	free(strings);
	free_bit_vector(vec);

	return tree;
}

void free_wavelet_tree(wavelet_tree* tree) {
	if (tree == NULL)
		return;

	//free alphabet, since it only has one allocation throughout the tree
	free(tree->nodes[0].alphabet);

	free_subtree(&tree->nodes[0]);
}

void free_subtree(wavelet_node* node) {
	if (node == NULL)
		return;

	//free bitvector and string first
	free_bit_vector(&node->vector);
	free(node->string);

	//recursively call children
	free_subtree(node->children[0]);
	free_subtree(node->children[1]);

	//free entire struct
	free(node);
}
