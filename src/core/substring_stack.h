/**
 * @file	substring_stack.h
 * @brief	A simple implementation of a stack for storing substrings.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef SUBSTRING_STACK_H_
#define SUBSTRING_STACK_H_

struct substring;

/**
 * @brief	A simple stack-structure for storing substrings.
 *
 * Can hold any amount of data, array size is automatically doubled if memory gets full.
 *
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug 	No known bugs.
 */
typedef struct substring_stack_struct
{
	struct substring* array;
	int array_size;
	int array_ptr;
} substring_stack;

/**
 * @brief 	Creates an empty stack with given initial size.
 * @param 	initial_size 	Initial stack size.
 * @return 					Pointer to the new empty stack.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
substring_stack* create_stack(int initial_size);

/**
 * @brief 	Pushes given element onto given stack.
 * @param 	stack 	The stack onto which the substring should be pushed.
 * @param 	substr	The substring to be pushed onto the stack.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void push(substring_stack* stack, struct substring* substr);

/**
 * @brief 	Pops and removes the top-most element from a stack.
 * @param 	stack	The stack from which the top-most element is to be popped.
 * @return 			A pointer to the popped substring.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
struct substring* pop(substring_stack* stack);

/**
 * @brief	Frees an entire stack structure and all data connected to it.
 * @param	stack	The stack to be freed.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void free_stack(substring_stack* stack);

#endif /* SUBSTRING_STACK_H_ */
