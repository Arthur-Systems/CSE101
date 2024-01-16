/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA7
* Order.cpp
* Contains the main function for pa7
***/

#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file \"" << argv[1] << "\"\n";
        return 1;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output file \"" << argv[2] << "\"\n";
        return 1;
    }

    Dictionary dict;
    std::string line;
    int lineNumber = 1;

    // Read lines from the input file and insert them into the Dictionary
    while (std::getline(inputFile, line)) {
        dict.setValue(line, lineNumber++);
    }

    // Write the first string representation (key-value pairs in alphabetical order)
    outputFile << dict.to_string(); // Assuming Dictionary::to_string() outputs in this format

    // Write the second string representation (keys in pre-order traversal)
    outputFile << dict.pre_string(); // Assuming Dictionary::pre_string() outputs keys in pre-order

    inputFile.close();
    outputFile.close();

    return 0;
}
