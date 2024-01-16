/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA8
* DictionaryTest.cpp
* A test client for the Dictionary ADT
***/
#include <iostream>
#include <string>
#include <cassert>
#include "Dictionary.h"

void testConstructor() {
    Dictionary dict;
    assert(dict.size() == 0);
    std::cout << "Constructor test passed.\n";
}

void testCopyConstructor() {
    Dictionary dict;
    dict.setValue("a", 1);
    Dictionary dictCopy = dict;
    assert(dictCopy.size() == 1);
    assert(dictCopy.contains("a"));
    std::cout << "Copy constructor test passed.\n";
}

void testAssignmentOperator() {
    Dictionary dict1, dict2;
    dict1.setValue("a", 1);
    dict2 = dict1;
    assert(dict2.size() == 1);
    assert(dict2.contains("a"));
    std::cout << "Assignment operator test passed.\n";
}

void testInsertAndSearch() {
    Dictionary dict;
    dict.setValue("a", 1);
    assert(dict.contains("a"));
    assert(dict.getValue("a") == 1);
    std::cout << "Insert and search test passed.\n";
}

void testRemove() {
    Dictionary dict;
    dict.setValue("a", 1);
    dict.remove("a");
    assert(!dict.contains("a"));
    std::cout << "Remove test passed.\n";
}

void testClear() {
    Dictionary dict;
    dict.setValue("a", 1);
    dict.clear();
    assert(dict.size() == 0);
    std::cout << "Clear test passed.\n";
}

void testSize() {
    Dictionary dict;
    dict.setValue("a", 1);
    dict.setValue("b", 2);
    assert(dict.size() == 2);
    std::cout << "Size test passed.\n";
}

void testIterator() {
    Dictionary dict;
    dict.setValue("a", 1);
    dict.setValue("b", 2);
    dict.begin();
    assert(dict.currentKey() == "a");
    dict.next();
    assert(dict.currentKey() == "b");
    dict.prev();
    assert(dict.currentKey() == "a");
    std::cout << "Iterator test passed.\n";
}

void testToString() {
    Dictionary dict;
    dict.setValue("a", 1);
    assert(!dict.to_string().empty());
    std::cout << "ToString test passed.\n";
}

void testEquality() {
    Dictionary dict1, dict2;
    dict1.setValue("a", 1);
    dict2.setValue("a", 1);
    assert(dict1.equals(dict2));
    std::cout << "Equality test passed.\n";
}

int main() {
    testConstructor();
    testCopyConstructor();
    testAssignmentOperator();
    testInsertAndSearch();
    testRemove();
    testClear();
    testSize();
    testIterator();
    testToString();
    testEquality();

    std::cout << "All tests passed!\n";

    return 0;
}
