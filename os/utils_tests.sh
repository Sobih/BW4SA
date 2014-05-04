#!/bin/bash

gcc -std=c99 -o src/utils/utils.o src/utils/utils.c src/utils/bit_vector.c tests/utils/check_utils.c `pkg-config --cflags --libs check` -g -lm

./src/utils/utils.o
