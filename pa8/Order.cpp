/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA8
* Order.cpp
* Reads a text file and outputs a list of words and their frequencies.
***/
#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

int main(int argc, char* argv[]) {
    // Command-line argument check
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    // Open input and output files
    std::ifstream inputFile(argv[1], std::ios::in | std::ios::binary); // Faster file reading
    if (!inputFile) {
        std::cerr << "Error: Unable to open input file \"" << argv[1] << "\"\n";
        return 1;
    }

    std::ofstream outputFile(argv[2], std::ios::out | std::ios::binary); // Faster file writing
    if (!outputFile) {
        std::cerr << "Error: Unable to open output file \"" << argv[2] << "\"\n";
        inputFile.close();
        return 1;
    }

    Dictionary dict;
    std::string line;
    int lineNumber = 1;

    // Reading and processing the file line by line
    while (std::getline(inputFile, line)) {
        // Assuming each line is unique and dictionary handles large data efficiently
        dict.setValue(line, lineNumber++);
    }

    // Efficiently writing to the file
    outputFile << dict.to_string(); // In-order traversal
    outputFile << dict.pre_string(); // Pre-order traversal

    // Closing files
    inputFile.close();
    outputFile.close();

    return 0;
}
