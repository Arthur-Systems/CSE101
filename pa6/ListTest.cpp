/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA6
* ListTest.c
* Test client for List ADT
***/
#include "List.h"
#include <iostream>
#include <cassert>

void testConstructorsAndDestructor() {
    // Default constructor
    List myList;
    assert(myList.length() == 0);

    // Copy constructor
    myList.insertBefore(1);
    List copyList(myList);
    assert(copyList.length() == 1 && copyList.front() == 1);

    // Destructor is implicitly tested when objects go out of scope
    std::cout << "Constructors and destructor test passed." << std::endl;
}

void testAccessFunctions() {
    List myList;
    myList.insertBefore(1);
    myList.insertAfter(2);

    assert(myList.length() == 2);
    assert(myList.front() == 1);
    assert(myList.back() == 2);
    assert(myList.position() == 1);

    myList.moveFront();
    assert(myList.peekNext() == 1);

    myList.moveBack();
    assert(myList.peekPrev() == 2);

    std::cout << "Access functions test passed." << std::endl;
}

void testManipulationProcedures() {
    List myList;
    myList.insertBefore(1); // List: [1]
    myList.insertAfter(2);  // List: [1, 2]

    myList.moveBack(); // Move cursor to the end of the list
    std::cout << "List before moving prev: " << myList << std::endl;
    std::cout << "Cursor position before moving prev: " << myList.position() << std::endl;

    myList.movePrev(); // First movePrev() points to 2
    int prevElement = myList.movePrev(); // Second movePrev() should point to 1
    std::cout << "Element returned by movePrev: " << prevElement << std::endl;
    assert(prevElement == 1); // Verify that movePrev returns 1

    myList.clear();
    assert(myList.length() == 0);
    std::cout << "Manipulation procedures test passed." << std::endl;
}



void testCursorMovement() {
    List myList;
    myList.insertBefore(1);
    myList.insertBefore(2);
    myList.insertBefore(3);

    myList.moveFront();
    assert(myList.position() == 0);

    myList.moveBack();
    assert(myList.position() == 3);

    std::cout << "Cursor movement test passed." << std::endl;
}

void testElementInsertionAndRemoval() {
    List myList;
    myList.insertBefore(1);
    myList.insertBefore(2);

    assert(myList.length() == 2);
    myList.eraseBefore();
    assert(myList.length() == 1 && myList.front() == 1);

    myList.insertAfter(3);
    assert(myList.back() == 3);

    myList.eraseAfter();
    assert(myList.length() == 1 && myList.back() == 1);

    std::cout << "Element insertion and removal test passed." << std::endl;
}

void testFindFunctions() {
    List myList;
    myList.insertBefore(1); // List: [1]
    myList.insertAfter(2);  // List: [1, 2]
    myList.insertAfter(1);  // List: [1, 2, 1]

    myList.moveFront(); // Move cursor to the front
    assert(myList.findNext(1) == 1); // Find next occurrence of 1

    myList.moveBack(); // Move cursor to the end
    assert(myList.findPrev(2) == 2); // Find previous occurrence of 2

    std::cout << "Find functions test passed." << std::endl;
}



void testCleanupFunction() {
    List myList;
    myList.insertBefore(1);
    myList.insertBefore(1);
    myList.insertBefore(2);
    myList.cleanup();
    assert(myList.length() == 2);

    std::cout << "Cleanup function test passed." << std::endl;
}

void testConcatFunction() {
    List list1, list2;
    list1.insertBefore(1);
    list2.insertBefore(2);
    List list3 = list1.concat(list2);
    assert(list3.length() == 2);

    std::cout << "Concat function test passed." << std::endl;
}

void testToStringAndEquals() {
    List myList;
    myList.insertBefore(1);
    myList.insertAfter(2);
    assert(myList.to_string() == "(1, 2)");

    List anotherList;
    anotherList.insertBefore(1);
    anotherList.insertAfter(2);
    assert(myList.equals(anotherList));

    std::cout << "toString and equals test passed." << std::endl;
}

void testAssignmentOperator() {
    List myList;
    myList.insertBefore(1);
    List anotherList = myList;
    assert(anotherList.length() == 1 && anotherList.front() == 1);

    std::cout << "Assignment operator test passed." << std::endl;
}

int main() {
    testConstructorsAndDestructor();
    testAccessFunctions();
    testManipulationProcedures();
    testCursorMovement();
    testElementInsertionAndRemoval();
    testFindFunctions();
    testCleanupFunction();
    testConcatFunction();
    testToStringAndEquals();
    testAssignmentOperator();

    std::cout << "All tests passed." << std::endl;
    return 0;
}
