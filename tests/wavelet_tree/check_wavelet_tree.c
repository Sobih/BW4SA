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
#include <limits.h>
#include "../../include/utils.h"
#include "../../include/wavelet_tree.h"
#include "../../include/bit_vector.h"

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

START_TEST (test_rank_query) {
	char* string = "banana";
	struct wavelet_node* root = create_wavelet_tree(string);

	int rank = root->rank(root, 'a', INT_MAX);
	ck_assert(rank == 3);

	rank = root->rank(root, 'b', INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'n', INT_MAX);
	ck_assert(rank == 2);
}
END_TEST

START_TEST (test_rank_query_long_string) {
	char* string = "LAsufhaliILUAShfauishfiuLIUASifuhasvgjbeaukfaAJLsyufluABsasfohASfliiuuBwLIUASFb8239LIUbf787glBAfAuiosdfhliUAFl789aASIFOy9ASfbilAfs98YL7gLify3bliafl98SAYFAAUKSFtifSAbAFYbKUASY8tfsakuyBfkuaYBASF7tk8asGYKJFsbKUAYSF87TASKufygskbjhKJysfa8g";
	struct wavelet_node* root = create_wavelet_tree(string);

	int rank = root->rank(root, '2', INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, '3', INT_MAX);
	ck_assert(rank == 2);

	rank = root->rank(root, '7', INT_MAX);
	ck_assert(rank == 6);

	rank = root->rank(root, '8', INT_MAX);
	ck_assert(rank == 9);

	rank = root->rank(root, '9', INT_MAX);
	ck_assert(rank == 5);

	rank = root->rank(root, 'A', INT_MAX);
	ck_assert(rank == 22);

	rank = root->rank(root, 'B', INT_MAX);
	ck_assert(rank == 5);

	rank = root->rank(root, 'F', INT_MAX);
	ck_assert(rank == 9);

	rank = root->rank(root, 'G', INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'I', INT_MAX);
	ck_assert(rank == 5);

	rank = root->rank(root, 'J', INT_MAX);
	ck_assert(rank == 3);

	rank = root->rank(root, 'K', INT_MAX);
	ck_assert(rank == 6);

	rank = root->rank(root, 'L', INT_MAX);
	ck_assert(rank == 8);

	rank = root->rank(root, 'O', INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'S', INT_MAX);
	ck_assert(rank == 13);

	rank = root->rank(root, 'T', INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'U', INT_MAX);
	ck_assert(rank == 8);

	rank = root->rank(root, 'Y', INT_MAX);
	ck_assert(rank == 7);

	rank = root->rank(root, 'a', INT_MAX);
	ck_assert(rank == 12);

	rank = root->rank(root, 'b', INT_MAX);
	ck_assert(rank == 9);

	rank = root->rank(root, 'd', INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'e', INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'f', INT_MAX);
	ck_assert(rank == 20);

	rank = root->rank(root, 'g', INT_MAX);
	ck_assert(rank == 5);

	rank = root->rank(root, 'h', INT_MAX);
	ck_assert(rank == 7);

	rank = root->rank(root, 'i', INT_MAX);
	ck_assert(rank == 12);

	rank = root->rank(root, 'j', INT_MAX);
	ck_assert(rank == 2);

	rank = root->rank(root, 'k', INT_MAX);
	ck_assert(rank == 5);

	rank = root->rank(root, 'l', INT_MAX);
	ck_assert(rank == 9);

	rank = root->rank(root, 'o', INT_MAX);
	ck_assert(rank == 2);

	rank = root->rank(root, 's', INT_MAX);
	ck_assert(rank == 13);

	rank = root->rank(root, 't', INT_MAX);
	ck_assert(rank == 3);

	rank = root->rank(root, 'u', INT_MAX);
	ck_assert(rank == 13);

	rank = root->rank(root, 'v', INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'w', INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'y', INT_MAX);
	ck_assert(rank == 6);
}
END_TEST

Suite* array_suite(void) {
	Suite* suite = suite_create("Wavelet Suite");

	TCase* tc_wavelet_tree = tcase_create("Wavelet Tree");
	tcase_add_test (tc_wavelet_tree, test_create_wavelet_tree);
	tcase_add_test (tc_wavelet_tree, test_faulty_parameters);

	TCase* tc_wavelet_rank = tcase_create("Wavelet Rank Query");
	tcase_add_test (tc_wavelet_rank, test_rank_query);
	tcase_add_test (tc_wavelet_rank, test_rank_query_long_string);

	suite_add_tcase (suite, tc_wavelet_tree);
	suite_add_tcase (suite, tc_wavelet_rank);

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
