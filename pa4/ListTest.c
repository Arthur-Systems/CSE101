/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA4
* ListTest.c
* Contains the testing code for the List ADT.
***/
#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main() {
    List A = newList();
    List B = newList();
    int i;

    // Populate Lists A and B with values 1-20
    for(i = 1; i <= 20; i++) {
        append(A, (void*)(long)i);
        prepend(B, (void*)(long)i);
    }

    // Print List A
    printf("List A: ");
    for(moveFront(A); index(A) >= 0; moveNext(A)) {
        printf("%ld ", (long)get(A));
    }
    printf("\n");

    // Print List B
    printf("List B: ");
    for(moveFront(B); index(B) >= 0; moveNext(B)) {
        printf("%ld ", (long)get(B));
    }
    printf("\n");

// Check length and index of Lists A and B
    printf("Length of A: %d\n", length(A));
    printf("Length of B: %d\n", length(B));
    printf("Index of A: %d\n", index(A));
    printf("Index of B: %d\n", index(B));

// Move cursor to a valid position in List A
    moveFront(A);
    printf("Cursor in A set to: %ld\n", (long)get(A));

// Test set function on List A
    set(A, (void*)100);
    printf("List A after set(): ");
    for(moveFront(A); index(A) >= 0; moveNext(A)) {
        printf("%ld ", (long)get(A));
    }
    printf("\n");

    // Test clear function on List A
    clear(A);
    printf("List A after clear(): %d\n", length(A));

    // Repopulate List A with values 1-10
    for(i = 1; i <= 10; i++) {
        append(A, (void*)(long)i);
    }

    // Test cursor movement functions
    moveFront(A);
    printf("List A after moveFront(): %ld\n", (long)get(A));
    moveBack(A);
    printf("List A after moveBack(): %ld\n", (long)get(A));
    movePrev(A);
    printf("List A after movePrev(): %ld\n", (long)get(A));
    moveNext(A);
    printf("List A after moveNext(): %ld\n", (long)get(A));

    // Test prepend function on List A
    prepend(A, (void*)15);
    printf("List A after prepend(): ");
    for(moveFront(A); index(A) >= 0; moveNext(A)) {
        printf("%ld ", (long)get(A));
    }
    printf("\n");

    // Test append function on List A
    append(A, (void*)25);
    printf("List A after append(): ");
    for(moveFront(A); index(A) >= 0; moveNext(A)) {
        printf("%ld ", (long)get(A));
    }
    printf("\n");
// Move cursor to a valid position in List A
    moveFront(A);
    printf("Cursor in A set to: %ld\n", (long)get(A));

// Test insertBefore function on List A
    insertBefore(A, (void*)5);
    printf("List A after insertBefore(): ");
    for(moveFront(A); index(A) >= 0; moveNext(A)) {
        printf("%ld ", (long)get(A));
    }
    printf("\n");

    moveFront(A);
    printf("Cursor in A reset to: %ld\n", (long)get(A));


    if (index(A) >= 0) {
        insertAfter(A, (void*)10);
        printf("List A after insertAfter(): ");
        for(moveFront(A); index(A) >= 0; moveNext(A)) {
            printf("%ld ", (long)get(A));
        }
        printf("\n");
    } else {
        printf("Cursor is undefined, cannot call insertAfter.\n");
    }

    deleteFront(A);
    printf("List A after deleteFront(): ");
    for(moveFront(A); index(A) >= 0; moveNext(A)) {
        printf("%ld ", (long)get(A));
    }
    printf("\n");

    // Test deleteBack function on List A
    deleteBack(A);
    printf("List A after deleteBack(): ");
    for(moveFront(A); index(A) >= 0; moveNext(A)) {
        printf("%ld ", (long)get(A));
    }
    printf("\n");

    // Test delete function on List A
    moveFront(A);
    delete(A);
    printf("List A after delete(): ");
    for(moveFront(A); index(A) >= 0; moveNext(A)) {
        printf("%ld ", (long)get(A));
    }
    printf("\n");

    // Free Lists A and B
    freeList(&A);
    freeList(&B);
    printf("List A after freeList(): %p\n", (void*)A);
    printf("List B after freeList(): %p\n", (void*)B);

    printf("All List tests passed!\n");

    return EXIT_SUCCESS;
}
