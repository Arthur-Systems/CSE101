/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA5
* Shuffle.cpp
* Main program that tests the shuffle function
***/
#include <iostream>
#include <iomanip>
#include "List.h"

using namespace std;

// shuffle function that performs one perfect shuffle operation
void shuffle(List& D) {
    int n = D.length();
    List L1, L2;

    // Splitting the deck into two halves
    D.moveFront();
    for (int i = 0; i < n / 2; ++i) {
        L1.insertBefore(D.peekNext());
        D.moveNext();
    }
    for (int i = n / 2; i < n; ++i) {
        L2.insertBefore(D.peekNext());
        D.moveNext();
    }

    // Merging the two halves
    D.clear();
    L1.moveFront();
    L2.moveFront();
    for (int i = 0; i < n / 2; ++i) {
        D.insertBefore(L2.peekNext());
        L2.moveNext();
        D.insertBefore(L1.peekNext());
        L1.moveNext();
    }
    if (n % 2 != 0) {
        D.insertBefore(L2.peekNext());
        L2.moveNext();
    }
}

bool areListsEqual(List L1, List L2) { // Removed 'const' and '&' to make copies
    if (L1.length() != L2.length()) {
        return false;
    }

    L1.moveFront();
    L2.moveFront();
    for (int i = 0; i < L1.length(); i++) {
        if (L1.peekNext() != L2.peekNext()) {
            return false;
        }
        L1.moveNext();
        L2.moveNext();
    }
    return true;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <max_deck_size>" << endl;
        return 1;
    }

    int max_deck_size = atoi(argv[1]);

    cout << "deck size shuffle count" << endl;
    cout << "------------------------------" << endl;

    for (int deck_size = 1; deck_size <= max_deck_size; ++deck_size) {
        List D;
        // Initialize the deck
        for (int i = 0; i < deck_size; ++i) {
            D.insertBefore(i);
        }

        int shuffle_count = 0;
        List original_deck = D;

        do {
            shuffle(D);
            shuffle_count++;
        } while (!areListsEqual(D, original_deck));

        cout << setw(8) << left << deck_size << setw(12) << right << shuffle_count << endl;
    }

    return 0;
}