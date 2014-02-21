#include "../bwt/s_to_bwt.h"
#include "../../include/bwt_to_s.h"
#include "../../include/rbwt.h"
#include "../../include/c_array.h"
#include "../../include/iterate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_choices()
{
	printf("Welcome to the Glfbabot-BWT program!\n");
	printf("Operations:\n");
	printf("1 Print right maximal nodes\n");
	printf("2 Make BWT\n");
	printf("3 Make original string from BWT\n");
	printf("4 Make reverse BWT\n");
	printf("5 Print C-array\n");
	printf("6 Make runs vector\n");
	printf("7 Find MUM:s\n");
	printf("8 Make DOT tree\n");
	printf("9 Count distinct substrings\n");

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
	if (choice == 1)
		printf("...\n");
	else if (choice == 2 || choice == 4)
		printf("Do not give a dollar sign.\n");
	else if (choice == 3)
		printf("Give a bwt string.\n");
	else if (choice == 5)
		printf("Give a dollar sign ($) to the end of the string.\n");
}


int main(void)
{
	int choice, len = 0;
	char* input = malloc(sizeof(char));
	char* res = malloc(sizeof(char));
	int* array = calloc(20, sizeof(int)); 
	
	print_choices();
	
	printf("Write the number of the operation you want to do:\n");
	scanf("%d", &choice);
	
	printf("Give the input string. ");
	print_instructions(choice);
	scanf("%s", input);

	if (choice == 1) {
		printf("Not supported yet\n");
	} else if (choice == 2) {
		res = s_to_BWT(input);
		printf("%s\n", res);
	} else if (choice == 3) {
		res = bwt_to_s(input);
		printf("%s\n", res);
	} else if (choice == 4) {
		res = reverse_bwt(input);
		printf("%s\n", res);
	} else if (choice == 5) {
		array = create_c_array(input);
		len = strlen(get_alphabet(input));
		print_int_array(array, len);
	} else if (choice == 6) {
		printf("Not supported yet\n");
	} else if (choice == 7) {
		printf("Not supported yet\n");
	} else if (choice == 8) {
		printf("Not supported yet\n");
	} else if (choice == 9) {
		printf("Not supported yet\n");
	} else {
		printf("Invalid choice\n");
	}
	

	return 0;

}
