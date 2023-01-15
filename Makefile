CC=gcc
FLAGS=-g -Wall -Wextra -Werror
SRC=$(wildcard s21_*.c)
OBJ=$(SRC:*.c=*.o)
LIB_NAME=s21_polish_notation

all: to_style hand_test

to_style:
	clang-format -i *.c *.h

hand_test:
	$(CC) $(FLAGS) $(SRC) hand_test.c -o a.out
	./a.out

hand_test_leak:
	$(CC) $(FLAGS) $(SRC) hand_test.c -o a.out
	leaks -atExit -- ./a.out