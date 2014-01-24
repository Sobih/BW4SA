#include "../../src/backward-search/c-array.h"
#include <check.h>

START_TEST(test_get_index)
{
	char* alphabet = "ACGT";
	char c = 'C';
	ck_assert_int_eq(1, get_index(alphabet, c));
}
END_TEST

START_TEST(test_create_alphabet)
{
	char* correct_alphabet = "biopsy";
	char* returned = get_alphabet("pspspspyyssysysobiiiiiiibbboooopspspsp");
	int i;
	ck_assert_str_eq(correct_alphabet, returned);
}
END_TEST

START_TEST(test_create_alphabet2)
{
	char* correct_alphabet = "almost";
	char* returned = get_alphabet("mmlloooooosssaassoslsaatstststalala");
	int i;
	ck_assert_str_eq(correct_alphabet, returned);
}
END_TEST

START_TEST(test_carray_simple)
{
	int correct_array[] = {1, 6, 8, 9, 10, 12};
	char* string = "ABRACADABRA$";
	int i;
	int* carray = create_c_array(string);
	for(i=0;i<6;i++){
		ck_assert_int_eq(correct_array[i], carray[i]);
	}
}
END_TEST

START_TEST(test_carray_simple2)
{
	int correct_array[] = {1,3,4,6,10, 11};
	char* string = "hattivatti$";
	int i;
	int* carray = create_c_array(string);
	for(i=0;i<6;i++){
		ck_assert_int_eq(correct_array[i], carray[i]);
	}
}
END_TEST

TCase * create_carray_test_case(void){
	TCase * tc_carray = tcase_create("carray_test");
	tcase_add_test(tc_carray, test_get_index);
	tcase_add_test(tc_carray, test_create_alphabet);
	tcase_add_test(tc_carray, test_carray_simple);
	tcase_add_test(tc_carray, test_carray_simple2);
	
	//tcase_add_test(tc_carray, test_carray_simple);
	return tc_carray;
}
