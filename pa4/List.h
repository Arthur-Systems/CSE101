/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA4
* List.h
* Contains function prototypes and type definitions for the generic List ADT.
***/
#ifndef CSE101_LIST_H
#define CSE101_LIST_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Define the NodeObj and ListObj types
typedef struct NodeObj* Node;
typedef struct ListObj* List;

// Define the structure of NodeObj
struct NodeObj {
    void* data; // Pointer to generic data
    Node next; // Pointer to the next node in the list
    Node prev; // Pointer to the previous node in the list
};

// Define the structure of ListObj
struct ListObj {
    Node front; // Pointer to the front node in the list
    Node back; // Pointer to the back node in the list
    Node cursor; // Pointer to the cursor node in the list
    int length; // Number of elements in the list
    int index; // Index of the cursor element
};

// Constructors-Destructors ---------------------------------------------------
List newList(void); // Creates and returns a new empty List.
void freeList(List* pL); // Frees all heap memory associated with *pL, and sets *pL to NULL.

// Access functions -----------------------------------------------------------
int length(List L); // Returns the number of elements in L.
int index(List L); // Returns index of cursor element if defined, -1 otherwise.
void* front(List L); // Returns front element of L. Pre: length()>0
void* back(List L); // Returns back element of L. Pre: length()>0
void* get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0

// Manipulation procedures ----------------------------------------------------
void clear(List L); // Resets L to its original empty state.
void set(List L, void* data); // Overwrites the cursor element’s data with data. Pre: length()>0, index()>=0
void moveFront(List L); // If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveBack(List L); // If L is non-empty, sets cursor under the back element, otherwise does nothing.
void movePrev(List L); // If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L); // If cursor is defined and not at back, move cursor one step toward the back of L; if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing
void prepend(List L, void* data); // Insert new element into L. If L is non-empty, insertion takes place before front element.
void append(List L, void* data); // Insert new element into L. If L is non-empty, insertion takes place after back element.
void insertBefore(List L, void* data); // Insert new element before cursor. Pre: length()>0, index()>=0
void insertAfter(List L, void* data); // Insert new element after cursor. Pre: length()>0, index()>=0
void deleteFront(List L); // Delete the front element. Pre: length()>0
void deleteBack(List L); // Delete the back element. Pre: length()>0
void delete(List L); // Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0

// Other operations -----------------------------------------------------------
Node newNode(void* data); // Creates a new Node with data.
void freeNode(Node* pN); // Frees all heap memory associated with *pN, and sets *pN to NULL.

#endif //CSE101_LIST_H
