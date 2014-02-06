
#include <check.h>
#include "../../include/iterate.h"
#include "../../src/iterate/substring_stack.h"
#include <stdlib.h>

substring* create_substr(void)
{
	substring* new = malloc(sizeof(substring));
	return new;
}

substring** create_n_substrs(int n)
{
	substring** array = malloc(sizeof(substring*)*n);
	int i;
	for(i=0;i<n;i++){
		array[i] = create_substr();
	}
	return array;
}

START_TEST(test_simple_pushnpop)
{
	substring_stack* stack = create_stack(10);
	substring* new = create_substr();
	push(stack, new);
	fail_unless(new == pop(stack));
}
END_TEST

START_TEST(test_simple_pushnpop2)
{
	substring_stack* stack = create_stack(10);
	substring* new = create_substr();
	push(stack, new);
	substring* new2 = create_substr();
	push(stack, new2);
	substring* new3 = create_substr();
	push(stack, new3);
	fail_unless(new3 == pop(stack));
	fail_unless(new2 == pop(stack));
	fail_unless(new == pop(stack));
}
END_TEST

START_TEST(heavy_pushnpop)
{
	substring_stack* stack = create_stack(7);
	int n = 129;
	substring** arr = create_n_substrs(n);
	int i;
	for(i=0; i<n; i++){
		push(stack, arr[i]);
	}
	int j;
	for(i=n-1, j= 0; i>=0; i--, j++){
		fail_unless(arr[i] == pop(stack));
	}
	
}
END_TEST

START_TEST(heavy_pushnpop2)
{
	substring_stack* stack = create_stack(3);
	int n = 200;
	int i, k, j;
	substring** arr = create_n_substrs(n);
	for(i=0;i<n;i++){
	
		for(j=0;j<=i;j++){
			push(stack, arr[j]);
		}
		for(k=i;k>=0;k--){
			fail_unless(arr[k] == pop(stack));
		}
	}
	
}
END_TEST

START_TEST(heavy_pushnpop3)
{
	substring_stack* stack = create_stack(27);
	int n = 1500;
	int i, k, j;
	substring** arr = create_n_substrs(n);
	for(i=0;i<n;i++){
	
		for(j=0;j<=i;j++){
			push(stack, arr[j]);
		}
		for(k=i;k>=0;k--){
			fail_unless(arr[k] == pop(stack));
		}
	}
	
}
END_TEST

START_TEST(even_more_heavier_pushnpop)
{
	substring_stack* stack = create_stack(1);
	int n = 700;
	substring** arr = create_n_substrs(n);
	int i;
	for(i=0; i<n; i++){
		push(stack, arr[i]);
	}
	int j;
	for(i=n-1, j= 0; i>=0; i--, j++){
		fail_unless(arr[i] == pop(stack));
	}
}
END_TEST
	
TCase * create_heavy_stack_test_case(void){
	TCase * tc_stack = tcase_create("heavy_stack_test");
	tcase_add_test(tc_stack, even_more_heavier_pushnpop);
	tcase_add_test(tc_stack, heavy_pushnpop2);
	tcase_add_test(tc_stack, heavy_pushnpop3);
	return tc_stack;
}

TCase * create_stack_test_case(void){
	TCase * tc_stack = tcase_create("substring_stack_test");
	tcase_add_test(tc_stack, test_simple_pushnpop);
	tcase_add_test(tc_stack, test_simple_pushnpop2);
	tcase_add_test(tc_stack, heavy_pushnpop);
	return tc_stack;
}

Suite * test_suite(void)
{
	Suite *s = suite_create("testi");
	TCase *tc_stack = create_stack_test_case();
	TCase *tc_heavy = create_heavy_stack_test_case();
	suite_add_tcase(s, tc_stack);
	suite_add_tcase(s, tc_heavy);
	
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
