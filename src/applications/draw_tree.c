/*
 * draw_tree.c
 *
 *  Created on: 24.2.2014
 *      Author: topatopa
 */

#include "draw_tree.h"
#include "../core/iterate.h"
#include "../core/c_array.h"
#include "../core/backward_search.h"
#include "../core/s_to_bwt.h"
#include "../utils/bit_vector.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct i_node {
	struct i_node* first_child;
	struct i_node* next_sibling;
	struct i_node* previous_sibling;
	struct i_node* parent;
	struct i_node* weiner_node;
	int id;
	char c;
	substring* substr;
} internal_node;

internal_node* root;
int node_id_index;

//function for debugging
void print_recursively(internal_node* node, int depth) {
	if (depth == 0) {
		printf("I AM THE ROOT in address %d\n", node->id);
	} else {
		printf(
				"node %d, interval (%d, %d). My depth is %d and my parent is node %d\n",
				node->id, node->substr->normal->i, node->substr->normal->j,
				depth, node->parent->id);
	}
	if (node->first_child != NULL) {
		print_recursively(node->first_child, depth + 1);
	}
	if (node->next_sibling != NULL) {
		print_recursively(node->next_sibling, depth);
	}
}

int* create_suffix_array_from_bwt(const char* bwt)
{
	int string_length = strlen(bwt);
	int* suffix_array = malloc(sizeof(int)*string_length);
	int interval = 0;

	int* c_array = create_c_array(bwt);
	char* alphabet = get_alphabet(bwt);
	int c_value = 0;

	for(int i=string_length-1; i>= 0; i--){
		suffix_array[interval] = i;
		interval = get_char_index(c_array, alphabet, bwt[interval])
				+ rank(interval, bwt[interval], bwt);

	}
	return suffix_array;

}

void collect_internal_nodes(substring* substr, substring* prev_substr, char c);

void print_tree_to_file(char* filename, int* suffix_array, char* orig_string);

internal_node* find_node_by_substring(substring* substr);

void print_node_label_to_file(FILE* f, internal_node* node);

void draw_suffix_tree(char* string, char* filename) {
	unsigned char* bwt = s_to_BWT(string);
	int* suffix_array = create_suffix_array_from_bwt(bwt);

	root = calloc(1, sizeof(internal_node));
	root->id = 0;
	root->substr = calloc(1, sizeof(substring));
	root->substr->normal = calloc(1, sizeof(Interval));
	root->substr->normal->i = 0;
	root->substr->normal->j = strlen(string);
	root->c = ' ';
	node_id_index = 1;

	iterate_for_tree_drawing(string, &collect_internal_nodes);
	print_tree_to_file("suffix_tree.gv", suffix_array, string);

}

int is_child(substring* parent, substring* child);

void collect_internal_nodes(substring* substr, substring* prev_substr, char c) {

	//initialise the node to be inserted
	internal_node* insert_node = calloc(1, sizeof(internal_node));
	insert_node->substr = substr;

	insert_node->id = node_id_index;
	node_id_index++;
	internal_node* prev_node = find_node_by_substring(prev_substr);

	insert_node->c = c;

	insert_node->weiner_node = prev_node;
	internal_node* temp_node = root->first_child;

	//if this node is first to be put in the tree, it will be the first child of the root node
	if (temp_node == NULL) {
		root->first_child = insert_node;
		insert_node->parent = root;
		insert_node->weiner_node = root;
		return;
	}
	//otherwise go through the suffix tree until right place is found
	while (1) {
		if (is_child(temp_node->substr, insert_node->substr)) {
			if (temp_node->first_child == NULL) {
//				printf("is child. parent node %d, child node %d\n",
//						temp_node->id, insert_node->id);
				temp_node->first_child = insert_node;
				insert_node->parent = temp_node;
				break;
			}
			temp_node = temp_node->first_child;
//			printf("moving to child...\n");
		} else if (is_child(insert_node->substr, temp_node->substr)) {

//			printf("is inverted child. parent node %d, child node %d\n",
//					insert_node->id, temp_node->id);
			insert_node->previous_sibling = temp_node->previous_sibling;
			insert_node->next_sibling = temp_node->next_sibling;

			if (insert_node->previous_sibling != NULL) {
				insert_node->previous_sibling->next_sibling = insert_node;
			}
			if (insert_node->next_sibling != NULL) {
				insert_node->next_sibling->previous_sibling = insert_node;
			}
			insert_node->first_child = temp_node;
			insert_node->parent = temp_node->parent;
			if (temp_node->parent->first_child == temp_node) {
//				printf("parent fixed\n");
				temp_node->parent->first_child = insert_node;
			}
			temp_node->parent = insert_node;
			temp_node->next_sibling = NULL;
			temp_node->previous_sibling = NULL;
			break;
		} else {
			if (temp_node->next_sibling == NULL) {
//				printf("is sibling. node %d, sibling of %d\n", insert_node->id,
//						temp_node->id);
				temp_node->next_sibling = insert_node;
				insert_node->previous_sibling = temp_node;
				insert_node->parent = temp_node->parent;
				break;
			}
			temp_node = temp_node->next_sibling;
//			printf("moving to sibling...\n");
		}
	}
}

