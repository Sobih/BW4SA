#!/bin/bash
gcc -std=c99 -o src/iterate/stack_test.o src/iterate/substring_stack.c tests/iterate/check_substring_stack.c `pkg-config --cflags --libs check`

./src/iterate/stack_test.o
