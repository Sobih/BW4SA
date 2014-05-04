#!/bin/bash

gcc -std=c99 -o src/utils/wavelet_tree.o src/utils/wavelet_tree.c src/utils/bit_vector.c src/utils/utils.c tests/utils/check_wavelet_tree.c `pkg-config --cflags --libs check` -g -lm

./src/utils/wavelet_tree.o
