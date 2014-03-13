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
	ck_assert(node->vector.length == vec_length);

	for (int i = 0; i < vec_length; ++i)
		ck_assert(node->vector.vector[i] == correct_bits[i]);
}

START_TEST (test_create_wavelet_tree) {
	char* string = "banana", *alphabet = "abn";

	printf("Creating tree\n");

	wavelet_tree* tree = create_wavelet_tree(string);
	wavelet_node* node;
	unsigned int correct_bits;

	printf("Tree created\n");

	//assert tree internals
	ck_assert(tree->nodes != 0);
	ck_assert(tree->num_nodes == 3);

	//assert root internals
	printf("Asserting root\n");
	correct_bits = 42;
	node = &tree->nodes[0];
	assert_node_internals(node, string, alphabet, 3, 1, &correct_bits);
	ck_assert(node->children[0] == 1);
	ck_assert(node->children[1] == 2);

	//assert left child internals
	printf("Asserting left child\n");
	string = "aaa";
	correct_bits = 7;
	node = &tree->nodes[1];
	assert_node_internals(node, string, alphabet, 1, 1, &correct_bits);
	ck_assert(node->children[0] == 0);
	ck_assert(node->children[1] == 0);

	//assert right child internals
	printf("Asserting right child\n");
	string = "bnn";
	alphabet = "bn";
	correct_bits = 1;
	node = &tree->nodes[2];
	print_wavelet_node(node);
	assert_node_internals(node, string, alphabet, 2, 1, &correct_bits);
	ck_assert(node->children[0] == 0);
	ck_assert(node->children[1] == 0);
}
END_TEST

START_TEST (test_faulty_parameters) {
	//empty string
	printf("Creating tree on empty string\n");
	char* string = "";
	wavelet_tree* tree = create_wavelet_tree(string);
	unsigned int correct_bits;

	//assert root internals
	printf("Asserting root\n");
	wavelet_node* root = &tree->nodes[0];
	correct_bits = 0;
	assert_node_internals(root, string, string, 0, 1, &correct_bits);
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
	wavelet_tree* tree = create_wavelet_tree(string);

	int rank = tree->rank(tree, 'a', 0, INT_MAX);
	ck_assert(rank == 3);

	//printf("Rank: %d, should be: %d\n", rank, 3);

	rank = tree->rank(tree, 'b', 0, INT_MAX);
	ck_assert(rank == 1);

	//printf("Rank: %d, should be: %d\n", rank, 1);

	rank = tree->rank(tree, 'n', 0, INT_MAX);
	ck_assert(rank == 2);

	//printf("Rank: %d, should be: %d\n", rank, 2);
}
END_TEST

START_TEST (test_rank_query_lower_index) {
	char* string = "banana";
	wavelet_tree* tree = create_wavelet_tree(string);

	int rank = tree->rank(tree, 'a', 0, 3);
	ck_assert(rank == 2);

	//printf("Rank: %d, should be: %d\n", rank, 2);

	rank = tree->rank(tree, 'b', 0, 0);
	ck_assert(rank == 1);

	//printf("Rank: %d, should be: %d\n", rank, 1);

	rank = tree->rank(tree, 'n', 0, 1);
	ck_assert(rank == 0);

	//printf("Rank: %d, should be: %d\n", rank, 0);
}
END_TEST

START_TEST (test_rank_query_lower_index1) {
	char* string = "ard$rcaaaabb";
	wavelet_tree* tree = create_wavelet_tree(string);

	print_wavelet_tree(tree);

	int rank = tree->rank(tree, 'a', 0, 6);
	ck_assert(rank == 2);

	//printf("Rank: %d, should be: %d\n", rank, 2);

	rank = tree->rank(tree, 'b', 0, 10);
	ck_assert(rank == 1);

	//printf("Rank: %d, should be: %d\n", rank, 1);

	rank = tree->rank(tree, 'n', 0, INT_MAX);
	ck_assert(rank == 0);

	//printf("Rank: %d, should be: %d\n", rank, 0);
}
END_TEST

