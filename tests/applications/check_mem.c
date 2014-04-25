#include <check.h>
#include "../../include/core.h"
#include "../../include/applications.h"
#include "../../include/utils.h"
#include "../../src/core/s_to_bwt.h"
#include "../../src/applications/mapper.h"
#include "../utils_for_tests.h"
#include "../../src/utils/structs.h"
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
	char** strings = malloc(2 * sizeof(char*));
	char* alphabet = "qwaesrdtfywugihoijokjplkplcznbvcxznbvm";
	substring_pair* naive_mems;
	parameter_struct* params;
	iterator_state* state;

	for (int i = 0; i < 10; i++) {
		int len1 = rand() % 20 + 1;
		int len2 = rand() % 20 + 1;

		strings[0] = generate_random_string(alphabet, len1);
		strings[1] = generate_random_string(alphabet, len2);

		naive_mems = find_maximal_exact_matches(strings[0], strings[1], 1);

		params = initialize_for_mems(strings, 10000);
		state = iterate(params);
		mem_results* results = (mem_results*) params->ret_data;
		triplet* fast_mems = results->data;
		int num_mems = results->length;

		map_mem_triplets_to_string(fast_mems, &state->bwts[0], &state->bwts[1], num_mems, mem_make_bit_vectors(results, state));

		for(int j = 0; j < num_mems; j++)
			fail_unless(search_and_remove(fast_mems[j], naive_mems));

		fail_unless(naive_mems->next == NULL);

		free(strings[0]);
		free(strings[1]);
		free(results->params);
		free(results);
		free(params);
		free(naive_mems);
		free_iterator_state(state);
	}

	free(strings);
}
END_TEST

START_TEST(test_mems_randomized_small_alphabet) {
	srand(time(NULL));
	char** strings = malloc(2 * sizeof(char*));
	char* alphabet = "abcgdf";
	substring_pair* naive_mems;
	parameter_struct* params;
	iterator_state* state;
	
	for (int i = 0; i < 10; i++) {
		int len1 = rand() % 20 + 1;
		int len2 = rand() % 20 + 1;

		strings[0] = generate_random_string(alphabet, len1);
		strings[1] = generate_random_string(alphabet, len2);

		naive_mems = find_maximal_exact_matches(strings[0], strings[1], 1);

		params = initialize_for_mems(strings, 10000);
		state = iterate(params);
		mem_results* results = (mem_results*) params->ret_data;
		triplet* fast_mems = results->data;
		int num_mems = results->length;

		map_mem_triplets_to_string(fast_mems, &state->bwts[0], &state->bwts[1], num_mems, mem_make_bit_vectors(results, state));


		for(int j = 0; j < num_mems; j++)
			fail_unless(search_and_remove(fast_mems[j], naive_mems));

		fail_unless(naive_mems->next == NULL);

		free(strings[0]);
		free(strings[1]);
		free(results->params);
		free(results);
		free(params);
		free(naive_mems);
		free_iterator_state(state);
	}

	free(strings);
}
END_TEST

START_TEST(test_mems_randomized_few_long_strings) {
	srand(time(NULL));
	char** strings = malloc(2 * sizeof(char*));
	char* alphabet = "abcgdf";
	substring_pair* naive_mems;
	parameter_struct* params;
	iterator_state* state;

	for (int i = 0; i < 2; i++){
		int len1 = rand() % 300 + 1;
		int len2 = rand() % 300 + 1;

		strings[0] = generate_random_string(alphabet, len1);
		strings[1] = generate_random_string(alphabet, len2);

		naive_mems = find_maximal_exact_matches(strings[0], strings[1], 1);

		params = initialize_for_mems(strings, 10000);
		state = iterate(params);
		mem_results* results = (mem_results*) params->ret_data;
		triplet* fast_mems = results->data;
		int num_mems = results->length;

		map_mem_triplets_to_string(fast_mems, &state->bwts[0], &state->bwts[1], num_mems, mem_make_bit_vectors(results, state));

		for(int j = 0; j < num_mems; j++)
			fail_unless(search_and_remove(fast_mems[j], naive_mems));

		fail_unless(naive_mems->next == NULL);

		free(strings[0]);
		free(strings[1]);
		free(results->params);
		free(results);
		free(params);
		free(naive_mems);
		free_iterator_state(state);
	}

	free(strings);
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
