//--- tests/check_money.2.c	2013-09-20 23:37:40.000000000 -0400
//+++ tests/check_money.3.c	2013-09-20 23:37:40.000000000 -0400
//@@ -1,18 +1,38 @@
#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <math.h>
#include "../../src/core/rbwt.h"
#include "../../src/utils/wavelet_tree.h"

int wavelet_tree_matches_string(wavelet_tree* tree, char* string, int length) {
	int i;
	for (i = 0; i < length; i++) {
		if (tree->char_at(tree, i) != string[i]) {
			return 0;
		}
	}
	return 1;
}

START_TEST (reverse_test)
	{
		char* string = malloc(sizeof(char) * 12);
		string = reverse_string("MISSISSIPPI", string, 11);
		ck_assert_str_eq(string, "IPPISSISSIM");
	}END_TEST

START_TEST (reverse_test2)
	{
		char* string = malloc(sizeof(char) * 12);
		string = reverse_string("TAAA", string, 4);
		ck_assert_str_eq(string, "AAAT");
	}END_TEST

START_TEST (reverse_bwt_test)
	{
		wavelet_tree* rbwt = reverse_bwt("ABRACADABRA");
		ck_assert_int_eq(1, wavelet_tree_matches_string(rbwt,"ABDBC$RRAAAA",12));
	}END_TEST

START_TEST (reverse_bwt_test2)
	{
		wavelet_tree* rbwt = reverse_bwt("HATTIVATTI");
		ck_assert_int_eq(1, wavelet_tree_matches_string(rbwt,"HTTAV$TTIIA",11));
	}END_TEST


Suite *count_suite(void) {
	Suite *s = suite_create("Reverse_BWT");

	/* Core test case */
	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, reverse_test);
	tcase_add_test(tc_core, reverse_test2);
	tcase_add_test(tc_core, reverse_bwt_test);
	tcase_add_test(tc_core, reverse_bwt_test2);

	suite_add_tcase(s, tc_core);

	return s;
}

int main(void) {

	int number_failed;
	Suite *s = count_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
