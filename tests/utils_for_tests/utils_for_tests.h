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

char* generate_random_string(char* alphabet, int length);

test_substr* find_maximal_repeat_substrings(char* string);

test_substr* find_right_maximal_substrings(char* string);

void print_rmaximal_list(char* string, test_substr* head);

#endif /* UTILS_FOR_TESTS_H_ */
