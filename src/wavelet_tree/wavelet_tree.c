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
 * has been encoded as a 0 or a 1 in the current node. If <code>end</code>
 * is larger than the size of the bit vector, the rank operation will
 * be done for the entire length of the vector.
 *
 * @param	tree		The wavelet tree on which the rank query is
 * 						performed.
 * @param	curr_node	The node on which the rank query is currently
 * 						operating on.
 * @param	c			The character for which the rank is to be found.
 * @param	start		The indec of the first character from which the
 * 						rank query should start.
 * @param	end			The index up to which the rank query is going to
 *	 					be made inside the bit vector.
 * @return				Returns the number of occurrences of character
 * 						<code>c</code> in a string.
 * @see		#wavelet_root_rank_query
 * @see		bit_vector.c#rank_query
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int wavelet_rank_query(const wavelet_tree* tree, unsigned int curr_node, char c, int start, int end) {
	if (start > end)
		return 0;

	wavelet_node* node = &tree->nodes[curr_node];

	//determine rank
	int end_rank = node->vector.rank(&node->vector, start, end);
	int half_length = (node->alphabet_length / 2) - 1;
	int child = 0, i = binary_search(node->alphabet, &c, sizeof(char), half_length >= 0 ? half_length : 0, 0);

	//if leaf node, return rank
	if (node->children[child] <= 0)
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
		end = end - (end - start - end_rank) - (start > 0 ? start + 1 - start_rank : 1);
		start = start - (start - start_rank);
	}

	//recurse to a child
	return wavelet_rank_query(tree, node->children[child], c, start, end);
}

