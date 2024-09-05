lib/libpgn.a: lib/pgn.o
	ar rcs lib/libpgn.a lib/pgn.o

lib/pgn.o: pgn.c pgn.h bool.h
	mkdir lib
	gcc -c pgn.c -o lib/pgn.o

