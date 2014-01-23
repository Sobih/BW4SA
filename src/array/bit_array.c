/*
 * bit_array.c
 *
 *  Created on: 21.1.2014
 *      Author: Max Sandberg
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/bit_array.h"

//method declarations
char_mapping* construct_mapping(const char* alphabet, unsigned int length);
char* determine_alphabet(const char* string);
void quick_sort(char* string, unsigned int size);


char_mapping* map_alphabet(const char* string) {
	char* alphabet;

	if ((alphabet = determine_alphabet(string)) == 0)
		//return null if alphabet couldn't be determined
		return 0;

	//sort constructed alphabet into lexicographic order
	unsigned int length = strlen(alphabet);
	quick_sort(alphabet, length);

	char_mapping* mapping = construct_mapping(alphabet, length);

	//delete alphabet
	free(alphabet);

	return mapping;
}

char_mapping* construct_mapping(const char* alphabet, unsigned int length) {
	char_mapping* mapping;
	unsigned int bit_value = 1;

	if ((mapping = calloc(length + 1, sizeof(char_mapping))) == 0)
		//allocation failed, return NULL
		return 0;

	//add starting value that defines length of array
	mapping[0].bit_value = length;
	mapping[0].character = 0;

	//create mapping
	for (int i = 0; i < length; ++i) {
		mapping[i + 1].character = alphabet[i];
		mapping[i + 1].bit_value = bit_value;

		bit_value++;
	}

	return mapping;
}

char* determine_alphabet(const char* string) {
	int chars_left = 10, alphabet_size = 0;
	unsigned int size = strlen(string);
	char* alphabet;

	if ((alphabet = calloc(chars_left, sizeof(char))) == 0)
		return 0;

	int exists;

	for (int i = 0; i < size; ++i) {
		exists = 0;

		for (int j = 0; j < alphabet_size; ++j) {
			//break if character already in alphabet
			if (strncmp(string + i, alphabet + j, 1) == 0) {
				exists = 1;
				break;
			}
		}

		//character doesn't exist in alphabet, insert it
		if (!exists) {

			if (chars_left == 0) {
				//expand alphabet array
				chars_left = 10;

				if ((alphabet = realloc(alphabet, alphabet_size + chars_left)) == 0)
					//realloc failed, return NULL
					return 0;
			}

			//add to alphabet
			chars_left--;
			alphabet[alphabet_size] = *(string + i);
			alphabet_size++;
		}
	}

	//add null-marker
	if (chars_left == 0)
		//expand alphabet array
		if ((alphabet = realloc(alphabet, alphabet_size + 1)) == 0)
			//realloc failed, return NULL
			return 0;

	//add to alphabet
	alphabet[alphabet_size] = 0;

	return alphabet;
}

void swap(char* arr, int i, int j) {
    char temp = arr[j];
    arr[j] = arr[i];
    arr[i] = temp;
}

void quicksort(char* arr, int a, int b) {
    if (a >= b)
        return;

    char key = arr[a];
    int i = a + 1, j = b;

    while (i < j) {
        while (i < j && arr[j] >= key)
            --j;

        while (i < j && arr[i] <= key)
            ++i;

        if (i < j)
            swap(arr, i, j);
    }

    if (arr[a] > arr[i]) {
        swap(arr, a, i);
        quicksort(arr, a, i - 1);
        quicksort(arr, i + 1, b);
    }

    // there is no left-hand-side
    else {
        quicksort(arr, a + 1, b);
    }
}

void quick_sort(char* string, unsigned int size) {
	quicksort(string, 0, size - 1);
}
