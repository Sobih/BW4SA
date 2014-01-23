 	
//--- tests/check_money.2.c	2013-09-20 23:37:40.000000000 -0400
//+++ tests/check_money.3.c	2013-09-20 23:37:40.000000000 -0400
//@@ -1,18 +1,38 @@
 #include <stdlib.h>
 #include <check.h>
 #include "../src/count_substrings.h"
 
 START_TEST (lcp_test)
 {

	ck_assert_int_eq(lcp("ANA", "ANANA", 3, 5), 3);
	ck_assert_int_eq(lcp("ANA", "BANANA", 3, 6), 0);
 }
 END_TEST

START_TEST (lcp_test2)
{
	ck_assert_int_eq(lcp("MISSISSIPPI", "MISSISS", 11, 7), 7);

}
END_TEST

START_TEST (swap_test)
{
	
	
}
END_TEST
 
Suite *
count_suite (void)
{
  Suite *s = suite_create ("Count_substrings");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, lcp_test);
  tcase_add_test (tc_core, lcp_test2);
  tcase_add_test (tc_core, swap_test);
  suite_add_tcase (s, tc_core);

  return s;
}

 int
 main (void)
 {
  
  int number_failed;
  Suite *s = count_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
 }

