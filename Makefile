all:
	gcc -Wall --pedantic src/*.c -o bin/gauss

test: all
	bin/gauss dane/A dane/b
	bin/gauss dane/A2 dane/b2
	bin/gauss dane/A3 dane/b3
