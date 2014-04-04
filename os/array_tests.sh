#!/bin/bash

gcc -std=c99 -o src/utils/bit_vector.o src/utils/bit_vector.c tests/utils/check_bit_vector.c src/utils/utils.c `pkg-config --cflags --libs check` -lm

./src/utils/bit_vector.o
