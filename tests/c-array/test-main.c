#include <check.h>
#include "c-array-test.h"

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
	
	if(number_failed == 0)
	{
		return 0;
	}
	else
	{
	return 1;
	}
}
