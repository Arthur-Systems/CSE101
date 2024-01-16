/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA8
* WordFrequency.cpp
* Reads a text file and outputs a list of words and their frequencies.
***/
#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

int main(int argc, char* argv[]) {
    // Check command line for correct number of arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return(EXIT_FAILURE);
    }

    // Open files for reading and writing
    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cerr << "Unable to open file " << argv[1] << " for reading\n";
        return(EXIT_FAILURE);
    }

    std::ofstream out(argv[2]);
    if (!out.is_open()) {
        std::cerr << "Unable to open file " << argv[2] << " for writing\n";
        return(EXIT_FAILURE);
    }

    // Create a Dictionary object
    Dictionary D;
    std::string line, token;
    std::string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

    // Read each line of input file and process tokens
    while (getline(in, line)) {
        size_t begin, end, len = line.length();
        begin = line.find_first_not_of(delim, 0);

        // Process each token in the line
        while (begin < len) {
            end = line.find_first_of(delim, begin);
            token = line.substr(begin, end - begin);

            // Convert token to lowercase
            for (char& ch : token) {
                ch = std::tolower(ch);
            }

            // Update token frequency in Dictionary
            if (!token.empty()) {
                D.contains(token) ? D.setValue(token, D.getValue(token) + 1) : D.setValue(token, 1);
            }

            // Find the beginning of the next token
            begin = line.find_first_not_of(delim, end);
        }
    }

    // Write Dictionary to output file
    out << D;

    // Close files
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
