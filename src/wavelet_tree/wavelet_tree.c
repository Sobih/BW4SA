/*
 * wavelet_tree.c
 *
 *  Created on: 4.2.2014
 *      Author: Max Sandberg
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include "../../include/utils.h"
#include "../../include/wavelet_tree.h"

void print_bit_vector(struct bit_vec* vector) {
	if (vector == 0) {
		printf("(NULL)\n");
		return;
	}

	for (int i = 0; i < vector->length; ++i) {
		printf("\t%u, ", vector->vector[i]);
		print_bits(vector->vector[i]);
		printf("\n");
	}

	printf("\n");
}

void print_node(struct wavelet_node* node) {
	printf("\tBit vector:\n");
	if (node->vector != 0)
		print_bit_vector(node->vector);
	else
		printf("\t(NULL)\n");
	printf("\tString: %s\n", node->string);
	printf("\tAlphabet: %s\n", node->alphabet);
	printf("\tAlphabet length: %u\n", node->alphabet_length);
}

unsigned int wavelet_rank_query(const struct wavelet_node* node, char c, unsigned int index) {
	if (index >= node->vector->length * 32)
		index = node->vector->length * 32;

	printf("Current index: %u\n", index);

	printf("Alphabet length: %u\n", node->alphabet_length);
	printf("Alphabet: %s\n", node->alphabet);

	//find index of c in alphabet
	int i = binary_search(node->alphabet, &c, 0, node->alphabet_length - 1, sizeof(char));

	printf("Result of binary search: %u\n", i);

	if (i < 0 || i > node->alphabet_length)
		return UINT_MAX;

	unsigned int rank = node->vector->rank(node->vector, index);
	int child = 1;

	//c is in bottom half of alphabet = 0 = inverse rank
	if (i < node->alphabet_length / 2) {
		rank = node->vector->length * 32 - rank - node->vector->filler_bits;
		child = 0;
	}

	printf("Rank result: %u\n", rank);
	printf("Left child? %s\n", child == 1 ? "true" : "false");

	//query a child, or return rank if leaf node
	if (node->children[child] != 0) {
		printf("Not leaf, recursing...\n");
		rank = node->rank(node->children[child], c, rank);
	}

	return rank;
}

struct bit_vec* create_bit_vector(const char* string, const char* alphabet, unsigned int alphabet_length) {
	struct bit_vec* vector = calloc(1, sizeof(struct bit_vec));
	unsigned int length = strlen(string);

	//init bit vector
	if ((vector = init_bit_vector(vector, length)) == 0)
		return 0;

	printf("alphabet length: %u\n", alphabet_length);

	//mark all chars that are in alphabet
	for (int i = 0; i < length; ++i) {
		int index = binary_search(alphabet, string + i, 0, alphabet_length - 1, sizeof(char));

		printf("Result of search: %u\n", index);

		//binary search on alphabet for current char, and if found, mark bit at
		//same location in vector as current char in string
		if (index >= 0 && index < alphabet_length)
			vector->mark_bit(vector, i);
	}

	return vector;
}

struct wavelet_node* init_node(struct wavelet_node* node, const char* string, const char* alphabet,
		unsigned int alphabet_length, struct wavelet_node* parent) {
	node->alphabet = (char*) alphabet;
	node->alphabet_length = alphabet_length;
	node->string = (char*) string;
	node->vector = 0;
	node->parent = parent;
	node->children = calloc(2, sizeof(struct wavelet_node*));
	node->rank = &wavelet_rank_query;

	return node;
}

char** determine_substrings(const struct wavelet_node* parent) {
	struct bit_vec* vector = parent->vector;
	unsigned int num_bits = strlen(parent->string);

	char** string_arr = calloc(2, sizeof(char*));

	//determine length of substrings
	unsigned int left = vector->rank(vector, num_bits) + 1;
	unsigned int right = num_bits - left + 2;

	printf("Length of substrings: %u, %u\n", left, right);

	//allocate substrings
	string_arr[0] = calloc(left, sizeof(char));
	string_arr[1] = calloc(right, sizeof(char));

	left = 0; right = 0;

	//create substrings
	for (int i = 0; i < num_bits; ++i) {
		//marked bit = append to first substring
		if (vector->is_bit_marked(vector, i)) {
			printf("Bit marked: %c\n", parent->string[i]);
			string_arr[0][left] = parent->string[i];
			left++;
		}
		//unmarked bit = append to second substring
		else {
			printf("Bit not marked: %c\n", parent->string[i]);
			string_arr[1][right] = parent->string[i];
			right++;
		}
	}

	//append null-markers to end of both substrings
	string_arr[0][left] = 0;
	string_arr[1][right] = 0;

	printf("Finished substrings: %s, %s\n", string_arr[0], string_arr[1]);

	return string_arr;
}

struct wavelet_node* create_children(struct wavelet_node* node) {
	//determine bitvector of node
	printf("Creating bit vector\n");
	unsigned int left_length = node->alphabet_length / 2;
	node->vector = create_bit_vector(node->string, node->alphabet, left_length > 0 ? left_length : 1);
	printf("Finished vector:\n");
	print_bit_vector(node->vector);

	//alphabet can still be split
	if (node->alphabet_length > 2) {
		printf("Allocating children\n");

		//allocate children
		struct wavelet_node* children = calloc(2, sizeof(struct wavelet_node));
		struct wavelet_node* left_child = &children[0];
		struct wavelet_node* right_child = &children[1];

		//determine length of alphabet for both children
		unsigned int right_length = node->alphabet_length - left_length;

		printf("Determining substrings\n");
		//determine substrings for children
		char** substrings = determine_substrings(node);

		printf("Substrings: %s, %s\n", substrings[0], substrings[1]);

		//recursively create children of left child
		left_child = init_node(left_child, substrings[0], node->alphabet, left_length, node);
		node->children[0] = left_child;
		printf("Left child created, creating children for it\n");
		create_children(left_child);

		printf("Back from recursion\n");

		//recursively create children of right child
		right_child = init_node(right_child, substrings[1], node->alphabet + left_length, right_length, node);
		node->children[1] = right_child;
		printf("Right child created, creating children for it\n");
		create_children(right_child);

		free(substrings);
	}

	//alphabet small enough = no children
	else {
		printf("Alphabet small enough\n");
		node->children[0] = 0;
		node->children[1] = 0;
	}

	return node;
}

struct wavelet_node* create_wavelet_tree(const char* string) {
	if (string == 0)
		return 0;

	//allocate the root node
	struct wavelet_node* root = calloc(1, sizeof(wavelet_node));

	printf("Root allocated\n");

	//determine the alphabet and its length
	char* alphabet = determine_alphabet(string);
	unsigned int alphabet_length = strlen(alphabet);
	quick_sort(alphabet, alphabet_length, sizeof(char));

	printf("Alphabet determined and sorted\n");

	//init root and populate tree
	root = init_node(root, string, alphabet, alphabet_length, 0);

	printf("Root initialized:\n");
	print_node(root);
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
	free_subtree(node->children[0]);
	free_subtree(node->children[1]);

	//free entire struct
	free(node);
}
