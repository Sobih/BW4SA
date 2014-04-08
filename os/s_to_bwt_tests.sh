#!/bin/bash

gcc -std=c99 -o src/core/s_to_bwt.o src/utils/wavelet_tree.c src/utils/bit_vector.c src/utils/utils.c src/core/s_to_bwt.c tests/core/check_s_to_bwt.c libs/DBWT/*.c -I libs/DBWT/ -I src/bwt `pkg-config --cflags --libs check` -lm

./src/core/s_to_bwt.o
