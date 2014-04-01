

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../../include/backward_search.h"
#include "../../include/c_array.h"
#include "../../include/wavelet_tree.h"
#include "../../include/structs.h"
#include "../../include/utils.h"

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

	int length = (rand() % 500) + 1;
	char* string = malloc(length * sizeof(char));

	generate_random_string(string, length);
	wavelet_tree* tree = create_wavelet_tree(string);

	int start = rand() % length, end;

	do {
		end = rand() % length;
	} while (end <= start);

	interval* inter = malloc(sizeof(interval));
	inter->i = start;
	inter->j = end;

	//find correct alphabet naïvely
	int counter = 0, index;
	char* correct_alphabet = calloc(length, sizeof(char));
	for (int i = start; i <= end; ++i) {
		index = binary_search(correct_alphabet, (string + i), sizeof(char), counter, 0);
		if (index < 0 || index >= counter) {
			correct_alphabet[counter] = string[i];
			counter++;
			quick_sort(correct_alphabet, counter, sizeof(char));
		}
	}

	int correct_length = strlen(correct_alphabet);

	alphabet_data* alphabet = create_alphabet_interval(inter, tree, 0);

	printf("Alphabet: %s\n", alphabet->alphabet);
	printf("Length: %d\n", alphabet->length);
	printf("Correct alphabet: %s\n", correct_alphabet);
	printf("Correct length: %d\n", correct_length);

	ck_assert(correct_length == alphabet->length);

	for (int i = 0; i < correct_length; ++i)
		ck_assert(alphabet->alphabet[i] == correct_alphabet[i]);
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
