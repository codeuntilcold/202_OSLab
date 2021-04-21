ex1.o: ex1.c ex1.h
	gcc ex1.c -c
main.o: main.c ex1.h
	gcc main.c -c
all: ex1.o main.o
	gcc ex1.o main.o -o main
main: ex1.c main.c
	gcc ex1.c main.c -o main
clean:
	rm -f *.o main