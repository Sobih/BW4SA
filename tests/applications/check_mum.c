/*
 * check_mum.c
 *
 *  Created on: 14.3.2014
 *      Author: lvapaaka
 */

#include "../../src/core/iterate.h"
#include "../../src/core/s_to_bwt.h"
#include "../../src/utils/bit_vector.h"
#include "../../include/utils.h"
#include "../../src/applications/mum.h"
#include "../../src/applications/mapper.h"
#include "../../src/utils/structs.h"
#include "../utils_for_tests.h"

#include <stdlib.h>
#include <check.h>
#include <time.h>

START_TEST(test_mum1)
	{
		double_iterate("laatikko", "mehukatti", &search_mums);
		triplet* nodes = get_mums();
		ck_assert_int_eq(2, get_mums_amount());
		ck_assert_int_eq(2, nodes[0].pos1);
		ck_assert_int_eq(1, nodes[0].pos2);
		ck_assert_int_eq(2, nodes[0].length);
		ck_assert_int_eq(8, nodes[1].pos1);
		ck_assert_int_eq(7, nodes[1].pos2);
		ck_assert_int_eq(2, nodes[1].length);
	}END_TEST

START_TEST(test_mum1_mapped)
	{
		double_iterate("laatikko", "mehukatti", &search_mums);
		triplet* nodes = get_mums();
		map_mum_triplets_to_string(nodes, s_to_BWT("laatikko"),
				s_to_BWT("mehukatti"), get_mums_amount());
		ck_assert_int_eq(2, get_mums_amount());
		ck_assert_int_eq(2, nodes[0].pos1);
		ck_assert_int_eq(5, nodes[0].pos2);
		ck_assert_int_eq(2, nodes[0].length);
		ck_assert_int_eq(3, nodes[1].pos1);
		ck_assert_int_eq(7, nodes[1].pos2);
		ck_assert_int_eq(2, nodes[1].length);
	}END_TEST

START_TEST(test_mum2)
	{
		double_iterate("abracadabra", "arbadacarba", &search_mums);
		triplet* nodes = get_mums();
		ck_assert_int_eq(2, get_mums_amount());
		ck_assert_int_eq(5, nodes[0].pos1);
		ck_assert_int_eq(3, nodes[0].pos2);
		ck_assert_int_eq(3, nodes[0].length);
		ck_assert_int_eq(4, nodes[1].pos1);
		ck_assert_int_eq(2, nodes[1].pos2);
		ck_assert_int_eq(3, nodes[1].length);
	}END_TEST

START_TEST(test_mum2_mapped)
	{
		double_iterate("abracadabra", "arbadacarba", &search_mums);
		triplet* nodes = get_mums();
		map_mum_triplets_to_string(nodes, s_to_BWT("abracadabra"),
				s_to_BWT("arbadacarba"), get_mums_amount());
		ck_assert_int_eq(2, get_mums_amount());
		ck_assert_int_eq(5, nodes[0].pos1);
		ck_assert_int_eq(3, nodes[0].pos2);
		ck_assert_int_eq(3, nodes[0].length);
		ck_assert_int_eq(3, nodes[1].pos1);
		ck_assert_int_eq(5, nodes[1].pos2);
		ck_assert_int_eq(3, nodes[1].length);
	}END_TEST

START_TEST(test_mum_empty)
	{
		double_iterate("qwertyui", "asdfghjkl", &search_mums);
		triplet* nodes = get_mums();
		ck_assert_int_eq(0, get_mums_amount());
	}END_TEST

START_TEST(test_mum3)
	{
		double_iterate("qwertnmyuiop", "asdfgnmhjkl", &search_mums);
		triplet* nodes = get_mums();
		ck_assert_int_eq(1, get_mums_amount());
		ck_assert_int_eq(2, nodes[0].length);
	}END_TEST

START_TEST(test_mum3_mapped)
	{
		double_iterate("qwertnmyuiop", "asdfgnmhjkl", &search_mums);
		triplet* nodes = get_mums();
		map_mum_triplets_to_string(nodes, s_to_BWT("qwertnmyuiop"),
				s_to_BWT("asdfgnmhjkl"), get_mums_amount());
		ck_assert_int_eq(1, get_mums_amount());
		ck_assert_int_eq(5, nodes[0].pos1);
		ck_assert_int_eq(5, nodes[0].pos2);
		ck_assert_int_eq(2, nodes[0].length);
	}END_TEST

START_TEST(test_mum1_bitvector)
	{
		double_iterate("laatikko", "mehukatti", &search_mums);
		triplet* nodes = get_mums();
		map_mum_triplets_to_string(nodes, s_to_BWT("laatikko"),
				s_to_BWT("mehukatti"), get_mums_amount());
		bit_vector** vectors = mum_make_bit_vectors(nodes);
		ck_assert_int_eq(1, vectors[0]->is_bit_marked(vectors[0], 2));
		ck_assert_int_eq(1, vectors[0]->is_bit_marked(vectors[0], 3));
		ck_assert_int_eq(0, vectors[0]->is_bit_marked(vectors[0], 5));
		ck_assert_int_eq(0, vectors[0]->is_bit_marked(vectors[0], 7));
		ck_assert_int_eq(1, vectors[1]->is_bit_marked(vectors[1], 5));
		ck_assert_int_eq(1, vectors[1]->is_bit_marked(vectors[1], 7));
		ck_assert_int_eq(0, vectors[1]->is_bit_marked(vectors[1], 2));
		ck_assert_int_eq(0, vectors[1]->is_bit_marked(vectors[1], 3));
	}END_TEST

