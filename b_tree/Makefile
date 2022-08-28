CC=gcc
FLAGS=-Wall -Werror

run : run.o Tree.o colour.o
		$(CC) $(FLAGS) -o run run.o Tree.o colour.o

run.o : run.c Tree.h colour.h
		$(CC) $(FLAGS) -c run.c

tree.o : Tree.c Tree.h colour.h
		$(CC) $(FLAGS) -c Tree.c

colour.o : colour.c colour.h
		$(CC) $(FLAGS) -c colour.c

clean:
		rm -f *.o run