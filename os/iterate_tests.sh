#!/bin/bash

gcc -std=c99 -o src/iterate/iterate_test.o -I libs/DBWT libs/DBWT/*.c src/utils.c src/bwt/*.c src/array/bit_vector.c src/backward-search/*.c  src/iterate/*.c tests/iterate/check_iterate.c tests/utils_for_tests/utils_for_tests.c src/wavelet_tree/wavelet_tree.c  `pkg-config --cflags --libs check` -lm


./src/iterate/iterate_test.o


