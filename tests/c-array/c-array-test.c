#include "../src/backward-search/c-array.h"
#include <check.h>

START_TEST(test_get_index)
{
	char* alphabet = "ACGT";
	char c = 'C';
	ck_assert_int_eq(1, get_index(alphabet, c));
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

TCase * create_carray_test_case(void){
	TCase * tc_carray = tcase_create("carray_test");
	tcase_add_test(tc_carray, test_get_index);
	tcase_add_test(tc_carray, test_carray_simple);
	return tc_carray;
}