/**
 * @brief	The rank query that is called from inside the tree.
 *
 * The entry point for the rank query. Checks all parameters are
 * within bounds and does an initial search for the character inside
 * the root alphabet. If not found, 0 can be returned right away.
 *
 * @param	tree	The wavelet tree upon which a rank query is to
 * 					be made.
 * @param	c		The character that is to be counted.
 * @param	start	The starting index for the rank query.
 * @param	end		The ending index for the rank query.
 * @return			Returns the number of occurrences of character
 * 					<code>c</code> between <code>start</code> and
 * 					<code>end</code>.
 * @see		#wavelet_rank_query
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int wavelet_root_rank_query(const wavelet_tree* tree, char c, int start, int end) {
	if (start < 0 || end < 0 || start > end)
		return 0;

	//preliminary search, return 0 if character not even in alphabet
	int ind = binary_search(tree->nodes[0].alphabet, &c, sizeof(char), tree->nodes[0].alphabet_length, 0);

	if (ind >= tree->nodes[0].alphabet_length || ind < 0)
		return 0;

	if (end >= tree->get_num_bits(tree))
		end = tree->get_num_bits(tree) - 1;

	return wavelet_rank_query(tree, 0, c, start, end);
}

/**
 * @brief	Returns the character at a certain index inside a wavelet tree.
 * @param	tree		The tree that is to be searched.
 * @param	curr_node	The current node that is under search.
 * @param	index		The index of the character that is to be identified.
 * @return				The found character at the location.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char wavelet_char_at(const wavelet_tree* tree, unsigned int curr_node, int index) {
	wavelet_node* node = &tree->nodes[curr_node];

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

/**
 * @brief	The root function of char at that is called from the tree.
 * @param	tree	The tree that is to be searched.
 * @param	index	The index of the character that is to be recognized.
 * @return			The found character.
 * @see		#wavelet_char_at
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char wavelet_root_char_at(const wavelet_tree* tree, int index) {
	if (index < 0 || index > tree->get_num_bits(tree))
		return 0;

	return wavelet_char_at(tree, 0, index);
}

/**
 * @brief	A function that returns the number of bits inside the
 * 			bit vector of the root node (= length of the string).
 * @param	tree	The wavelet tree for which the length of the
 * 					root string is to be determined.
 * @return			The length of the string used by the root node.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
unsigned int get_num_bits_tree(const wavelet_tree* tree) {
	return tree->nodes[0].vector.get_length(&tree->nodes[0].vector);
}

/**
 * @brief	A function that returns the length of the alphabet of
 * 			the root node.
 * @param	tree	The tree for which the alphabet length should
 * 					be determined.
 * @return	The length of the longest alphabet in the tree.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
unsigned int get_alphabet_length_tree(const wavelet_tree* tree) {
	return tree->nodes[0].alphabet_length;
}

/**
 * @brief	A function that returns the alphabet of the root node.
 * @param	tree	The tree for which the alphabet should be
 * 					returned.
 * @return	The alphabet used by the root node.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char* get_alphabet(const wavelet_tree* tree) {
	return tree->nodes[0].alphabet;
}

/**
 * @brief	A simple function for initializing the values in a wavelet node.
 * @param	node			The node that is to be initialized.
 * @param	string			The string used by the node.
 * @param	alphabet		Half of the alphabet used by the string of the node.
 * @param	alphabet_length	Length of the alphabet.
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
 * @param	vector			The bit vector that is to be initialized.
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
	if (init_bit_vector(vector, length) == 0)
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
 * @param	tree		The wavelet tree where the parent node resides.
 * @param	parent		The index of the parent node inside the wavelet tree
 * 						from which a new set of substrings should be determined.
 * @param	string_arr	An array of strings with space for 2 strings.
 * @param	string		The string that is to be split.
 * @return				An array of the two constructed substrings.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char** determine_substrings(const wavelet_tree* tree, unsigned int parent, char** string_arr,
		const char* string) {
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
			string_arr[0][left] = string[i];
			left++;
		}
		//unmarked bit = append to second substring
		else {
			string_arr[1][right] = string[i];
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
 * for the children. Otherwise it will return the index where the next
 * node should be placed inside the tree.
 *
 * @param	tree		The wavelet tree that is being populated.
 * @param	curr_node	The index of the node for which a bit vector and
 * 						children is to be created.
 * @param	next		Index of the next free space inside the wavelet
 * 						tree.
 * @param	string		The substring used by the current node.
 * @return				The next free index inside the wavelet tree.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int create_children(wavelet_tree* tree, unsigned int curr_node, unsigned int next, const char* string) {
	wavelet_node* node = &tree->nodes[curr_node];

	//determine bitvector of node
	unsigned int left_length = node->alphabet_length / 2;
	create_bit_vector(&node->vector, string, node->alphabet, left_length > 0 ? left_length : 1);

	//alphabet can still be split
	if (node->alphabet_length > 2) {
		//determine length of alphabet for both children
		unsigned int right_length = node->alphabet_length - left_length;

		//determine substrings for children
		char** strings = malloc(2 * sizeof(char*));
		determine_substrings(tree, curr_node, strings, string);

		//recursively create children of left child
		wavelet_node* next_child = &tree->nodes[next];
		string = strings[0];
		next_child = init_node(next_child, string, node->alphabet, left_length);
		node->children[0] = next;
		next = create_children(tree, next, next + 1, string);

		//recursively create children of right child
		next_child = &tree->nodes[next];
		string = strings[1];
		next_child = init_node(next_child, string, node->alphabet + left_length, right_length);
		node->children[1] = next;
		free(strings);

		return create_children(tree, next, next + 1, string);
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
	tree->num_nodes = alphabet_length > 0 ? alphabet_length * (int) log2(alphabet_length) : 1;
	tree->nodes = malloc(tree->num_nodes * sizeof(wavelet_node));
	tree->char_at = &wavelet_root_char_at;
	tree->get_num_bits = &get_num_bits_tree;
	tree->get_alphabet_length = &get_alphabet_length_tree;
	tree->rank = &wavelet_root_rank_query;

	//init root and populate tree
	init_node(&tree->nodes[0], string, alphabet, alphabet_length);
	create_children(tree, 0, 1, string);

	return tree;
}

void free_wavelet_tree(wavelet_tree* tree) {
	if (tree == NULL)
		return;

	//free alphabet, since it only has one allocation throughout the tree
	free(tree->nodes[0].alphabet);

	//free subtrees of root to leave original string intact
	if (tree->nodes[0].children[0] != 0) {
		free_subtree(tree, tree->nodes[0].children[0]);
		free_subtree(tree, tree->nodes[0].children[1]);
	}

	//free root bit vector
	free(tree->nodes[0].vector.vector);

	free(tree->nodes);
	free(tree);
}

/**
 * @brief	Frees a wavelet (sub)tree.
 *
 * This algorithm frees a wavelet node and all of it's
 * descendants. It does not free the alphabet used by the
 * wavelet tree but it does break the link between the
 * parent node and the subtree that is being free, so it
 * should be used with caution.
 *
 * @param	tree	The wavelet tree where the subtree resides.
 * @param	node	The index of the root of the subtree
 * 					that is to be freed.
 * @see		#free_wavelet_tree
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void free_subtree(wavelet_tree* tree, unsigned int node) {
	if (tree == NULL)
		return;

	//free bitvector and string first
	free(tree->nodes[node].vector.vector);
	free(tree->nodes[node].string);

	//recursively call children
	if (tree->nodes[node].children[0] != 0) {
		free_subtree(tree, tree->nodes[node].children[0]);
		free_subtree(tree, tree->nodes[node].children[1]);
	}
}
