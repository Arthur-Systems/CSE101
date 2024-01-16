#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 3
#
#  make                     makes FindComponents
#  make GraphClient         makes GraphClient
#  make GraphTest           makes GraphTest
#  make clean               removes binaries
#  make checkFind           tests FindComponents for memory leaks on in3
#  make checkClient         tests GraphClient for memory leaks
#  make checkGraphTest      tests GraphTest for memory leaks
#------------------------------------------------------------------------------

CC            = gcc
FLAGS         = -std=c17 -Wall -g
COMPILE       = $(CC) $(FLAGS) -c
LINK          = $(CC) $(FLAGS) -o
REMOVE        = rm -f
MEMCHECK      = valgrind --leak-check=full

HEADERS       = Graph.h List.h
SOURCES       = Graph.c List.c
OBJECTS       = Graph.o List.o

FindComponents: FindComponents.o $(OBJECTS)
	$(LINK) FindComponents FindComponents.o $(OBJECTS)

GraphClient: GraphClient.o $(OBJECTS)
	$(LINK) GraphClient GraphClient.o $(OBJECTS)

GraphTest: GraphTest.o $(OBJECTS)
	$(LINK) GraphTest GraphTest.o $(OBJECTS)

FindComponents.o: FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c

GraphClient.o: GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

GraphTest.o: GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

Graph.o: Graph.c Graph.h List.h
	$(COMPILE) Graph.c

List.o: List.c List.h
	$(COMPILE) List.c

clean:
	$(REMOVE) FindComponents GraphClient GraphTest FindComponents.o GraphClient.o GraphTest.o $(OBJECTS)

checkFind: FindComponents
	$(MEMCHECK) FindComponents in8 junk8

checkClient: GraphClient
	$(MEMCHECK) GraphClient

checkGraphTest: GraphTest
	$(MEMCHECK) GraphTest

.PHONY: clean checkFind checkClient checkGraphTest
