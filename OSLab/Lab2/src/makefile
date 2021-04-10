findsubstr.o: findsubstr.c findsubstr.h
	gcc -c findsubstr.c

readline.o: readline.c readline.h
	gcc -c readline.c

main.o: main.c findsubstr.h readline.h
	gcc -c main.c

mygrep: main.c findsubstr.c readline.c
	gcc main.c findsubstr.c readline.c -o mygrep

all: main.o findsubstr.o readline.o
	gcc main.o findsubstr.o readline.o -o mygrep

clean:
	@echo "Cleaning..."
	rm -f *.o mygrep
