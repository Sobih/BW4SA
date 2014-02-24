#!/bin/bash

gcc -std=c99 -o src/wavelet_tree/wavelet_tree.o src/wavelet_tree/wavelet_tree.c src/array/bit_vector.c src/utils.c tests/wavelet_tree/check_wavelet_tree.c `pkg-config --cflags --libs check` -lm

./src/wavelet_tree/wavelet_tree.o