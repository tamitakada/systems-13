all: main.o data.o
	gcc -o main main.o data.o
main.o: main.c data.c data.h
	gcc -c main.c
data.o: data.c
	gcc -c data.c
run: main
	./main