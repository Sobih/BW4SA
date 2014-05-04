#!/bin/bash
gcc -std=c99 -o src/core/stack_test.o src/core/substring_stack.c tests/core/check_substring_stack.c `pkg-config --cflags --libs check` -g -lm

./src/core/stack_test.o
