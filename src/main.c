/*
 * main.c
 *
 *      Author: lvapaaka
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/bwt_to_s.h"

//#include "../include/iterate.h"
//#include "iterate/print_node.h"

int main(void) {
	/*char* test = "TCATGTGGTTTTTGTCTTTGGTTCTGTTTATATGCTGGATTACGTTTATTGGTTTGCGTATGTTGAACCAGCCTAAGCAAAGCAGTTTTATCTTTCACAAAGTCATTCACATTTATGATAAGTAATAGAACATGGGAAGTACATCTGGATATTGGGATTTGCATTTTTGTCAGGAGTCCTTCTTAAATAATTATATAAGAGTTCTTATAGTTAACACGGTAAGGAAGAAAACAGTGGATTTTACTGTTAACTGAGGGGTGTTAGATTTTTATAGTCTCAGGCCATATCTCATTATCAAAACCAAAAGCATAAGTGGGAAGTAAGTTGGTGCTTTGTATGCTTCCCTTGGTTGTGAAAATTAGCATCAGTAATGATAGGTAATACCTTTTGCCTAGATTAAGCCAATGAAGTTTCTCAATTTCTGCACCCCTGAGTTCCTTCTCTTGGGTGCAGCTTCAGTTGGTTCTGCTACCACCAAGACCTCCTCTGGCCTCTGTGGTTCTAAAATAATTCTGATTTAGTCTTTCCATTTCCCCTCAGCTGAAATATGACAGTTAATGTGTTTGAGAATGATTGATGTTCATATGTGTGGCATTTTGCCTTTGAAATGGAAATTTAAAAATCACTGAAATTCTAGTTTGATTTGCAATCTGACAGGTTTTTTTGTCTTTTCTTAGGTATGGTGTGGTGGACTTTCTTTGAGTACTGGGATGCAGGTTCCAAGTGCTGTGAGAACACTTCAGAAAAGTGAAAATGGAATGACTGGTTCAGCTAGCAGCCTGAACAATGTTGTTACTCAATAGTGTCTACTCAGAATACGTTTACCCTCCGTCTTGATTA";
	char* test2 = "abracadabra";
	char* test3 = "joulupukinpikkuapurit";
	iterate(test2, &print_node);
	printf("TIDDIDDII!");*/
	printf("joku printti\n");
	char * bwt = "ARD$RCAAAABB";
	char* a = bwt_to_s(bwt);
	printf("%s\n", a);
	return 0;
}
