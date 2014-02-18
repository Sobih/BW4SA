/*
 * wavelet_tree.h
 *
 *  Created on: 4.2.2014
 *      Author: maxsandb
 */

#ifndef WAVELET_TREE_H_
#define WAVELET_TREE_H_

#include "bit_vector.h"

struct wavelet_node {
	char* string;
	struct bit_vec* vector;
	char* alphabet;
	unsigned int alphabet_length;
	struct wavelet_node* parent;
	struct wavelet_node** children;

	int (*rank) (const struct wavelet_node* node, char c, unsigned int index);
} wavelet_node;

struct wavelet_node* create_wavelet_tree(const char* string);

void free_wavelet_tree(struct wavelet_node* node);

void free_subtree(struct wavelet_node* node);

#endif /* WAVELET_TREE_H_ */
