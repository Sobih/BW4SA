/*
 * map_bwt_to_s.c
 *
 *  Created on: 27.2.2014
 *      Author: lvapaaka
 */

int* map_create_suffix_array_from_bwt(const char* bwt)
{
	int string_length = strlen(bwt);
	int* suffix_array = malloc(sizeof(int)*string_length);
	int interval = 0;

	int* c_array = create_c_array(bwt);
	char* alphabet = get_alphabet(bwt);
	int c_value = 0;

	for(int i=string_length-1; i>= 0; i--){
		suffix_array[interval] = i;
		interval = get_char_index(c_array, alphabet, bwt[interval])
				+ rank(interval, bwt[interval], bwt);

	}
	return suffix_array;
}
