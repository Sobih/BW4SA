/*
 * main.c
 *
 *      Author: lvapaaka
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/iterate.h"
#include "iterate/print_node.h"

int main(void) {
	char* test = "TCATGTGGTTTTTGTCTTTGGTTCTGTTTATATGCTGGATTACGTTTATTGGTTTGCGTATGTTGAACCAGCCTAAGCAAAGCAGTTTTATCTTTCACAAAGTCATTCACATTTATGATAAGTAATAGAACATGGGAAGTACATCTGGATATTGGGATTTGCATTTTTGTCAGGAGTCCTTCTTAAATAATTATATAAGAGTTCTTATAGTTAACACGGTAAGGAAGAAAACAGTGGATTTTACTGTTAACTGAGGGGTGTTAGATTTTTATAGTCTCAGGCCATATCTCATTATCAAAACCAAAAGCATAAGTGGGAAGTAAGTTGGTGCTTTGTATGCTTCCCTTGGTTGTGAAAATTAGCATCAGTAATGATAGGTAATACCTTTTGCCTAGATTAAGCCAATGAAGTTTCTCAATTTCTGCACCCCTGAGTTCCTTCTCTTGGGTGCAGCTTCAGTTGGTTCTGCTACCACCAAGACCTCCTCTGGCCTCTGTGGTTCTAAAATAATTCTGATTTAGTCTTTCCATTTCCCCTCAGCTGAAATATGACAGTTAATGTGTTTGAGAATGATTGATGTTCATATGTGTGGCATTTTGCCTTTGAAATGGAAATTTAAAAATCACTGAAATTCTAGTTTGATTTGCAATCTGACAGGTTTTTTTGTCTTTTCTTAGGTATGGTGTGGTGGACTTTCTTTGAGTACTGGGATGCAGGTTCCAAGTGCTGTGAGAACACTTCAGAAAAGTGAAAATGGAATGACTGGTTCAGCTAGCAGCCTGAACAATGTTGTTACTCAATAGTGTCTACTCAGAATACGTTTACCCTCCGTCTTGATTA";
	char* test2 = "abracadabra";
	char* test3 = "joulupukinpikkuapurit";
	iterate(test2, &print_node);
	printf("TIDDIDDII!");
	return 0;
}
