/**
 * @file	substring_stack.c
 * @brief	Implementation of the substring stack.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "../../include/structs.h"
#include "substring_stack.h"
#include <stdlib.h>
#include <stdio.h>

substring_stack* create_stack(int initial_size)
{
	if(initial_size <= 0) initial_size = 10;
	
	substring_stack* stack = malloc(sizeof(substring_stack));
	stack->array = malloc(sizeof(substring) * initial_size);
	stack->array_size = initial_size;
	stack->array_ptr = 0;	
	return stack;
}

/**
 * @brief 	A function that doubles the size of given stack.
 * @param	stack	The stack whose size is to be doubled.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void double_size(substring_stack* stack)
{
	stack->array_size *= 2;
	stack->array = realloc(stack->array, sizeof(substring) * stack->array_size);
}

void push(substring_stack* stack, substring* substr)
{
	if(stack->array_size == stack->array_ptr)
		double_size(stack);

	substring* current = &stack->array[stack->array_ptr];
	current->length = substr->length;
	current->normal = substr->normal;
	current->reverse = substr->reverse;
	stack->array_ptr++;
}

substring* pop(substring_stack* stack)
{
	if(stack->array_ptr == 0) return NULL;
	
	substring* substr = &stack->array[stack->array_ptr - 1];
	stack->array_ptr--;
	return substr;
}

inline void free_stack(substring_stack* stack) {
	free(stack->array);
	free(stack);
}



