#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include "utils_for_tests.h"

char* generate_random_string(char* alphabet, int length)
{
	int alphabet_size = strlen(alphabet);
	char* string = calloc(length+1, sizeof(char));
	srand((int) time(NULL));

	for(int i = 0; i < length; i++){
		string[i] = alphabet[rand() % alphabet_size];
	}
	return string;
}

int two_substrings_maximal(char* string, int string_length, int first_index, int second_index, int substr_length);

int list_contains_substr(char* string, rmaximal_substr* head, int start, int length);

int is_substring_right_maximal(char* string, int string_length, int substr_start, int substr_length)
{
	for(int i = 0; i+substr_length<=string_length; i++){
		if(two_substrings_maximal(string, string_length, substr_start, i, substr_length)){
			return 1;
		}
	}
	return 0;
}

int two_substrings_maximal(char* string, int string_length, int first_index, int second_index, int substr_length)
{

	if(first_index == second_index){
		return 0;
	}
	if(first_index+substr_length > string_length || second_index+substr_length > string_length){

		return 0;
	}
	for(int i=0; i<substr_length; i++){

		if(string[first_index+i] != string[second_index+i]){
			return 0;
		}
	}
	if(first_index+substr_length >= string_length || second_index+substr_length >= string_length){
		return 1;
	}
	if(string[first_index+substr_length] != string[second_index+substr_length]){
		return 1;
	}
	return 0;
}
void print_substr(char* string, int start_index, int length){
	for(int i = 0; i < length ; i++){
		printf("%c", string[start_index+i]);
	}
	printf("\n");
}
rmaximal_substr* find_right_maximal_substrings(char* string)
{

	rmaximal_substr* current = calloc(1, sizeof(rmaximal_substr));
	rmaximal_substr* head = current;
	rmaximal_substr* new;

	int string_length = strlen(string);

	for(int length = 1; length < string_length; length++){
		for(int i = 0; i+length<=string_length; i++){

			if(is_substring_right_maximal(string, string_length, i, length)){

				new = calloc(1, sizeof(rmaximal_substr));
				new->start_index = i;
				new->length = length;
				current->next = new;
				current = new;
			}
		}
	}
	return head;
}

int two_substrings_equal(char* string, int start1, int start2, int length)
{
	for(int i = 0; i< length; i++){
		if(string[start1+i] != string[start2+i]){
			return 0;
		}
	}
	return 1;
}
int list_contains_substr(char* string, rmaximal_substr* head, int start, int length)
{

	rmaximal_substr* current = head->next;
	while(current != NULL){
		if(current->length == length){
			if(two_substrings_equal(string, current->start_index, start, length)){
				return 1;
			}
		}
		current = current->next;
	}
	return 0;
}

void print_rmaximal_list(char* string, rmaximal_substr* head)
{
	rmaximal_substr* current = head->next;
	while(current != NULL){
		print_substr(string, current->start_index, current->length);
		current = current->next;
	}
}

