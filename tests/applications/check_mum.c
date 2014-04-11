/*
 * check_mum.c
 *
 *  Created on: 14.3.2014
 *      Author: lvapaaka
 */

#include "../../src/core/iterate.h"
#include "../../src/core/s_to_bwt.h"
#include "../../src/utils/bit_vector.h"
#include "../../src/applications/mum.h"
#include "../../src/applications/mapper.h"
#include <stdlib.h>
#include <check.h>

START_TEST(test_mum1)
{
	char** strings = malloc(2 * sizeof(char*));
	strings[0] = "laatikko";
	strings[1] = "mehukatti";
	parameter_struct* params = initialize_for_mums(strings);
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
	free_iterator_state(state);
	//free_parameter_struct(params);
}END_TEST

START_TEST(test_mum1_mapped)
{
	char** strings = malloc(2 * sizeof(char*));
	strings[0] = "laatikko";
	strings[1] = "mehukatti";
	parameter_struct* params = initialize_for_mums(strings);
	iterator_state* state = iterate(params);
	mum_results* results = (mum_results*) params->ret_data;
	triplet* nodes = results->data;
	map_mum_triplets_to_string(nodes, s_to_bwt("laatikko"), s_to_bwt("mehukatti"), results->length);
	ck_assert_int_eq(2, results->length);
	ck_assert_int_eq(2, nodes[0].pos1);
	ck_assert_int_eq(5, nodes[0].pos2);
	ck_assert_int_eq(2, nodes[0].length);
	ck_assert_int_eq(3, nodes[1].pos1);
	ck_assert_int_eq(7, nodes[1].pos2);
	ck_assert_int_eq(2, nodes[1].length);

	free(strings);
	free(results->data);
	free_iterator_state(state);
	//free_parameter_struct(params);
}END_TEST

START_TEST(test_mum2)
{
	char** strings = malloc(2 * sizeof(char*));
	strings[0] = "abracadabra";
	strings[1] = "arbadacarba";
	parameter_struct* params = initialize_for_mums(strings);
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
	free_iterator_state(state);
	//free_parameter_struct(params);
}END_TEST

START_TEST(test_mum2_mapped)
{
	char** strings = malloc(2 * sizeof(char*));
	strings[0] = "abracadabra";
	strings[1] = "arbadacarba";
	parameter_struct* params = initialize_for_mums(strings);
	iterator_state* state = iterate(params);
	mum_results* results = (mum_results*) params->ret_data;
	triplet* nodes = results->data;
	map_mum_triplets_to_string(nodes, s_to_bwt("abracadabra"), s_to_bwt("arbadacarba"), results->length);
	ck_assert_int_eq(2, results->length);
	ck_assert_int_eq(5, nodes[0].pos1);
	ck_assert_int_eq(3, nodes[0].pos2);
	ck_assert_int_eq(3, nodes[0].length);
	ck_assert_int_eq(3, nodes[1].pos1);
	ck_assert_int_eq(5, nodes[1].pos2);
	ck_assert_int_eq(3, nodes[1].length);

	free(strings);
	free(results->data);
	free_iterator_state(state);
	//free_parameter_struct(params);
}END_TEST

START_TEST(test_mum_empty)
{
	char** strings = malloc(2 * sizeof(char*));
	strings[0] = "qwertyui";
	strings[1] = "asdfghjkl";
	parameter_struct* params = initialize_for_mums(strings);
	iterator_state* state = iterate(params);
	mum_results* results = (mum_results*) params->ret_data;
	ck_assert_int_eq(0, results->length);

	free(strings);
	free(results->data);
	free_iterator_state(state);
	//free_parameter_struct(params);
}END_TEST

START_TEST(test_mum3)
{
	char** strings = malloc(2 * sizeof(char*));
	strings[0] = "qwertnmyuiop";
	strings[1] = "asdfgnmhjkl";
	parameter_struct* params = initialize_for_mums(strings);
	iterator_state* state = iterate(params);
	mum_results* results = (mum_results*) params->ret_data;
	triplet* nodes = results->data;
	ck_assert_int_eq(1, results->length);
	ck_assert_int_eq(2, nodes[0].length);

	free(strings);
	free(results->data);
	free_iterator_state(state);
	//free_parameter_struct(params);
}END_TEST

START_TEST(test_mum3_mapped)
{
	char** strings = malloc(2 * sizeof(char*));
	strings[0] = "qwertnmyuiop";
	strings[1] = "asdfgnmhjkl";
	parameter_struct* params = initialize_for_mums(strings);
	iterator_state* state = iterate(params);
	mum_results* results = (mum_results*) params->ret_data;
	triplet* nodes = results->data;
	map_mum_triplets_to_string(nodes, s_to_bwt("qwertnmyuiop"), s_to_bwt("asdfgnmhjkl"), results->length);
	ck_assert_int_eq(1, results->length);
	ck_assert_int_eq(5, nodes[0].pos1);
	ck_assert_int_eq(5, nodes[0].pos2);
	ck_assert_int_eq(2, nodes[0].length);

	free(strings);
	free(results->data);
	free_iterator_state(state);
	//free_parameter_struct(params);
}END_TEST

