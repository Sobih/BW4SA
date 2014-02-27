

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/c_array.h"
#include "../../include/backward_search.h";
#include "../../include/wavelet_tree.h"

START_TEST(test_get_index)
{
	const char* alphabet = "ACGT";
	char c = 'C';
	ck_assert_int_eq(1, get_index(alphabet, c));
	
}
END_TEST

START_TEST(test_create_alphabet)
{
	const char* correct_alphabet = "biopsy";
	char* returned = get_alphabet("pspspspyyssysysobiiiiiiibbboooopspspsp");
	int i;
	ck_assert_str_eq(correct_alphabet, returned);
	
}
END_TEST

START_TEST(test_create_alphabet2)
{
	const char* correct_alphabet = "almost";
	char* returned = get_alphabet("mmlloooooosssaassoslsaatstststalala");
	ck_assert_str_eq(correct_alphabet, returned);
	
	
}
END_TEST

START_TEST(test_get_alphabet3)
{
	const char* correct_alphabet = "$abcdr";
	char* returned = get_alphabet("abracadabra$");
	ck_assert_str_eq(correct_alphabet, returned);
	
}
END_TEST

START_TEST(test_carray_simple)
{
	const int correct_array[] = {0,1, 6, 8, 9, 10};
	char* string = "ABRACADABRA$";
	wavelet_node* root = create_wavelet_tree(string);

	int* carray = create_c_array(root);

	for(int i = 0; i < 6; i++)
		ck_assert_int_eq(correct_array[i], carray[i]);
}
END_TEST

START_TEST(test_carray_simple2)
{
	int correct_array[] = {0,1,3,4,6,10};
	char* string = "hattivatti$";
	wavelet_node* root = create_wavelet_tree(string);

	int* carray = create_c_array(root);
	
	for(int i = 0; i < 6; i++)
		ck_assert_int_eq(correct_array[i], carray[i]);
}
END_TEST

START_TEST(carray_interval1)
{
	char* string = "aasdjfsbdhablsdaksdakjsdaksjdbiuephq";
	interval* interval = malloc(sizeof(interval));
	interval->i = 0;
	interval->j = 5;
	int correct[] = {0,2,3,4,5};
	int* c_arr = create_c_array_interval(interval, string);
	for(int i=0; i< 5; i++){
		ck_assert_int_eq(correct[i], c_arr[i]);
	}
}
END_TEST

START_TEST(carray_interval2)
{
	char* string = "aggcaggaatttacagcaagacagcgacgacattat";
	interval* interval = malloc(sizeof(interval));
	interval->i = 7;
	interval->j = 13;
	int correct[] = {0,3,4};
	int* c_arr = create_c_array_interval(interval, string);
	for(int i=0; i< 4; i++){
		ck_assert_int_eq(correct[i], c_arr[i]);
	}
}
END_TEST

START_TEST(alphabet_interval1)
{
	char* string = "abracadabra";
	interval* interval = malloc(sizeof(interval));
	interval->i = 4;
	interval->j = 6;
	char* correct = "acd";
	char* alphabet = create_alphabet_interval(interval, string);
	ck_assert_str_eq(correct, alphabet);
		
	
}
END_TEST

START_TEST(alphabet_interval2)
{
	char* string = "dsdasdasdasdppkkklklkljjljpkkpkp";
	interval* interval = malloc(sizeof(interval));
	interval->i = 10;
	interval->j = 14;
	char* correct = "dkps";
	char* alphabet = create_alphabet_interval(interval, string);
	ck_assert_str_eq(correct, alphabet);
		
	
}
END_TEST

TCase * create_carray_test_case(void){
	TCase * tc_carray = tcase_create("carray_test");
	tcase_add_test(tc_carray, test_get_index);
	tcase_add_test(tc_carray, test_create_alphabet);
	tcase_add_test(tc_carray, test_create_alphabet2);
	tcase_add_test(tc_carray, test_carray_simple);
	tcase_add_test(tc_carray, test_carray_simple2);
	tcase_add_test(tc_carray, test_get_alphabet3);
	tcase_add_test(tc_carray, carray_interval2);
	tcase_add_test(tc_carray, carray_interval1);
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
