/*
 * backward_search.c
 *
 *  Created on: 30.1.2014
 *      Author: lvapaaka
 */

/**
 * @brief Counts the number of occurrences of the given character in the given string before the given index.
 *
 * @param index search for c from 0 to (index -1)
 * @param c character to be counted
 * @param string the string searched
 * @author Lassi Vapaakallio, Neo Lehtola
 * @return how many occurrences of the character c
 */
int rank(const int index, const char c, const char* string){
	int i, count = 0;
	if(index <= 0){
		return 0;
	}

	for(i = index - 1; i >= 0; i--){
		if(string[i] == c){
			count++;
		}
	}
	return count;
}
