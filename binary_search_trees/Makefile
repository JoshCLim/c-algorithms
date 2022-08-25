CC=gcc
FLAGS=-Wall -Werror

run : run.o Tree.o
		$(CC) -o run run.o Tree.o

run.o : run.c Tree.h
		$(CC) $(FLAGS) -c run.c

Tree.o : Tree.c Tree.h
		$(CC) $(FLAGS) -c Tree.c

clean :
		rm -f *.o run