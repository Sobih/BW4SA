
#include <check.h>
#include "../../include/iterate.h"
#include "../../src/iterate/print_node.h"
#include <stdlib.h>

substring* create_substr(void)
{
	substring* new = malloc(sizeof(substring));
	new->normal = malloc(sizeof(Interval));
	new->reverse = malloc(sizeof(Interval));
	return new;
}

START_TEST(test_print)
{
	substring* new = create_substr();
	new->normal->i = 5;
	new->normal->j = 8;
	new->reverse->i = 6;
	new->reverse->j = 9;
	new->length = 3;
	print_node(new);
}
END_TEST

TCase * create_print_node_test_case(void){
	TCase * tc_stack = tcase_create("print_node_test");
	tcase_add_test(tc_stack, test_print);
	return tc_stack;
}

Suite * test_suite(void)
{
	Suite *s = suite_create("testi");
	TCase *tc_stack = create_print_node_test_case();
	suite_add_tcase(s, tc_stack);

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
