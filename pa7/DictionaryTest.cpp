/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA7
* DisctionaryTest.cpp
* Contains the test cases for the Dictionary ADT
***/

#include <iostream>
#include <cassert>
#include "Dictionary.h"

void testConstructor() {
    std::cout << "Testing Constructor...\n";
    Dictionary dict;
    assert(dict.size() == 0);
    std::cout << "Constructor test passed.\n";
}

void testInsertionAndRetrieval() {
    std::cout << "Testing Insertion and Retrieval...\n";
    Dictionary dict;
    dict.setValue("apple", 1);
    std::cout << "Inserted 'apple' with value 1.\n";
    dict.setValue("banana", 2);
    std::cout << "Inserted 'banana' with value 2.\n";
    assert(dict.getValue("apple") == 1);
    assert(dict.getValue("banana") == 2);
    assert(dict.size() == 2);
    std::cout << "Insertion and retrieval test passed.\n";
}

void testCopyConstructor() {
    std::cout << "Testing Copy Constructor...\n";
    Dictionary dict1;
    dict1.setValue("apple", 1);
    std::cout << "Created dict1 and inserted 'apple' with value 1.\n";
    Dictionary dict2 = dict1;
    std::cout << "Created dict2 as a copy of dict1.\n";
    assert(dict2.getValue("apple") == 1);
    std::cout << "Copy constructor test passed.\n";
}

void testAssignmentOperator() {
    std::cout << "Testing Assignment Operator...\n";
    Dictionary dict1;
    dict1.setValue("apple", 1);
    std::cout << "Created dict1 and inserted 'apple' with value 1.\n";
    Dictionary dict2;
    dict2 = dict1;
    std::cout << "Assigned dict1 to dict2.\n";
    assert(dict2.getValue("apple") == 1);
    std::cout << "Assignment operator test passed.\n";
}

void testRemove() {
    std::cout << "Testing Remove...\n";
    Dictionary dict;
    dict.setValue("apple", 1);
    dict.setValue("banana", 2);
    std::cout << "Inserted 'apple' and 'banana'.\n";
    dict.remove("apple");
    std::cout << "Removed 'apple'.\n";
    assert(!dict.contains("apple"));
    assert(dict.size() == 1);
    std::cout << "Remove test passed.\n";
}

void testClear() {
    std::cout << "Testing Clear...\n";
    Dictionary dict;
    dict.setValue("apple", 1);
    std::cout << "Inserted 'apple'.\n";
    dict.clear();
    std::cout << "Cleared dictionary.\n";
    assert(dict.size() == 0);
    std::cout << "Clear test passed.\n";
}

void testIterator() {
    std::cout << "Testing Iterator...\n";
    Dictionary dict;
    dict.setValue("apple", 1);
    dict.setValue("banana", 2);
    std::cout << "Inserted 'apple' and 'banana'.\n";
    dict.begin();
    std::cout << "Iterator set to begin.\n";
    assert(dict.currentKey() == "apple");
    dict.next();
    std::cout << "Moved iterator to next.\n";
    assert(dict.currentKey() == "banana");
    dict.prev();
    std::cout << "Moved iterator to prev.\n";
    assert(dict.currentKey() == "apple");
    std::cout << "Iterator test passed.\n";
}

void testToString() {
    std::cout << "Testing ToString...\n";
    Dictionary dict;
    dict.setValue("apple", 1);
    dict.setValue("banana", 2);
    std::cout << "Inserted 'apple' and 'banana'.\n";
    assert(!dict.to_string().empty());
    std::cout << "ToString test passed.\n";
}

void testPreString() {
    std::cout << "Testing PreString...\n";
    Dictionary dict;
    dict.setValue("apple", 1);
    dict.setValue("banana", 2);
    std::cout << "Inserted 'apple' and 'banana'.\n";
    assert(!dict.pre_string().empty());
    std::cout << "PreString test passed.\n";
}

int main() {
    std::cout << "Starting Dictionary tests...\n";
    testConstructor();
    testInsertionAndRetrieval();
    testCopyConstructor();
    testAssignmentOperator();
    testRemove();
    testClear();
    testIterator();
    testToString();
    testPreString();
    std::cout << "All tests passed.\n";


   return( EXIT_SUCCESS );
}