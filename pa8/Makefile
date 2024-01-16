#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryClient    makes DictionaryClient
#  make Order                makes Order
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg
#  make DictionaryCheck     runs DictionaryClient under valgrind
#  make OrderCheck           runs Order under valgrind (modify as needed)
#------------------------------------------------------------------------------

MAIN           = WordFrequency
ADT            = Dictionary
ORDER          = Order
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
SOURCE2        = $(ORDER).cpp
OBJECT2        = $(ORDER).o
ADT_TEST       = $(ADT)Test
ADT_CLIENT     = $(ADT)Client
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c -g
LINK           = g++ -std=c++17 -Wall -g -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

all: $(MAIN) $(ADT_TEST) $(ORDER)

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(ORDER): $(OBJECT2) $(ADT_OBJECT)
	$(LINK) $(ORDER) $(OBJECT2) $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

$(OBJECT2): $(SOURCE2)
	$(COMPILE) $(SOURCE2)

clean:
	$(REMOVE) $(MAIN) $(ADT_TEST) $(ORDER) $(OBJECT) $(ADT_TEST).o $(ADT_OBJECT) $(OBJECT2)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) Gutenberg myGutenberg-out

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)

$(ORDER)Check: $(ORDER)
	$(MEMCHECK) $(ORDER)

runWordFrequency: $(MAIN)
	./$(MAIN) input_file.txt

runDictionaryClient: $(ADT_TEST)
	./$(ADT_TEST)

runOrder: $(ORDER)
	./$(ORDER)

.PHONY: all clean $(MAIN)Check $(ADT)Check $(ORDER)Check runWordFrequency runDictionaryClient runOrder
