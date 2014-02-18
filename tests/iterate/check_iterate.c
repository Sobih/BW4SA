
#include <check.h>
#include "../../include/iterate.h"
#include "../../src/iterate/substring_stack.h"
#include "../../include/bit_vector.h"
#include "../../include/backward_search.h"
#include <stdlib.h>

START_TEST(simple_runs_test)
{
	char* string = "abracadabra";
	bit_vector* runs = create_runs_vector(string);
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 0));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 1));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 2));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 3));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 4));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 5));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 6));
	ck_assert_int_eq(0, runs->is_bit_marked(runs, 7));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 8));
	ck_assert_int_eq(0, runs->is_bit_marked(runs, 9));
	ck_assert_int_eq(0, runs->is_bit_marked(runs, 10));
	ck_assert_int_eq(0, runs->is_bit_marked(runs, 11));
}
END_TEST

START_TEST(another_simple_test)
{
	char* string = "HATTIVATTI";
	bit_vector* runs = create_runs_vector(string);
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 0));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 1));
	ck_assert_int_eq(0, runs->is_bit_marked(runs, 2));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 3));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 4));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 5));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 6));
	ck_assert_int_eq(0, runs->is_bit_marked(runs, 7));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 8));
	ck_assert_int_eq(0, runs->is_bit_marked(runs, 9));
	ck_assert_int_eq(1, runs->is_bit_marked(runs, 10));
}
END_TEST

START_TEST(test_interval_query)
{
	char* string = "ABRACADABRA";
	bit_vector* runs = create_runs_vector(string);
	Interval* test1 = malloc(sizeof(Interval));
	test1->i = 6;
	test1->j = 7;
	Interval* test2 = malloc(sizeof(Interval));
	test2->i = 1;
	test2->j = 3;
	ck_assert_int_eq(0, is_reverse_interval_right_maximal(runs, test1));
	ck_assert_int_eq(1, is_reverse_interval_right_maximal(runs, test2));
}
END_TEST

START_TEST(test_wrong_intervals)
{
	char* string = "ABRACADABRA";
	bit_vector* runs = create_runs_vector(string);
	Interval* test1 = malloc(sizeof(Interval));
	test1->i = 6;
	test1->j = 4;
	Interval* test2 = malloc(sizeof(Interval));
	test2->i = 6;
	test2->j = 6;
	ck_assert_int_eq(0, is_reverse_interval_right_maximal(runs, test1));
	ck_assert_int_eq(0, is_reverse_interval_right_maximal(runs, test2));
}
END_TEST
TCase * create_runs_vec_test_case(void){
	TCase * tc_runs = tcase_create("runs_vec_test");
	tcase_add_test(tc_runs, simple_runs_test);
	tcase_add_test(tc_runs, another_simple_test);
	tcase_add_test(tc_runs, test_interval_query);
	tcase_add_test(tc_runs, test_wrong_intervals);
	return tc_runs;
}

Suite * test_suite(void)
{
	Suite *s = suite_create("Iterate");
	TCase *tc_runs = create_runs_vec_test_case();
	suite_add_tcase(s, tc_runs);
	
	return s;
}
	
int main(){
	int number_failed;
	Suite *s = test_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	
	if(number_failed == 0){
		return 0;
	}
	else{
	return 1;
	}
}
