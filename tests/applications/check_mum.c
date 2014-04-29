/*
 * check_mum.c
 *
 *  Created on: 14.3.2014
 *      Author: lvapaaka
 */

#include "../../src/core/iterate.h"
#include "../../src/core/s_to_bwt.h"
#include "../../src/utils/bit_vector.h"
#include "../../include/utils.h"
#include "../../src/applications/mum.h"
#include "../../src/applications/mapper.h"
#include "../../src/utils/structs.h"
#include "../utils_for_tests.h"

#include <stdlib.h>
#include <check.h>
#include <time.h>

START_TEST(test_mum1)
	{
		char** strings = malloc(2 * sizeof(char*));
		strings[0] = "laatikko";
		strings[1] = "mehukatti";
		parameter_struct* params = initialize_for_mums(strings, 1);
		iterator_state* state = iterate(params);
		mum_results* results = (mum_results*) params->ret_data;
		triplet* nodes = results->data;
		ck_assert_int_eq(2, results->length);
		ck_assert_int_eq(2, nodes[0].pos1);
		ck_assert_int_eq(1, nodes[0].pos2);
		ck_assert_int_eq(2, nodes[0].length);
		ck_assert_int_eq(8, nodes[1].pos1);
		ck_assert_int_eq(7, nodes[1].pos2);
		ck_assert_int_eq(2, nodes[1].length);

		free(strings);
		free(results->data);
		free(results);
		free_iterator_state(state);
		free(params);
	}END_TEST

START_TEST(test_mum1_mapped)
	{
		char** strings = malloc(2 * sizeof(char*));
		strings[0] = "laatikko";
		strings[1] = "mehukatti";
		parameter_struct* params = initialize_for_mums(strings, 1);
		iterator_state* state = iterate(params);
		mum_results* results = (mum_results*) params->ret_data;
		triplet* nodes = results->data;
		bit_vector** vectors = mum_make_bit_vectors(results,state);
		wavelet_tree* tree1 = s_to_bwt("laatikko"), *tree2 = s_to_bwt("mehukatti");
		map_mum_triplets_to_string(nodes, tree1, tree2, results->length, vectors);
		ck_assert_int_eq(2, results->length);
		ck_assert_int_eq(2, nodes[0].pos1);
		ck_assert_int_eq(5, nodes[0].pos2);
		ck_assert_int_eq(2, nodes[0].length);
		ck_assert_int_eq(3, nodes[1].pos1);
		ck_assert_int_eq(7, nodes[1].pos2);
		ck_assert_int_eq(2, nodes[1].length);

		free(tree1->nodes[0].string);
		free(tree2->nodes[0].string);
		free_wavelet_tree(tree1);
		free_wavelet_tree(tree2);
		free_bit_vector(vectors[0]);
		free_bit_vector(vectors[1]);
		free(vectors);
		free(strings);
		free(results->data);
		free(results);
		free_iterator_state(state);
		free(params);
	}END_TEST

START_TEST(test_mum2)
	{
		char** strings = malloc(2 * sizeof(char*));
		strings[0] = "abracadabra";
		strings[1] = "arbadacarba";
		parameter_struct* params = initialize_for_mums(strings, 1);
		iterator_state* state = iterate(params);
		mum_results* results = (mum_results*) params->ret_data;
		triplet* nodes = results->data;
		ck_assert_int_eq(2, results->length);
		ck_assert_int_eq(5, nodes[0].pos1);
		ck_assert_int_eq(3, nodes[0].pos2);
		ck_assert_int_eq(3, nodes[0].length);
		ck_assert_int_eq(4, nodes[1].pos1);
		ck_assert_int_eq(2, nodes[1].pos2);
		ck_assert_int_eq(3, nodes[1].length);

		free(strings);
		free(results->data);
		free(results);
		free_iterator_state(state);
		free(params);
	}END_TEST

