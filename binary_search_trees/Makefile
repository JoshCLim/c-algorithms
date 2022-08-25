CC=gcc
FLAGS=-Wall -Werror

test : test.o Tree.o
		$(CC) -o test test.o Tree.o

test.o : test.c Tree.h
		$(CC) $(FLAGS) -c test.c

Tree.o : Tree.c Tree.h
		$(CC) $(FLAGS) -c Tree.c

clean :
		rm -f *.o test