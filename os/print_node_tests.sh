#!/bin/bash

gcc -std=c99 -o src/utils/print_node.o src/utils/print_node.c tests/utils/check_print_node.c `pkg-config --cflags --libs check` -lm

./src/utils/print_node.o 
