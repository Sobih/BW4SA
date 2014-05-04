#!/bin/bash

gcc -std=c99 -o src/core/backward_search.o src/core/s_to_bwt.c src/utils/bit_vector.c src/utils/wavelet_tree.c src/core/backward_search.c tests/core/check_backward_search.c src/core/c_array.c src/utils/utils.c libs/DBWT/*.c -I libs/DBWT/ -I src/bwt `pkg-config --cflags --libs check` -g -lm

src/core/backward_search.o
