#!/bin/bash

gcc -std=c99 -o src/core/bwt_to_s.o tests/core/check_bwt_to_s.c src/core/bwt_to_s.c src/core/s_to_bwt.c libs/DBWT/*.c -I libs/DBWT src/core/c_array.c src/core/backward_search.c src/utils/utils.c src/utils/wavelet_tree.c src/utils/bit_vector.c `pkg-config --cflags --libs check` -g -lm

./src/core/bwt_to_s.o
