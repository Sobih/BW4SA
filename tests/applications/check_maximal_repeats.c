/*
 * check_maximal_repeats.c
 *
 *  Created on: 13.3.2014
 *      Author: lvapaaka
 */

#include "../utils_for_tests.h"
#include "../../src/core/iterate.h"
#include "../../src/core/s_to_bwt.h"
#include "../../src/applications/maximal_repeats.h"
#include "../../src/applications/mapper.h"
#include "../../src/applications/map_bwt_to_s.h"
#include "../../src/utils/wavelet_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <check.h>

START_TEST(test_maximal_repeat2)
	{
		iterate("abracadabra", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		ck_assert_int_eq(2, get_max_repeats_nodes_index());
		ck_assert_int_eq(1, nodes[0].normal.i);
		ck_assert_int_eq(5, nodes[0].normal.j);
		ck_assert_int_eq(1, nodes[0].length);
		ck_assert_int_eq(2, nodes[1].normal.i);
		ck_assert_int_eq(3, nodes[1].normal.j);
		ck_assert_int_eq(4, nodes[1].length);
	}END_TEST

START_TEST(test_maximal_repeat2_mapped)
	{
		iterate("abracadabra", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		map_maximal_repeats_to_string(nodes, s_to_BWT("abracadabra"),get_max_repeats_nodes_index(), max_repeat_make_bit_vector(nodes));
		ck_assert_int_eq(2, get_max_repeats_nodes_index());
		ck_assert_int_eq(10, nodes[0].normal.i);
		ck_assert_int_eq(1, nodes[0].length);
		ck_assert_int_eq(7, nodes[1].normal.i);
		ck_assert_int_eq(4, nodes[1].length);
	}END_TEST

START_TEST(test_maximal_repeat2b)
	{
		iterate("hattivatti", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		ck_assert_int_eq(2, get_max_repeats_nodes_index());
		ck_assert_int_eq(6, nodes[0].normal.i);
		ck_assert_int_eq(9, nodes[0].normal.j);
		ck_assert_int_eq(1, nodes[0].length);
		ck_assert_int_eq(1, nodes[1].normal.i);
		ck_assert_int_eq(2, nodes[1].normal.j);
		ck_assert_int_eq(4, nodes[1].length);
	}END_TEST

START_TEST(test_maximal_repeat2b_mapped)
	{
		iterate("hattivatti", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		map_maximal_repeats_to_string(nodes, s_to_BWT("hattivatti"),get_max_repeats_nodes_index(), max_repeat_make_bit_vector(nodes));
		ck_assert_int_eq(2, get_max_repeats_nodes_index());
		ck_assert_int_eq(8, nodes[0].normal.i);
		ck_assert_int_eq(1, nodes[0].length);
		ck_assert_int_eq(6, nodes[1].normal.i);
		ck_assert_int_eq(4, nodes[1].length);
	}END_TEST

START_TEST(test_maximal_repeat3)
	{
		iterate("balalaikka", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		ck_assert_int_eq(3, get_max_repeats_nodes_index());
		ck_assert_int_eq(1, nodes[0].normal.i);
		ck_assert_int_eq(4, nodes[0].normal.j);
		ck_assert_int_eq(1, nodes[0].length);
		ck_assert_int_eq(7, nodes[1].normal.i);
		ck_assert_int_eq(8, nodes[1].normal.j);
		ck_assert_int_eq(1, nodes[1].length);
		ck_assert_int_eq(3, nodes[2].normal.i);
		ck_assert_int_eq(4, nodes[2].normal.j);
		ck_assert_int_eq(3, nodes[2].length);
	}END_TEST

START_TEST(test_maximal_repeat3_mapped)
	{
		iterate("balalaikka", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		map_maximal_repeats_to_string(nodes, s_to_BWT("balalaikka"),get_max_repeats_nodes_index(),max_repeat_make_bit_vector(nodes));
		ck_assert_int_eq(3, get_max_repeats_nodes_index());
		ck_assert_int_eq(9, nodes[0].normal.i);
		ck_assert_int_eq(1, nodes[0].length);
		ck_assert_int_eq(8, nodes[1].normal.i);
		ck_assert_int_eq(1, nodes[1].length);
		ck_assert_int_eq(3, nodes[2].normal.i);
		ck_assert_int_eq(3, nodes[2].length);
	}END_TEST

START_TEST(test_maximal_repeat_empty)
	{
		iterate("abc", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		ck_assert_int_eq(0, get_max_repeats_nodes_index());
	}END_TEST

START_TEST(test_maximal_repeat1)
	{
		iterate("ilotalo", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		ck_assert_int_eq(1, get_max_repeats_nodes_index());
		ck_assert_int_eq(3, nodes[0].normal.i);
		ck_assert_int_eq(4, nodes[0].normal.j);
		ck_assert_int_eq(2, nodes[0].length);
	}END_TEST

START_TEST(test_maximal_repeat1_mapped)
	{
		iterate("ilotalo", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		map_maximal_repeats_to_string(nodes, s_to_BWT("ilotalo"),get_max_repeats_nodes_index(),max_repeat_make_bit_vector(nodes));
		ck_assert_int_eq(1, get_max_repeats_nodes_index());
		ck_assert_int_eq(5, nodes[0].normal.i);
		ck_assert_int_eq(2, nodes[0].length);
	}END_TEST

//returns 0 if the searched substring is not found
int find_and_remove_test_substr(test_substr* head, int index, int length) {
	test_substr* previous = head;
	test_substr* current = head->next;

	while (current != NULL) {

		if (current->length == length && current->start_index == index) {
			previous->next = current->next;
			free(current);
			return 1;
		}
		previous = current;
		current = current->next;
	}
	return 0;
}

START_TEST(test_max_repeats_randomized)
{
	srand(time(NULL));
	char* test;
	wavelet_tree* bwt;
	int* suffix_array;
	int length;
	char* alphabet = "abcgdf";

	for (int i = 0; i < 100; i++) {

		test = generate_random_string(alphabet, rand() % 100 + 1);
		bwt = s_to_BWT(test);
		suffix_array = map_create_suffix_array_from_bwt(bwt);

		test_substr* maxrep_naive = find_maximal_repeat_substrings(test);
		iterate(test, &search_maximal_repeats);
		max_repeat_node* maxrep_fast = get_nodes();

		int max_number_nodes = get_max_repeats_nodes_index();

		for(int j = 0; j < max_number_nodes; j++){
			for(int k = 0; k + maxrep_fast[j].normal.i <=  maxrep_fast[j].normal.j; k++){

				fail_unless(find_and_remove_test_substr(maxrep_naive,
						 suffix_array[maxrep_fast[j].normal.i + k], maxrep_fast[j].length));
			}
		}
		print_substring_list(test, maxrep_naive);
		fail_unless(maxrep_naive->next == NULL);

	}
}END_TEST

START_TEST(test_max_repeats_randomized2)
{
	srand(time(NULL));
	char* test;
	wavelet_tree* bwt;
	int* suffix_array;
	int length;
	char* alphabet = "aoskfdhebs";

	for (int i = 0; i < 10; i++) {

		test = generate_random_string(alphabet, rand() % 1000 + 100);
		bwt = s_to_BWT(test);
		suffix_array = map_create_suffix_array_from_bwt(bwt);

		test_substr* maxrep_naive = find_maximal_repeat_substrings(test);
		iterate(test, &search_maximal_repeats);
		max_repeat_node* maxrep_fast = get_nodes();

		int max_number_nodes = get_max_repeats_nodes_index();

		for(int j = 0; j < max_number_nodes; j++){
			for(int k = 0; k + maxrep_fast[j].normal.i <=  maxrep_fast[j].normal.j; k++){

				fail_unless(find_and_remove_test_substr(maxrep_naive,
						 suffix_array[maxrep_fast[j].normal.i + k], maxrep_fast[j].length));
			}
		}
		print_substring_list(test, maxrep_naive);
		fail_unless(maxrep_naive->next == NULL);

	}
}END_TEST

TCase * create_max_repeats_randomized_test_case(void) {
	TCase * tc_randrep = tcase_create("max_repeats_randomized");
	tcase_add_test(tc_randrep, test_max_repeats_randomized2);
	tcase_add_test(tc_randrep, test_max_repeats_randomized);
	tcase_set_timeout(tc_randrep, 100);
	return tc_randrep;
}

TCase * create_maximal_repeats_test_case(void) {
	TCase * tc_stack = tcase_create("maximal_repeat_test");
	tcase_add_test(tc_stack, test_maximal_repeat2);
	tcase_add_test(tc_stack, test_maximal_repeat2_mapped);
	tcase_add_test(tc_stack, test_maximal_repeat2b);
	tcase_add_test(tc_stack, test_maximal_repeat2b_mapped);
	tcase_add_test(tc_stack, test_maximal_repeat3);
	tcase_add_test(tc_stack, test_maximal_repeat3_mapped);
	tcase_add_test(tc_stack, test_maximal_repeat_empty);
	tcase_add_test(tc_stack, test_maximal_repeat1);
	tcase_add_test(tc_stack, test_maximal_repeat1_mapped);
	return tc_stack;
}

Suite * test_suite(void) {
	Suite *s = suite_create("Maximal repeats tests");
	TCase *tc_stack = create_maximal_repeats_test_case();
	TCase *tc_randrep = create_max_repeats_randomized_test_case();
	suite_add_tcase(s, tc_stack);
	suite_add_tcase(s, tc_randrep);

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

