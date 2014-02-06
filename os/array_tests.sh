#!/bin/bash

gcc -std=c99 -o src/array/bit_vector.o src/array/bit_vector.c tests/array/check_bit_vector.c src/utils.c `pkg-config --cflags --libs check` -lm

./src/array/bit_vector.o
