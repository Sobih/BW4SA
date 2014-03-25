/*
 * backward_search.c
 *
 *  Created on: 30.1.2014
 *      Author: lvapaaka
 */
#include <string.h>
#include <stdlib.h>
#include "../../include/utils.h"
#include "../../include/c_array.h"
#include "../../include/structs.h"
#include "../../include/backward_search.h"
#include "../../include/wavelet_tree.h"

interval* backward_search(const wavelet_tree* bwt, const wavelet_tree* string, interval* target) {
	printf("OAIGDJ\n");
	int i = 0, j = bwt->get_num_bits(bwt) - 1, k, index;
	printf("OAIGDJ\n");
	unsigned int alphabet_length = bwt->get_alphabet_length(bwt) - 1;
	printf("OAIGDJ\n");
	char* alphabet = bwt->get_alphabet(bwt), current;
	printf("OAIGDJ\n");
	unsigned int* c_array = create_c_array(bwt, 0, 0, 0, 0);
	printf("OAIGDJ\n");

	for(k = string->get_num_bits(string) - 1; k >= 0; k--) {
		printf("i: %d, j: %d\n", i, j);

		if(j < i) {
			printf("NULLNULLNULLNULL\n");
			return NULL;
		}

		current = string->char_at(string, k);
		index = binary_search(alphabet, &current, sizeof(char), alphabet_length, 0);

		printf("index: %d\n", index);

		if (index < 0) {
			printf("NULLNULLNULLNULL\n");
			return NULL;
		}

		i = c_array[index] + bwt->rank(bwt, current, 0, i - 1);
		j = i + bwt->rank(bwt, current, i, j) - 1;
	}

	printf("ASODIJSAOIDJOAISJHFOIAHSOGIHSAOFIH\n");

	if (target == 0)
		target = malloc(sizeof(interval));

	printf("AOSIDJBGEYIIBGEAFDGKJHBSHGKJBDGSGFDSKJEAKJYGDAGDAKJHGDAKJHBGDAKJHB\n");

	target->i = i;
	target->j = j;

	printf("AOSIDJBGEYIIBGEAFDGKJHBSHGKJBDGSGFDSKJEAKJYGDAGDAKJHGDAKJHBGDAKJHB\n");

	return target;
}

interval* backward_search_interval(const wavelet_tree* bwt, const interval* inter, char c,
		interval* target) {
	int* c_array = create_c_array(bwt, 0, 0, 0, 0);
	char* alphabet = bwt->get_alphabet(bwt);

	int index = binary_search(alphabet, &c, 0, bwt->get_alphabet_length(bwt) - 1, sizeof(char));
	int i = index + bwt->rank(bwt, c, 0, inter->i - 1);
	int j = i + bwt->rank(bwt, c, inter->i, inter->j) - 1;

	if (i > j) return NULL;

	if (target == 0)
		target = malloc(sizeof(interval));

	target->i = i;
	target->j = j;

	return target;
}
	
