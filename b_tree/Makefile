CC=gcc
FLAGS=-Wall -Werror

run : run.o Tree2.o colour.o
		$(CC) $(FLAGS) -o run run.o Tree2.o colour.o

run.o : run.c Tree.h colour.h
		$(CC) $(FLAGS) -c run.c

tree.o : Tree.c Tree.h colour.h
		$(CC) $(FLAGS) -c Tree.c

tree2.o : Tree2.c Tree.h colour.h
		$(CC) $(FLAGS) -c Tree2.c

colour.o : colour.c colour.h
		$(CC) $(FLAGS) -c colour.c

clean:
		rm -f *.o run