#include "../../src/core/s_to_bwt.h"
#include "../../src/core/bwt_to_s.h"
#include "../../src/utils/wavelet_tree.h"
#include <check.h>
#include <stdlib.h>

void test(char* input)
{
	wavelet_tree* bwt = s_to_BWT(input);
	char* result = bwt_to_s(bwt);
	ck_assert_str_eq(input, result);
}

START_TEST(test_abracadabra_bwt)
	{
		char* input = "abracadabra";
		test(input);
	}END_TEST

START_TEST(test_hattivatti_bwt)
	{
		char* input = "hattivatti";
		test(input);
	}END_TEST

START_TEST(test_lol_bwt)
	{
		char* input = "lol";
		test(input);
	}END_TEST

START_TEST(test_hei_bwt)
	{
		char* input = "hei";
		test(input);

	}END_TEST

START_TEST(test_a_bwt)
	{
		char* input = "a";
		test(input);

	}END_TEST

START_TEST(test_laatikko_bwt)
	{
		char* input = "laatikko";
		test(input);

	}END_TEST


Suite *test_suite (void)
{
  	Suite *s = suite_create ("bwt_to_s");

  	/* Core test case */
  	TCase *tc_core = tcase_create ("bwt_to_s");
  	tcase_add_test (tc_core, test_abracadabra_bwt);
	tcase_add_test(tc_core, test_hattivatti_bwt);
	tcase_add_test(tc_core, test_lol_bwt);	
	tcase_add_test(tc_core, test_hei_bwt);
	tcase_add_test(tc_core, test_a_bwt);
	tcase_add_test(tc_core, test_laatikko_bwt);

  	suite_add_tcase (s, tc_core);

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