START_TEST(test_mum1_bitvector)
{
	char** strings = malloc(2 * sizeof(char*));
	strings[0] = "laatikko";
	strings[1] = "mehukatti";
	parameter_struct* params = initialize_for_mums(strings);
	iterator_state* state = iterate(params);
	mum_results* results = (mum_results*) params->ret_data;
	map_mum_triplets_to_string(results->data, s_to_bwt("laatikko"), s_to_bwt("mehukatti"), results->length);
	bit_vector** vectors = mum_make_bit_vectors(results, state);
	ck_assert_int_eq(1, vectors[0]->is_bit_marked(vectors[0], 2));
	ck_assert_int_eq(1, vectors[0]->is_bit_marked(vectors[0], 3));
	ck_assert_int_eq(0, vectors[0]->is_bit_marked(vectors[0], 5));
	ck_assert_int_eq(0, vectors[0]->is_bit_marked(vectors[0], 7));
	ck_assert_int_eq(1, vectors[1]->is_bit_marked(vectors[1], 5));
	ck_assert_int_eq(1, vectors[1]->is_bit_marked(vectors[1], 7));
	ck_assert_int_eq(0, vectors[1]->is_bit_marked(vectors[1], 2));
	ck_assert_int_eq(0, vectors[1]->is_bit_marked(vectors[1], 3));

	free(strings);
	free(results->data);
	free_bit_vector(vectors[0]);
	free_bit_vector(vectors[1]);
	free_iterator_state(state);
	//free_parameter_struct(params);
}END_TEST

START_TEST(test_mum2_bitvector)
{
	char** strings = malloc(2 * sizeof(char*));
	strings[0] = "abracadabra";
	strings[1] = "arbadacarba";
	parameter_struct* params = initialize_for_mums(strings);
	iterator_state* state = iterate(params);
	mum_results* results = (mum_results*) params->ret_data;
	map_mum_triplets_to_string(results->data, s_to_bwt("abracadabra"), s_to_bwt("arbadacarba"), results->length);
	bit_vector** vectors = mum_make_bit_vectors(results, state);
	ck_assert_int_eq(1, vectors[0]->is_bit_marked(vectors[0], 3));
	ck_assert_int_eq(1, vectors[0]->is_bit_marked(vectors[0], 5));
	ck_assert_int_eq(1, vectors[1]->is_bit_marked(vectors[1], 3));
	ck_assert_int_eq(1, vectors[1]->is_bit_marked(vectors[1], 5));

	free(strings);
	free(results->data);
	free_bit_vector(vectors[0]);
	free_bit_vector(vectors[1]);
	free_iterator_state(state);
	//free_parameter_struct(params);
}END_TEST

START_TEST(test_mum3_bitvector_no_mums)
{
	char** strings = malloc(2 * sizeof(char*));
	strings[0] = "abracadabra";
	strings[1] = "vzxmneytymn";
	parameter_struct* params = initialize_for_mums(strings);
	iterator_state* state = iterate(params);
	mum_results* results = (mum_results*) params->ret_data;
	map_mum_triplets_to_string(results->data, s_to_bwt("abracadabra"),s_to_bwt("arbadacarba"), results->length);
	bit_vector** vectors = mum_make_bit_vectors(results, state);
	int i;
	for (i = 0; i < vectors[0]->length; i++) {
		ck_assert_int_eq(0, vectors[0]->is_bit_marked(vectors[0], i));
	}
	for (i = 0; i < vectors[1]->length; i++) {
		ck_assert_int_eq(0, vectors[1]->is_bit_marked(vectors[1], i));
	}

	free(strings);
	free(results->data);
	free_bit_vector(vectors[0]);
	free_bit_vector(vectors[1]);
	free_iterator_state(state);
	//free_parameter_struct(params);
}END_TEST

TCase * create_mums_test_case(void) {
	TCase * tc_stack = tcase_create("mum_test");
	tcase_add_test(tc_stack, test_mum1);
	tcase_add_test(tc_stack, test_mum1_mapped);
	tcase_add_test(tc_stack, test_mum2);
	tcase_add_test(tc_stack, test_mum2_mapped);
	tcase_add_test(tc_stack, test_mum3);
	tcase_add_test(tc_stack, test_mum3_mapped);
	tcase_add_test(tc_stack, test_mum_empty);
	tcase_add_test(tc_stack, test_mum1_bitvector);
	tcase_add_test(tc_stack, test_mum2_bitvector);
	tcase_add_test(tc_stack, test_mum3_bitvector_no_mums);
	return tc_stack;
}

Suite * test_suite(void) {
	Suite *s = suite_create("testi");
	TCase *tc_stack = create_mums_test_case();
	suite_add_tcase(s, tc_stack);

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