START_TEST(test_mum2_bitvector)
	{
		double_iterate("abracadabra", "arbadacarba", &search_mums);
		triplet* nodes = get_mums();
		map_mum_triplets_to_string(nodes, s_to_BWT("abracadabra"),
				s_to_BWT("arbadacarba"), get_mums_amount());
		bit_vector** vectors = mum_make_bit_vectors(nodes);
		ck_assert_int_eq(1, vectors[0]->is_bit_marked(vectors[0], 3));
		ck_assert_int_eq(1, vectors[0]->is_bit_marked(vectors[0], 5));
		ck_assert_int_eq(1, vectors[1]->is_bit_marked(vectors[1], 3));
		ck_assert_int_eq(1, vectors[1]->is_bit_marked(vectors[1], 5));
	}END_TEST

START_TEST(test_mum3_bitvector_no_mums)
	{
		double_iterate("abracadabra", "vzxmneytymn", &search_mums);
		triplet* nodes = get_mums();
		map_mum_triplets_to_string(nodes, s_to_BWT("abracadabra"),
				s_to_BWT("arbadacarba"), get_mums_amount());
		bit_vector** vectors = mum_make_bit_vectors(nodes);
		int i;
		for (i = 0; i < vectors[0]->length; i++) {
			ck_assert_int_eq(0, vectors[0]->is_bit_marked(vectors[0], i));
		}
		for (i = 0; i < vectors[1]->length; i++) {
			ck_assert_int_eq(0, vectors[1]->is_bit_marked(vectors[1], i));
		}
	}END_TEST


	int search_and_remove(triplet trip, substring_pair* head) {
		substring_pair* previous = head;
		substring_pair* current = head->next;
		while (current != NULL) {
			if (trip.pos1 == current->index1 && trip.pos2 == current->index2
					&& trip.length == current->length) {
				previous->next = current->next;
				free(current);
				return 1;
			}
			previous = previous->next;
			current = current->next;
		}
		return 0;
	}

START_TEST(test_mums_randomized)
{
	srand(time(NULL));
	char* test1;
	char* test2;
	wavelet_tree* bwt;
	int* suffix_array;
	int length;
	char* alphabet = "qwaesrdtfywugihoijokjplkplcznbvcxznbvm";

	for (int i = 0; i < 100; i++){
//		test1 = generate_random_string(alphabet, rand() % 100 + 1);
//		test2 = generate_random_string(alphabet, rand() % 100 + 1);
		test1 = "battikatti";
		test2 = "mehukatti";
		int len1 = strlen(test1);
		int len2 = strlen(test2);
		printf("%s\n%s\n\n",test1,test2);

		substring_pair* naive_mums = find_maximal_unique_matches(test1, test2, 1);
		print_substring_pairs(naive_mums, test1);

		double_iterate(test1, test2, &search_mums);
		triplet* fast_mums = get_mums();
		int num_mums = get_mums_amount();

		//custom mapping for mums. This has to be changed when real mapping is ready.
		map_mum_triplets_to_string(fast_mums, s_to_BWT(test1), s_to_BWT(test2), num_mums);

		for(int j = 0; j < num_mums; j++){
			fail_unless(search_and_remove(fast_mums[j], naive_mums));
		}
		fail_unless(naive_mums->next == NULL);
	}
}
END_TEST


TCase * create_mums_test_case(void) {
	TCase * tc_mums = tcase_create("mum_test");
	tcase_add_test(tc_mums, test_mum1);
	tcase_add_test(tc_mums, test_mum1_mapped);
	tcase_add_test(tc_mums, test_mum2);
	tcase_add_test(tc_mums, test_mum2_mapped);
	tcase_add_test(tc_mums, test_mum3);
	tcase_add_test(tc_mums, test_mum3_mapped);
	tcase_add_test(tc_mums, test_mum_empty);
	tcase_add_test(tc_mums, test_mum1_bitvector);
	tcase_add_test(tc_mums, test_mum2_bitvector);
	tcase_add_test(tc_mums, test_mum3_bitvector_no_mums);
	return tc_mums;
}

TCase * create_mums_randomized_test_case(void){
	TCase * tc_random_mums = tcase_create("random_mums");
	tcase_add_test(tc_random_mums, test_mums_randomized);
	return tc_random_mums;
}


Suite * test_suite(void) {
	Suite *s = suite_create("testi");
	suite_add_tcase(s, create_mums_test_case());
	suite_add_tcase(s, create_mums_randomized_test_case());

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

