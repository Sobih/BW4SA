/**
 * @file	draw_tree.c
 * @brief	Implementation of dot-tree drawing functions.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "draw_tree.h"
#include "../core/iterate.h"
#include "../core/c_array.h"
#include "../core/backward_search.h"
#include "../core/s_to_bwt.h"
#include "../utils/bit_vector.h"
#include "../../include/utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief	A struct for storing a suffix tree node and its data.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
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

/**
 * @brief	A function for checking if a substring is a substring of another substring.
 * @param	parent	The suspected parent of the other substring.
 * @param	child	The suspected child of the other substring.
 * @return			Returns <code>1</code> if <code>child</code> is inside (in other words a child) of
 * 					<code>parent</code>, otherwise returns <code>0</code>.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int is_child(substring* parent, substring* child) {

	if (parent->normal.i <= child->normal.i
			&& parent->normal.j >= child->normal.j){

		return 1;
	}

	return 0;
}

/**
 * @brief	A simple function that checks if a substring is the same as one stored in a node.
 * @param	substr	The substring to be compared to the one stored in a node.
 * @param	node	The node storing a substring to be compared to the other substring.
 * @return			Returns <code>1</code> if the substrings are equals, <code>0</code>
 * 					otherwise.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int substring_and_node_equal(substring* substr, internal_node* node) {
	if (substr->normal.i == node->substr->normal.i
			&& substr->normal.j == node->substr->normal.j)
		return 1;
	return 0;
}

/**
 * @brief	A function for finding a node inside the tree based on a substring.
 * @param	substr	The substring to be searched for.
 * @return			Returns the node containing the substring, or <code>NULL</code>
 * 					if no node matching the substring could be found.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
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

/**
 * @brief	Inserts a new node into the dot tree as a callback-function to iterate.
 * @param	state		The internal state of the iterator.
 * @param	results		A pointer to a region of memory containing any previous
 * 						results stored by this callback (not used in this function).
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void collect_internal_nodes(iterator_state* state, void* results) {
	substring* substr1 = state->current;

	substring* substr = calloc(1, sizeof(substring));
	substr->length = substr1->length;
	substr->normal.i = substr1->normal.i;
	substr->normal.j = substr1->normal.j;
	substr->reverse.i = substr1->reverse.i;
	substr->reverse.j = substr1->reverse.j;

	//initialise the node to be inserted
	internal_node* insert_node = calloc(1, sizeof(internal_node));
	insert_node->substr = substr;

	insert_node->id = node_id_index;
	node_id_index++;
	internal_node* prev_node = find_node_by_substring(state->prev);
	insert_node->c = state->current_extension;

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
				temp_node->first_child = insert_node;
				insert_node->parent = temp_node;
				break;
			}
			temp_node = temp_node->first_child;
		} else if (is_child(insert_node->substr, temp_node->substr)) {

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
				temp_node->parent->first_child = insert_node;
			}
			temp_node->parent = insert_node;
			temp_node->next_sibling = NULL;
			temp_node->previous_sibling = NULL;
			break;
		} else {
			if (temp_node->next_sibling == NULL) {
				temp_node->next_sibling = insert_node;
				insert_node->previous_sibling = temp_node;
				insert_node->parent = temp_node->parent;
				break;
			}
			temp_node = temp_node->next_sibling;

		}
	}
}

/**
 * @brief	Prints a label of a node to a file.
 * @param	f		The file to be printed to.
 * @param	node	The node to be printed to a file.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
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

/**
 * @brief	Prints the outgoing arcs of a node to a file.
 * @param	f		The file to be printed to.
 * @param	node	The node to be printed to a file.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_arcs(FILE* f, internal_node* node) {
	fprintf(f, "	node%d->node%d", node->parent->id, node->id);
	fprintf(f, " 	[label=\"");
	print_node_label_to_file(f, node);
	fprintf(f, "\"];\n");
}

/**
 * @brief	A function for printing the arcs of an entire suffix tree to
 * 			a file recursively.
 * @param	f		The file to be printed to.
 * @param	node	The root of the tree to be printed to a file.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_arcs_recursively(FILE* f, internal_node* node) {
	print_arcs(f, node);
	if (node->next_sibling != NULL) {
		print_arcs_recursively(f, node->next_sibling);
	}
	if (node->first_child != NULL) {
		print_arcs_recursively(f, node->first_child);
	}
}

/**
 * @brief	A function for printing leaf nodes of a suffix tree to a file recursively.
 * @param	f				The file to be printed to.
 * @param	node			A node that is to be checked if its a leaf node.
 * @param	suffix_array	A suffix array for creating a substring.
 * @param	orig_string		The entire original string that the tree was created of as
 * 							a character sequence.
 * @param	leaf_vec		A bit vector for checking which characters of the original
 * 							string should be printed.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_leaves_recursively(FILE* f, internal_node* node, int* suffix_array, char* orig_string, bit_vector* leaf_vec)
{
	if(node->first_child != NULL){
		print_leaves_recursively(f, node->first_child, suffix_array, orig_string, leaf_vec);
	}
	if(node->next_sibling != NULL){
		print_leaves_recursively(f, node->next_sibling, suffix_array, orig_string, leaf_vec);
	}

	int j;
	for(int i = node->substr->normal.i; i<=node->substr->normal.j; i++){
		if(leaf_vec->is_bit_marked(leaf_vec, i)) continue;
		fprintf(f, "	node%d->leafnode%d [label=\"", node->id, i);

		for(int j = suffix_array[i]+node->substr->length; j<strlen(orig_string); j++){
			fprintf(f, "%c", orig_string[j]);
		}
		fprintf(f, "$\"];\n");
		leaf_vec->mark_bit(leaf_vec, i);
	}
}

/**
 * @brief	Prints the Weiner-links of a node to a file.
 * @param	node	The node whose Weiner-links are to be printed.
 * @param	f		The file to be printed to.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_weiner_links(internal_node* node, FILE* f) {
	if (node->weiner_node != NULL) {
		fprintf(f, "	node%d->node%d;\n", node->weiner_node->id, node->id);
	}
}

/**
 * @brief	Prints all the Weiner-links of a suffix tree to a file recursively.
 * @param	f		The file to be printed to.
 * @param	node	The root of the tree to be printed to a file.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_weiner_links_recursively(FILE* f, internal_node* node) {
	print_weiner_links(node, f);
	if (node->next_sibling != NULL) {
		print_weiner_links_recursively(f, node->next_sibling);
	}
	if (node->first_child != NULL) {
		print_weiner_links_recursively(f, node->first_child);
	}

}

/**
 * @brief	Prints a suffix tree in dot-format to a file.
 * @param	filename		The path to the file to be printed to.
 * @param	suffix_array	The suffix array of the suffix tree.
 * @param	orig_string		The original string used for creating the suffix
 * 							tree.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
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

void draw_suffix_tree(char* string, char* filename) {
	wavelet_tree* bwt = s_to_bwt(string);
	int* suffix_array = map_create_suffix_array_from_bwt(bwt);

	root = calloc(1, sizeof(internal_node));
	root->id = 0;
	root->substr = calloc(1, sizeof(substring));
	root->substr->normal = ((interval ) { .i = 0, .j = strlen(string) } );
	root->c = ' ';
	node_id_index = 1;

	iterate_for_tree_drawing(string, &collect_internal_nodes);
	print_tree_to_file("suffix_tree.gv", suffix_array, string);

}
