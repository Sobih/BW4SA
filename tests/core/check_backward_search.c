/*
 * check_backward_search.c
 *
 *  Created on: 30.1.2014
 *      Author: lvapaaka
 */

#include "../../src/core/backward_search.h"
#include "../../src/core/s_to_bwt.h"
#include "../../src/utils/structs.h"
#include "../../src/utils/wavelet_tree.h"
#include "../../src/utils/utils.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

int get_char_index(const int* c_array, const char* alphabet, const char c)
{
	int i;
	for(i=0;i<strlen(alphabet);i++){
		if(alphabet[i] == c){
			return c_array[i];
		}
	}
	return -1;
}

int get_index(const char* string, const char c, int length)
{
	int i;
	for(i=0;i<length;i++){
		if(c == string[i]){
			return i;
		}
	}
	return -1;
}

char* get_alphabet(const char* string)
{
	int i;
	char* alphabet = malloc(200 * sizeof(char));
	int alphabet_index = 0;

	int length = strlen(string);
	for(i=0;i<length;i++){
		if(get_index(alphabet, string[i], alphabet_index) == -1){
			//alphabet[alphabet_index+1] = alphabet[alphabet_index];
			alphabet[alphabet_index] = string[i];
			alphabet_index++;
		}
	}

	alphabet[alphabet_index] = 0;

	quick_sort(alphabet, strlen(alphabet), sizeof(char));
	return alphabet;
}

int* create_c_array_naive(const char* string)
{
	int i;
	char* alphabet = get_alphabet(string);
	int alpha_length = strlen(alphabet);
	int* c_array = calloc(alpha_length, sizeof(int));

	for(i=0;i<strlen(string);i++){
		int index = get_index(alphabet, string[i], alpha_length);
		c_array[index] += 1;
	}
	for(i=0;i<strlen(alphabet)-1;i++){
		c_array[i+1] = c_array[i+1] + c_array[i];
	}

	for(i=strlen(alphabet)-1; i>0;i--){
		c_array[i] = c_array[i-1];
	}
	c_array[0] = 0;

	free(alphabet);

	return c_array;
}

int rank(const int index, const char c, const char* string){
	int i, count = 0;
	if(index <= 0){
		return 0;
	}

	for(i = index - 1; i >= 0; i--){
		if(string[i] == c){
			count++;
		}
	}
	return count;
}

interval* backward_search_interval_naive(const char* bwt, interval* inter, const char c){
	int* c_array = create_c_array_naive(bwt);
	char* alphabet = get_alphabet(bwt);

	int i = inter->i;
	int j = inter->j;
	i = get_char_index(c_array, alphabet, c)+rank(i, c, bwt);
	j = get_char_index(c_array, alphabet, c)+rank(j+1, c, bwt)-1;
	if(i > j){
		return NULL;
	}
	interval* new_interval = malloc(sizeof(interval));
	new_interval->i = i;
	new_interval->j = j;
	return new_interval;
}

char* generate_random_string(char* string, unsigned int length) {
	if (length == 0)
		return string;

	string[length - 1] = 0;

	if (length == 1)
		return string;

	for (int i = length - 2; i >= 0; --i)
		*(string + i) = (char) ((rand() % 75) + 49);

	return string;
}

START_TEST(test_search_simple)
{
	char* str = "ard$rcaaaabb";
	wavelet_tree* bwt = create_wavelet_tree(str);

	str = "abra";
	wavelet_tree* string = create_wavelet_tree(str);

	interval* interval = backward_search(bwt, string, 0);

	ck_assert_int_eq(2, interval->i);
	ck_assert_int_eq(3, interval->j);

	free_wavelet_tree(bwt);
	free_wavelet_tree(string);
	free(interval);
}
END_TEST

START_TEST(test_search_simple2)
{
	char* str = "ard$rcaaaabb";
	wavelet_tree* bwt = create_wavelet_tree(str);

	str = "bra";
	wavelet_tree* string = create_wavelet_tree(str);

	interval* interval = backward_search(bwt, string, 0);

	ck_assert_int_eq(6, interval->i);
	ck_assert_int_eq(7, interval->j);

	free_wavelet_tree(bwt);
	free_wavelet_tree(string);
	free(interval);
}
END_TEST

START_TEST(test_search_simple3)
{
	char* str = "ard$rcaaaabb";
	wavelet_tree* bwt = create_wavelet_tree(str);

	str = "abracadabra";
	wavelet_tree* string = create_wavelet_tree(str);

	interval* interval = backward_search(bwt, string, 0);

	ck_assert_int_eq(3, interval->i);
	ck_assert_int_eq(3, interval->j);

	free_wavelet_tree(bwt);
	free_wavelet_tree(string);
	free(interval);
}
END_TEST

START_TEST(test_search_when_not_found)
{
	char* str = "ard$rcaaaabb";
	wavelet_tree* bwt = create_wavelet_tree(str);

	str = "nakki";
	wavelet_tree* string = create_wavelet_tree(str);

	interval* interval = backward_search(bwt, string, 0);

	fail_unless(interval == NULL);

	free_wavelet_tree(bwt);
	free_wavelet_tree(string);
	free(interval);
}
END_TEST

START_TEST(test_search_different_word)
{
	char* str = "ipssm$pissii";
	wavelet_tree* bwt = create_wavelet_tree(str);

	str = "iss";
	wavelet_tree* string = create_wavelet_tree(str);

	interval* interval = backward_search(bwt, string, 0);

	ck_assert_int_eq(3, interval->i);
	ck_assert_int_eq(4, interval->j);

	free_wavelet_tree(bwt);
	free_wavelet_tree(string);
	free(interval);
}
END_TEST

