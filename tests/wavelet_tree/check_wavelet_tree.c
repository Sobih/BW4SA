/*
 * check_wavelet_tree.c
 *
 *  Created on: 7.2.2014
 *      Author: maxsandb
 */

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <check.h>
#include <math.h>
#include <stdio.h>
#include "../../include/utils.h"
#include "../../include/wavelet_tree.h"
#include "../../include/bit_vector.h"

void print_bit_vector_asd(struct bit_vec* vector) {
	for (int i = 0; i < vector->length; ++i) {
		printf("\t%u, ", vector->vector[i]);
		print_bits(vector->vector[i]);
		printf("\n");
	}

	printf("\n");
}

void print_node_asd(struct wavelet_node* node) {
	printf("\tBit vector:\n");
	if (node->vector != 0)
		print_bit_vector_asd(node->vector);
	else
		printf("\t(NULL)\n");
	printf("\tString: %s\n", node->string);
	printf("\tAlphabet: %s\n", node->alphabet);
	printf("\tAlphabet length: %u\n", node->alphabet_length);
}

void assert_node_internals(struct wavelet_node* node, const char* string, const char* alphabet,
		unsigned int alphabet_length, unsigned int vec_length, unsigned int* correct_bits) {

	ck_assert(strcmp(node->alphabet, alphabet) == 0);
	ck_assert(strcmp(node->string, string) == 0);
	ck_assert(alphabet_length == node->alphabet_length);
	ck_assert(node->vector->length == vec_length);

	for (int i = 0; i < vec_length; ++i)
		ck_assert(node->vector->vector[i] == correct_bits[i]);
}

START_TEST (test_create_wavelet_tree) {
	char* string = "banana", *alphabet = "abn";
	struct wavelet_node* root = create_wavelet_tree(string), *child;
	unsigned int correct_bits;

	//assert root internals
	correct_bits = 42;
	assert_node_internals(root, string, alphabet, 3, 1, &correct_bits);
	ck_assert(root->parent == 0);
	ck_assert(root->children[0] != 0);
	ck_assert(root->children[1] != 0);

	//assert left child internals
	string = "aaa";
	correct_bits = 7;
	child = root->children[0];
	assert_node_internals(child, string, alphabet, 1, 1, &correct_bits);
	ck_assert(child->children[0] == 0);
	ck_assert(child->children[1] == 0);
	ck_assert(child->parent == root);

	//assert right child internals
	string = "bnn";
	alphabet = "bn";
	correct_bits = 1;
	child = root->children[1];
	assert_node_internals(child, string, alphabet, 2, 1, &correct_bits);
	ck_assert(child->children[0] == 0);
	ck_assert(child->children[1] == 0);
	ck_assert(child->parent == root);
}
END_TEST

START_TEST (test_faulty_parameters) {
	//empty string
	char* string = "";
	struct wavelet_node* root = create_wavelet_tree(string);
	unsigned int correct_bits;

	printf("Root\n");
	print_node_asd(root);

	//assert root internals
	correct_bits = 0;
	assert_node_internals(root, string, string, 0, 1, &correct_bits);
	ck_assert(root->parent == 0);
	ck_assert(root->children[0] == 0);
	ck_assert(root->children[1] == 0);

	//null pointer
	string = 0;
	root = create_wavelet_tree(string);

	ck_assert(root == 0);
}
END_TEST

Suite* array_suite(void) {
	Suite* suite = suite_create("Array");

	TCase* tc_wavelet_tree = tcase_create("Wavelet Tree");
	tcase_add_test (tc_wavelet_tree, test_create_wavelet_tree);
	tcase_add_test (tc_wavelet_tree, test_faulty_parameters);
	suite_add_tcase (suite, tc_wavelet_tree);

	return suite;
}

int main (void) {
	int number_failed;
	Suite* suite = array_suite();
	SRunner* suite_runner = srunner_create(suite);
	srunner_run_all(suite_runner, CK_NORMAL);
	number_failed = srunner_ntests_failed(suite_runner);
	srunner_free(suite_runner);

	return (number_failed == 0) ? 0 : 1;
}
