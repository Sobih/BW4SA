#!/bin/bash

gcc -std=c99 -o src/core/iterate_test.o -I libs/DBWT libs/DBWT/*.c src/utils/*.c src/core/*.c tests/core/check_iterate.c tests/utils_for_tests.c `pkg-config --cflags --libs check` -lm


./src/core/iterate_test.o


