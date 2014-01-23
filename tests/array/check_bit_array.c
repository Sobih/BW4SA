/*
 * check_bit_array.c
 *
 *  Created on: 21.1.2014
 *      Author: Max Sandberg
 */

#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../../include/bit_array.h"

START_TEST (test_alphabet_mapping) {
	char* string = "banana";

	char_mapping* mapping = map_alphabet(string);

	//test the length marker
	ck_assert(mapping[0].character == 0);
	ck_assert(mapping[0].bit_value == 3);

	//test characters
	ck_assert(mapping[1].character == 'a');
	ck_assert(mapping[1].bit_value == 1);

	ck_assert(mapping[2].character == 'b');
	ck_assert(mapping[2].bit_value == 2);

	ck_assert(mapping[3].character == 'n');
	ck_assert(mapping[3].bit_value == 3);

	free(mapping);
}
END_TEST

START_TEST (test_empty_string_mapping) {
	char* string = "";

	char_mapping* mapping = map_alphabet(string);

	//test the length marker
	ck_assert(mapping[0].character == 0);
	ck_assert(mapping[0].bit_value == 0);

	free(mapping);
}
END_TEST

START_TEST (test_faulty_string_mapping) {
	char* string;

	char_mapping* mapping = map_alphabet(string);

	//assert that return value is NULL
	ck_assert(mapping == 0);

	free(mapping);
}
END_TEST

