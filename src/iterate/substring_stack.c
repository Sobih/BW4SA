#include "../../include/iterate.h"
#include "substring_stack.h"
#include <stdlib.h>
#include <stdio.h>

substring_stack* create_stack(int initial_size)
{
	if(initial_size <= 0) initial_size = 10;
	
	substring_stack* stack = malloc(sizeof(substring_stack));
	stack->array = malloc(sizeof(substring_stack*)*initial_size);
	stack->array_size = initial_size;
	stack->array_ptr = 0;	
	return stack;
}

void double_size(substring_stack* stack);

void push(substring_stack* stack, substring* substr)
{
	printf("stack size %d \n",stack->array_ptr);
	if(stack->array_size == stack->array_ptr){
		double_size(stack);
	}
	stack->array[stack->array_ptr] = substr;
	stack->array_ptr++;
}

substring* pop(substring_stack* stack)
{
	printf("stack size %d\n", stack->array_ptr);
	if(stack->array_ptr == 0) return NULL;
	
	substring* substr = stack->array[stack->array_ptr-1];
	stack->array_ptr--;
	return substr;
}

/**
* @brief function that doubles the size of given stack's array and copies the values to the new array. After copying the old array's memory is freed
**/
void double_size(substring_stack* stack)
{
	printf("doubled!!!!\n");
	int old_size = stack->array_size;
	substring** old_array = stack->array;
	substring** new_array = malloc(sizeof(substring*)*old_size*2);
	
	int i;	
	for(i=0; i<old_size; i++){
		new_array[i] = old_array[i];
	}
	stack->array = new_array;
	stack->array_size = old_size*2;
	
	free(old_array);
}



