#!/bin/bash

gcc -std=c99 -o src/applications/substr.o src/applications/distinct_substrings.c tests/applications/check_distinct_substrings.c src/utils/utils.c src/utils/bit_vector.c `pkg-config --cflags --libs check` -g -lm

src/applications/substr.o
