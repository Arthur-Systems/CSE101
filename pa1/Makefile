#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex and ListTest
# make Lex               makes Lex
# make ListTest          makes ListTest
# make clean             removes all binaries
# make checkListTest     checks ListTest for memory errors
# make checkLex          checks Lex for memory errors
# make run               runs Lex with default input and output files
#------------------------------------------------------------------------------

CFLAGS = -std=c17 -Wall -Wno-error -Wno-incompatible-library-redeclaration

all: Lex ListTest

Lex : Lex.o List.o
	gcc $(CFLAGS) -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc $(CFLAGS) -c Lex.c

ListTest: ListTest.o List.o
	gcc $(CFLAGS) -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc $(CFLAGS) -c ListTest.c

List.o : List.c List.h
	gcc $(CFLAGS) -c List.c

Testing/ListClient.o: Testing/ListClient.c List.h
	gcc $(CFLAGS) -c Testing/ListClient.c -o Testing/ListClient.o

test: Testing/ListClient.o List.o
	gcc $(CFLAGS) -o test Testing/ListClient.o List.o

clean :
	rm -f Lex ListTest Lex.o ListTest.o List.o Testing/ListClient.o test

checkListTest :
	valgrind --leak-check=full ListTest

checkLex :
	valgrind --leak-check=full Lex defaultInput.txt defaultOutput.txt

run :
	./Lex defaultInput.txt defaultOutput.txt


