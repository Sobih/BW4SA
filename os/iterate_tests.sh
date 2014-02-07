#!/bin/bash

gcc -std=c99 -o src/iterate/iterate_test.o src/array/bit_vector.c src/iterate/iterate.c tests/iterate/check_iterate.c `pkg-config --cflags --libs check` -lm

./src/iterate/iterate_test.o
