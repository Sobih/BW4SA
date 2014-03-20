#include <check.h>
#include "../../include/iterate.h"
#include "../../include/maximal_repeats.h"
#include "../../include/mapper.h"
#include "../../include/mum.h"
#include "../../include/utils.h"
#include "../../src/iterate/triplet_sorter.h"
#include <stdlib.h>


START_TEST(int_array)
{
	int array[5] = {5, 4, 3, 2, 1};

	compare_quick_sort(array, 5, sizeof(int), &compare_ints);
	
	ck_assert_int_eq(0, array[0]);

} END_TEST

/*START_TEST(test_pos1_1)
{

	triplet* first = &((triplet) {.pos1 = 5, .pos2 = 3, .length = 3});
	triplet* second = &((triplet) {.pos1 = 0, .pos2 = 2, .length = 3});
	triplet* third = &((triplet) {.pos1 = 3, .pos2 = 5, .length = 2});
	
	triplet* array[3];
	
	array[0] = first;
	array[1] = second;
	array[2] = third;
	
	compare_quick_sort(array, 3, sizeof(triplet*), &compare_triplets_pos1);
	
	triplet* a = (triplet*)array[0];
	ck_assert_int_eq(0, a->pos1);
	//ck_assert_int_eq(2, a->pos2);
	a = (triplet*)array[1];
	ck_assert_int_eq(3, a->pos1);
	//ck_assert_int_eq(3, a->pos2);
	a = (triplet*)array[2];
	ck_assert_int_eq(5, a->pos1); 
	//ck_assert_int_eq(5, a->pos2);


typedef struct triplet_struct {
	unsigned int pos1;
	unsigned int pos2;
	unsigned int length;
} triplet;
*/

//void compare_quick_sort(void* arr, unsigned int arr_size, unsigned int entry_size, int (*compare)(void* first, void* second))


/*} END_TEST*/


TCase * create_triplet_sorter_test_case(void) {
	TCase * tc_stack = tcase_create("triplet_sorter_test");
	tcase_add_test(tc_stack, int_array);
	//tcase_add_test(tc_stack, test_pos1_1);
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