START_TEST (test_rank_query_long_string) {
	char* string = "LAsufhaliILUAShfauishfiuLIUASifuhasvgjbeaukfaAJLsyufluABsasfohASfliiuuBwLIUASFb8239LIUbf787glBAfAuiosdfhliUAFl789aASIFOy9ASfbilAfs98YL7gLify3bliafl98SAYFAAUKSFtifSAbAFYbKUASY8tfsakuyBfkuaYBASF7tk8asGYKJFsbKUAYSF87TASKufygskbjhKJysfa8g";
	wavelet_tree* root = create_wavelet_tree(string);

	int rank = root->rank(root, '2', 0, INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, '3', 0, INT_MAX);
	ck_assert(rank == 2);

	rank = root->rank(root, '7', 0, INT_MAX);
	ck_assert(rank == 6);

	rank = root->rank(root, '8', 0, INT_MAX);
	ck_assert(rank == 9);

	rank = root->rank(root, '9', 0, INT_MAX);
	ck_assert(rank == 5);

	rank = root->rank(root, 'A', 0, INT_MAX);
	ck_assert(rank == 22);

	rank = root->rank(root, 'B', 0, INT_MAX);
	ck_assert(rank == 5);

	rank = root->rank(root, 'F', 0, INT_MAX);
	ck_assert(rank == 9);

	rank = root->rank(root, 'G', 0, INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'I', 0, INT_MAX);
	ck_assert(rank == 5);

	rank = root->rank(root, 'J', 0, INT_MAX);
	ck_assert(rank == 3);

	rank = root->rank(root, 'K', 0, INT_MAX);
	ck_assert(rank == 6);

	rank = root->rank(root, 'L', 0, INT_MAX);
	ck_assert(rank == 8);

	rank = root->rank(root, 'O', 0, INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'S', 0, INT_MAX);
	ck_assert(rank == 13);

	rank = root->rank(root, 'T', 0, INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'U', 0, INT_MAX);
	ck_assert(rank == 8);

	rank = root->rank(root, 'Y', 0, INT_MAX);
	ck_assert(rank == 7);

	rank = root->rank(root, 'a', 0, INT_MAX);
	ck_assert(rank == 12);

	rank = root->rank(root, 'b', 0, INT_MAX);
	ck_assert(rank == 9);

	rank = root->rank(root, 'd', 0, INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'e', 0, INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'f', 0, INT_MAX);
	ck_assert(rank == 20);

	rank = root->rank(root, 'g', 0, INT_MAX);
	ck_assert(rank == 5);

	rank = root->rank(root, 'h', 0, INT_MAX);
	ck_assert(rank == 7);

	rank = root->rank(root, 'i', 0, INT_MAX);
	ck_assert(rank == 12);

	rank = root->rank(root, 'j', 0, INT_MAX);
	ck_assert(rank == 2);

	rank = root->rank(root, 'k', 0, INT_MAX);
	ck_assert(rank == 5);

	rank = root->rank(root, 'l', 0, INT_MAX);
	ck_assert(rank == 9);

	rank = root->rank(root, 'o', 0, INT_MAX);
	ck_assert(rank == 2);

	rank = root->rank(root, 's', 0, INT_MAX);
	ck_assert(rank == 13);

	rank = root->rank(root, 't', 0, INT_MAX);
	ck_assert(rank == 3);

	rank = root->rank(root, 'u', 0, INT_MAX);
	ck_assert(rank == 13);

	rank = root->rank(root, 'v', 0, INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'w', 0, INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'y', 0, INT_MAX);
	ck_assert(rank == 6);
}
END_TEST

START_TEST (test_rank_query_interval) {
	char* string = "banana";
	wavelet_tree* root = create_wavelet_tree(string);

	int rank = root->rank(root, 'a', 3, INT_MAX);
	ck_assert(rank == 2);

	//printf("Rank: %d, should be: %d\n", rank, 2);

	rank = root->rank(root, 'b', 2, INT_MAX);
	ck_assert(rank == 0);

	//printf("Rank: %d, should be: %d\n", rank, 0);

	rank = root->rank(root, 'n', 2, 3);
	ck_assert(rank == 1);

	//printf("Rank: %d, should be: %d\n", rank, 1);

	string = "abracadabra";
	root = create_wavelet_tree(string);

	rank = root->rank(root, 'a', 3, 7);
	ck_assert(rank == 3);

	rank = root->rank(root, 'b', 2, 5);
	ck_assert(rank == 0);

	rank = root->rank(root, 'c', 1, INT_MAX);
	ck_assert(rank == 1);

	rank = root->rank(root, 'd', 6, 6);
	ck_assert(rank == 1);

	rank = root->rank(root, 'r', 9, 10);
	ck_assert(rank == 1);
}
END_TEST

START_TEST (test_wavelet_char_at) {
	char* string = "banana";
	wavelet_tree* root = create_wavelet_tree(string);

	ck_assert(root->char_at(root, 0) == 'b');
	ck_assert(root->char_at(root, 1) == 'a');
	ck_assert(root->char_at(root, 2) == 'n');
	ck_assert(root->char_at(root, 3) == 'a');
	ck_assert(root->char_at(root, 4) == 'n');
	ck_assert(root->char_at(root, 5) == 'a');

	string = "abracadabra";
	root = create_wavelet_tree(string);

	ck_assert(root->char_at(root, 0) == 'a');
	ck_assert(root->char_at(root, 1) == 'b');
	ck_assert(root->char_at(root, 2) == 'r');
	ck_assert(root->char_at(root, 3) == 'a');
	ck_assert(root->char_at(root, 4) == 'c');
	ck_assert(root->char_at(root, 5) == 'a');
	ck_assert(root->char_at(root, 6) == 'd');
	ck_assert(root->char_at(root, 7) == 'a');
	ck_assert(root->char_at(root, 8) == 'b');
	ck_assert(root->char_at(root, 9) == 'r');
	ck_assert(root->char_at(root, 10) == 'a');
}
END_TEST

Suite* array_suite(void) {
	Suite* suite = suite_create("Wavelet Suite");

	TCase* tc_wavelet_tree = tcase_create("Wavelet Tree");
	tcase_add_test (tc_wavelet_tree, test_create_wavelet_tree);
	tcase_add_test (tc_wavelet_tree, test_faulty_parameters);

	TCase* tc_wavelet_rank = tcase_create("Wavelet Rank Query");
	tcase_add_test (tc_wavelet_rank, test_rank_query);
	tcase_add_test (tc_wavelet_rank, test_rank_query_lower_index);
	tcase_add_test (tc_wavelet_rank, test_rank_query_lower_index1);
	tcase_add_test (tc_wavelet_rank, test_rank_query_long_string);
	tcase_add_test (tc_wavelet_rank, test_rank_query_interval);

	TCase* tc_wavelet_char_at = tcase_create("Wavelet Char At");
	tcase_add_test (tc_wavelet_char_at, test_wavelet_char_at);

	suite_add_tcase (suite, tc_wavelet_tree);
	suite_add_tcase (suite, tc_wavelet_rank);
	suite_add_tcase (suite, tc_wavelet_char_at);

	return suite;
}

int main (void) {
	int number_failed;
	Suite* suite = array_suite();
	SRunner* suite_runner = srunner_create(suite);
	srunner_run_all(suite_runner, CK_VERBOSE);
	number_failed = srunner_ntests_failed(suite_runner);
	srunner_free(suite_runner);

	return (number_failed == 0) ? 0 : 1;
}
