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
		uchar* expected_BWT = "ard$rcaaaabb";
		uchar* result = malloc((strlen(input) + 1) * sizeof(unsigned char));
		result = s_to_BWT(input);
		ck_assert_str_eq(result, expected_BWT);
	}END_TEST

START_TEST(test_hattivatti_bwt)
	{
		uchar* input = "hattivatti";
		uchar* expected_BWT = "ivh$ttttaai";
		uchar* result = malloc((strlen(input) + 1) * sizeof(unsigned char));
		result = s_to_BWT(input);
		ck_assert_str_eq(result, expected_BWT);
	}END_TEST

START_TEST(test_lol_bwt)
	{
		uchar* input = "lol";
		uchar* expected_BWT = "lo$l";
		uchar* result = malloc((strlen(input) + 1) * sizeof(unsigned char));
		result = s_to_BWT(input);
		ck_assert_str_eq(result, expected_BWT);
	}END_TEST

START_TEST(test_hei_bwt)
	{
		uchar* input = "hei";
		uchar* expected_BWT = "ih$e";
		uchar* result = malloc((strlen(input) + 1) * sizeof(unsigned char));
		result = s_to_BWT(input);
		ck_assert_str_eq(result, expected_BWT);
	}END_TEST

START_TEST(test_a_bwt)
	{
		uchar* input = "a";
		uchar* expected_BWT = "a$";
		uchar* result = malloc((strlen(input) + 1) * sizeof(unsigned char));
		result = s_to_BWT(input);
		ck_assert_str_eq(result, expected_BWT);
	}END_TEST

START_TEST(test_laatikko_bwt)
	{
		uchar* input = "laatikko";
		uchar* expected_BWT = "olatik$ka";
		uchar* result = malloc((strlen(input) + 1) * sizeof(unsigned char));
		result = s_to_BWT(input);
		ck_assert_str_eq(result, expected_BWT);
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
