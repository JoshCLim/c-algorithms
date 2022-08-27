CC=gcc
FLAGS=-Wall -Werror
TESTS=./tests/

run : run.o Tree.o log.o
		$(CC) -o run run.o Tree.o ./logs/log.o

run.o : run.c Tree.h
		$(CC) $(FLAGS) -c run.c

Tree.o : Tree.c Tree.h ./logs/log.h
		$(CC) $(FLAGS) -c Tree.c

./logs/log.o : ./logs/log.c ./logs/log.h
		$(CC) -Wall -c ./logs/log.c

clean :
		rm -f *.o run

check : test1

test1 :
		./run 0 < $(TESTS)test1.txt > $(TESTS)output.txt
		diff $(TESTS)output.txt $(TESTS)test1_out.txt