START_TEST (test_long_string_mapping) {

	char* string = "HasSDUwqaBiUSRiduwIUHGFIUAGHouLKrJVNlkaslkBVlPkvLJHYbAliwyr947hgfrLQGIflhigaASflkuBAlv7v3liuIoHAkuhflhbbvlLIUae7dslf7g9LKUAsylfIjfliga5ASflkuBAlv7v3liuIHAkuWhflhbbJvlLIFUae7dslf7g9LKUAsylflv17v3liuIHAwkuhflhbbvlLIUae7dslf7g9LKUAsylifasSDwqaiUSiduwIUHGFIUQAGHoVuLKeJVNlkasklkBgVlkvqLJHYAovliwyr9Z47hgf0rLQGIflGiQgaASflkuBAlv7v3liuIIHAkuhflhbbvlLIUae7dslf7g9LKUAsylfasDuAfSd6MwadAsgfGSAgSAgnse3c3gAdEgGDOKafHf9N7m6a9o7bfULHnofay8NogOIYbvoi8yfd9loYAB9plfp2ASydMDx87yAGFgitumUHAliugd7liuhgNAJ3DsLKudjhgliu8ylPiulOiugyliazduH9GLIAKudHGLiqXTYSdnC4";

	/*
	printf("Allocating string...\n");

	char* string = calloc(1000, sizeof(char));

	printf("Opening file...\n");

	FILE* file = fopen("../../res/long_string.txt", "r");

	if (file == 0)
		printf("File = NULL\n");

	printf("Reading string...\n");

	while(fgets(string + strlen(string) - 1, 1000, file) != NULL) {}

	fclose(file);

	printf("Mapping alphabet...\n");*/

	char_mapping* mapping = map_alphabet(string);

	//test the length marker
	ck_assert(mapping[0].character == 0);
	ck_assert(mapping[0].bit_value == 62);

	//test characters
	ck_assert(mapping[1].character == '0');
	ck_assert(mapping[1].bit_value == 1);

	ck_assert(mapping[2].character == '1');
	ck_assert(mapping[2].bit_value == 2);

	ck_assert(mapping[3].character == '2');
	ck_assert(mapping[3].bit_value == 3);

	ck_assert(mapping[4].character == '3');
	ck_assert(mapping[4].bit_value == 4);

	ck_assert(mapping[5].character == '4');
	ck_assert(mapping[5].bit_value == 5);

	ck_assert(mapping[6].character == '5');
	ck_assert(mapping[6].bit_value == 6);

	ck_assert(mapping[7].character == '6');
	ck_assert(mapping[7].bit_value == 7);

	ck_assert(mapping[8].character == '7');
	ck_assert(mapping[8].bit_value == 8);

	ck_assert(mapping[9].character == '8');
	ck_assert(mapping[9].bit_value == 9);

	ck_assert(mapping[10].character == '9');
	ck_assert(mapping[10].bit_value == 10);

	ck_assert(mapping[11].character == 'A');
	ck_assert(mapping[11].bit_value == 11);

	ck_assert(mapping[12].character == 'B');
	ck_assert(mapping[12].bit_value == 12);

	ck_assert(mapping[13].character == 'C');
	ck_assert(mapping[13].bit_value == 13);

	ck_assert(mapping[14].character == 'D');
	ck_assert(mapping[14].bit_value == 14);

	ck_assert(mapping[15].character == 'E');
	ck_assert(mapping[15].bit_value == 15);

	ck_assert(mapping[16].character == 'F');
	ck_assert(mapping[16].bit_value == 16);

	ck_assert(mapping[17].character == 'G');
	ck_assert(mapping[17].bit_value == 17);

	ck_assert(mapping[18].character == 'H');
	ck_assert(mapping[18].bit_value == 18);

	ck_assert(mapping[19].character == 'I');
	ck_assert(mapping[19].bit_value == 19);

	ck_assert(mapping[20].character == 'J');
	ck_assert(mapping[20].bit_value == 20);

	ck_assert(mapping[21].character == 'K');
	ck_assert(mapping[21].bit_value == 21);

	ck_assert(mapping[22].character == 'L');
	ck_assert(mapping[22].bit_value == 22);

	ck_assert(mapping[23].character == 'M');
	ck_assert(mapping[23].bit_value == 23);

	ck_assert(mapping[24].character == 'N');
	ck_assert(mapping[24].bit_value == 24);

	ck_assert(mapping[25].character == 'O');
	ck_assert(mapping[25].bit_value == 25);

	ck_assert(mapping[26].character == 'P');
	ck_assert(mapping[26].bit_value == 26);

	ck_assert(mapping[27].character == 'Q');
	ck_assert(mapping[27].bit_value == 27);

	ck_assert(mapping[28].character == 'R');
	ck_assert(mapping[28].bit_value == 28);

	ck_assert(mapping[29].character == 'S');
	ck_assert(mapping[29].bit_value == 29);

	ck_assert(mapping[30].character == 'T');
	ck_assert(mapping[30].bit_value == 30);

	ck_assert(mapping[31].character == 'U');
	ck_assert(mapping[31].bit_value == 31);

	ck_assert(mapping[32].character == 'V');
	ck_assert(mapping[32].bit_value == 32);

	ck_assert(mapping[33].character == 'W');
	ck_assert(mapping[33].bit_value == 33);

	ck_assert(mapping[34].character == 'X');
	ck_assert(mapping[34].bit_value == 34);

	ck_assert(mapping[35].character == 'Y');
	ck_assert(mapping[35].bit_value == 35);

	ck_assert(mapping[36].character == 'Z');
	ck_assert(mapping[36].bit_value == 36);

	ck_assert(mapping[37].character == 'a');
	ck_assert(mapping[37].bit_value == 37);

	ck_assert(mapping[38].character == 'b');
	ck_assert(mapping[38].bit_value == 38);

	ck_assert(mapping[39].character == 'c');
	ck_assert(mapping[39].bit_value == 39);

	ck_assert(mapping[40].character == 'd');
	ck_assert(mapping[40].bit_value == 40);

	ck_assert(mapping[41].character == 'e');
	ck_assert(mapping[41].bit_value == 41);

	ck_assert(mapping[42].character == 'f');
	ck_assert(mapping[42].bit_value == 42);

	ck_assert(mapping[43].character == 'g');
	ck_assert(mapping[43].bit_value == 43);

	ck_assert(mapping[44].character == 'h');
	ck_assert(mapping[44].bit_value == 44);

	ck_assert(mapping[45].character == 'i');
	ck_assert(mapping[45].bit_value == 45);

	ck_assert(mapping[46].character == 'j');
	ck_assert(mapping[46].bit_value == 46);

	ck_assert(mapping[47].character == 'k');
	ck_assert(mapping[47].bit_value == 47);

	ck_assert(mapping[48].character == 'l');
	ck_assert(mapping[48].bit_value == 48);

	ck_assert(mapping[49].character == 'm');
	ck_assert(mapping[49].bit_value == 49);

	ck_assert(mapping[50].character == 'n');
	ck_assert(mapping[50].bit_value == 50);

	ck_assert(mapping[51].character == 'o');
	ck_assert(mapping[51].bit_value == 51);

	ck_assert(mapping[52].character == 'p');
	ck_assert(mapping[52].bit_value == 52);

	ck_assert(mapping[53].character == 'q');
	ck_assert(mapping[53].bit_value == 53);

	ck_assert(mapping[54].character == 'r');
	ck_assert(mapping[54].bit_value == 54);

	ck_assert(mapping[55].character == 's');
	ck_assert(mapping[55].bit_value == 55);

	ck_assert(mapping[56].character == 't');
	ck_assert(mapping[56].bit_value == 56);

	ck_assert(mapping[57].character == 'u');
	ck_assert(mapping[57].bit_value == 57);

	ck_assert(mapping[58].character == 'v');
	ck_assert(mapping[58].bit_value == 58);

	ck_assert(mapping[59].character == 'w');
	ck_assert(mapping[59].bit_value == 59);

	ck_assert(mapping[60].character == 'x');
	ck_assert(mapping[60].bit_value == 60);

	ck_assert(mapping[61].character == 'y');
	ck_assert(mapping[61].bit_value == 61);

	ck_assert(mapping[62].character == 'z');
	ck_assert(mapping[62].bit_value == 62);

	free(mapping);
}
END_TEST

Suite* array_suite(void) {
	Suite* suite = suite_create("Array");

	TCase* tc_alphabet_mapping = tcase_create("Alphabet Mapping");
	tcase_add_test (tc_alphabet_mapping, test_alphabet_mapping);
	tcase_add_test (tc_alphabet_mapping, test_empty_string_mapping);
	tcase_add_test (tc_alphabet_mapping, test_faulty_string_mapping);
	tcase_add_test (tc_alphabet_mapping, test_long_string_mapping);
	suite_add_tcase (suite, tc_alphabet_mapping);

	return suite;
}

int main (void) {
	int number_failed;
	Suite* suite = array_suite();
	SRunner* suite_runner = srunner_create(suite);
	srunner_run_all(suite_runner, CK_NORMAL);
	number_failed = srunner_ntests_failed(suite_runner);
	srunner_free(suite_runner);

	return (number_failed == 0) ? 0 : 1;
 }
