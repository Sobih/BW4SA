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

wavelet_node* init_node(struct wavelet_node* node, const char* parent_string, const char* alphabet,
		unsigned int alphabet_length) {
	node->alphabet = (char*) alphabet;
	node->alphabet_length = alphabet_length;
	node->string = determine_substring(parent_string, node->alphabet, node->alphabet_length);
	node->bit_vector = create_bit_vector(node->string, node->alphabet);

	return node;
}

unsigned int* create_bit_vector(const char* string, const char* alphabet) {
	//TODO: Implement this once a bitvector-representation has been determined
	return NULL;
}

char* determine_substring(const char* string, const char* alphabet, unsigned int alphabet_size) {
	int size = 0, chars_left = 10;
	char* substring = calloc(chars_left, sizeof(char));

	for (int i = 0; i < strlen(string); ++i)
		//if current character in string can be found in alphabet, append to substring
		if (binary_search(alphabet, string + i, 0, alphabet_size, sizeof(char)) >= 0) {

			if (chars_left == 0) {
				//expand array
				chars_left = 10;

				if ((substring = realloc(substring, size + chars_left)) == 0)
					//realloc failed, return NULL
					return 0;
			}

			//add to substring
			chars_left--;
			substring[size] = *(string + i);
			size++;
		}

	//add null-marker
	if (chars_left == 0)
		//expand array
		if ((substring = realloc(substring, size + 1)) == 0)
			//realloc failed, return NULL
			return 0;

	//add to substring
	substring[size] = 0;

	return substring;
}

wavelet_node* create_children(struct wavelet_node* node) {
	//alphabet can still be split
	if (node->alphabet_length > 2) {
		node->children = calloc(2, sizeof(wavelet_node));
		struct wavelet_node* left_child = node->children[0], right_child = node->children[1];
		unsigned int left_length = ceil(node->alphabet_length / 2),
				right_length = node->alphabet_length - left_length;

		//recursively create children of left child
		left_child = init_node(left_child, node->string, node->alphabet, left_length);
		create_children(left_child);

		//recursively create children of right child
		right_child = init_node(right_child, node->string, node->alphabet + left_length, right_length);
		create_children(right_child);
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
	free(node->bit_vector);
	free(node->string);

	//recursively call children
	free_subtree(node->children);
	free_subtree(node->children + 1);

	//free entire struct
	free(node);
}
