#!/bin/bash

gcc -std=c99 -o src/bwt/s_to_bwt.o src/wavelet_tree/wavelet_tree.c src/array/bit_vector.c src/utils.c src/bwt/s_to_bwt.c tests/bwt/check_s_to_bwt.c libs/DBWT/*.c -I libs/DBWT/ -I src/bwt `pkg-config --cflags --libs check` -lm

./src/bwt/s_to_bwt.o
