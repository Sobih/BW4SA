/*
 * check_utils.c
 *
 *  Created on: 24.1.2014
 *      Author: Max Sandberg & Paula Lehtola
 */

#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/utils.h"

START_TEST (test_quicksort) {
	int* array = calloc(6, sizeof(int));
	array[0] = 5;
	array[1] = 1;
	array[2] = 42;
	array[3] = 7;
	array[4] = 30;
	array[5] = 666;

	quick_sort(array, 6, sizeof(int));

	//check all ints
	ck_assert(array[0] == 1);
	ck_assert(array[1] == 5);
	ck_assert(array[2] == 7);
	ck_assert(array[3] == 30);
	ck_assert(array[4] == 42);
	ck_assert(array[5] == 666);

	free(array);
}
END_TEST

START_TEST (test_faulty_array) {
	long* array = 0;

	quick_sort(array, 420, sizeof(long));

	//if the algorithm doesn't crash, the test has passed
}
END_TEST

START_TEST (test_large_array) {
	char* comp = "HasSDUwqaBiUSRiduwIUHGFIUAGHouLKrJVNlkaslkBVlPkvLJHYbAliwyr947hgfrLQGIflhigaASflkuBAlv7v3liuIoHAkuhflhbbvlLIUae7dslf7g9LKUAsylfIjfliga5ASflkuBAlv7v3liuIHAkuWhflhbbJvlLIFUae7dslf7g9LKUAsylflv17v3liuIHAwkuhflhbbvlLIUae7dslf7g9LKUAsylifasSDwqaiUSiduwIUHGFIUQAGHoVuLKeJVNlkasklkBgVlkvqLJHYAovliwyr9Z47hgf0rLQGIflGiQgaASflkuBAlv7v3liuIIHAkuhflhbbvlLIUae7dslf7g9LKUAsylfasDuAfSd6MwadAsgfGSAgSAgnse3c3gAdEgGDOKafHf9N7m6a9o7bfULHnofay8NogOIYbvoi8yfd9loYAB9plfp2ASydMDx87yAGFgitumUHAliugd7liuhgNAJ3DsLKudjhgliu8ylPiulOiugyliazduH9GLIAKudHGLiqXTYSdnC4";

	char* array = calloc(strlen(comp) + 1, sizeof(char));
	for (int i = 0; i <= strlen(comp); ++i)
		*(array + i) = comp[i];

	quick_sort(array, strlen(array), sizeof(char));

	//check if lengths match
	ck_assert(strlen(array) == strlen(comp));

	char current = '0';
	int i = 0;

	while (current <= 'z' && i < strlen(array) - 1) {
		ck_assert(array[i] == current);

		if (array[i + 1] != current) {
			current = current == '9' ? 'A' : current + 1;
			current = current == '[' ? 'a' : current;
			ck_assert(array[i + 1] == current);
		}

		i++;
	}

	free(array);
}
END_TEST

START_TEST (test_string_quicksort) 
{
	char *array[] = {"aa",  "baa", "aba", "a"};
	char *sorted[] = {"a", "aa", "aba", "baa"};
	string_quick_sort(array, 4);
	int i;
	for (i = 0; i < 4; i++) {
		ck_assert_str_eq(array[i], sorted[i]);
	}
	
}
END_TEST	

START_TEST (test_string_quicksort2) 
{
	char *array[] = {"aaa",  "aa", "a", "a"};
	char *sorted[] = {"a", "a", "aa", "aaa"};
	string_quick_sort(array, 4);
	int i;
	for (i = 0; i < 4; i++) {
		ck_assert_str_eq(array[i], sorted[i]);
	}
	
}
END_TEST

START_TEST (test_string_quicksort3) 
{
	char *array[] = {"testing", "if", "a", "quicksort", "can", "sort", "this"};
	char *sorted[] = {"a", "can", "if", "quicksort", "sort", "testing", "this"};
	string_quick_sort(array, 7);
	int i;
	for (i = 0; i < 7; i++) {
		ck_assert_str_eq(array[i], sorted[i]);
	}
	
}
END_TEST


Suite* array_suite(void) {
	Suite* suite = suite_create("Utils");

	TCase* tc_alphabet_mapping = tcase_create("Quicksort");
	tcase_add_test (tc_alphabet_mapping, test_quicksort);
	tcase_add_test (tc_alphabet_mapping, test_faulty_array);
	tcase_add_test (tc_alphabet_mapping, test_large_array);
	tcase_add_test (tc_alphabet_mapping, test_string_quicksort);
	tcase_add_test (tc_alphabet_mapping, test_string_quicksort2);
	tcase_add_test (tc_alphabet_mapping, test_string_quicksort3);
	suite_add_tcase (suite, tc_alphabet_mapping);

	return suite;
}

int main() {
	int number_failed;
	Suite* suite = array_suite();
	SRunner* suite_runner = srunner_create(suite);
	srunner_run_all(suite_runner, CK_VERBOSE);
	number_failed = srunner_ntests_failed(suite_runner);
	srunner_free(suite_runner);

	return (number_failed == 0) ? 0 : 1;
}
