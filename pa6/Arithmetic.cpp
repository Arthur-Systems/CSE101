/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA6
* Arithmetic.cpp
* Contains the main function for the BigInteger ADT
***/
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "BigInteger.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Check command line for correct number of arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // Open files for reading and writing
    ifstream in(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    ofstream out(argv[2]);
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // Read each line of input file
    string As, Bs;
    getline(in, As);
    in.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip the blank line
    getline(in, Bs);

    BigInteger A(As), B(Bs);
    const BigInteger s3("3"), s2("2"), s9("9"), s16("16");

    // Perform various arithmetic operations and write to output file
    out << A << "\n\n"
        << B << "\n\n"
        << A + B << "\n\n"
        << A - B << "\n\n"
        << A - A << "\n\n"
        << s3 * A - s2 * B << "\n\n"
        << A * B << "\n\n"
        << A * A << "\n\n"
        << B * B << "\n\n"
        << s9 * A * A * A * A + s16 * B * B * B * B * B << "\n";

    // Close files
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
