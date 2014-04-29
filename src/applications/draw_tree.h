/**
 * @file	draw_tree.h
 * @brief	A function for writing a suffix tree in dot-format to a file.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef DRAW_TREE_H_
#define DRAW_TREE_H_

/**
 * @brief	Writes a suffix tree of the given string in dot format to a file.
 * @param	string		The string to be written.
 * @param	filename	The path to the file to be written to.
 * @author 	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void draw_suffix_tree(char* string, char* filename);

#endif
