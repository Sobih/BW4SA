#!/bin/bash

gcc -std=c99 -o src/iterate/print_node.o src/iterate/*.c tests/iterate/check_print_node.c `pkg-config --cflags --libs check`

./src/iterate/print_node.o 
