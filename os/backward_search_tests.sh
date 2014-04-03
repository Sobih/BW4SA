gcc -std=c99 -o src/backward-search/backward_search.o src/bwt/s_to_bwt.c src/array/bit_vector.c src/wavelet_tree/wavelet_tree.c src/backward-search/backward_search.c tests/backward-search/check_backward_search.c src/backward-search/c_array.c src/utils.c libs/DBWT/*.c -I libs/DBWT/ -I src/bwt `pkg-config --cflags --libs check` -lm

src/backward-search/backward_search.o
