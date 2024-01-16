/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA1
* ListTest.c
* Contains tests for all ADT operations of the List.
***/


#include"List.h"

int main(int argc, char *argv[]) {

    List A = newList();
    List B = newList();
    List C = NULL;
    int i;

    // Test append() and prepend()
    for (i = 1; i <= 20; i++) {
        append(A, i);
        prepend(B, i);
    }

    printf("After append and prepend:\n");
    printList(stdout, A);
    printf("\n");
    printList(stdout, B);
    printf("\n");

    // Test moveFront(), moveNext(), and get()
    printf("Printing A using moveFront and moveNext:\n");
    for (moveFront(A); index(A) >= 0; moveNext(A)) {
        printf("%d ", get(A));
    }
    printf("\n");

    // Test moveBack(), movePrev(), and get()
    printf("Printing B using moveBack and movePrev:\n");
    for (moveBack(B); index(B) >= 0; movePrev(B)) {
        printf("%d ", get(B));
    }
    printf("\n");

    // Test copyList() and equals()
    C = copyList(A);
    printf("A equals B? %s\n", equals(A, B) ? "true" : "false");
    printf("B equals C? %s\n", equals(B, C) ? "true" : "false");
    printf("C equals A? %s\n", equals(C, A) ? "true" : "false");

    // Test insertBefore() and insertAfter()
    moveFront(A);
    for (i = 0; i < 5; i++) moveNext(A); // at index 5
    insertBefore(A, -1);            // at index 6
    for (i = 0; i < 9; i++) moveNext(A); // at index 15
    insertAfter(A, -2);
    printf("After insertions:\n");
    printList(stdout, A);
    printf("\n");

    // Test delete()
    for (i = 0; i < 5; i++) movePrev(A); // at index 10
    delete(A);
    printf("After delete:\n");
    printList(stdout, A);
    printf("\n");

    // Test length() and clear()
    printf("Length of A before clear: %d\n", length(A));
    clear(A);
    printf("Length of A after clear: %d\n", length(A));

    // Test front(), back(), and set()
    prepend(A, 42);
    append(A, 43);
    printf("Front of A: %d\n", front(A));
    printf("Back of A: %d\n", back(A));
    moveFront(A);
    set(A, 44);
    printf("After set, front of A: %d\n", front(A));

    // Test movePrev() from front
    moveFront(A);
    movePrev(A);
    if (index(A) != -1) {
        printf("Error: Expected index -1 after movePrev() from front, but got %d\n", index(A));
    }

    // Test moveNext() from back
    moveBack(A);
    moveNext(A);
    if (index(A) != -1) {
        printf("Error: Expected index -1 after moveNext() from back, but got %d\n", index(A));
    }

    // Test deleteFront() and deleteBack()
    deleteFront(A);
    if (length(A) != 1 || front(A) != 43) {
        printf("Error: After deleteFront(), expected length 1 and front 43, but got length %d and front %d\n",
               length(A), front(A));
    }
    deleteBack(A);
    if (length(A) != 0) {
        printf("Error: After deleteBack(), expected length 0, but got length %d\n", length(A));
    }

    // Free all Lists
    freeList(&A);
    freeList(&B);
    freeList(&C);

    return (0);
}
