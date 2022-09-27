CC=gcc
FLAGS=-Wall -Werror
TESTS=./tests/

run : run.o Tree.o BSTree.o
		$(CC) -o run run.o Tree.o BSTree.o

run.o : run.c Tree.h BSTree.h
		$(CC) $(FLAGS) -c run.c

Tree.o : Tree.c Tree.h
		$(CC) $(FLAGS) -c Tree.c

BSTree.o : BSTree.c BSTree.h
		$(CC) $(FLAGS) -c BSTree.c

clean :
		rm -f *.o run

check : test1

test1 :
		./run 0 < $(TESTS)test1.txt > $(TESTS)output.txt
		diff $(TESTS)output.txt $(TESTS)test1_out.txt