void print_normal_style_definitions(FILE* f) {
	fprintf(f, "	edge [arrowhead=\"none\", color=\"black\"];\n");
}

void print_weiner_links(internal_node* node, FILE* f) {
	if (node->weiner_node != NULL) {
		fprintf(f, "	node%d->node%d;\n", node->weiner_node->id, node->id);
	}
}

void print_weiner_links_recursively(FILE* f, internal_node* node) {
	print_weiner_links(node, f);
	if (node->next_sibling != NULL) {
		print_weiner_links_recursively(f, node->next_sibling);
	}
	if (node->first_child != NULL) {
		print_weiner_links_recursively(f, node->first_child);
	}

}

void print_arcs(FILE* f, internal_node* node) {
	fprintf(f, "	node%d->node%d", node->parent->id, node->id);
	fprintf(f, " 	[label=\"");
	print_node_label_to_file(f, node);
	fprintf(f, "\"];\n");
}

void print_arcs_recursively(FILE* f, internal_node* node) {
	print_arcs(f, node);
	if (node->next_sibling != NULL) {
		print_arcs_recursively(f, node->next_sibling);
	}
	if (node->first_child != NULL) {
		print_arcs_recursively(f, node->first_child);
	}
}

void print_leaves_recursively(FILE* f, internal_node* node, int* suffix_array, char* orig_string, bit_vector* leaf_vec)
{
	if(node->first_child != NULL){
		print_leaves_recursively(f, node->first_child, suffix_array, orig_string, leaf_vec);
	}
	if(node->next_sibling != NULL){
		print_leaves_recursively(f, node->next_sibling, suffix_array, orig_string, leaf_vec);
	}

	int j;
	for(int i = node->substr->normal->i; i<=node->substr->normal->j; i++){
		if(leaf_vec->is_bit_marked(leaf_vec, i)) continue;
		fprintf(f, "	node%d->leafnode%d [label=\"", node->id, i);

		for(int j = suffix_array[i]+node->substr->length; j<strlen(orig_string); j++){
			fprintf(f, "%c", orig_string[j]);
		}
		fprintf(f, "$\"];\n");
		leaf_vec->mark_bit(leaf_vec, i);
	}
}


void print_tree_to_file(char* filename, int* suffix_array, char* orig_string) {
//	printf("starting printin'\n");
	FILE* f = fopen(filename, "w");
	fprintf(f, "//This is a suffix tree generated by Glfbabot-BWT library\n");
	fprintf(f, "digraph suffixtree{\n");
	fprintf(f, "	edge [arrowhead=\"none\", color=\"black\"];\n");
	fprintf(f, "	node [label=\"\", shape=\"point\"];\n");
	fprintf(f, "	//arcs leading to the internal nodes of the suffix tree:\n");

	print_arcs_recursively(f, root->first_child);

	bit_vector* leaf_vec = calloc(1, sizeof(bit_vector));
	init_bit_vector(leaf_vec, strlen(orig_string));

	fprintf(f, "	//arcs leading to the leaves of the suffix tree:\n");
	fprintf(f, "	node [label=\"\", shape=\"square\", width=0.1];\n");
	print_leaves_recursively(f, root, suffix_array, orig_string, leaf_vec);

	fprintf(f, "	//Weiner links:\n");
	fprintf(f, "	edge [color=\"red\", arrowhead=\"normal\"];\n");
	print_weiner_links_recursively(f, root);

	fprintf(f, "}\n");
	fclose(f);
}

//function returns 1 if substr2 is inside (in other words a child) of substring 1, otherwise 0
int is_child(substring* parent, substring* child) {
	if (parent->normal->i <= child->normal->i
			&& parent->normal->j >= child->normal->j)
		return 1;
	return 0;
}

int substring_and_node_equal(substring* substr, internal_node* node) {
	if (substr->normal->i == node->substr->normal->i
			&& substr->normal->j == node->substr->normal->j)
		return 1;
	return 0;
}

internal_node* find_node_by_substring(substring* substr) {
	internal_node* temp_node = root;
	while (temp_node != NULL) {

		if (substring_and_node_equal(substr, temp_node)) {
			return temp_node;
		} else if (is_child(temp_node->substr, substr)) {
			temp_node = temp_node->first_child;
		} else {
			temp_node = temp_node->next_sibling;
		}
	}
	return NULL;
}

void print_node_label_to_file(FILE* f, internal_node* node) {

	internal_node* temp_node = node;

	int parent_label_length = 0;
	if (node->parent->parent != NULL) {
		parent_label_length = node->parent->substr->length;
	}
	int label_length = node->substr->length - parent_label_length;

	int loop_index = 0;
	while (temp_node != NULL) {
		if (loop_index >= parent_label_length) {
			fprintf(f, "%c", temp_node->c);
		}
		temp_node = temp_node->weiner_node;
		loop_index++;
	}
}
