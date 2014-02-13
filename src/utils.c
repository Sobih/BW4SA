/**
 * @file	utils.c
 * @brief	Implementation of the utility-algorithms.
 * @see		utils.h
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/utils.h"

/**
 * @brief	Simple swap-function.
 *
 * Swaps the position of two entries in an array.
 *
 * @param	arr			Pointer to the array is to be manipulated.
 * @param	entry_size	Size of the entries that are to be swapped.
 * @param	i			Index of the first entry.
 * @param	j			Index of the second entry.
 * @see		utils.h#quick_sort
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void swap(void* arr, unsigned int entry_size, int i, int j) {
	void* tmp = malloc(entry_size);

	memcpy(tmp, (arr + (j * entry_size)), entry_size);
    memcpy((arr + (j * entry_size)), (arr + (i * entry_size)), entry_size);
    memcpy((arr + (i * entry_size)), tmp, entry_size);

    free(tmp);
}

/**
 * @brief	The implementation of the quicksort-algorithm.
 * @param	arr			Pointer to the array that is to be sorted.
 * @param	entry_size	Size of the individual entries in the array.
 * @param	a			Index to the first entry to be sorted.
 * @param	b			Index to the last entry to be sorted.
 * @see		utils.h#quick_sort
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void quicksort(void* arr, unsigned int entry_size, unsigned int a,
		unsigned int b) {

    if (a >= b)
        return;

    void* key = (arr + (a * entry_size));
    int i = a + 1, j = b;

    while (i < j) {
        while (i < j && memcmp((arr + (j * entry_size)), key, entry_size) >= 0)
        	--j;

        while (i < j && memcmp((arr + (i * entry_size)), key, entry_size) <= 0)
        	++i;

        if (i < j)
            swap(arr, entry_size, i, j);
    }

    if (memcmp((arr + (a * entry_size)), (arr + (i * entry_size)), entry_size) > 0) {
        swap(arr, entry_size, a, i);
        quicksort(arr, entry_size, a, i - 1);
        quicksort(arr, entry_size, i + 1, b);
    }

    // there is no left-hand-side
    else
        quicksort(arr, entry_size, a + 1, b);
}

void quick_sort(void* arr, unsigned int arr_size, unsigned int entry_size) {
	if (arr == 0 || arr_size == 0 || entry_size == 0)
		return;

	quicksort(arr, entry_size, 0, arr_size - 1);
}

void print_bits(unsigned int mask) {
	unsigned int size = sizeof(unsigned int);
	unsigned int max_pow = 1 << (size * 8 - 1);

	for (int i = 0; i < size * 8; ++i) {
		// print last bit and shift left.
	    printf("%u", mask & max_pow ? 1 : 0);
	    mask = mask << 1;
	}
}

/**
 * @brief	Simple swap-function.
 *
 * Swaps the position of two strings in an array.
 *
 * @param	a, b	pointers to pointers of strings to be swapped
 * @see		utils.h#string_quick_sort
 * @author	Paula Lehtola
 * @bug		No known bugs.
 */

void string_swap(char **a, char **b) {
	char *tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * @brief	quicksort for an array of strings
 * @param	strings 	array of pointers of strings
 * @param	a	index of the first entry to be sorted
 * @param	b	index of the last entry to be sorted
 * @see		utils.h#quick_sort
 * @author	Paula Lehtola
 * @bug		No known bugs.
 */

void string_quicksort(char **strings, unsigned int a, unsigned int b) {
	if (a >= b)
		return;

	const char *key = strings[a];
	int i = a+1, j = b;

	while (i < j) {
		while (i < j && strcmp(strings[j], key) >= 0)
			j--;

		while (i < j && strcmp(strings[i], key) <= 0)
			i++;

		if (i < j)
			string_swap(strings+i, strings+j);
	}

	if (strcmp(strings[a],strings[i]) > 0) {
		string_swap(strings+a, strings+i);
		string_quicksort(strings, a, i-1);
		string_quicksort(strings, i+1, b);
	} else {
		string_quicksort(strings, a+1, b);
	}

}

void string_quick_sort(char **strings, unsigned int arr_size) {
	if (strings == 0 || arr_size == 0)
		return;

	string_quicksort(strings, 0, arr_size-1);

}

/**
 * @brief	Determines the alphabet used by a string.
 * @param	string	The string from which the alphabet should be deduced.
 * @return			The alphabet used by the string.
 * @see		bit_array.h#map_alphabet
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
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

int binary_search(const void* arr, const void* key, unsigned int min, unsigned int max,
		unsigned int entry_size) {

	//(sub)set empty
	if (max < min)
		return -1;

	//(sub)set has size 1
	if (max == min)
		return memcmp(arr + (min * entry_size), key, entry_size) == 0 ? min : -1;

	int mid = min + ((max - min) / 2);

	printf("Mid: %d\n", mid);

	int comparison = memcmp(arr + (mid * entry_size), key, entry_size);

	printf("Comparison: %d\n", comparison);

	//key is in lower subset
	if (comparison > 0)
		return binary_search(arr, key, min, mid - 1, entry_size);

	//key is in upper subset
	if (comparison < 0)
		return binary_search(arr, key, mid + 1, max, entry_size);

	return mid;
}
