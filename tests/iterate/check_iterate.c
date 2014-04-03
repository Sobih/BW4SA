
#include <check.h>
#include "../../include/iterate.h"
#include "../../src/iterate/substring_stack.h"
#include "../../include/bit_vector.h"
#include "../../include/backward_search.h"
#include "../../include/wavelet_tree.h"
#include "../../include/structs.h"
#include "../../include/utils.h"
#include "../../include/rbwt.h"
#include "../utils_for_tests/utils_for_tests.h"
#include "../../src/bwt/s_to_bwt.h"
#include "../../src/bwt/map_bwt_to_s.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

substring** shared_list;
int list_ptr = 0;

//static variables for randomized tests
static test_substr* naive_rmaximals;
static int callback_flag;
static int* suffix_array;

START_TEST(simple_runs_test)
{
	printf("SIMPLE RUNS TEST\n");
	char* string = "abracadabra";
	wavelet_tree* tree = reverse_bwt(string);
	bit_vector* runs = create_runs_vector(tree, 0);
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
	printf("ANOTHER SIMPLE TEST\n");
	char* string = "HATTIVATTI";
	wavelet_tree* tree = reverse_bwt(string);
	bit_vector* runs = create_runs_vector(tree, 0);
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
	printf("TEST INTERVAL QUERY\n");
	char* string = "ABRACADABRA";
	wavelet_tree* tree = reverse_bwt(string);
	bit_vector* runs = create_runs_vector(tree, 0);
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
	printf("TEST WRONG INTERVALS\n");
	char* string = "ABRACADABRA";
	wavelet_tree* tree = reverse_bwt(string);
	bit_vector* runs = create_runs_vector(tree, 0);
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
	shared_list[list_ptr] = malloc(sizeof(substring));
	substring* tmp = shared_list[list_ptr];

	tmp->length = substr->length;

	tmp->normal.i = substr->normal.i;
	tmp->normal.j = substr->normal.j;

	tmp->reverse.i = substr->reverse.i;
	tmp->reverse.j = substr->reverse.j;

	list_ptr++;
}

//checks if shared_list contains given element. 1 if contains, 0 if not.
int shared_list_contains(substring* comp)
{
	substring* sub;
	for(int i = 0; i<list_ptr; i++){
		sub = shared_list[i];
		if(sub->normal.i == comp->normal.i &&
				sub->normal.j == comp->normal.j &&
				sub->reverse.i == comp->reverse.i &&
				sub->reverse.j == comp->reverse.j &&
				sub->length == comp->length){
			return 1;
		}
	}

	return 0;
}

//this test tests nothing??
START_TEST(test_iterate2)
{
	printf("TEST ITERATE 2\n");
	list_ptr = 0;
	int max_size = 20;
	shared_list = malloc(sizeof(substring*)*max_size);
	char* string = "hattivatti";

	interval normal = (interval) {.i = 8, .j = 9};
	interval reverse = (interval) {.i = 4, .j = 5};
	substring* tti = &((substring) {.normal = normal, .reverse = reverse, .length = 3});

	iterate(string, &put_substring_list);
}END_TEST

START_TEST(test_iterate1)
{
	printf("TEST ITERATE 1\n");
	list_ptr = 0;
	int max_size = 20;
	shared_list = malloc(sizeof(substring*)*max_size);
	char* string = "abracadabra";

	interval normal = (interval) {.i = 2, .j = 3};
	interval reverse = (interval) {.i = 4, .j = 5};
	substring* abra = &((substring) {.normal = normal, .reverse = reverse, .length = 4});

	normal = (interval) {.i = 10, .j = 11};
	reverse = (interval) {.i = 4, .j = 5};
	substring* ra = &((substring) {.normal = normal, .reverse = reverse, .length = 2});

	iterate(string, &put_substring_list);

	fail_unless(shared_list_contains(abra) == 1);
	fail_unless(shared_list_contains(ra) == 1);
}
END_TEST

