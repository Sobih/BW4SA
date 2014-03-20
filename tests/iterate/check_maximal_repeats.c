/*
 * check_maximal_repeats.c
 *
 *  Created on: 13.3.2014
 *      Author: lvapaaka
 */

#include <check.h>
#include "../../include/iterate.h"
#include "../../include/maximal_repeats.h"
#include "../../include/mapper.h"
#include "../../src/bwt/s_to_bwt.h"
#include <stdlib.h>

START_TEST(test_maximal_repeat2)
	{
		iterate("abracadabra", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		ck_assert_int_eq(2, get_max_repeats_nodes_index());
		ck_assert_int_eq(1, nodes[0].normal->i);
		ck_assert_int_eq(5, nodes[0].normal->j);
		ck_assert_int_eq(1, nodes[0].length);
		ck_assert_int_eq(2, nodes[1].normal->i);
		ck_assert_int_eq(3, nodes[1].normal->j);
		ck_assert_int_eq(4, nodes[1].length);
	}END_TEST

START_TEST(test_maximal_repeat2_mapped)
	{
		iterate("abracadabra", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		map_maximal_repeats_to_string(nodes, s_to_BWT("abracadabra"),get_max_repeats_nodes_index());
		ck_assert_int_eq(2, get_max_repeats_nodes_index());
		ck_assert_int_eq(10, nodes[0].normal->i);
		ck_assert_int_eq(1, nodes[0].length);
		ck_assert_int_eq(7, nodes[1].normal->i);
		ck_assert_int_eq(4, nodes[1].length);
	}END_TEST

START_TEST(test_maximal_repeat2b)
	{
		iterate("hattivatti", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		ck_assert_int_eq(2, get_max_repeats_nodes_index());
		ck_assert_int_eq(6, nodes[0].normal->i);
		ck_assert_int_eq(9, nodes[0].normal->j);
		ck_assert_int_eq(1, nodes[0].length);
		ck_assert_int_eq(1, nodes[1].normal->i);
		ck_assert_int_eq(2, nodes[1].normal->j);
		ck_assert_int_eq(4, nodes[1].length);
	}END_TEST

START_TEST(test_maximal_repeat2b_mapped)
	{
		iterate("hattivatti", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		map_maximal_repeats_to_string(nodes, s_to_BWT("hattivatti"),get_max_repeats_nodes_index());
		ck_assert_int_eq(2, get_max_repeats_nodes_index());
		ck_assert_int_eq(8, nodes[0].normal->i);
		ck_assert_int_eq(1, nodes[0].length);
		ck_assert_int_eq(6, nodes[1].normal->i);
		ck_assert_int_eq(4, nodes[1].length);
	}END_TEST

START_TEST(test_maximal_repeat3)
	{
		iterate("balalaikka", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		ck_assert_int_eq(3, get_max_repeats_nodes_index());
		ck_assert_int_eq(1, nodes[0].normal->i);
		ck_assert_int_eq(4, nodes[0].normal->j);
		ck_assert_int_eq(1, nodes[0].length);
		ck_assert_int_eq(7, nodes[1].normal->i);
		ck_assert_int_eq(8, nodes[1].normal->j);
		ck_assert_int_eq(1, nodes[1].length);
		ck_assert_int_eq(3, nodes[2].normal->i);
		ck_assert_int_eq(4, nodes[2].normal->j);
		ck_assert_int_eq(3, nodes[2].length);
	}END_TEST

START_TEST(test_maximal_repeat3_mapped)
	{
		iterate("balalaikka", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		map_maximal_repeats_to_string(nodes, s_to_BWT("balalaikka"),get_max_repeats_nodes_index());
		ck_assert_int_eq(3, get_max_repeats_nodes_index());
		ck_assert_int_eq(9, nodes[0].normal->i);
		ck_assert_int_eq(1, nodes[0].length);
		ck_assert_int_eq(8, nodes[1].normal->i);
		ck_assert_int_eq(1, nodes[1].length);
		ck_assert_int_eq(3, nodes[2].normal->i);
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
		ck_assert_int_eq(3, nodes[0].normal->i);
		ck_assert_int_eq(4, nodes[0].normal->j);
		ck_assert_int_eq(2, nodes[0].length);
	}END_TEST

START_TEST(test_maximal_repeat1_mapped)
	{
		iterate("ilotalo", &search_maximal_repeats);
		max_repeat_node* nodes = get_nodes();
		map_maximal_repeats_to_string(nodes, s_to_BWT("ilotalo"),get_max_repeats_nodes_index());
		ck_assert_int_eq(1, get_max_repeats_nodes_index());
		ck_assert_int_eq(5, nodes[0].normal->i);
		ck_assert_int_eq(2, nodes[0].length);
	}END_TEST

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
	Suite *s = suite_create("testi");
	TCase *tc_stack = create_maximal_repeats_test_case();
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

