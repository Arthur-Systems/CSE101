#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 7
#
#  make                     makes Order
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make OrderCheck          runs Order under valgrind on in5 junk5
#  make DictionaryCheck     runs DictionaryClient under valgrind
#------------------------------------------------------------------------------

MAIN           = Order
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT_TEST       = $(ADT)Test
ADT_CLIENT     = $(ADT)Client
ADT_TEST_SOURCE= $(ADT_TEST).cpp
ADT_TEST_OBJECT= $(ADT_TEST).o
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE = g++ -std=c++17 -Wall -c -g  # Compile command with debugging flag
LINK    = g++ -std=c++17 -Wall -g -o  # Link command with debugging flag
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

# Add the ADT test executable to the all target
all: $(MAIN) $(ADT_TEST)

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

# Rule for making the ADT test executable
$(ADT_TEST): $(ADT_TEST_OBJECT) $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST_OBJECT) $(ADT_OBJECT)

# Rule for making the ADT Client executable
$(ADT_CLIENT): $(ADT_CLIENT).o $(ADT_OBJECT)
	$(LINK) $(ADT_CLIENT) $(ADT_CLIENT).o $(ADT_OBJECT)

# Rule for compiling the main object
$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

# Rule for compiling the ADT test object
$(ADT_TEST_OBJECT): $(ADT_TEST_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST_SOURCE)

# Rule for compiling the ADT object
$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

# Clean rule
clean:
	$(REMOVE) $(MAIN) $(ADT_TEST) $(OBJECT) $(ADT_TEST_OBJECT) $(ADT_OBJECT)

# Check rule for the main program
$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) in5 junk5

# Check rule for the ADT test
$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)
