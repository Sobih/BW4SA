#ifndef SUBSTRING_STACK_H_
#define SUBSTRING_STACK_H_

struct substring;

/**
* @brief simple stack data structure for substring structs. Can hold any amount of data, array size is automatically doubled is memory gets full
* @author Topi Paavilainen
*
* @bug no known bugs
**/
typedef struct substring_stack_struct
{
	substring** array;
	int array_size;
	int array_ptr;
}substring_stack;

/**
* @brief creates empty stack with given initial size
*
* @param initial_size initial stack size
*
* @return pointer to the new empty stack structure
**/
substring_stack* create_stack(int initial_size);

/**
* @brief pushes given element to given stack struct
*
* @param stack where given substring is pushed
*
* @param substr 
**/
void push(substring_stack* stack, substring* substr);

/**
* @brief pops the topmost element from given stack and removes it from stack
*
* @param stack
*
* @return pointer to the popped substring
**/
substring* pop(substring_stack* stack);

#endif /* SUBSTRING_STACK_H_ */
