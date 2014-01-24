#!/bin/bash

gcc -std=c99 -o src/array/bit_array.o src/array/bit_array.c tests/array/check_bit_array.c `pkg-config --cflags --libs check`

./src/array/bit_array.o