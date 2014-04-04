#!/bin/bash

gcc -std=c99 -o src/core/mum_test.o -I libs/DBWT libs/DBWT/*.c src/utils/*.c src/core/*.c tests/core/check_mum.c `pkg-config --cflags --libs check` -lm

./src/core/mum_test.o
