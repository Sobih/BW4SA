

#include "c-array.h"
#include <check.h>
#include <stdio.h>

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
	int i;
	ck_assert_str_eq(correct_alphabet, returned);
	
}
END_TEST

START_TEST(test_carray_simple)
{
	const int correct_array[] = {0,1, 6, 8, 9, 10};
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
	int correct_array[] = {0,1,3,4,6,10};
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
	
	return tc_carray;
}

Suite * test_suite(void)
{
	Suite *s = suite_create("testi");
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
