/*
 * check_backward_search.c
 *
 *  Created on: 30.1.2014
 *      Author: lvapaaka
 */

#include "backward_search.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_count_zero_letters)
{
	const char* string = "abracadabra";
	ck_assert_int_eq(0, rank(0, 'c', string));
}
END_TEST

START_TEST(test_count_one_letter)
{
	const char* string = "abracadabra";
	ck_assert_int_eq(1, rank(8, 'c', string));
}
END_TEST

START_TEST(test_count_all_a_letters)
{
	const char* string = "abracadabra";
	ck_assert_int_eq(5, rank(11, 'a', string));
}
END_TEST

START_TEST(test_count_some_a_letters)
{
	const char* string = "abracadabra";
	ck_assert_int_eq(3, rank(7, 'a', string));
}
END_TEST

TCase * create_backward_search_test_case(void){
	TCase * tc_backward_search = tcase_create("backward_search_test");
	tcase_add_test(tc_backward_search, test_count_zero_letters);
	tcase_add_test(tc_backward_search, test_count_one_letter);
	tcase_add_test(tc_backward_search, test_count_all_a_letters);
	tcase_add_test(tc_backward_search, test_count_some_a_letters);


	return tc_backward_search;
}

Suite * test_suite(void)
{
	Suite *s = suite_create("testi");
	TCase *tc_backward_search = create_backward_search_test_case();
	suite_add_tcase(s, tc_backward_search);

	return s;
}

int main(){
	int number_failed;
	Suite *s = test_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	if(number_failed == 0){
		return 0;
	}
	else{
	return 1;
	}
}
