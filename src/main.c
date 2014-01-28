
/*
 * main.c
 *
 *  Created on: 16.1.2014
 *      Author: lvapaaka
 */

#include "distinct_substrings.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>

void print_list(char **args, int len)
{
    int i=0;
    for (;i<len;++i)
        puts(args[i]);

}



int main(void) {

	//printf("%d\n", distinct_substrings("BANANA"));

    char *args[] =
    {
        //"this", "is", "a", "test", "of", "quicksort", "with", "strings"
		 "aa",  "baa", "aba", "a",
    };

    string_quick_sort(args, 4);
    print_list(args, sizeof(args)/sizeof(*args)); 

	

	return 0;
}