int check_list_contains_and_remove(int index_bwt, int length){
	test_substr* prev = naive_rmaximals;
	test_substr* node = naive_rmaximals->next;

	while(node != NULL){
		if(node->length == length && node->start_index == suffix_array[index_bwt]){
			prev->next = node->next;
			free(node);
			return 1;
		}
		prev = node;
		node = node->next;
	}
	return 0;
}

void check_substrings_callback(substring* substr)
{
	for(int i = substr->normal.i; i <= substr->normal.j; i++){
		if(!check_list_contains_and_remove(i, substr->length)){
			callback_flag = 0;
		}
	}
}

START_TEST(test_iterate_randomized_small_alphabet)
{
	srand(time(NULL));
	char* alphabet = "acgt";
<<<<<<< HEAD
	char* bwt;
	for(int i= 0; i<100; i++){
=======
	wavelet_tree* bwt;
	for(int i= 0; i<1000; i++){
>>>>>>> 28b69ce15a01f4ea5191347f5f24d03e691c99fe
		int length = (rand() % 200)+1;
		char* rand_string = generate_random_string(alphabet, length);
		bwt = s_to_BWT(rand_string);

		suffix_array = map_create_suffix_array_from_bwt(bwt);
		naive_rmaximals = find_right_maximal_substrings(rand_string);
		callback_flag = 1;

		iterate(rand_string, &check_substrings_callback);
		fail_unless(naive_rmaximals->next == NULL);
		fail_unless(callback_flag == 1);
	}
}
END_TEST

START_TEST(test_iterate_randomized_big_alphabet)
{
	srand(time(NULL));
	char* alphabet = "qwaesrdtfyguhijokplmnbvcxz";
<<<<<<< HEAD
	char* bwt;
	for(int i= 0; i<100; i++){
=======
	wavelet_tree* bwt;
	for(int i= 0; i<1000; i++){
>>>>>>> 28b69ce15a01f4ea5191347f5f24d03e691c99fe
		int length = (rand() % 100) + 100;
		char* rand_string = generate_random_string(alphabet, length);
		bwt = s_to_BWT(rand_string);
		suffix_array = map_create_suffix_array_from_bwt(bwt);
		naive_rmaximals = find_right_maximal_substrings(rand_string);
		callback_flag = 1;

		iterate(rand_string, &check_substrings_callback);
		fail_unless(naive_rmaximals->next == NULL);
		fail_unless(callback_flag == 1);
	}
}
END_TEST

START_TEST(test_iterate_randomized_one_long_string)
{
	srand(time(NULL));
	char* alphabet = "qwaesrdtfyguhijokplmnbvcxz";
	wavelet_tree* bwt;

	int length = (rand() % 1000) + 1000;
	char* rand_string = generate_random_string(alphabet, length);
	bwt = s_to_BWT(rand_string);
	suffix_array = map_create_suffix_array_from_bwt(bwt);
	naive_rmaximals = find_right_maximal_substrings(rand_string);
	callback_flag = 1;

	iterate(rand_string, &check_substrings_callback);
	fail_unless(naive_rmaximals->next == NULL);
	fail_unless(callback_flag == 1);

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

TCase * create_randomized_tcase(void)
{
	TCase* tc_random = tcase_create("randomized_tests");
	tcase_add_test(tc_random, test_iterate_randomized_small_alphabet);
	tcase_add_test(tc_random, test_iterate_randomized_big_alphabet);
	tcase_add_test(tc_random, test_iterate_randomized_one_long_string);
	return tc_random;
}


Suite * test_suite(void)
{
	Suite* s = suite_create("Iterate");
	TCase* tc_runs = create_runs_vec_test_case();
	TCase* tc_iterate = create_iterate_tcase();
	TCase* tc_randomized = create_randomized_tcase();

	suite_add_tcase(s, tc_runs);
	suite_add_tcase(s, tc_iterate);
	suite_add_tcase(s, tc_randomized);

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
