build/pgen: build/main.o
	gcc -o build/pgen build/main.o -LDependencies/PGN/lib -lpgn

build/main.o: main.c
	mkdir build
	gcc -c main.c -o build/main.o -IDependencies/PGN
