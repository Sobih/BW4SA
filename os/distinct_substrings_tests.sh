gcc -std=c99 -o src/distinct_substrings/substr.o src/distinct_substrings/distinct_substrings.c tests/distinct_substrings/check_distinct_substrings.c src/utils.c `pkg-config --cflags --libs check`

src/distinct_substrings/substr.o
