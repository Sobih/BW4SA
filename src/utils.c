/*
 * utils.c
 *
 *  Created on: 24.1.2014
 *      Author: Max Sandberg
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/utils.h"

void swap(void* arr, unsigned int entry_size, int i, int j) {
	void* tmp = malloc(entry_size);

	memcpy(tmp, (arr + (j * entry_size)), entry_size);
    memcpy((arr + (j * entry_size)), (arr + (i * entry_size)), entry_size);
    memcpy((arr + (i * entry_size)), tmp, entry_size);

    free(tmp);
}

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
	quicksort(arr, entry_size, 0, arr_size - 1);
}

