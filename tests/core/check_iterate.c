
#include "../../src/core/iterate.h"
#include "../../src/core/substring_stack.h"
#include "../../src/core/backward_search.h"
#include "../../src/core/rbwt.h"
#include "../../src/core/s_to_bwt.h"
#include "../../src/applications/map_bwt_to_s.h"
#include "../../src/applications/maximal_repeats.h"
#include "../../include/utils.h"
#include "../utils_for_tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <check.h>

substring** shared_list;
int list_ptr = 0;

//static variables for randomized tests
static test_substr* naive_rmaximals;
static int callback_flag;
static int* suffix_array;

static test_substr** naive_doubles;
static int* suffix_array2;

int is_interval_right_maximal_test(bit_vector* runs, interval* inter) {
	return runs->rank(runs, (inter->i) + 1, inter->j) > 0 ? 1 : 0;
}

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

	free_wavelet_tree(tree);
	free_bit_vector(runs);
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

	free_wavelet_tree(tree);
	free_bit_vector(runs);
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
	ck_assert_int_eq(0, is_interval_right_maximal_test(runs, test1));
	ck_assert_int_eq(1, is_interval_right_maximal_test(runs, test2));

	free_wavelet_tree(tree);
	free_bit_vector(runs);
	free(test1);
	free(test2);
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
	ck_assert_int_eq(0, is_interval_right_maximal_test(runs, test1));
	ck_assert_int_eq(0, is_interval_right_maximal_test(runs, test2));

	free_wavelet_tree(tree);
	free_bit_vector(runs);
	free(test1);
	free(test2);
}
END_TEST

