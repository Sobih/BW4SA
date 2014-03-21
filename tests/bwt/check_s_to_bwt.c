/*
 * s_to_bwt_Test.c
 *
 *  Created on: 24.1.2014
 *      Author: lvapaaka
 */

#include "../../src/bwt/s_to_bwt.h"
#include <check.h>
#include <stdlib.h>

START_TEST(test_abracadabra_bwt)
	{
		uchar* input = "abracadabra";
		uchar* expected_string = "ard$rcaaaabb";
		wavelet_node* expected_BWT = create_wavelet_tree(expected_string);
		wavelet_node* result = s_to_BWT(input);

		ck_assert(result->char_at(result, 0) == expected_BWT->char_at(expected_BWT, 0));
		ck_assert(result->char_at(result, 1) == expected_BWT->char_at(expected_BWT, 1));
		ck_assert(result->char_at(result, 2) == expected_BWT->char_at(expected_BWT, 2));
		ck_assert(result->char_at(result, 3) == expected_BWT->char_at(expected_BWT, 3));
		ck_assert(result->char_at(result, 4) == expected_BWT->char_at(expected_BWT, 4));
		ck_assert(result->char_at(result, 5) == expected_BWT->char_at(expected_BWT, 5));
		ck_assert(result->char_at(result, 6) == expected_BWT->char_at(expected_BWT, 6));
		ck_assert(result->char_at(result, 7) == expected_BWT->char_at(expected_BWT, 7));
		ck_assert(result->char_at(result, 8) == expected_BWT->char_at(expected_BWT, 8));
		ck_assert(result->char_at(result, 9) == expected_BWT->char_at(expected_BWT, 9));
		ck_assert(result->char_at(result, 10) == expected_BWT->char_at(expected_BWT, 10));
		ck_assert(result->char_at(result, 11) == expected_BWT->char_at(expected_BWT, 11));
	}END_TEST

START_TEST(test_hattivatti_bwt)
	{
		uchar* input = "hattivatti";
		uchar* expected_string = "ivh$ttttaai";
		wavelet_node* expected_BWT = create_wavelet_tree(expected_string);
		wavelet_node* result = s_to_BWT(input);

		ck_assert(result->char_at(result, 0) == expected_BWT->char_at(expected_BWT, 0));
		ck_assert(result->char_at(result, 1) == expected_BWT->char_at(expected_BWT, 1));
		ck_assert(result->char_at(result, 2) == expected_BWT->char_at(expected_BWT, 2));
		ck_assert(result->char_at(result, 3) == expected_BWT->char_at(expected_BWT, 3));
		ck_assert(result->char_at(result, 4) == expected_BWT->char_at(expected_BWT, 4));
		ck_assert(result->char_at(result, 5) == expected_BWT->char_at(expected_BWT, 5));
		ck_assert(result->char_at(result, 6) == expected_BWT->char_at(expected_BWT, 6));
		ck_assert(result->char_at(result, 7) == expected_BWT->char_at(expected_BWT, 7));
		ck_assert(result->char_at(result, 8) == expected_BWT->char_at(expected_BWT, 8));
		ck_assert(result->char_at(result, 9) == expected_BWT->char_at(expected_BWT, 9));
		ck_assert(result->char_at(result, 10) == expected_BWT->char_at(expected_BWT, 10));
	}END_TEST

START_TEST(test_lol_bwt)
	{
		uchar* input = "lol";
		uchar* expected_string = "lo$l";
		wavelet_node* expected_BWT = create_wavelet_tree(expected_string);
		wavelet_node* result = s_to_BWT(input);

		ck_assert(result->char_at(result, 0) == expected_BWT->char_at(expected_BWT, 0));
		ck_assert(result->char_at(result, 1) == expected_BWT->char_at(expected_BWT, 1));
		ck_assert(result->char_at(result, 2) == expected_BWT->char_at(expected_BWT, 2));
		ck_assert(result->char_at(result, 3) == expected_BWT->char_at(expected_BWT, 3));
	}END_TEST

START_TEST(test_hei_bwt)
	{
		uchar* input = "hei";
		uchar* expected_string = "ih$e";
		wavelet_node* expected_BWT = create_wavelet_tree(expected_string);
		wavelet_node* result = s_to_BWT(input);

		ck_assert(result->char_at(result, 0) == expected_BWT->char_at(expected_BWT, 0));
		ck_assert(result->char_at(result, 1) == expected_BWT->char_at(expected_BWT, 1));
		ck_assert(result->char_at(result, 2) == expected_BWT->char_at(expected_BWT, 2));
		ck_assert(result->char_at(result, 3) == expected_BWT->char_at(expected_BWT, 3));
	}END_TEST

START_TEST(test_a_bwt)
	{
		uchar* input = "a";
		uchar* expected_string = "a$";
		wavelet_node* expected_BWT = create_wavelet_tree(expected_string);
		wavelet_node* result = s_to_BWT(input);

		ck_assert(result->char_at(result, 0) == expected_BWT->char_at(expected_BWT, 0));
		ck_assert(result->char_at(result, 1) == expected_BWT->char_at(expected_BWT, 1));
	}END_TEST

START_TEST(test_laatikko_bwt)
	{
		uchar* input = "laatikko";
		uchar* expected_string = "olatik$ka";
		wavelet_node* expected_BWT = create_wavelet_tree(expected_string);
		wavelet_node* result = s_to_BWT(input);

		ck_assert(result->char_at(result, 0) == expected_BWT->char_at(expected_BWT, 0));
		ck_assert(result->char_at(result, 1) == expected_BWT->char_at(expected_BWT, 1));
		ck_assert(result->char_at(result, 2) == expected_BWT->char_at(expected_BWT, 2));
		ck_assert(result->char_at(result, 3) == expected_BWT->char_at(expected_BWT, 3));
		ck_assert(result->char_at(result, 4) == expected_BWT->char_at(expected_BWT, 4));
		ck_assert(result->char_at(result, 5) == expected_BWT->char_at(expected_BWT, 5));
		ck_assert(result->char_at(result, 6) == expected_BWT->char_at(expected_BWT, 6));
		ck_assert(result->char_at(result, 7) == expected_BWT->char_at(expected_BWT, 7));
		ck_assert(result->char_at(result, 8) == expected_BWT->char_at(expected_BWT, 8));
	}END_TEST

TCase * create_carray_test_case(void) {
	TCase * tc_carray = tcase_create("s_to_bwt_test");
	tcase_add_test(tc_carray, test_abracadabra_bwt);
	tcase_add_test(tc_carray, test_hattivatti_bwt);
	tcase_add_test(tc_carray, test_lol_bwt);
	tcase_add_test(tc_carray, test_hei_bwt);
	tcase_add_test(tc_carray, test_a_bwt);
	tcase_add_test(tc_carray, test_laatikko_bwt);

	return tc_carray;
}

Suite * test_suite(void) {
	Suite *s = suite_create("testi");
	TCase *tc_carray = create_carray_test_case();
	suite_add_tcase(s, tc_carray);

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
