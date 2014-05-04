#!/bin/bash

gcc -std=c99 -o src/core/c_array.o src/core/c_array.c tests/core/check_c_array.c src/utils/utils.c src/utils/bit_vector.c src/utils/wavelet_tree.c `pkg-config --cflags --libs check` -g -lm

src/core/c_array.o
