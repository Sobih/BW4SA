#!/bin/bash

gcc -std=c99 -o src/array/bit_array.o src/array/bit_array.c tests/array/check_bit_array.c src/utils.c `pkg-config --cflags --libs check` -lm

./src/array/bit_array.o
