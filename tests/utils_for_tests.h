/*
 * utils_for_tests.h
 *
 *  Created on: 24.3.2014
 *      Author: topatopa
 */

#ifndef UTILS_FOR_TESTS_H_
#define UTILS_FOR_TESTS_H_

typedef struct tests_substring
{
	int start_index;
	int length;
	struct tests_substring* next;
}test_substr;

typedef struct substr_pair
{
	int index1;
	int index2;
	int length;
	struct substr_pair* next;
}substring_pair;

char* generate_random_string(char* alphabet, int length);

test_substr* find_maximal_repeat_substrings(char* string);

test_substr* find_right_maximal_substrings(char* string);

test_substr** find_common_substrings(char* first, char* second);

void print_substring_list(char* string, test_substr* head);

void print_substring_indices(test_substr* head);

int is_substring_maximal_exact_match(char* string1, char* string2, int string1_length, int string2_length, int string1_substr_start, int substr_length);

#endif /* UTILS_FOR_TESTS_H_ */
