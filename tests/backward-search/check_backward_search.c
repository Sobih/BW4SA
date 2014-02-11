/*
 * check_backward_search.c
 *
 *  Created on: 30.1.2014
 *      Author: lvapaaka
 */

#include "../../include/backward_search.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

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

START_TEST(test_search_simple)
{
	Interval* interval = backward_search("ard$rcaaaabb", "abra");
	ck_assert_int_eq(2, interval->i);
	ck_assert_int_eq(3, interval->j);
}
END_TEST

START_TEST(test_search_simple2)
{
	Interval* interval = backward_search("ard$rcaaaabb", "bra");
	ck_assert_int_eq(6, interval->i);
	ck_assert_int_eq(7, interval->j);
}
END_TEST

START_TEST(test_search_simple3)
{
	Interval* interval = backward_search("ard$rcaaaabb", "abracadabra");
	ck_assert_int_eq(3, interval->i);
	ck_assert_int_eq(3, interval->j);
}
END_TEST

START_TEST(test_search_when_not_found)
{
	
	Interval* interval = backward_search("ard$rcaaaabb", "nakki");
	fail_unless(interval == NULL);
}
END_TEST

START_TEST(test_search_different_word)
{
	
	Interval* interval = backward_search("ipssm$pissii", "iss");
	ck_assert_int_eq(3, interval->i);
	ck_assert_int_eq(4, interval->j);
}
END_TEST

START_TEST(test_interval_search)
{
	printf("Starting interval test \n");
	Interval* interval = malloc(sizeof(Interval));
	interval->i = 1;
	interval->j = 5;
	printf("dhgkjhdfgkjhdgfkjhdsgfkhdsglkjhfdg \n");
	Interval* result = backward_search_interval("ard$rcaaaabb", interval, 'r');
	ck_assert_int_eq(10, result->i);
    ck_assert_int_eq(11, result->j);

}
END_TEST

TCase * create_rank_test_case(void){
	TCase * tc_rank = tcase_create("rank_test");
	tcase_add_test(tc_rank, test_count_zero_letters);
	tcase_add_test(tc_rank, test_count_one_letter);
	tcase_add_test(tc_rank, test_count_all_a_letters);
	tcase_add_test(tc_rank, test_count_some_a_letters);

	return tc_rank;
}
TCase * create_backward_search_test_case(void){
	TCase * tc_backward_search = tcase_create("backward_search_test");
	tcase_add_test(tc_backward_search, test_search_simple);
	tcase_add_test(tc_backward_search, test_search_simple2);
	tcase_add_test(tc_backward_search, test_search_simple3);
	tcase_add_test(tc_backward_search, test_search_when_not_found);
	tcase_add_test(tc_backward_search, test_search_different_word);

	return tc_backward_search;
}

TCase * create_backward_search_interval_test_case(void){
	TCase * tc_backward_search_interval = tcase_create("backward_search_interval_test");
	tcase_add_test(tc_backward_search_interval, test_interval_search);
	//tcase_add_test(tc_backward_search, test_search_simple2);
	//tcase_add_test(tc_backward_search, test_search_simple3);
	//tcase_add_test(tc_backward_search, test_search_when_not_found);
	//tcase_add_test(tc_backward_search, test_search_different_word);

	return tc_backward_search_interval;
}

Suite * test_suite(void)
{
	Suite *s = suite_create("testi");
	TCase *tc_backward_search = create_backward_search_test_case();
	TCase *tc_rank = create_rank_test_case();
	TCase *tc_backward_search_interval = create_backward_search_interval_test_case();
	suite_add_tcase(s, tc_backward_search);
	suite_add_tcase(s, tc_rank);
	suite_add_tcase(s, tc_backward_search_interval);
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
