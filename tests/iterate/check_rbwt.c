 	
//--- tests/check_money.2.c	2013-09-20 23:37:40.000000000 -0400
//+++ tests/check_money.3.c	2013-09-20 23:37:40.000000000 -0400
//@@ -1,18 +1,38 @@
 #include <stdlib.h>
 #include <check.h>
 #include "../../include/rbwt.h"
 
START_TEST (reverse_test)
{
	ck_assert_str_eq(reverse_string("MISSISSIPPI"), "IPPISSISSIM");
}
END_TEST

START_TEST (reverse_test2)
{
	ck_assert_str_eq(reverse_string("TAAA"), "AAAT");
}
END_TEST

START_TEST (reverse_bwt_test) 
{
	ck_assert_str_eq(reverse_bwt("ABRACADABRA"), "ABDBC$RRAAAA");	
}
END_TEST

START_TEST (reverse_bwt_test2) 
{
	ck_assert_str_eq(reverse_bwt("HATTIVATTI"), "HTTAV$TTIIA");	
}
END_TEST

Suite *count_suite (void)
{
  	Suite *s = suite_create ("Count_substrings");

  	/* Core test case */
  	TCase *tc_core = tcase_create ("Core");
  	tcase_add_test (tc_core, reverse_test);
  	tcase_add_test (tc_core, reverse_test2);
	tcase_add_test (tc_core, reverse_bwt_test);
	tcase_add_test (tc_core, reverse_bwt_test2);

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