START_TEST(test_interval_search_ra)
{
	interval* inter = malloc(sizeof(interval));
	inter->i = 1;
	inter->j = 5;

	wavelet_tree* tree = create_wavelet_tree("ard$rcaaaabb");

	interval* result = backward_search_interval(tree, inter, 'r', 0);

	ck_assert_int_eq(10, result->i);
    ck_assert_int_eq(11, result->j);

    free_wavelet_tree(tree);
    free(result);
    free(inter);
}
END_TEST

START_TEST(test_interval_search_da)
{
	interval* inter = malloc(sizeof(interval));
	inter->i = 1;
	inter->j = 5;

	wavelet_tree* tree = create_wavelet_tree("ard$rcaaaabb");

	interval* result = backward_search_interval(tree, inter, 'd', 0);

	ck_assert_int_eq(9, result->i);
    ck_assert_int_eq(9, result->j);

    free_wavelet_tree(tree);
    free(result);
    free(inter);
}
END_TEST

START_TEST(test_interval_search_bra)
{
	interval* inter = malloc(sizeof(interval));
	inter->i = 10;
	inter->j = 11;

	wavelet_tree* tree = create_wavelet_tree("ard$rcaaaabb");

	interval* result = backward_search_interval(tree, inter, 'b', 0);

	ck_assert_int_eq(6, result->i);
    ck_assert_int_eq(7, result->j);

    free_wavelet_tree(tree);
    free(result);
    free(inter);
}
END_TEST

START_TEST(test_interval_search_tt)
{
	interval* inter = malloc(sizeof(interval));
	inter->i = 6;
	inter->j = 9;

	wavelet_tree* tree = create_wavelet_tree("ivh$ttttaai");

	interval* result = backward_search_interval(tree, inter, 't', 0);

	ck_assert_int_eq(8, result->i);
    ck_assert_int_eq(9, result->j);

    free_wavelet_tree(tree);
    free(result);
    free(inter);
}
END_TEST

START_TEST(test_interval_search_ha)
{
	interval* inter = malloc(sizeof(interval));
	inter->i = 1;
	inter->j = 2;

	wavelet_tree* tree = create_wavelet_tree("ivh$ttttaai");

	interval* result = backward_search_interval(tree, inter, 'h', 0);

	ck_assert_int_eq(3, result->i);
    ck_assert_int_eq(3, result->j);

    free_wavelet_tree(tree);
    free(result);
    free(inter);
}
END_TEST

START_TEST(test_interval_search_not_found) {
	interval* inter = malloc(sizeof(interval));
	inter->i = 5;
	inter->j = 8;

	wavelet_tree* tree = create_wavelet_tree("ivh$ttttaai");

	interval* result = backward_search_interval(tree, inter, 'k', 0);

	ck_assert(result == NULL);

	free_wavelet_tree(tree);
	free(result);
	free(inter);
}
END_TEST

START_TEST (test_interval_search_random) {
	srand(time(NULL));

	int length = (rand() % 50) + 2, runs = 100, start, end;
	char* string = malloc(length * sizeof(char)), *bwt = malloc((length + 2) * sizeof(char));
	interval* inter = malloc(sizeof(interval)), *complex = malloc(sizeof(interval)), *naive;
	wavelet_tree* tree;

	int run_counter = 1;

	for (; run_counter <= runs; ++run_counter) {
		string = generate_random_string(string, length);
		tree = s_to_bwt(string);

		for (int j = 0; j < tree->get_num_bits(tree); ++j)
			bwt[j] = tree->char_at(tree, j);

		bwt[tree->get_num_bits(tree)] = 0;

		start = rand() % ((length + 1) / 2);

		do {
			end = rand() % (length + 1);
		} while (end <= start);

		inter->i = start;
		inter->j = end;

		for (int j = 0; j < tree->get_num_bits(tree); ++j) {
			naive = backward_search_interval_naive(bwt, inter, bwt[j]);
			complex = backward_search_interval(tree, inter, bwt[j], complex);

			if (complex == NULL || naive == NULL) {
				ck_assert(complex == naive);
				continue;
			}

			ck_assert(naive->i == complex->i);
			ck_assert(naive->j == complex->j);

			free(naive);
		}

		free_wavelet_tree(tree);
	}
}
END_TEST

TCase* create_backward_search_test_case(void) {
	TCase* tc_backward_search = tcase_create("backward_search_test");
	tcase_add_test(tc_backward_search, test_search_simple);
	tcase_add_test(tc_backward_search, test_search_simple2);
	tcase_add_test(tc_backward_search, test_search_simple3);
	tcase_add_test(tc_backward_search, test_search_when_not_found);
	tcase_add_test(tc_backward_search, test_search_different_word);

	return tc_backward_search;
}

TCase* create_backward_search_interval_test_case(void) {
	TCase* tc_backward_search_interval = tcase_create("backward_search_interval_test");
	tcase_add_test(tc_backward_search_interval, test_interval_search_ra);
	tcase_add_test(tc_backward_search_interval, test_interval_search_da);
	tcase_add_test(tc_backward_search_interval, test_interval_search_bra);
	tcase_add_test(tc_backward_search_interval, test_interval_search_tt);
	tcase_add_test(tc_backward_search_interval, test_interval_search_ha);
	tcase_add_test(tc_backward_search_interval, test_interval_search_not_found);
	tcase_add_test(tc_backward_search_interval, test_interval_search_random);

	return tc_backward_search_interval;
}

Suite * test_suite(void)
{
	Suite *s = suite_create("testi");
	TCase *tc_backward_search = create_backward_search_test_case();
	TCase *tc_backward_search_interval = create_backward_search_interval_test_case();
	suite_add_tcase(s, tc_backward_search);
	suite_add_tcase(s, tc_backward_search_interval);
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