START_TEST(test_mum2_mapped)
	{
		char** strings = malloc(2 * sizeof(char*));
		strings[0] = "abracadabra";
		strings[1] = "arbadacarba";
		parameter_struct* params = initialize_for_mums(strings, 1);
		iterator_state* state = iterate(params);
		mum_results* results = (mum_results*) params->ret_data;
		triplet* nodes = results->data;
		bit_vector** vectors = mum_make_bit_vectors(results, state);
		wavelet_tree* tree1 = s_to_bwt("abracadabra"), *tree2 = s_to_bwt("arbadacarba");
		map_mum_triplets_to_string(nodes, tree1, tree2, results->length, vectors);
		ck_assert_int_eq(2, results->length);
		ck_assert_int_eq(3, nodes[0].pos1);
		ck_assert_int_eq(5, nodes[0].pos2);
		ck_assert_int_eq(3, nodes[0].length);
		ck_assert_int_eq(5, nodes[1].pos1);
		ck_assert_int_eq(3, nodes[1].pos2);
		ck_assert_int_eq(3, nodes[1].length);

		free(tree1->nodes[0].string);
		free(tree2->nodes[0].string);
		free_wavelet_tree(tree1);
		free_wavelet_tree(tree2);
		free_bit_vector(vectors[0]);
		free_bit_vector(vectors[1]);
		free(vectors);
		free(strings);
		free(results->data);
		free(results);
		free_iterator_state(state);
		free(params);
	}END_TEST

START_TEST(test_mum_empty)
	{
		char** strings = malloc(2 * sizeof(char*));
		strings[0] = "qwertyui";
		strings[1] = "asdfghjkl";
		parameter_struct* params = initialize_for_mums(strings, 1);
		iterator_state* state = iterate(params);
		mum_results* results = (mum_results*) params->ret_data;
		ck_assert_int_eq(0, results->length);

		free(strings);
		free(results->data);
		free(results);
		free_iterator_state(state);
		free(params);
	}END_TEST

START_TEST(test_mum3)
	{
		char** strings = malloc(2 * sizeof(char*));
		strings[0] = "qwertnmyuiop";
		strings[1] = "asdfgnmhjkl";
		parameter_struct* params = initialize_for_mums(strings, 1);
		iterator_state* state = iterate(params);
		mum_results* results = (mum_results*) params->ret_data;
		triplet* nodes = results->data;
		ck_assert_int_eq(1, results->length);
		ck_assert_int_eq(2, nodes[0].length);

		free(strings);
		free(results->data);
		free(results);
		free_iterator_state(state);
		free(params);
	}END_TEST

START_TEST(test_mum3_mapped)
	{
		char** strings = malloc(2 * sizeof(char*));
		strings[0] = "qwertnmyuiop";
		strings[1] = "asdfgnmhjkl";
		parameter_struct* params = initialize_for_mums(strings, 1);
		iterator_state* state = iterate(params);
		mum_results* results = (mum_results*) params->ret_data;
		triplet* nodes = results->data;
		bit_vector** vectors = mum_make_bit_vectors(results, state);
		wavelet_tree* tree1 = s_to_bwt("qwertnmyuiop"), *tree2 = s_to_bwt("asdfgnmhjkl");
		map_mum_triplets_to_string(nodes, tree1, tree2, results->length, vectors);
		ck_assert_int_eq(1, results->length);
		ck_assert_int_eq(5, nodes[0].pos1);
		ck_assert_int_eq(5, nodes[0].pos2);
		ck_assert_int_eq(2, nodes[0].length);

		free(tree1->nodes[0].string);
		free(tree2->nodes[0].string);
		free_wavelet_tree(tree1);
		free_wavelet_tree(tree2);
		free_bit_vector(vectors[0]);
		free_bit_vector(vectors[1]);
		free(vectors);
		free(strings);
		free(results->data);
		free(results);
		free_iterator_state(state);
		free(params);
	}END_TEST

START_TEST(test_mum1_bitvector)
	{
		char** strings = malloc(2 * sizeof(char*));
		strings[0] = "laatikko";
		strings[1] = "mehukatti";
		parameter_struct* params = initialize_for_mums(strings, 1);
		iterator_state* state = iterate(params);
		mum_results* results = (mum_results*) params->ret_data;
		bit_vector** vectors = mum_make_bit_vectors(results, state);
		wavelet_tree* tree1 = s_to_bwt("laatikko"), *tree2 = s_to_bwt("mehukatti");
		map_mum_triplets_to_string(results->data, tree1, tree2, results->length, vectors);

		free_bit_vector(vectors[0]);
		free_bit_vector(vectors[1]);
		free(vectors);
		vectors = mum_make_bit_vectors(results, state);

		ck_assert_int_eq(1, vectors[0]->is_bit_marked(vectors[0], 2));
		ck_assert_int_eq(1, vectors[0]->is_bit_marked(vectors[0], 3));
		ck_assert_int_eq(0, vectors[0]->is_bit_marked(vectors[0], 5));
		ck_assert_int_eq(0, vectors[0]->is_bit_marked(vectors[0], 7));
		ck_assert_int_eq(1, vectors[1]->is_bit_marked(vectors[1], 5));
		ck_assert_int_eq(1, vectors[1]->is_bit_marked(vectors[1], 7));
		ck_assert_int_eq(0, vectors[1]->is_bit_marked(vectors[1], 2));
		ck_assert_int_eq(0, vectors[1]->is_bit_marked(vectors[1], 3));

		free(tree1->nodes[0].string);
		free(tree2->nodes[0].string);
		free_wavelet_tree(tree1);
		free_wavelet_tree(tree2);
		free_bit_vector(vectors[0]);
		free_bit_vector(vectors[1]);
		free(vectors);
		free(strings);
		free(results->data);
		free(results);
		free_iterator_state(state);
		free(params);
	}END_TEST

