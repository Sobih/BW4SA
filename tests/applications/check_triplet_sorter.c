#include <check.h>
#include "../../include/core.h"
#include "../../include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



START_TEST(test_pos1_1)
{

	triplet* first = &((triplet) {.pos1 = 5, .pos2 = 3, .length = 3});
	triplet* second = &((triplet) {.pos1 = 1, .pos2 = 2, .length = 3});
	triplet* third = &((triplet) {.pos1 = 3, .pos2 = 5, .length = 2});
	
	
	triplet* array = malloc(sizeof(triplet) * 3);
	
	array[0] = *first;
	array[1] = *second;
	array[2] = *third;
	compare_quick_sort(array, 3, sizeof(triplet), &compare_triplets_pos1);
	

	triplet a = (triplet)array[0];
	ck_assert_int_eq(1, a.pos1);
	a = (triplet)array[1];
	ck_assert_int_eq(3, a.pos1);
	a = (triplet)array[2];
	ck_assert_int_eq(5, a.pos1); 



} END_TEST

triplet* generate_random_triplet_array(int size)
{
	triplet* array = malloc(sizeof(triplet) * size);
	int i;
	srand(time(NULL));
	for (i = 0; i < size; i++) {
		triplet* t = &((triplet) {.pos1 = rand(), .pos2 = rand(), .length = rand()});
		array[i] = *t;	
	}

	return array;
}

START_TEST (test_pos1_2)
{

	srand(time(NULL));
	for(int i = 0; i < 100; i++){
		int size = rand() % 1000 +2;
		triplet* array = generate_random_triplet_array(size);
		compare_quick_sort(array, size, sizeof(triplet), &compare_triplets_pos1);
		for (int j = 0; j < size-1; j++) {
			fail_unless(array[j].pos1 <= array[j+1].pos1);
		}
	}

} END_TEST

START_TEST (test_pos2_1)
{
	srand(time(NULL));
	for(int i = 0; i < 100; i++){
		int size = rand() % 1000 +2;
		triplet* array = generate_random_triplet_array(size);
		compare_quick_sort(array, size, sizeof(triplet), &compare_triplets_pos2);
		for (int j = 0; j < size-1; j++) {
			fail_unless(array[j].pos2 <= array[j+1].pos2);
		}
	}


} END_TEST


max_repeat_node* generate_random_max_repeat_array(int size)
{


	max_repeat_node* array = malloc(sizeof(max_repeat_node) * size);
	int i, r1, r2;
	srand(time(NULL));
	for (i = 0; i < size; i++) {
		r1 = rand() % 10000;
		r2 = rand() % 10000;
		Interval* ival = malloc(sizeof(Interval*));
		if (r1 < r2) {
			ival->i = r1;
			ival->j = r2;				
		} else {
			ival->i = r2;
			ival->j = r1;
		}
		
		max_repeat_node* m = &((max_repeat_node) {.normal = ival, .length = rand()});
		array[i] = *m;	
	}

	return array;

}

START_TEST (test_max_repeat_nodes)
{
	srand(time(NULL));
	for(int i = 0; i < 100; i++){
		int size = rand() % 1000 +2;
		max_repeat_node* array = generate_random_max_repeat_array(size);
		compare_quick_sort(array, size, sizeof(max_repeat_node), &compare_max_repeat_nodes);
		for (int j = 0; j < size-1; j++) {
			fail_unless((array[j].normal->i < array[j+1].normal->i) || (array[j].normal->i == array[j+1].normal->i && array[j].normal->j <= array[j+1].normal->j) );
		}
	}


} END_TEST

TCase * create_triplet_sorter_test_case(void) {
	TCase * tc_stack = tcase_create("triplet_sorter_test");
	tcase_add_test(tc_stack, test_pos1_1);
	tcase_add_test(tc_stack, test_pos1_2);
	tcase_add_test(tc_stack, test_pos2_1);
	tcase_add_test(tc_stack, test_max_repeat_nodes);
	return tc_stack;
}

Suite * test_suite(void) {
	Suite *s = suite_create("triplet_sorter_test");
	TCase *tc_stack = create_triplet_sorter_test_case();
	suite_add_tcase(s, tc_stack);

	return s;
}

int main() {
	int number_failed;
	Suite *s = test_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	if (number_failed == 0) {
		return 0;
	} else {
		return 1;
	}
}
