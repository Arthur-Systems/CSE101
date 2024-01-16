/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA6
* BigInteger.cpp
* Contains the BigInteger ADT Implementation
***/

#include "BigInteger.h"
#include <sstream>
long base = 1000000000;
int power = 9;


// Helper functions ---------------------------------------------------------

void negateList(List& L) {
    L.moveFront();
    while (L.position()< L.length()) {
        L.setAfter(-L.peekNext());
        L.moveNext();
    }
}

void sumList(List& S, List A, List B, int sgn) {
    S.clear();

    A.moveBack(); // Start from the least significant digit
    B.moveBack(); // Start from the least significant digit

    long carry = 0;
    while (A.position() > 0 || B.position() > 0 || carry != 0) {
        long aDigit = (A.position() > 0) ? A.peekPrev() : 0;
        long bDigit = (B.position() > 0) ? sgn * B.peekPrev() : 0;
        long sum = aDigit + bDigit + carry;
        carry = sum / base; // Carry for the next iteration
        sum %= base; // The digit to be inserted

        // Insert the digit at the front of S
        S.moveFront();
        S.insertBefore(sum);

        // Move A and B cursors to the next more significant digit
        if (A.position() > 0) A.movePrev();
        if (B.position() > 0) B.movePrev();
    }

    // Remove leading zeros from S, but keep at least one digit
    while (S.length() > 1 && S.front() == 0) {
        S.moveFront(); // Move to the front of the list
        S.eraseAfter(); // Remove the zero at the front
    }
}







int normalizeList(List& L) {
    if (L.length() == 0) {
        return 0; // If the list is empty, represent it as zero
    }

    L.moveBack();
    long carry = 0;
    while (L.position() > 0) {
        long digit = L.peekPrev() + carry;
        if (digit < 0) {
            // Handle negative digit
            carry = -1; // Borrow from the next more significant digit
            digit += base; // Adjust the current digit to be positive
        } else {
            carry = digit / base; // Regular carry for positive digits
            digit %= base;
        }

        L.setBefore(digit); // Set the normalized digit
        L.movePrev(); // Move to the next more significant digit
    }

    // Handle remaining carry, if any
    if (carry > 0) {
        L.moveFront();
        L.insertAfter(carry); // Insert remaining carry at the front
    } else if (carry < 0) {
        // The result is negative; this shouldn't normally happen in correct usage
        return -1;
    }

    // Remove leading zeros, but keep at least one digit
    while (L.length() > 1 && L.front() == 0) {
        L.eraseAfter();
    }

    return (L.length() > 1 || L.front() != 0) ? 1 : 0; // Return 1 if non-zero, 0 otherwise
}



// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p) {
    L.moveBack();
    for (int i = 0; i < p; i++) {
        L.insertBefore(0);  // Insert zeros at the front of the list
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setAfter(L.peekNext() * m);
        L.moveNext();
    }
}

// Constructors & Destructors --------------------------------------------------------

BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}

BigInteger::BigInteger(long x) {
    if (x == 0) {
        signum = 0;
        digits.insertBefore(0); // Insert 0 for a zero value
    } else {
        signum = (x > 0) ? 1 : -1; // Set signum based on the sign of x
        x = std::abs(x); // Make x positive for the following loop

        while (x > 0) {
            long segment = x % base;
            digits.insertBefore(segment); // Insert the least significant segment
            x /= base; // Move to the next segment
        }
    }
}



BigInteger::BigInteger(std::string s) {
    if (s.empty()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }

    // Determine sign and remove sign character if present
    signum = (s[0] == '-') ? -1 : 1;
    if (s[0] == '+' || s[0] == '-') {
        s.erase(0, 1);
    }

    // If only sign is present without any digits
    if (s.empty()) {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }

    // Check if the remaining string is numeric
    for (char c : s) {
        if (!isdigit(c) ) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    // Parse the string in segments according to 'power'
    int pos = s.length() % power; // Position to start parsing segments
    if (pos > 0) { // Handle the first segment if it's shorter than 'power'
        digits.insertBefore(std::stol(s.substr(0, pos)));
    }
    for ( ; pos < static_cast<int>(s.length()); pos += power) {
        digits.insertBefore(std::stol(s.substr(pos, power)));
    }

    // Remove leading zeros (from the front of the list)
    digits.moveFront();
    while (digits.length() > 1 && digits.peekNext() == 0) {
        digits.eraseAfter();
        digits.moveFront();
    }

    // Handle the case where the entire number is 0
    if (digits.length() == 0) {
        signum = 0;
        digits.insertBefore(0);
    }
}


BigInteger::BigInteger(const BigInteger& N) : signum(N.signum), digits(N.digits) {
    this->signum = N.signum;
    this->digits = N.digits;
}


// Access functions --------------------------------------------------------

int BigInteger::sign() const {
    return signum;
}

int BigInteger::compare(const BigInteger& N) const {
    // First, compare the signum
    if (signum < N.signum) return -1;
    if (signum > N.signum) return 1;

    // For numbers with the same sign, compare their magnitudes
    if (signum != 0) {
        // Compare lengths first for a quick check
        int thisLength = digits.length();
        int NLength = N.digits.length();
        if (thisLength < NLength) return -signum;
        if (thisLength > NLength) return signum;

        // Make copies for traversal
        List thisDigitsCopy = digits;
        List NDigitsCopy = N.digits;
        thisDigitsCopy.moveBack();
        NDigitsCopy.moveBack();

        // Compare digit by digit from the most significant digit
        while (thisDigitsCopy.position() > 0 && NDigitsCopy.position() > 0) {
            int thisDigit = thisDigitsCopy.peekPrev();
            int nDigit = NDigitsCopy.peekPrev();

            if (thisDigit < nDigit) return -signum;
            if (thisDigit > nDigit) return signum;

            thisDigitsCopy.movePrev();
            NDigitsCopy.movePrev();
        }
    }
    return 0;
}


// Manipulation procedures -------------------------------------------------

void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

void BigInteger::negate() {
    signum = -signum;
}

BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger sum;

    if (this->signum == N.signum) {
        // If both numbers have the same sign, simply add them
        sumList(sum.digits, this->digits, N.digits, 1);
        sum.signum = this->signum;
    } else {
        // If the numbers have different signs, find out which is larger in magnitude
        BigInteger absThis = *this;
        BigInteger absN = N;
        absThis.signum = absN.signum = 1;  // Temporarily treat both as positive for comparison

        int cmp = absThis.compare(absN);

        if (cmp == 0) {
            // If magnitudes are equal, the result is zero
            sum.makeZero();
            return sum;
        }

        if (cmp > 0) {
            // *this has greater magnitude, perform subtraction and keep the sign of *this
            sumList(sum.digits, this->digits, N.digits, -1);
            sum.signum = this->signum;
        } else {
            // N has greater magnitude, perform subtraction and keep the sign of N
            sumList(sum.digits, N.digits, this->digits, -1);
            sum.signum = N.signum;
        }
    }

    normalizeList(sum.digits);

    // Remove leading zeros and adjust the sign if necessary
    while (sum.digits.length() > 1 && sum.digits.front() == 0) {
        sum.digits.eraseAfter();
    }
    if (sum.digits.length() == 1 && sum.digits.front() == 0) {
        sum.signum = 0;
    }

    return sum;
}



BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger result;

    // If the signs are different, perform addition
    if (this->signum != N.signum) {
        sumList(result.digits, this->digits, N.digits, 1);
        result.signum = this->signum;
    } else {
        // If both numbers have the same sign
        int cmp = this->compare(N);

        if (cmp == 0) {
            // If the numbers are equal, the result is zero
            result.makeZero();
            return result;
        }

        if ((cmp > 0 && this->signum > 0) || (cmp < 0 && this->signum < 0)) {
            // If *this is greater than N (for positive numbers) or *this is less than N (for negative numbers)
            sumList(result.digits, this->digits, N.digits, -1);
            result.signum = this->signum;
        } else {
            // If *this is less than N (for positive numbers) or *this is greater than N (for negative numbers)
            sumList(result.digits, N.digits, this->digits, -1);
            result.signum = -this->signum;
        }
    }

    normalizeList(result.digits);

    // Remove leading zeros and adjust the sign if necessary
    while (result.digits.length() > 1 && result.digits.front() == 0) {
        result.digits.eraseAfter();
    }
    if (result.digits.length() == 1 && result.digits.front() == 0) {
        result.signum = 0;
    }

    return result;
}



BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger product;
    if (signum == 0 || N.signum == 0) {
        return product;
    }
    List sum;
    List NDigitsCopy = N.digits;
    List temp;

    NDigitsCopy.moveBack();

    for (int shift = 0; NDigitsCopy.position() > 0; ++shift, NDigitsCopy.movePrev()) {
        temp = this->digits;
        scalarMultList(temp, NDigitsCopy.peekPrev());
        shiftList(temp, shift);
        List newSum = sum;
        sumList(sum, newSum, temp, 1);
        normalizeList(sum);
    }
    product.digits = sum;
    product.signum = signum * N.signum;
    return product;
}

// Other Functions ---------------------------------------------------------

std::string BigInteger::to_string() {
    if (this->signum == 0) return "0";

    std::string s = (this->signum == -1) ? "-" : "";

    // Remove leading zeros, but leave a single zero if that's all there is
    digits.moveFront();
    while (digits.front() == 0 && digits.length() > 1) {
        digits.eraseAfter();
        digits.moveFront();
    }

    // Constructing the string representation
    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        std::string d = std::to_string(digits.peekNext());
        std::string m = "";

        // Add leading zeros to segments except for the first one
        while (static_cast<int>(m.length() + d.length()) < power && digits.position() > 0) {
            m += '0';
        }
        s += m + d;
    }

    return s;
}





// Overriden Operators -----------------------------------------------------

std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    return stream << N.to_string();
}

bool operator==(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 0;
}

bool operator<(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) < 0;
}

bool operator<=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) <= 0;
}

bool operator>(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) > 0;
}

bool operator>=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) >= 0;
}

BigInteger operator+(const BigInteger& A, const BigInteger& B) {
    return A.add(B);
}

BigInteger operator+=(BigInteger& A, const BigInteger& B) {
    A = A.add(B);
    return A;
}

BigInteger operator-(const BigInteger& A, const BigInteger& B) {
    return A.sub(B);
}

BigInteger operator-=(BigInteger& A, const BigInteger& B) {
    A = A.sub(B);
    return A;
}

BigInteger operator*(const BigInteger& A, const BigInteger& B) {
    return A.mult(B);
}

BigInteger operator*=(BigInteger& A, const BigInteger& B) {
    A = A.mult(B);
    return A;
}




// The end of BigInteger.cpp
