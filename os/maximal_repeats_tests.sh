#!/bin/bash

gcc -std=c99 -g -o src/iterate/maximal_repeats_test.o -I libs/DBWT libs/DBWT/*.c src/utils.c src/bwt/*.c src/array/bit_vector.c src/backward-search/*.c  src/iterate/*.c tests/iterate/check_maximal_repeats.c tests/utils_for_tests/utils_for_tests.c`pkg-config --cflags --libs check` -lm

./src/iterate/maximal_repeats_test.o
