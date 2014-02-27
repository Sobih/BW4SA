
#include <check.h>
#include "../../include/iterate.h"
#include "../../src/iterate/substring_stack.h"
#include "../../include/bit_vector.h"
#include "../../include/backward_search.h"
#include <stdio.h>
#include <stdlib.h>

substring** shared_list;
int list_ptr = 0;

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
	interval* test1 = malloc(sizeof(interval));
	test1->i = 6;
	test1->j = 7;
	interval* test2 = malloc(sizeof(interval));
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
	interval* test1 = malloc(sizeof(interval));
	test1->i = 6;
	test1->j = 4;
	interval* test2 = malloc(sizeof(interval));
	test2->i = 6;
	test2->j = 6;
	ck_assert_int_eq(0, is_reverse_interval_right_maximal(runs, test1));
	ck_assert_int_eq(0, is_reverse_interval_right_maximal(runs, test2));
}
END_TEST

void put_substring_list(substring* substr)
{
	printf("putting substr \n");
	shared_list[list_ptr] = substr;
	list_ptr++;
}

//checks if shared_list contains given element. 1 if contains, 0 if not.
int shared_list_contains(substring* comp)
{
	substring* sub;
	for(int i = 0; i<list_ptr; i++){
		sub = shared_list[i];
		if(sub->normal->i == comp->normal->i &&
				sub->normal->j == comp->normal->j &&
				sub->reverse->i == comp->reverse->i &&
				sub->reverse->j == comp->reverse->j &&
				sub->length == comp->length){
			return 1;
		}
	}

	return 0;
}

START_TEST(test_iterate2)
{
	list_ptr = 0;
	int max_size = 20;
	shared_list = malloc(sizeof(substring*)*max_size);
	char* string = "hattivatti";

	Interval* normal = &((Interval) {.i = 8, .j = 9});
	Interval* reverse = &((Interval) {.i = 4, .j = 5});
	substring* tti = &((substring) {.normal = normal, .reverse = reverse, .length = 3});

	printf("testing iterate2\n");
	iterate(string, &put_substring_list);
	printf("iterate done\n");
	for(int i=0;i<list_ptr;i++){
		printf("normal i %d, normal j %d\n",
				shared_list[i]->normal->i, shared_list[i]->reverse->j);
	}
}END_TEST

START_TEST(test_iterate1)
{
	list_ptr = 0;
	int max_size = 20;
	shared_list = malloc(sizeof(substring*)*max_size);
	char* string = "abracadabra";

	Interval* normal = &((Interval) {.i = 2, .j = 3});
	Interval* reverse = &((Interval) {.i = 4, .j = 5});
	substring* abra = &((substring) {.normal = normal, .reverse = reverse, .length = 4});

	normal = &((Interval) {.i = 10, .j = 11});
	reverse = &((Interval) {.i = 4, .j = 5});
	substring* ra = &((substring) {.normal = normal, .reverse = reverse, .length = 2});

	iterate(string, &put_substring_list);
	for(int i=0;i<list_ptr;i++){
			printf("normal i %d, normal j %d\n",
					shared_list[i]->normal->i, shared_list[i]->normal->j);
		}

	fail_unless(shared_list_contains(abra) == 1);
	fail_unless(shared_list_contains(ra) == 1);
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

TCase * create_iterate_tcase(void){
	TCase* tc_iterate = tcase_create("iterate_tests");
	tcase_add_test(tc_iterate, test_iterate2);
	tcase_add_test(tc_iterate, test_iterate1);

	return tc_iterate;
}


Suite * test_suite(void)
{
	Suite *s = suite_create("Iterate");
	TCase *tc_runs = create_runs_vec_test_case();
	TCase *tc_iterate = create_iterate_tcase();
	suite_add_tcase(s, tc_runs);
	suite_add_tcase(s, tc_iterate);
	
	return s;
}
	
int main(){
	int number_failed;
	Suite *s = test_suite();
	SRunner *sr = srunner_create(s);
	srunner_set_fork_status (sr, CK_NOFORK);
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
