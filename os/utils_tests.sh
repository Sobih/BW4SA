#!/bin/bash

gcc -std=c99 -o src/utils.o src/utils.c src/array/bit_vector.c tests/check_utils.c `pkg-config --cflags --libs check`

./src/utils.o
