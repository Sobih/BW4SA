 	
//--- tests/check_money.2.c	2013-09-20 23:37:40.000000000 -0400
//+++ tests/check_money.3.c	2013-09-20 23:37:40.000000000 -0400
//@@ -1,18 +1,38 @@
 #include <stdlib.h>
 #include <check.h>
 #include "../include/utils.h"
 #include "../src/distinct_substrings.h"
 
START_TEST (lcp_test)
{

	ck_assert_int_eq(lcp("ANA", "ANANA"), 3);
	ck_assert_int_eq(lcp("ANA", "BANANA"), 0);
}
END_TEST



START_TEST (lcp_test2)
{
	ck_assert_int_eq(lcp("MISSISSIPPI", "MISSISS"), 7);

}
END_TEST

START_TEST (suffixes_test)
{
	char *ans[] = {"BANANA", "ANANA", "NANA", "ANA", "NA", "A"};
	int i;
	char **suffixes = create_suffixes("BANANA");
	for (i = 0; i < 6; i++) {
		ck_assert_str_eq(ans[i], suffixes[i]);
	}	
}
END_TEST

START_TEST (suffixes_test2)
{
	char *ans[] = {"AAAA", "AAA", "AA", "A"};
	int i; 
	char **suffixes = create_suffixes("AAAA");
	for (i = 0; i < 4; i++) {
		ck_assert_str_eq(ans[i], suffixes[i]);
	}
}
END_TEST

START_TEST (compare_pairs_test)
{
	char *array[] = {"A", "ANA", "ANANA", "BANANA", "NA", "NANA"};
	int res = compare_pairs(array, 6);
	ck_assert_int_eq(res, 15);

}
END_TEST

START_TEST (compare_pairs_test2)
{
	char *array[] = {"ABCD", "BCD", "CD", "D"};
	int res = compare_pairs(array, 4);
	ck_assert_int_eq(res, 10);
}
END_TEST
 
START_TEST (distinct_substrings_test)
{
	ck_assert_int_eq(distinct_substrings("BANANA"), 15);

}
END_TEST

START_TEST (distinct_substrings_test2)
{
	ck_assert_int_eq(distinct_substrings("ABCD"), 10);
}
END_TEST


Suite *count_suite (void)
{
  Suite *s = suite_create ("Count_substrings");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, lcp_test);
  tcase_add_test (tc_core, lcp_test2);
  tcase_add_test(tc_core, suffixes_test);
  tcase_add_test(tc_core, suffixes_test2);
  tcase_add_test(tc_core, compare_pairs_test);
  tcase_add_test(tc_core, compare_pairs_test2);
  tcase_add_test(tc_core, distinct_substrings_test);
  tcase_add_test(tc_core, distinct_substrings_test2);
  suite_add_tcase (s, tc_core);

  return s;
}

 int main (void)
{
  
  int number_failed;
  Suite *s = count_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

