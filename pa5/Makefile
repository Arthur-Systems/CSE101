#------------------------------------------------------------------------------
#  Makefile for List ADT
#------------------------------------------------------------------------------

# Compiler
CC     = g++
# Compiler Flags
CFLAGS = -std=c++17 -Wall

# Targets
Shuffle : Shuffle.o List.o
	$(CC) $(CFLAGS) -o Shuffle Shuffle.o List.o

Shuffle.o : List.h Shuffle.cpp
	$(CC) $(CFLAGS) -c Shuffle.cpp

ListClient : ListClient.o List.o
	$(CC) $(CFLAGS) -o ListClient ListClient.o List.o

ListClient.o : List.h ListClient.cpp
	$(CC) $(CFLAGS) -c ListClient.cpp

ListTest : ListTest.o List.o
	$(CC) $(CFLAGS) -o ListTest ListTest.o List.o

ListTest.o : List.h ListTest.cpp
	$(CC) $(CFLAGS) -c ListTest.cpp

List.o : List.h List.cpp
	$(CC) $(CFLAGS) -c List.cpp

# Clean
clean :
	rm -f Shuffle Shuffle.o ListClient ListClient.o ListTest ListTest.o List.o

# Check Memory Leak
check1 : ListClient
	valgrind --leak-check=full ListClient

check2 : Shuffle
	valgrind --leak-check=full Shuffle 35

# Run Tests
run : ListClient
	./ListClient > out.txt
	diff --side-by-side out.txt expected.txt

dig : ListClient
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ListClient