START_TEST(test_mum2_bitvector)
	{
		char** strings = malloc(2 * sizeof(char*));
		strings[0] = "abracadabra";
		strings[1] = "arbadacarba";
		parameter_struct* params = initialize_for_mums(strings, 1);
		iterator_state* state = iterate(params);
		mum_results* results = (mum_results*) params->ret_data;
		bit_vector** vectors = mum_make_bit_vectors(results, state);
		wavelet_tree* tree1 = s_to_bwt("abracadabra"), *tree2 = s_to_bwt("arbadacarba");
		map_mum_triplets_to_string(results->data, tree1, tree2, results->length, vectors);

		free_bit_vector(vectors[0]);
		free_bit_vector(vectors[1]);
		free(vectors);
		vectors = mum_make_bit_vectors(results, state);

		ck_assert_int_eq(1, vectors[0]->is_bit_marked(vectors[0], 3));
		ck_assert_int_eq(1, vectors[0]->is_bit_marked(vectors[0], 5));
		ck_assert_int_eq(1, vectors[1]->is_bit_marked(vectors[1], 3));
		ck_assert_int_eq(1, vectors[1]->is_bit_marked(vectors[1], 5));

		free(tree1->nodes[0].string);
		free(tree2->nodes[0].string);
		free_wavelet_tree(tree1);
		free_wavelet_tree(tree2);
		free_bit_vector(vectors[0]);
		free_bit_vector(vectors[1]);
		free(vectors);
		free(strings);
		free(results->data);
		free(results);
		free_iterator_state(state);
		free(params);
	}END_TEST

START_TEST(test_mum3_bitvector_no_mums)
	{
		char** strings = malloc(2 * sizeof(char*));
		strings[0] = "abracadabra";
		strings[1] = "vzxmneytymn";
		parameter_struct* params = initialize_for_mums(strings, 1);
		iterator_state* state = iterate(params);
		mum_results* results = (mum_results*) params->ret_data;
		bit_vector** vectors = mum_make_bit_vectors(results, state);
		wavelet_tree* tree1 = s_to_bwt("abracadabra"), *tree2 = s_to_bwt("vzxmneytymn");
		map_mum_triplets_to_string(results->data, tree1, tree2, results->length, vectors);

		free_bit_vector(vectors[0]);
		free_bit_vector(vectors[1]);
		free(vectors);
		vectors = mum_make_bit_vectors(results, state);

		int i;
		for (i = 0; i < vectors[0]->length; i++) {
			ck_assert_int_eq(0, vectors[0]->is_bit_marked(vectors[0], i));
		}
		for (i = 0; i < vectors[1]->length; i++) {
			ck_assert_int_eq(0, vectors[1]->is_bit_marked(vectors[1], i));
		}

		free(tree1->nodes[0].string);
		free(tree2->nodes[0].string);
		free_wavelet_tree(tree1);
		free_wavelet_tree(tree2);
		free_bit_vector(vectors[0]);
		free_bit_vector(vectors[1]);
		free(vectors);
		free(strings);
		free(results->data);
		free(results);
		free_iterator_state(state);
		free(params);
	}END_TEST

int search_and_remove(triplet trip, substring_pair* head) {
	substring_pair* previous = head;
	substring_pair* current = head->next;
	while (current != NULL) {
		if (trip.pos1 == current->index1 && trip.pos2 == current->index2
				&& trip.length == current->length) {
			previous->next = current->next;
			free(current);
			return 1;
		}
		previous = previous->next;
		current = current->next;
	}
	return 0;
}

