/*
 * wavelet_tree.h
 *
 *  Created on: 4.2.2014
 *      Author: maxsandb
 */

#ifndef WAVELET_TREE_H_
#define WAVELET_TREE_H_

struct wavelet_node {
	char* string;
	unsigned int* bit_vector;	//TODO: MODIFY THIS!!!!!!!!!!!
	char* alphabet;
	unsigned int alphabet_length;
	struct wavelet_node* parent;
	struct wavelet_node* children;
} wavelet_node;

wavelet_node* create_wavelet_tree(const char* string);

#endif /* WAVELET_TREE_H_ */
