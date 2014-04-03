#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include "utils_for_tests.h"

char* generate_random_string(char* alphabet, int length) {
	int alphabet_size = strlen(alphabet);
	char* string = calloc(length + 1, sizeof(char));
	srand((int) time(NULL));

	for (int i = 0; i < length; i++) {
		string[i] = alphabet[rand() % alphabet_size];
	}
	return string;
}

int two_substrings_right_maximal(char* string, int string_length,
		int first_index, int second_index, int substr_length);

int list_contains_substr(char* string, test_substr* head, int start, int length);

int two_substrings_equal_not_same(char* string, int string_length,
		int first_index, int second_index, int substr_length) {

	if (first_index == second_index) {
		return 0;
	}
	if (first_index + substr_length > string_length
			|| second_index + substr_length > string_length) {

		return 0;
	}
	for (int i = 0; i < substr_length; i++) {

		if (string[first_index + i] != string[second_index + i]) {
			return 0;
		}
	}
	return 1;
}

int two_substrings_left_maximal(char* string, int string_length,
		int first_index, int second_index, int substr_length) {

	if (!two_substrings_equal_not_same(string, string_length, first_index,
			second_index, substr_length)) {
		return 0;
	}
	if (first_index == 0 || second_index == 0) {
		return 1;
	}
	if (string[first_index - 1] != string[second_index - 1]) {
		return 1;
	}
	return 0;
}

int two_substrings_right_maximal(char* string, int string_length,
		int first_index, int second_index, int substr_length) {

	if (!two_substrings_equal_not_same(string, string_length, first_index,
			second_index, substr_length)) {
		return 0;
	}
	if (first_index + substr_length >= string_length
			|| second_index + substr_length >= string_length) {
		return 1;
	}
	if (string[first_index + substr_length]
			!= string[second_index + substr_length]) {
		return 1;
	}
	return 0;
}

int is_substring_right_maximal(char* string, int string_length,
		int substr_start, int substr_length) {
	for (int i = 0; i + substr_length <= string_length; i++) {
		if (two_substrings_right_maximal(string, string_length, substr_start, i,
				substr_length)) {
			return 1;
		}
	}
	return 0;
}

int is_substring_max_repeat(char* string, int string_length, int substr_start,
		int substr_length) {

	int found = 0;
	for (int i = 0; i + substr_length <= string_length; i++) {
		if (two_substrings_right_maximal(string, string_length, substr_start, i,
				substr_length)) {
			found = 1;
			break;
		}
	}
	if(!found){
		return 0;
	}
	for (int i = 0; i + substr_length <= string_length; i++) {
			if (two_substrings_left_maximal(string, string_length,
							substr_start, i, substr_length)) {
				return 1;
			}
		}
	return 0;
}

void print_substr(char* string, int start_index, int length) {
	for (int i = 0; i < length; i++) {
		printf("%c", string[start_index + i]);
	}
	printf("\n");
}

test_substr* find_maximal_repeat_substrings(char* string) {

	test_substr* current = calloc(1, sizeof(test_substr));
	test_substr* head = current;
	test_substr* new;

	int string_length = strlen(string);

	for (int length = 1; length < string_length; length++) {
		for (int i = 0; i + length <= string_length; i++) {

			if (is_substring_max_repeat(string, string_length, i, length)) {

				new = calloc(1, sizeof(test_substr));
				new->start_index = i;
				new->length = length;
				current->next = new;
				current = new;
			}
		}
	}
	return head;
}
test_substr* find_right_maximal_substrings(char* string) {

	test_substr* current = calloc(1, sizeof(test_substr));
	test_substr* head = current;
	test_substr* new;

	int string_length = strlen(string);

	for (int length = 1; length < string_length; length++) {
		for (int i = 0; i + length <= string_length; i++) {

			if (is_substring_right_maximal(string, string_length, i, length)) {

				new = calloc(1, sizeof(test_substr));
				new->start_index = i;
				new->length = length;
				current->next = new;
				current = new;
			}
		}
	}
	return head;
}

