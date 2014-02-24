/*
 * draw_tree.c
 *
 *  Created on: 24.2.2014
 *      Author: topatopa
 */

#include "../../include/iterate.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct i_node
{
	struct i_node* first_child;
	struct i_node* next_sibling;
	struct i_node* previous_sibling;
	struct i_node* parent;
	substring* substr;
}internal_node;

//typedef struct suffix_tree_root
//{
//	internal_node* first_child;
//}suffix_tree;

substring** node_list;
int node_list_index;

void collect_internal_nodes(substring* substr)
{
	node_list[node_list_index] = substr;
	node_list_index++;
}

void print_recursively(internal_node* node, int depth)
{
	printf("node, interval i = %d, j = %d. My depth is %d\n",node->substr->normal->i, node->substr->normal->j, depth);

	if(node->first_child != NULL){
		print_recursively(node->first_child, depth+1);
	}
	if(node->next_sibling != NULL){
		print_recursively(node->next_sibling, depth+1);
	}
}

internal_node* create_suffix_tree();

void draw_suffix_tree(char* bwt,int max_number_nodes)
{
	node_list = malloc(sizeof(substring*)*max_number_nodes);
	node_list_index = 0;
	iterate(bwt, &collect_internal_nodes);
	internal_node* root = create_suffix_tree();

	print_recursively(root, 0);
}

int is_child(internal_node* parent, internal_node* child);

//returns the pointer to the root node of the suffix tree created
internal_node* create_suffix_tree()
{
	internal_node* insert_node;
	internal_node* temp_node;

	internal_node* root = calloc(1, sizeof(internal_node));
	//put first node to the tree for technical reasons if there is at least one node
	if (node_list_index != 0){
		root->first_child = calloc(1, sizeof(internal_node));
		root->first_child->substr = node_list[0];
		root->first_child->parent = root;
	}
	temp_node = root->first_child;

	for(int i = 1; i < node_list_index; i++){
		insert_node = calloc(1, sizeof(internal_node));
		insert_node->substr = node_list[i];

		while(temp_node != NULL){
			if(is_child(temp_node, insert_node)){
				if(temp_node->first_child == NULL){
					temp_node->first_child = insert_node;
					insert_node->parent = temp_node;
					break;
				}
				temp_node = temp_node->first_child;
			}
			else if(is_child(insert_node, temp_node)){
				insert_node->previous_sibling = temp_node->previous_sibling;
				insert_node->next_sibling = temp_node->next_sibling;
				if(insert_node->previous_sibling != NULL){
					insert_node->previous_sibling->next_sibling = insert_node;
				}
				if(insert_node->next_sibling != NULL){
					insert_node->next_sibling->previous_sibling = insert_node;
				}
				insert_node->first_child = temp_node;
				insert_node->parent = temp_node->parent;
				temp_node->parent = insert_node;
				temp_node->next_sibling = NULL;
				temp_node->previous_sibling = NULL;
				break;
			}
			else{
				if(temp_node->next_sibling == NULL){
					temp_node->next_sibling = insert_node;
					insert_node->previous_sibling = insert_node;
					break;
				}
				temp_node = temp_node->next_sibling;
			}
		}

	}
	return root;
}

//function returns 1 if substr2 is inside (in other words a child) of substring 1, otherwise 0
int is_child(internal_node* parent, internal_node* child)
{
	if(parent->substr->normal->i <= child->substr->normal->i &&
			parent->substr->normal->j >= child->substr->normal->j) return 1;
	return 0;
}
