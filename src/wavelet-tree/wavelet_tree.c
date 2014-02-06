/*
 * wavelet_tree.c
 *
 *  Created on: 4.2.2014
 *      Author: Max Sandberg
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../include/utils.h"
#include "../../include/wavelet_tree.h"

wavelet_node* init_node(struct wavelet_node* node, const char* string, const char* alphabet,
		unsigned int alphabet_length) {
	node->alphabet = (char*) alphabet;
	node->alphabet_length = alphabet_length;
	node->string = (char*) string;
	node->vector = create_bit_vector(node->string, node->alphabet, node->alphabet_length / 2);

	return node;
}

bit_vector* create_bit_vector(const char* string, const char* alphabet, unsigned int alphabet_length) {
	struct bit_vec* vector = calloc(1, sizeof(bit_vector));
	unsigned int length = strlen(string);

	//init bit vector
	if ((vector = init_bit_vector(vector, length)) == 0)
		return 0;

	//mark all chars that are in alphabet
	for (int i = 0; i < length; ++i)
		//binary search on alphabet for current char, and if found, mark bit at
		//same location in vector as current char in string
		if (binary_search(alphabet, string[i], 0, alphabet_length, sizeof(char)) > 0)
			vector->mark_bit(vector, i);

	return vector;
}

char** determine_substrings(const struct wavelet_node* parent) {
	struct bit_vec* vector = parent->vector;
	unsigned int num_bits = vector->length * 32;

	char** string_arr = calloc(2, sizeof(char*));

	//determine length of substrings
	unsigned int left = vector->rank(vector, num_bits) + 1;
	unsigned int right = num_bits - left + 1;

	//allocate substrings
	string_arr[0] = calloc(left, sizeof(char));
	string_arr[1] = calloc(right, sizeof(char));

	left = 0; right = 0;

	//create substrings
	for (int i = 0; i < num_bits; ++i) {
		//marked bit = append to first substring
		if (vector->is_bit_marked(vector, i)) {
			string_arr[0][left] = parent->string[left];
			left++;
		}
		//unmarked bit = append to second substring
		else {
			string_arr[1][right] = parent->string[right];
			right++;
		}
	}

	//append null-markers to end of both substrings
	string_arr[0][left] = 0;
	string_arr[1][right] = 0;

	return string_arr;
}

wavelet_node* create_children(struct wavelet_node* node) {
	//alphabet can still be split
	if (node->alphabet_length > 2) {
		//allocate children
		node->children = calloc(2, sizeof(wavelet_node));
		struct wavelet_node* left_child = node->children[0], right_child = node->children[1];

		//determine length of alphabet for both children
		unsigned int left_length = node->alphabet_length / 2,
				right_length = node->alphabet_length - left_length;

		//determine substrings for children
		char** substrings = determine_substrings(node);

		//recursively create children of left child
		left_child = init_node(left_child, substrings[0], node->alphabet, left_length);
		create_children(left_child);

		//recursively create children of right child
		right_child = init_node(right_child, substrings[1], node->alphabet + left_length, right_length);
		create_children(right_child);

		free(substrings);
	}

	//alphabet small enough = no children
	else
		node->children = 0;

	return node;
}

wavelet_node* create_wavelet_tree(const char* string) {
	//allocate the root node
	struct wavelet_node* root = calloc(1, sizeof(wavelet_node));

	//determine the alphabet and its length
	char* alphabet = determine_alphabet(string);
	unsigned int alphabet_length = strlen(alphabet);
	alphabet = quick_sort(alphabet, alphabet_length, sizeof(char));

	//init root and populate tree
	root = init_node(root, string, alphabet, alphabet_length);
	root = create_children(root);

	return root;
}

void free_wavelet_tree(struct wavelet_node* node) {
	if (node == NULL)
		return;

	//free alphabet, since it only has one allocation throughout the tree
	free(node->alphabet);

	free_subtree(node);
}

void free_subtree(struct wavelet_node* node) {
	if (node == NULL)
		return;

	//set parent's connection to this node to NULL
	if (node->parent->children[0] == node)
		node->parent->children[0] = NULL;
	else if (node->parent->children[1] == node)
		node->parent->children[1] = NULL;

	//free bitvector and string first
	free(node->vector);
	free(node->string);

	//recursively call children
	free_subtree(node->children);
	free_subtree(node->children + 1);

	//free entire struct
	free(node);
}
