/*
 * print_node.h
 *
 *  Created on: 7.2.2014
 *      Author: lvapaaka
 */

#ifndef PRINT_NODE_H_
#define PRINT_NODE_H_

struct substring_struct;

/**
 * Prints all the information about the node in a readable form.
 *
 * @param node a substring struct to be printed
 */
void print_node(struct substring_struct* node);
void print_double_node(struct substring_struct* node1, struct substring_struct* node2);

#endif /* PRINT_NODE_H_ */
