/**
 * @file	print_node.h
 * @brief	A collection of functions for printing substrings to stdout.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef PRINT_NODE_H_
#define PRINT_NODE_H_

struct substring;
struct iterator_state;

/**
 * @brief	Prints all the information about a substring in a readable form
 * 			to stdout.
 * @param 	state 		Internal state of the iterator where the current node is pulled from
 * @param 	results		Not used, just there to conform to callback
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_node(struct iterator_state* state, void* results);

#endif /* PRINT_NODE_H_ */
