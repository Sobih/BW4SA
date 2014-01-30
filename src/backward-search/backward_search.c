/*
 * backward_search.c
 *
 *  Created on: 30.1.2014
 *      Author: lvapaaka
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
