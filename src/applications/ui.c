#include "ui.h"
#include "distinct_substrings.h"
#include "triplet_sorter.h"
#include "../core/s_to_bwt.h"
#include "../core/bwt_to_s.h"
#include "../core/rbwt.h"
#include "../core/c_array.h"
#include "../../include/core.h"
#include "../../include/utils.h"
#include "../../include/applications.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT_STRING_LENGTH 100

void print_choices()
{
	printf("Welcome to the Glfbabot-BWT program!\n");
	printf("Operations:\n");
	printf("1 Print right maximal nodes\n");
	printf("2 Make a BWT\n");
	printf("3 Make the original string from BWT\n");
	printf("4 Make a reverse BWT\n");
	printf("5 Print a C-array\n");
	printf("6 Make a runs vector\n");
	printf("7 Find MUM:s\n");
	printf("8 Make a DOT tree\n");
	printf("9 Count distinct substrings\n");
	printf("10 Display maximal repeats\n");
}

void print_int_array(int* array, int len)
{
	int i;
	for (i = 0; i < len; i++) {
		printf("%d ", array[i]);
	}

}

void print_instructions(int choice)
{

	if (choice == 1 || choice == 2 || choice == 4 || choice == 6 || choice == 9)
		printf("Do not give a dollar sign.\n");
	else if (choice == 3)
		printf("Give a bwt string.\n");
	else if (choice == 5)
		printf("Give a dollar sign ($) to the end of the string.\n");
}

void print_runs_vector(bit_vector* runs, int len)
{
	int i;
	for (i = 0; i < len; i++) {
		if (runs->is_bit_marked(runs, i))
			printf("%d", 1);
		else 
			printf("%d", 0);
	}
	printf("\n");

}


void ui()
{
	int choice, len = 0;
	char* input = malloc(sizeof(char)*MAX_INPUT_STRING_LENGTH);
	char* res = malloc(sizeof(char));
	int* array = calloc(20, sizeof(int)); 
	
	print_choices();
	
	printf("Write the number of the operation you want to do:\n");
	scanf("%d", &choice);
	
	printf("Give the input string: (max size %d) ", MAX_INPUT_STRING_LENGTH);
	print_instructions(choice);
	scanf("%s", input);
	wavelet_tree* root = create_wavelet_tree(input);
	wavelet_tree* res_root;

	if (choice == 1) {
		iterate(input, &print_node);
	} else if (choice == 2) {
		res_root = s_to_bwt(input);
		print_wavelet_tree(res_root);
	} else if (choice == 3) {
		res = bwt_to_s(root);
		printf("%s\n", res);
	} else if (choice == 4) {
		res_root = reverse_bwt(input);
		print_wavelet_tree(res_root);
	} else if (choice == 5) {
		array = create_c_array(root,0,0,0,0);
		int len = strlen(determine_alphabet(input));
		print_int_array(array, len);
	} else if (choice == 6) {
		bit_vector* runs = create_runs_vector(root,0);
		print_runs_vector(runs, strlen(input)+1);
		free_bit_vector(runs);
	} else if (choice == 7) {
		printf("Give the second input string: ");
		char* input2 = malloc(sizeof(char)*MAX_INPUT_STRING_LENGTH);
		scanf("%s", input2);
		double_iterate(input, input2, &search_mums);
		print_mums(input);
		mum_print_bit_vectors(input,input2);

	} else if (choice == 8) {
		printf("Not supported yet\n");
	} else if (choice == 9) {		 
		printf("%d\n", distinct_substrings(input));
	} else if (choice == 10) {
		iterate(input, &search_maximal_repeats);
		//maximals_print_nodes(input);
		print_maximal_repeat_substrings(input);
		//compare_quick_sort()
	} else {
		printf("Invalid choice\n");
	}


}
