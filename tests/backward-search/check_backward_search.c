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
	wavelet_tree* bwt = create_wavelet_tree(str);

	str = "abra";
	wavelet_tree* string = create_wavelet_tree(str);

	interval* interval = backward_search(bwt, string, 0);

	ck_assert_int_eq(2, interval->i);
	ck_assert_int_eq(3, interval->j);

	free_wavelet_tree(bwt);
	free_wavelet_tree(string);
	free(interval);
}
END_TEST

START_TEST(test_search_simple2)
{
	char* str = "ard$rcaaaabb";
	wavelet_tree* bwt = create_wavelet_tree(str);

	str = "bra";
	wavelet_tree* string = create_wavelet_tree(str);

	interval* interval = backward_search(bwt, string, 0);

	ck_assert_int_eq(6, interval->i);
	ck_assert_int_eq(7, interval->j);

	free_wavelet_tree(bwt);
	free_wavelet_tree(string);
	free(interval);
}
END_TEST

START_TEST(test_search_simple3)
{
	char* str = "ard$rcaaaabb";
	wavelet_tree* bwt = create_wavelet_tree(str);

	str = "abracadabra";
	wavelet_tree* string = create_wavelet_tree(str);

	interval* interval = backward_search(bwt, string, 0);

	ck_assert_int_eq(3, interval->i);
	ck_assert_int_eq(3, interval->j);

	free_wavelet_tree(bwt);
	free_wavelet_tree(string);
	free(interval);
}
END_TEST

START_TEST(test_search_when_not_found)
{
	char* str = "ard$rcaaaabb";
	wavelet_tree* bwt = create_wavelet_tree(str);

	str = "nakki";
	wavelet_tree* string = create_wavelet_tree(str);

	interval* interval = backward_search(bwt, string, 0);

	fail_unless(interval == NULL);

	free_wavelet_tree(bwt);
	free_wavelet_tree(string);
	free(interval);
}
END_TEST

START_TEST(test_search_different_word)
{
	char* str = "ipssm$pissii";
	wavelet_tree* bwt = create_wavelet_tree(str);

	str = "iss";
	wavelet_tree* string = create_wavelet_tree(str);

	interval* interval = backward_search(bwt, string, 0);

	ck_assert_int_eq(3, interval->i);
	ck_assert_int_eq(4, interval->j);

	free_wavelet_tree(bwt);
	free_wavelet_tree(string);
	free(interval);
}
END_TEST

START_TEST(test_interval_search_ra)
{
	interval* inter = malloc(sizeof(interval));
	inter->i = 1;
	inter->j = 5;

	wavelet_tree* tree = create_wavelet_tree("ard$rcaaaabb");

	interval* result = backward_search_interval(tree, inter, 'r', 0);

	ck_assert_int_eq(10, result->i);
    ck_assert_int_eq(11, result->j);

    free_wavelet_tree(tree);
    free(result);
    free(inter);
}
END_TEST

START_TEST(test_interval_search_da)
{
	interval* inter = malloc(sizeof(interval));
	inter->i = 1;
	inter->j = 5;

	wavelet_tree* tree = create_wavelet_tree("ard$rcaaaabb");

	interval* result = backward_search_interval(tree, inter, 'd', 0);

	ck_assert_int_eq(9, result->i);
    ck_assert_int_eq(9, result->j);

    free_wavelet_tree(tree);
    free(result);
    free(inter);
}
END_TEST

START_TEST(test_interval_search_bra)
{
	interval* inter = malloc(sizeof(interval));
	inter->i = 10;
	inter->j = 11;

	wavelet_tree* tree = create_wavelet_tree("ard$rcaaaabb");

	interval* result = backward_search_interval(tree, inter, 'b', 0);

	ck_assert_int_eq(6, result->i);
    ck_assert_int_eq(7, result->j);

    free_wavelet_tree(tree);
    free(result);
    free(inter);
}
END_TEST

START_TEST(test_interval_search_tt)
{
	interval* inter = malloc(sizeof(interval));
	inter->i = 6;
	inter->j = 9;

	wavelet_tree* tree = create_wavelet_tree("ivh$ttttaai");

	interval* result = backward_search_interval(tree, inter, 't', 0);

	ck_assert_int_eq(8, result->i);
    ck_assert_int_eq(9, result->j);

    free_wavelet_tree(tree);
    free(result);
    free(inter);
}
END_TEST

START_TEST(test_interval_search_ha)
{
	interval* inter = malloc(sizeof(interval));
	inter->i = 1;
	inter->j = 2;

	wavelet_tree* tree = create_wavelet_tree("ivh$ttttaai");

	interval* result = backward_search_interval(tree, inter, 'h', 0);

	ck_assert_int_eq(3, result->i);
    ck_assert_int_eq(3, result->j);

    free_wavelet_tree(tree);
    free(result);
    free(inter);
}
END_TEST

TCase* create_backward_search_test_case(void) {
	TCase* tc_backward_search = tcase_create("backward_search_test");
	tcase_add_test(tc_backward_search, test_search_simple);
	tcase_add_test(tc_backward_search, test_search_simple2);
	tcase_add_test(tc_backward_search, test_search_simple3);
	tcase_add_test(tc_backward_search, test_search_when_not_found);
	tcase_add_test(tc_backward_search, test_search_different_word);

	return tc_backward_search;
}

TCase* create_backward_search_interval_test_case(void) {
	TCase* tc_backward_search_interval = tcase_create("backward_search_interval_test");
	tcase_add_test(tc_backward_search_interval, test_interval_search_ra);
	tcase_add_test(tc_backward_search_interval, test_interval_search_da);
	tcase_add_test(tc_backward_search_interval, test_interval_search_bra);
	tcase_add_test(tc_backward_search_interval, test_interval_search_tt);
	tcase_add_test(tc_backward_search_interval, test_interval_search_ha);

	return tc_backward_search_interval;
}

Suite * test_suite(void)
{
	Suite *s = suite_create("testi");
	TCase *tc_backward_search = create_backward_search_test_case();
	TCase *tc_backward_search_interval = create_backward_search_interval_test_case();
	suite_add_tcase(s, tc_backward_search);
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
