CC=gcc
FLAGS=-Wall -Werror
TESTS=./tests/
LEAK_CHECK=leaks --atExit --

run : run.o Tree.o log.o check.o colour.o
		$(CC) -o run run.o Tree.o log.o check.o colour.o

run.o : run.c Tree.h
		$(CC) $(FLAGS) -c run.c

Tree.o : Tree.c Tree.h ./logs/log.h
		$(CC) $(FLAGS) -c Tree.c

./logs/log.o : ./logs/log.c ./logs/log.h
		$(CC) $(FLAGS) -c ./logs/log.c

check.o : check.c check.h
		$(CC) $(FLAGS) -c check.c

colour.o : colour.c colour.h
		$(CC) $(FLAGS) -c colour.c

clean :
		rm -f *.o run

test1 :
		./run 0 < $(TESTS)test1.txt > $(TESTS)test1_out.txt
		diff $(TESTS)test1_out.txt $(TESTS)test1_exp.txt

test2 :
		./run 0 < $(TESTS)test2.txt

test : test1 test2

leaks : 
		$(LEAK_CHECK) ./run 1