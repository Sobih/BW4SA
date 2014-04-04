

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../../src/core/backward_search.h"
#include "../../src/core/c_array.h"
#include "../../src/utils/wavelet_tree.h"
#include "../../src/utils/structs.h"
#include "../../src/utils/utils.h"

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

START_TEST(test_carray_simple)
{
	const int correct_array[] = {0,1, 6, 8, 9, 10};
	char* string = "ABRACADABRA$";
	wavelet_tree* root = create_wavelet_tree(string);

	unsigned int* carray = create_c_array(root, 0, 0, 0, 0);

	for(int i = 0; i < 6; i++)
		ck_assert_int_eq(correct_array[i], carray[i]);

	free_wavelet_tree(root);
	free(carray);
}
END_TEST

START_TEST(test_carray_simple2)
{
	int correct_array[] = {0,1,3,4,6,10};
	char* string = "hattivatti$";
	wavelet_tree* root = create_wavelet_tree(string);

	int* carray = create_c_array(root, 0, 0, 0, 0);
	
	for(int i = 0; i < 6; i++)
		ck_assert_int_eq(correct_array[i], carray[i]);

	free_wavelet_tree(root);
	free(carray);
}
END_TEST

START_TEST(carray_interval1)
{
	char* string = "aasdjfsbdhablsdaksdakjsdaksjdbiuephq";
	wavelet_tree* tree = create_wavelet_tree(string);

	interval* inter = malloc(sizeof(interval));
	inter->i = 0;
	inter->j = 5;

	int correct[] = {0,2,3,4,5};
	unsigned int* c_arr = create_c_array(tree, inter, 0, 0, 0);

	for(int i=0; i< 5; i++)
		ck_assert_int_eq(correct[i], c_arr[i]);

	free_wavelet_tree(tree);
	free(inter);
	free(c_arr);
}
END_TEST

START_TEST(carray_interval2)
{
	char* string = "aggcaggaatttacagcaagacagcgacgacattat";
	wavelet_tree* tree = create_wavelet_tree(string);

	interval* inter = malloc(sizeof(interval));
	inter->i = 7;
	inter->j = 13;

	int correct[] = {0,3,4};
	unsigned int* c_arr = create_c_array(tree, inter, 0, 0, 0);

	for(int i=0; i< 3; i++)
		ck_assert_int_eq(correct[i], c_arr[i]);

	free_wavelet_tree(tree);
	free(inter);
	free(c_arr);
}
END_TEST

START_TEST(alphabet_interval) {
	srand(time(NULL));

	int length = (rand() % 500) + 1, runs = 500, start, end, counter, index, correct_length;
	char* string = malloc(length * sizeof(char));
	interval* inter = malloc(sizeof(interval));
	wavelet_tree* tree;
	char* correct_alphabet;
	alphabet_data* alphabet;

	int run_counter = 1;

	for (int i = 0; i < runs; ++i) {
		//printf("Commencing run %d / %d\n", run_counter, runs);

		generate_random_string(string, length);
		tree = create_wavelet_tree(string);

		start = rand() % (length / 2);

		do {
			end = rand() % (length - 1);
		} while (end <= start);

		inter->i = start;
		inter->j = end;

		//find correct alphabet naïvely
		counter = 0;
		correct_alphabet = calloc(length, sizeof(char));
		for (int i = start; i <= end; ++i) {
			index = binary_search(correct_alphabet, (string + i), sizeof(char), counter, 0);
			if (index < 0 || index > counter) {
				correct_alphabet[counter] = string[i];
				counter++;
				quick_sort(correct_alphabet, counter, sizeof(char));
			}
		}

		correct_alphabet[counter] = 0;

		correct_length = strlen(correct_alphabet);

		alphabet = create_alphabet_interval(inter, tree, 0);

		ck_assert(correct_length == alphabet->length);

		for (int i = 0; i < correct_length; ++i)
			ck_assert(alphabet->alphabet[i] == correct_alphabet[i]);

		free_wavelet_tree(tree);
		free(correct_alphabet);
		free(alphabet->alphabet);
		free(alphabet);

		run_counter++;
	}

	//printf("Finished %d / %d in total\n", run_counter - 1, runs);
}
END_TEST

START_TEST(alphabet_interval1)
{
	char* string = "abracadabra";
	wavelet_tree* tree = create_wavelet_tree(string);

	interval* inter = malloc(sizeof(interval));
	inter->i = 4;
	inter->j = 6;

	char* correct = "acd";
	alphabet_data* alphabet = create_alphabet_interval(inter, tree, 0);
	ck_assert_str_eq(correct, alphabet->alphabet);
		
	free_wavelet_tree(tree);
	free(inter);
	free(alphabet->alphabet);
	free(alphabet);
}
END_TEST

START_TEST(alphabet_interval2)
{
	char* string = "dsdasdasdasdppkkklklkljjljpkkpkp";
	wavelet_tree* tree = create_wavelet_tree(string);

	interval* inter = malloc(sizeof(interval));
	inter->i = 10;
	inter->j = 14;

	char* correct = "dkps";
	alphabet_data* alphabet = create_alphabet_interval(inter, tree, 0);
	ck_assert_str_eq(correct, alphabet->alphabet);
		
	free_wavelet_tree(tree);
	free(inter);
	free(alphabet->alphabet);
	free(alphabet);
}
END_TEST

TCase * create_carray_test_case(void){
	TCase * tc_carray = tcase_create("carray_test");
	tcase_add_test(tc_carray, test_carray_simple);
	tcase_add_test(tc_carray, test_carray_simple2);
	tcase_add_test(tc_carray, carray_interval1);
	tcase_add_test(tc_carray, carray_interval2);
	tcase_add_test(tc_carray, alphabet_interval);
	tcase_add_test(tc_carray, alphabet_interval1);
	tcase_add_test(tc_carray, alphabet_interval2);
	return tc_carray;
}

Suite * test_suite(void)
{
	Suite *s = suite_create("c-array");
	TCase *tc_carray = create_carray_test_case();
	suite_add_tcase(s, tc_carray);
	
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