void put_substring_list(iterator_state* state, void* results)
{
	substring* substr = state->current;

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

void free_shared_list() {
	for (int i = 0; i < list_ptr; ++i)
		free(shared_list[i]);

	free(shared_list);
}

//this test tests nothing??
START_TEST(test_iterate2)
{
	printf("TEST ITERATE 2\n");
	list_ptr = 0;
	int max_size = 20;
	shared_list = malloc(sizeof(substring*)*max_size);
	char** strings = malloc(sizeof(char*));
	strings[0] = "hattivatti";

	interval normal = (interval) {.i = 8, .j = 9};
	interval reverse = (interval) {.i = 4, .j = 5};
	substring* tti = &((substring) {.normal = normal, .reverse = reverse, .length = 3});

	iterator_state* state = initialize_iterator(strings, 1);
	single_iterate(state, &put_substring_list, 0);
	free_iterator_state(state);
	free(strings);
	free_shared_list();
}END_TEST

START_TEST(test_iterate1)
{
	printf("TEST ITERATE 1\n");
	list_ptr = 0;
	int max_size = 20;
	shared_list = malloc(sizeof(substring*)*max_size);
	char** strings = malloc(sizeof(char*));
	strings[0] = "abracadabra";

	interval normal = (interval) {.i = 2, .j = 3};
	interval reverse = (interval) {.i = 4, .j = 5};
	substring* abra = &((substring) {.normal = normal, .reverse = reverse, .length = 4});

	normal = (interval) {.i = 10, .j = 11};
	reverse = (interval) {.i = 4, .j = 5};
	substring* ra = &((substring) {.normal = normal, .reverse = reverse, .length = 2});

	iterator_state* state = initialize_iterator(strings, 1);
	single_iterate(state, &put_substring_list, 0);
	free_iterator_state(state);
	free(strings);

	fail_unless(shared_list_contains(abra) == 1);
	fail_unless(shared_list_contains(ra) == 1);

	free_shared_list();
}
END_TEST

int check_list_contains_and_remove(int index_bwt, int length, test_substr* list, int* suffixes){
	test_substr* prev = list;
	test_substr* node = list->next;

	while(node != NULL){
		if(node->length == length && node->start_index == suffixes[index_bwt]){
			prev->next = node->next;
			free(node);
			return 1;
		}
		prev = node;
		node = node->next;
	}
	return 0;
}

void check_substrings_callback(iterator_state* state, void* results)
{
	substring* substr = state->current;

	for(int i = substr->normal.i; i <= substr->normal.j; i++){
		if(!check_list_contains_and_remove(i, substr->length, naive_rmaximals, suffix_array)){
			callback_flag = 0;
		}
	}
}

START_TEST(test_iterate_randomized_small_alphabet)
{
	printf("TEST ITERATE SMALL RANDOM ALPHABET\n");
	srand(time(NULL));
	char* alphabet = "acgt";
	char** strings = malloc(sizeof(char*));
	wavelet_tree* bwt;
	iterator_state* state;
	for(int i= 0; i<1000; i++){

		int length = (rand() % 200)+1;
		strings[0] = generate_random_string(alphabet, length);
		bwt = s_to_bwt(strings[0]);

		suffix_array = map_create_suffix_array_from_bwt(bwt);
		naive_rmaximals = find_right_maximal_substrings(strings[0]);
		callback_flag = 1;

		state = initialize_iterator(strings, 1);
		single_iterate(state, &check_substrings_callback, 0);
		free_iterator_state(state);
		free_wavelet_tree(bwt);
		free(strings[0]);

		fail_unless(naive_rmaximals->next == NULL);
		fail_unless(callback_flag == 1);

		free(naive_rmaximals);
		free(suffix_array);
	}

	free(strings);
}
END_TEST

START_TEST(test_iterate_randomized_big_alphabet)
{
	printf("TEST ITERATE BIG RANDOM ALPHABET\n");
	srand(time(NULL));
	char* alphabet = "qwaesrdtfyguhijokplmnbvcxz";
	char** strings = malloc(sizeof(char*));
	wavelet_tree* bwt;
	iterator_state* state;
	for(int i= 0; i<1000; i++){
		int length = (rand() % 100) + 100;
		strings[0] = generate_random_string(alphabet, length);
		bwt = s_to_bwt(strings[0]);
		suffix_array = map_create_suffix_array_from_bwt(bwt);
		naive_rmaximals = find_right_maximal_substrings(strings[0]);
		callback_flag = 1;

		state = initialize_iterator(strings, 1);
		single_iterate(state, &check_substrings_callback, 0);
		free_iterator_state(state);
		free_wavelet_tree(bwt);
		free(strings[0]);

		fail_unless(naive_rmaximals->next == NULL);
		fail_unless(callback_flag == 1);

		free(naive_rmaximals);
		free(suffix_array);
	}

	free(strings);
}
END_TEST

START_TEST(test_iterate_randomized_one_long_string)
{
	printf("TEST ITERATE LONG RANDOM STRING\n");
	srand(time(NULL));
	char* alphabet = "qwaesrdtfyguhijokplmnbvcxz";
	char** strings = malloc(sizeof(char*));
	wavelet_tree* bwt;

	int length = (rand() % 1000) + 1000;
	strings[0] = generate_random_string(alphabet, length);
	bwt = s_to_bwt(strings[0]);
	suffix_array = map_create_suffix_array_from_bwt(bwt);
	naive_rmaximals = find_right_maximal_substrings(strings[0]);
	callback_flag = 1;

	iterator_state* state = initialize_iterator(strings, 1);
	single_iterate(state, &check_substrings_callback, 0);
	free_iterator_state(state);
	free_wavelet_tree(bwt);
	free(strings[0]);
	free(strings);

	fail_unless(naive_rmaximals->next == NULL);
	fail_unless(callback_flag == 1);

	free(naive_rmaximals);
	free(suffix_array);
}
END_TEST

void check_doubles_callback(iterator_state* state, void* results) {
	substring* substr1 = &state->current[0], *substr2 = &state->current[1];

	for(int i = substr1->normal.i; i <= substr1->normal.j; i++){
		if(!check_list_contains_and_remove(i, substr1->length, naive_doubles[0], suffix_array)){
			fail_unless(1 == 0);
		}
	}
	for(int i = substr2->normal.i; i <= substr2->normal.j; i++){
		if(!check_list_contains_and_remove(i, substr2->length, naive_doubles[1], suffix_array2)){
			fail_unless(1 == 0);
		}
	}
}

START_TEST(test_double_iterate_randomized)
{
	printf("DOUBLE ITERATE RANDOM\n");
	srand(time(NULL));
	char* alphabet = "acgt";
	char** strings = malloc(2 * sizeof(char*));
	wavelet_tree* bwt1, *bwt2;
	iterator_state* state;

	for(int i= 0; i<1000; i++){

		int length = (rand() % 200)+1;
		strings[0] = generate_random_string(alphabet, length);
		bwt1 = s_to_bwt(strings[0]);

		length = (rand() % 200)+1;
		strings[1] = generate_random_string(alphabet, length);
		bwt2 = s_to_bwt(strings[1]);

		suffix_array = map_create_suffix_array_from_bwt(bwt1);
		suffix_array2 = map_create_suffix_array_from_bwt(bwt2);

		naive_doubles = find_common_substrings(strings[0], strings[1]);
		callback_flag = 1;

		state = initialize_iterator(strings, 2);
		double_iterate(state, &check_doubles_callback, 0);
		free_iterator_state(state);
		free_wavelet_tree(bwt1);
		free_wavelet_tree(bwt2);
		free(strings[0]);
		free(strings[1]);

		fail_unless(naive_doubles[0]->next == NULL);
		fail_unless(naive_doubles[1]->next == NULL);

		free(naive_doubles[0]);
		free(naive_doubles[1]);
		free(naive_doubles);
		free(suffix_array);
		free(suffix_array2);
	}

	free(strings);
}
END_TEST

START_TEST(test_double_iterate_randomized_long_alphabet)
{
	printf("DOUBLE ITERATE RANDOM LONG ALPHABET\n");
	srand(time(NULL));
	char* alphabet = "qazwsxedcrfvtgbyhnujmikol1234567890";
	char** strings = malloc(2 * sizeof(char*));
	wavelet_tree* bwt1, *bwt2;
	iterator_state* state;

	for(int i= 0; i<1000; i++){

		int length = (rand() % 200)+1;
		strings[0] = generate_random_string(alphabet, length);
		bwt1 = s_to_bwt(strings[0]);

		length = (rand() % 200)+1;
		strings[1] = generate_random_string(alphabet, length);
		bwt2 = s_to_bwt(strings[1]);

		suffix_array = map_create_suffix_array_from_bwt(bwt1);
		suffix_array2 = map_create_suffix_array_from_bwt(bwt2);

		naive_doubles = find_common_substrings(strings[0], strings[1]);
		callback_flag = 1;

		state = initialize_iterator(strings, 2);
		double_iterate(state, &check_doubles_callback, 0);
		free_iterator_state(state);
		free_wavelet_tree(bwt1);
		free_wavelet_tree(bwt2);
		free(strings[0]);
		free(strings[1]);

		fail_unless(naive_doubles[0]->next == NULL);
		fail_unless(naive_doubles[1]->next == NULL);

		free(naive_doubles[0]);
		free(naive_doubles[1]);
		free(naive_doubles);
		free(suffix_array);
		free(suffix_array2);
	}

	free(strings);
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

TCase * create_double_iterate_randomized_tcase(void)
{
	TCase* tc_double = tcase_create("randomized_tests");
	tcase_add_test(tc_double, test_double_iterate_randomized);
	tcase_add_test(tc_double, test_double_iterate_randomized_long_alphabet);

	return tc_double;
}



Suite * test_suite(void)
{
	Suite* s = suite_create("Iterate");
	TCase* tc_runs = create_runs_vec_test_case();
	TCase* tc_iterate = create_iterate_tcase();
	TCase* tc_randomized = create_randomized_tcase();
	TCase* tc_double = create_double_iterate_randomized_tcase();

	suite_add_tcase(s, tc_runs);
	suite_add_tcase(s, tc_iterate);
	suite_add_tcase(s, tc_randomized);
	suite_add_tcase(s, tc_double);
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
