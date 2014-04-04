/**
 * @file	iterate.h
 * @brief	The core of the entire library.
 *
 * This file contains all functions for iterating through strings and
 * collecting data on the strings.
 *
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator),
 * 			Paula Lehtola
 * @bug		No known bugs.
 */

#ifndef ITERATE_H_
#define ITERATE_H_

struct substring;

/**
 * @brief 	A function for iterating through right maximal substrings of a string.
 *
 * Creates a BWT of a string and iterates through substrings of it. If the substring is right
 * maximal, the callback function given as parameter will be called on the substring.
 *
 * @param 	string 		C-string to be iterated over.
 * @param 	callback 	Function pointer to a callback function that is to be called on each
 * 						right maximal substring.
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void iterate(char* string, void (*callback) (struct substring* substr));

/**
 * @brief	A function for simultaneously iterating over two strings.
 * @param	string1		The first c-string to be iterated over.
 * @param	string2		The second c-string to be iterated over.
 * @param	callback	The callback function to be called whenever matching substrings
 * 						inside both strings are found to be right maximal.
 * @see		#iterate
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void double_iterate(char* string1, char* string2, void (*callback)(struct substring* substr1, struct substring* substr2));

//an additional iterate function. Works just like normal iterate, but passes few extra parameters to the callback function
//void iterate_for_tree_drawing(char* string, void (*callback)(substring* substr, substring* prev_substr, char c));

#endif
