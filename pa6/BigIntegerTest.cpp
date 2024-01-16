/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA6
* BigIntegerTest.cpp
* Contains the main test function for the BigInteger ADT
***/
#include <iostream>
#include <string>
#include <stdexcept>
#include "BigInteger.h"

using namespace std;

int main() {

    // Test constructors
    BigInteger A("123456789123456789");
    BigInteger B("-987654321987654321");
    BigInteger C(0);
    BigInteger D("99999999999999999999999999999999999999999999999999"); // Test large number

    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl;
    cout << "D = " << D << endl;

    // Test arithmetic operations
    cout << "A + B = " << A + B << endl;
    cout << "A - B = " << A - B << endl;
    cout << "A * B = " << A * B << endl;
    cout << "D + D = " << D + D << endl; // Test large number addition

    // Test comparison operators
    cout << "A == B: " << (A == B ? "true" : "false") << endl;
    cout << "A < B: " << (A < B ? "true" : "false") << endl;
    cout << "A <= B: " << (A <= B ? "true" : "false") << endl;
    cout << "A > B: " << (A > B ? "true" : "false") << endl;
    cout << "A >= B: " << (A >= B ? "true" : "false") << endl;

    // Test additional methods (like makeZero, negate)
    A.makeZero();
    cout << "After A.makeZero(), A = " << A << endl;

    B.negate();
    cout << "After B.negate(), B = " << B << endl;

    // Test toString()
    cout << "D.toString() = " << D.to_string() << endl;

    // Test exceptions
    try {
        BigInteger invalid("-123abc456");
    } catch (const invalid_argument& e) {
        cout << "Caught exception for invalid BigInteger: " << e.what() << endl;
    }

    // Test copy constructor and assignment operator
    BigInteger E = A;
    BigInteger F;
    F = D;

    cout << "E (copy of A) = " << E << endl;
    cout << "F (assigned D) = " << F << endl;

    // More tests can be added for edge cases and special scenarios
    cout << "A + C = " << A + C << endl;
    cout << "A - C = " << A - C << endl;
    cout << "A * C = " << A * C << endl;
    cout << "A == C: " << (A == C ? "true" : "false") << endl;
    cout << "A < C: " << (A < C ? "true" : "false") << endl;
    cout << "A <= C: " << (A <= C ? "true" : "false") << endl;
    cout << "A > C: " << (A > C ? "true" : "false") << endl;
    cout << "A >= C: " << (A >= C ? "true" : "false") << endl;
    cout << "A.toString() = " << A.to_string() << endl;
    cout << "C.toString() = " << C.to_string() << endl;
    cout << "E (copy of A) = " << E << endl;
    cout << "F (assigned D) = " << F << endl;
    cout << "ALL TESTS PASSED!" << endl;
    return (EXIT_SUCCESS);
}
