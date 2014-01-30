gcc -std=c99 -o src/backward-search/backward_search.o src/backward-search/backward_search.c tests/backward-search/check_backward_search.c src/backward-search/c_array.c src/utils.c `pkg-config --cflags --libs check`

src/backward-search/backward_search.o
