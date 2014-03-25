/*
 * check_backward_search.c
 *
 *  Created on: 30.1.2014
 *      Author: lvapaaka
 */

#include "../../include/backward_search.h"
#include "../../include/wavelet_tree.h"
#include "../../include/structs.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(test_search_simple)
{
	char* str = "ard$rcaaaabb";
	wavelet_node* bwt = create_wavelet_tree(str);

	printf("asd\n");

	str = "abra";
	wavelet_node* string = create_wavelet_tree(str);

	printf("asd\n");

	interval* interval = backward_search(bwt, string);

	printf("Interval: %u, %u\n", interval->i, interval->j);

	ck_assert_int_eq(2, interval->i);
	ck_assert_int_eq(3, interval->j);
}
END_TEST

START_TEST(test_search_simple2)
{
	char* str = "ard$rcaaaabb";
	wavelet_node* bwt = create_wavelet_tree(str);

	printf("asd\n");

	str = "bra";
	wavelet_node* string = create_wavelet_tree(str);

	printf("asd\n");

	interval* interval = backward_search(bwt, string);
	ck_assert_int_eq(6, interval->i);
	ck_assert_int_eq(7, interval->j);
}
END_TEST

START_TEST(test_search_simple3)
{
	char* str = "ard$rcaaaabb";
	wavelet_node* bwt = create_wavelet_tree(str);

	printf("asd\n");

	str = "abracadabra";
	wavelet_node* string = create_wavelet_tree(str);

	printf("asd\n");

	interval* interval = backward_search(bwt, string);
	printf("Interval: %u, %u\n", interval->i, interval->j);

	ck_assert_int_eq(3, interval->i);
	ck_assert_int_eq(3, interval->j);
}
END_TEST

START_TEST(test_search_when_not_found)
{
	char* str = "ard$rcaaaabb";
	wavelet_node* bwt = create_wavelet_tree(str);

	printf("asd\n");

	str = "nakki";
	wavelet_node* string = create_wavelet_tree(str);

	printf("asd\n");

	interval* interval = backward_search(bwt, string);
	fail_unless(interval == NULL);
}
END_TEST

START_TEST(test_search_different_word)
{
	char* str = "ipssm$pissii";
	wavelet_node* bwt = create_wavelet_tree(str);

	printf("asd\n");

	str = "iss";
	wavelet_node* string = create_wavelet_tree(str);

	printf("asd\n");

	interval* interval = backward_search(bwt, string);
	ck_assert_int_eq(3, interval->i);
	ck_assert_int_eq(4, interval->j);
}
END_TEST

/*
START_TEST(test_interval_search_ra)
{
	interval* interval = malloc(sizeof(interval));
	interval->i = 1;
	interval->j = 5;
	interval* result = backward_search_interval("ard$rcaaaabb", interval, 'r');
	ck_assert_int_eq(10, result->i);
    ck_assert_int_eq(11, result->j);
}
END_TEST

START_TEST(test_interval_search_da)
{
	interval* interval = malloc(sizeof(interval));
	interval->i = 1;
	interval->j = 5;
	interval* result = backward_search_interval("ard$rcaaaabb", interval, 'd');
	ck_assert_int_eq(9, result->i);
    ck_assert_int_eq(9, result->j);
}
END_TEST

START_TEST(test_interval_search_bra)
{
	interval* interval = malloc(sizeof(interval));
	interval->i = 10;
	interval->j = 11;
	interval* result = backward_search_interval("ard$rcaaaabb", interval, 'b');
	ck_assert_int_eq(6, result->i);
    ck_assert_int_eq(7, result->j);
}
END_TEST

START_TEST(test_interval_search_tt)
{
	interval* interval = malloc(sizeof(interval));
	interval->i = 6;
	interval->j = 9;
	interval* result = backward_search_interval("ivh$ttttaai", interval, 't');
	ck_assert_int_eq(8, result->i);
    ck_assert_int_eq(9, result->j);
}
END_TEST

START_TEST(test_interval_search_ha)
{
	interval* interval = malloc(sizeof(interval));
	interval->i = 1;
	interval->j = 2;
	interval* result = backward_search_interval("ivh$ttttaai", interval, 'h');
	ck_assert_int_eq(3, result->i);
    ck_assert_int_eq(3, result->j);
}
END_TEST
*/

TCase * create_backward_search_test_case(void){
	TCase * tc_backward_search = tcase_create("backward_search_test");
	tcase_add_test(tc_backward_search, test_search_simple);
	tcase_add_test(tc_backward_search, test_search_simple2);
	tcase_add_test(tc_backward_search, test_search_simple3);
	tcase_add_test(tc_backward_search, test_search_when_not_found);
	tcase_add_test(tc_backward_search, test_search_different_word);

	return tc_backward_search;
}

/*
TCase * create_backward_search_interval_test_case(void){
	TCase * tc_backward_search_interval = tcase_create("backward_search_interval_test");
	tcase_add_test(tc_backward_search_interval, test_interval_search_ra);
	tcase_add_test(tc_backward_search_interval, test_interval_search_da);
	tcase_add_test(tc_backward_search_interval, test_interval_search_bra);
	tcase_add_test(tc_backward_search_interval, test_interval_search_tt);
	tcase_add_test(tc_backward_search_interval, test_interval_search_ha);

	return tc_backward_search_interval;
}
*/

Suite * test_suite(void)
{
	Suite *s = suite_create("testi");
	TCase *tc_backward_search = create_backward_search_test_case();
	//TCase *tc_backward_search_interval = create_backward_search_interval_test_case();
	suite_add_tcase(s, tc_backward_search);
	//suite_add_tcase(s, tc_backward_search_interval);
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
