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

START_TEST(test_mem_randomized) {


	srand(time(NULL));
	char* test1;
	char* test2;
	wavelet_tree* bwt;
	int* suffix_array;
	int length;
	char* alphabet = "abcgdf";
	
	/*

	for (int i = 0; i < 100; i++) {

		test = generate_random_string(alphabet, rand() % 100 + 1);
		bwt = s_to_BWT(test);
		suffix_array = map_create_suffix_array_from_bwt(bwt);

		test_substr* maxrep_naive = find_maximal_repeat_substrings(test);
		iterate(test, &search_maximal_repeats);
		max_repeat_node* maxrep_fast = get_nodes();

		int max_number_nodes = get_max_repeats_nodes_index();

		for(int j = 0; j < max_number_nodes; j++){
			for(int k = 0; k + maxrep_fast[j].normal.i <=  maxrep_fast[j].normal.j; k++){

				fail_unless(find_and_remove_test_substr(maxrep_naive,
						 suffix_array[maxrep_fast[j].normal.i + k], maxrep_fast[j].length));
			}
		}
		print_substring_list(test, maxrep_naive);
		fail_unless(maxrep_naive->next == NULL);

	}



*/
}

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
