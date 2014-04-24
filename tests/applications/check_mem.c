#include <check.h>
#include "../../include/core.h"
#include "../../include/applications.h"
#include "../../include/utils.h"
#include "../../src/core/s_to_bwt.h"
#include "../../src/applications/mapper.h"
#include "../utils_for_tests.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int search_and_remove(triplet trip, substring_pair* head)
{
	substring_pair* previous = head;
	substring_pair* current = head->next;
	while(current != NULL){
		if(trip.pos1 == current->index1 &&
				trip.pos2 == current->index2 &&
				trip.length == current->length){
			previous->next = current->next;
			free(current);
			return 1;
		}
		previous = previous->next;
		current = current->next;
	}
	return 0;
}

START_TEST(test_mems_randomized_big_alphabet) {


	srand(time(NULL));
	char* test1;
	char* test2;
	wavelet_tree* bwt;
	int* suffix_array;
	int length;
	char* alphabet = "qwaesrdtfywugihoijokjplkplcznbvcxznbvm";

	for (int i = 0; i < 10; i++){
		test1 = generate_random_string(alphabet, rand() % 100 + 1);
		test2 = generate_random_string(alphabet, rand() % 100 + 1);
		int len1 = strlen(test1);
		int len2 = strlen(test2);

		substring_pair* naive_mems = find_maximal_exact_matches(test1, test2, 1);

		double_iterate(test1, test2, &search_mems);
		triplet* fast_mems = get_mems();
		int num_mems = get_mems_amount();



		//custom mapping for mems. This has to be changed when real mapping is ready.
		map_mem_triplets_to_string(fast_mems, s_to_BWT(test1), s_to_BWT(test2), num_mems, mem_make_bit_vectors(fast_mems));

		for(int h = 0; h <num_mems; h++){
		}
		for(int j = 0; j < num_mems; j++){
			if(!search_and_remove(fast_mems[j], naive_mems)){
				fail_unless(1 == 0);
			}
		}
		fail_unless(naive_mems->next == NULL);
	}
}
END_TEST

START_TEST(test_mems_randomized_small_alphabet) {


	srand(time(NULL));
	char* test1;
	char* test2;
	wavelet_tree* bwt;
	int* suffix_array;
	int length;
	char* alphabet = "abcgdf";
	
	for (int i = 0; i < 10; i++){
		test1 = generate_random_string(alphabet, rand() % 20 + 1);
		test2 = generate_random_string(alphabet, rand() % 20 + 1);
		int len1 = strlen(test1);
		int len2 = strlen(test2);

		substring_pair* naive_mems = find_maximal_exact_matches(test1, test2, 1);

		double_iterate(test1, test2, &search_mems);
		triplet* fast_mems = get_mems();
		int num_mems = get_mems_amount();



		//custom mapping for mems. This has to be changed when real mapping is ready.
		map_mem_triplets_to_string(fast_mems, s_to_BWT(test1), s_to_BWT(test2), num_mems, mem_make_bit_vectors(fast_mems));

		for(int h = 0; h <num_mems; h++){
		}
		for(int j = 0; j < num_mems; j++){
			if(!search_and_remove(fast_mems[j], naive_mems)){
				fail_unless(1 == 0);
			}
		}
		fail_unless(naive_mems->next == NULL);
	}
}
END_TEST

START_TEST(test_mems_randomized_few_long_strings) {


	srand(time(NULL));
	char* test1;
	char* test2;
	wavelet_tree* bwt;
	int* suffix_array;
	int length;
	char* alphabet = "abcgdf";

	for (int i = 0; i < 2; i++){
		test1 = generate_random_string(alphabet, rand() % 300 + 1);
		test2 = generate_random_string(alphabet, rand() % 300 + 1);
		int len1 = strlen(test1);
		int len2 = strlen(test2);

		substring_pair* naive_mems = find_maximal_exact_matches(test1, test2, 1);

		double_iterate(test1, test2, &search_mems);
		triplet* fast_mems = get_mems();
		int num_mems = get_mems_amount();

		//custom mapping for mems. This has to be changed when real mapping is ready.
		map_mem_triplets_to_string(fast_mems, s_to_BWT(test1), s_to_BWT(test2), num_mems, mem_make_bit_vectors(fast_mems));

		for(int h = 0; h <num_mems; h++){
		}
		for(int j = 0; j < num_mems; j++){
			if(!search_and_remove(fast_mems[j], naive_mems)){
				fail_unless(1 == 0);
			}
		}
		fail_unless(naive_mems->next == NULL);
	}
}
END_TEST

TCase * create_mems_test_case(void) {
	TCase * tc_mems = tcase_create("mems_test");
	tcase_add_test(tc_mems, test_mems_randomized_big_alphabet);
	tcase_add_test(tc_mems, test_mems_randomized_small_alphabet);
	tcase_add_test(tc_mems, test_mems_randomized_few_long_strings);
	tcase_set_timeout(tc_mems, 120);
	return tc_mems;
}

Suite * test_suite(void) {
	Suite *s = suite_create("test_for_mems");
	TCase *tc_mems = create_mems_test_case();
	suite_add_tcase(s, tc_mems);

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
