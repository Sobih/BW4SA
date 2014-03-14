/*
 * check_mum.c
 *
 *  Created on: 14.3.2014
 *      Author: lvapaaka
 */

#include <check.h>
#include "../../include/iterate.h"
#include "../../include/mum.h"
#include <stdlib.h>

START_TEST(test_mum1)
	{
		double_iterate("laatikko", "mehukatti", &search_mums);
		triplet* nodes = get_mums();
		ck_assert_int_eq(2, get_triplets_index());
		ck_assert_int_eq(2, nodes[0].pos1);
		ck_assert_int_eq(1, nodes[0].pos2);
		ck_assert_int_eq(2, nodes[0].length);
		ck_assert_int_eq(8, nodes[1].pos1);
		ck_assert_int_eq(7, nodes[1].pos2);
		ck_assert_int_eq(2, nodes[1].length);
	}END_TEST

TCase * create_mums_test_case(void) {
	TCase * tc_stack = tcase_create("mum_test");
	tcase_add_test(tc_stack, test_mum1);
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