int two_substrings_equal(char* string, int start1, int start2, int length) {
	for (int i = 0; i < length; i++) {
		if (string[start1 + i] != string[start2 + i]) {
			return 0;
		}
	}
	return 1;
}
int list_contains_substr(char* string, test_substr* head, int start, int length) {

	test_substr* current = head->next;
	while (current != NULL) {
		if (current->length == length) {
			if (two_substrings_equal(string, current->start_index, start,
					length)) {
				return 1;
			}
		}
		current = current->next;
	}
	return 0;
}

void print_substring_list(char* string, test_substr* head) {
	test_substr* current = head->next;
	while (current != NULL) {
		print_substr(string, current->start_index, current->length);
		current = current->next;
	}
}

void print_substring_indices(test_substr* head) {
	test_substr* current = head->next;
	while(current != NULL){
		printf("index: %d, length %d\n", current->start_index, current->length);
		current = current->next;
	}

}

int two_substrings_from_different_strings_equal(char* string1, char* string2, int string1_length, int string2_length, int string1_index, int string2_index, int substr_length)
{
	int i;

	if (string1_index + substr_length > string1_length || string2_index + substr_length > string2_length) {
		return 0;
	}
	
	for (i = 0; i < substr_length; i++) {
		if (string[string1_index] + i != string[second_index + i]) {
			return 0;
		}
	
	}
	
	return 1;

}


int two_substrings_from_different_strings_right_maximal(char* string1, char* string2, int string1_length, int string2_length, int string1_index, int string2_index, int substr_length) 
{
	if (!two_substrings_from_different_strings_equal(string1, string2, string1_length, string2_length, string1_index, string2_index, substr_length)) {
		return 0;
	}
	
	if (string1_index + substr_length >= string1_length || string2_index + substr_length >= string2_length) {
		return 1;	
	}
	
	if (string1[string1_index + substr_length] != string2[string2_index + substr_length]) {
		return 1;
	}
	
	return 0;
}

int two_substrings_from_different_strings_left_maximal(char* string1, char* string2, int string1_length, int string2_length, int string1_index, int string2_index, int substr_length) {
	
	if (!two_substrings_from_different_strings_equal(string1, string2, string1_length, string2_length, string1_index, string2_index, substr_length)) {
		return 0;
	}
	
	if (string1_index == 0 || string2_index == 0) {
		return 1;
	}
	
	if (string1[string1_index - 1] != string2[string2_index - 1]) {
		return 1;
	}
	
	return 0;

}

int is_substring_in_two_strings_max_repeat(char* string1, char* string2, int string1_length, int string2_length, int string1_substr_start, int substr_length)
{
	int i, found = 0;
	for (i = 0; i + substr_length <= string2_length; i++) {
		if (two_substrings_from_different_strings_right_maximal(string1, string2, string1_length, string2_length, string1_substr_start, i, substr_length)) {
			found = 1;
			break;
		}
	}
	
	if (!found) return 0;
	
		for (i = 0; i + substr_length <= string2_length; i++) {
			if (two_substrings_from_different_strings_left_maximal(string1, string2, string1_length, string2_length, string1_substr_start, i, substr_length)) {
			return 1;
			
		}
	}
	
	return 0;
	
}


void find_maximal_exact_match_naive(char* string1, char* string2)
{
	int length, i;
	
	
	test_substr* current = calloc(1, sizeof(test_substr));
	test_substr* head = current;
	test_substr* new;
	
	int string1_length = strlen(string1);
	int string2_length = strlen(string2);
	
	for (length = 1; length < string1_length; length++) {
		for (i = 0; i + length <= string1_length; i++) {
			
		}
	
	}


}

//int main(){
//
//	char* test = generate_random_string("acgt", 100);
//	test = "sadhgajhgshajdhsgdjakjdhaksdjqwgeyuoqweluywqiehqwhevjwqhevwqeiugqweqwuegqwiyeqweqiywleq";
//	test_substr* repeats = find_maximal_repeat_substrings(test);
//	print_substring_list(test, repeats);
//	return 0;
//}