START_TEST(test_mums_randomized_small_alphabet)
	{
		srand(time(NULL));
		char** strings = malloc(2 * sizeof(char*));
		char* alphabet = "abcgdf";
		substring_pair* naive_mums;
		parameter_struct* params;
		iterator_state* state;
		bit_vector** vectors;

		for (int i = 0; i < 100; i++) {
			int len1 = rand() % 100 + 1;
			int len2 = rand() % 100 + 1;

			strings[0] = generate_random_string(alphabet, len1);
			strings[1] = generate_random_string(alphabet, len2);
			int threshold = rand()%5+1;
			naive_mums = find_maximal_unique_matches(strings[0], strings[1], threshold);

			params = initialize_for_mums(strings, threshold);
			state = iterate(params);
			mum_results* results = (mum_results*) params->ret_data;
			triplet* fast_mems = results->data;
			int num_mums = results->length;

			//custom mapping for mems. This has to be changed when real mapping is ready.
			vectors = mum_make_bit_vectors(results,state);
			map_mum_triplets_to_string(fast_mems, &state->bwts[0],
					&state->bwts[1], num_mums, vectors);

			for (int j = 0; j < num_mums; j++)
				fail_unless(search_and_remove(fast_mems[j], naive_mums));

			fail_unless(naive_mums->next == NULL);

			free_bit_vector(vectors[0]);
			free_bit_vector(vectors[1]);
			free(vectors);
			free(strings[0]);
			free(strings[1]);
			free(results);
			free(params);
			free(naive_mums);
			free_iterator_state(state);
		}

		free(strings);
	}END_TEST

START_TEST(test_mums_randomized_big_alphabet)
	{
		srand(time(NULL));
		char** strings = malloc(2 * sizeof(char*));
		char* alphabet = "q1a2s3d4xtc6v7ghun8j9km0plo";
		substring_pair* naive_mums;
		parameter_struct* params;
		iterator_state* state;
		bit_vector** vectors;

		for (int i = 0; i < 100; i++) {
			int len1 = rand() % 100 + 1;
			int len2 = rand() % 100 + 1;

			strings[0] = generate_random_string(alphabet, len1);
			strings[1] = generate_random_string(alphabet, len2);

			naive_mums = find_maximal_unique_matches(strings[0], strings[1], 1);

			params = initialize_for_mums(strings, 1);
			state = iterate(params);
			mum_results* results = (mum_results*) params->ret_data;
			triplet* fast_mems = results->data;
			int num_mums = results->length;

			//custom mapping for mems. This has to be changed when real mapping is ready.
			vectors = mum_make_bit_vectors(results,state);
			map_mum_triplets_to_string(fast_mems, &state->bwts[0],
					&state->bwts[1], num_mums, vectors);

			for (int j = 0; j < num_mums; j++)
				fail_unless(search_and_remove(fast_mems[j], naive_mums));

			fail_unless(naive_mums->next == NULL);

			free_bit_vector(vectors[0]);
			free_bit_vector(vectors[1]);
			free(vectors);
			free(strings[0]);
			free(strings[1]);
			free(results);
			free(params);
			free(naive_mums);
			free_iterator_state(state);
		}

		free(strings);
	}END_TEST

TCase * create_mums_test_case(void) {
	TCase * tc_mums = tcase_create("mum_test");
	tcase_add_test(tc_mums, test_mum1);
	tcase_add_test(tc_mums, test_mum1_mapped);
	tcase_add_test(tc_mums, test_mum2);
	tcase_add_test(tc_mums, test_mum2_mapped);
	tcase_add_test(tc_mums, test_mum3);
	tcase_add_test(tc_mums, test_mum3_mapped);
	tcase_add_test(tc_mums, test_mum_empty);
	tcase_add_test(tc_mums, test_mum1_bitvector);
	tcase_add_test(tc_mums, test_mum2_bitvector);
	tcase_add_test(tc_mums, test_mum3_bitvector_no_mums);
	return tc_mums;
}

TCase * create_mums_randomized_test_case(void) {
	TCase * tc_random_mums = tcase_create("random_mums");
	tcase_add_test(tc_random_mums, test_mums_randomized_small_alphabet);
	tcase_add_test(tc_random_mums, test_mums_randomized_big_alphabet);
	return tc_random_mums;
}

Suite * test_suite(void) {
	Suite *s = suite_create("testi");
	suite_add_tcase(s, create_mums_test_case());
	suite_add_tcase(s, create_mums_randomized_test_case());

	return s;
}

int main() {
	int number_failed;
	Suite *s = test_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	if (number_failed == 0) {
		return 0;
	} else {
		return 1;
	}
}

