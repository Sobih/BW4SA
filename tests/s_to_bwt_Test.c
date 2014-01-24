/*
 * s_to_bwt_Test.c
 *
 *  Created on: 24.1.2014
 *      Author: lvapaaka
 */

#include "../../src/s_to_bwt.h"
#include <check.h>

START_TEST(test_abracadabra_bwt)
{
	char* input = "abracadabra";
	char* expected_BWT = "ardrcaaaabb";
	ck_assert_str_eq(s_to_BWT(input), expected_BWT);
}
END_TEST

START_TEST(test_hattivatti_bwt)
{
	char* input = "hattivatti";
	char* expected_BWT = "ivhttttaai";
	ck_assert_str_eq(s_to_BWT(input), expected_BWT);
}
END_TEST

START_TEST(test_lol_bwt)
{
	char* input = "lol";
	char* expected_BWT = "lol";
	ck_assert_str_eq(s_to_BWT(input), expected_BWT);
}
END_TEST

START_TEST(test_hei_bwt)
{
	char* input = "hei";
	char* expected_BWT = "ihe";
	ck_assert_str_eq(s_to_BWT(input), expected_BWT);
}
END_TEST

START_TEST(test_a_bwt)
{
	char* input = "a";
	char* expected_BWT = "a";
	ck_assert_str_eq(s_to_BWT(input), expected_BWT);
}
END_TEST

START_TEST(test_laatikko_bwt)
{
	char* input = "laatikko";
	char* expected_BWT = "olatikka";
	ck_assert_str_eq(s_to_BWT(input), expected_BWT);
}
END_TEST

TCase * create_carray_test_case(void){
	TCase * tc_carray = tcase_create("s_to_bwt_test");
	tcase_add_test(tc_carray, test_abracadabra_bwt);
	tcase_add_test(tc_carray, test_hattivatti_bwt);
	tcase_add_test(tc_carray, test_lol_bwt);
	tcase_add_test(tc_carray, test_hei_bwt);
	tcase_add_test(tc_carray, test_a_bwt);
	tcase_add_test(tc_carray, test_laatikko_bwt);

	return tc_carray;
}

Suite * test_suite(void)
{
        Suite *s = suite_create("testi");
        TCase *tc_carray = create_carray_test_case();
        suite_add_tcase(s, tc_carray);

        return s;
}

int main(){
        int number_failed;
        Suite *s = test_suite();
        SRunner *sr = srunner_create(s);
        srunner_run_all(sr, CK_VERBOSE);
        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);

        if(number_failed == 0)
        {
                return 0;
        }
        else
        {
        return 1;
        }
}
