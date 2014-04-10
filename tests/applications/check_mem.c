#include <check.h>
#include "../../include/iterate.h"
#include "../../include/mapper.h"
#include "../../src/bwt/s_to_bwt.h"
#include "../utils_for_tests/utils_for_tests.h"
#include <stdlib.h>

START_TEST(test_mem1) {

	ck_assert_int_eq(is_substring_maximal_exact_match("laatikko", "mehukatti", 8, 9, 2, 2), 1);
}
END_TEST


START_TEST(test_mem2) {
	
  ck_assert_int_eq(is_substring_maximal_exact_match("abracadabra", "abracadabra", 11, 14, 0, 4), 1);

}
END_TEST

TCase * create_mems_test_case(void) {
	TCase * tc_stack = tcase_create("mem_test");
	tcase_add_test(tc_stack, test_mem1);
	tcase_add_test(tc_stack, test_mem2);
	return tc_stack;
}

Suite * test_suite(void) {
	Suite *s = suite_create("test_for_mems");
	TCase *tc_stack = create_mems_test_case();
	suite_add_tcase(s, tc_stack);

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
