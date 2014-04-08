/**
 * @file	print_node.h
 * @brief	A collection of functions for printing substrings to stdout.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef PRINT_NODE_H_
#define PRINT_NODE_H_

struct substring;

/**
 * @brief	Prints all the information about a substring in a readable form
 * 			to stdout.
 * @param 	node 	A substring-struct to be printed.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_node(struct substring* node);

/**
 * @brief	Prints all the information of two substrings in a readable form
 * 			to stdout.
 * @param	node1	The first substring to be printed.
 * @param	node2	The second substring to be printed.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_double_node(struct substring* node1, struct substring* node2);

#endif /* PRINT_NODE_H_ */
