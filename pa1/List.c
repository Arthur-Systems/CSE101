//
// Created by Haichuan Wei on 9/30/23.
//

#include "List.h"
#include <stdlib.h>

List newList(void){
    List L = malloc(sizeof(List));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return L;
}

void freeList(List *pL) {
    if (pL != NULL && *pL != NULL) {
        while (length(*pL) > 0) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

int length(List L) {
    if (L == NULL) {
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }
    return L->length;
}

int index(List L) {
    if (L == NULL) {
        printf("List Error: calling index() on NULL List reference\n");
        exit(1);
    }
    return L->index;
}

int front(List L) {
    if (L == NULL) {
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }
    if (length(L) <= 0) {
        printf("List Error: calling front() on an empty List\n");
        exit(1);
    }
    return L->front->data;
}

int back(List L) {
    if (L == NULL) {
        printf("List Error: calling back() on NULL List reference\n");
        exit(1);
    }
    if (length(L) <= 0) {
        printf("List Error: calling back() on an empty List\n");
        exit(1);
    }
    return L->back->data;
}

int get(List L){
    if(L == NULL){
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling get() on an empty List\n");
        exit(1);
    }
    if(index(L) < 0){
        printf("List Error: calling get() on an undefined cursor\n");
        exit(1);
    }
    return L->cursor->data;
}

bool equals(List A, List B){
    if(A == NULL || B == NULL){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(1);
    }
    if(length(A) != length(B)){
        return false;
    }
    Node N = A->front;
    Node M = B->front;
    while(N != NULL && M != NULL){
        if(N->data != M->data){
            return false;
        }
        N = N->next;
        M = M->next;
    }
    return true;
}

void clear(List L){
    if(L == NULL){
        printf("List Error: calling clear() on NULL List reference\n");
        exit(1);
    }
    while(length(L) > 0){
        deleteFront(L);
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}

void set(List L, int x){
    if(L == NULL){
        printf("List Error: calling set() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling set() on an empty List\n");
        exit(1);
    }
    if(index(L) < 0){
        printf("List Error: calling set() on an undefined cursor\n");
        exit(1);
    }
    L->cursor->data = x;
}

void moveFront(List L){
    if(L == NULL){
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(1);
    }
    if(length(L) > 0){
        L->cursor = L->front;
        L->index = 0;
    }
}

void moveBack(List L){
    if(L == NULL){
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(1);
    }
    if(length(L) > 0){
        L->cursor = L->back;
        L->index = length(L) - 1;
    }
}

void movePrev(List L){
    if(L == NULL){
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(1);
    }
    if(L->cursor != NULL && L->index != 0){
        L->cursor = L->cursor->prev;
        L->index--;
    }else if(L->cursor != NULL && L->index == 0){
        L->cursor = NULL;
        L->index = -1;
    }
}

void moveNext(List L){
    if(L == NULL){
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(1);
    }
    if(L->cursor != NULL && L->index != length(L) - 1){
        L->cursor = L->cursor->next;
        L->index++;
    }else if(L->cursor != NULL && L->index == length(L) - 1){
        L->cursor = NULL;
        L->index = -1;
    }
}
void prepend(List L, int x){
    if(L == NULL){
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }
    Node N = newNode(x);
    if(length(L) <= 0){
        L->front = N;
        L->back = N;
    }else{
        L->front->prev = N;
        N->next = L->front;
        L->front = N;
    }
    L->length++;
    if(L->cursor != NULL){
        L->index++;
    }
}

void append(List L, int x){
    if(L == NULL){
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }
    Node N = newNode(x);
    if(length(L) <= 0){
        L->front = N;
        L->back = N;
    }else{
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
    }
    L->length++;
}
void insertBefore(List L, int x){
    if(L == NULL){
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling insertBefore() on an empty List\n");
        exit(1);
    }
    if(index(L) < 0){
        printf("List Error: calling insertBefore() on an undefined cursor\n");
        exit(1);
    }
    Node N = newNode(x);
    if(L->cursor == L->front){
        L->front = N;
    }else{
        L->cursor->prev->next = N;
        N->prev = L->cursor->prev;
    }
    L->cursor->prev = N;
    N->next = L->cursor;
    L->length++;
    L->index++;
}

void insertAfter(List L, int x){
    if(L == NULL){
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling insertAfter() on an empty List\n");
        exit(1);
    }
    if(index(L) < 0){
        printf("List Error: calling insertAfter() on an undefined cursor\n");
        exit(1);
    }
    Node N = newNode(x);
    if(L->cursor == L->back){
        L->back = N;
    }else{
        L->cursor->next->prev = N;
        N->next = L->cursor->next;
    }
    L->cursor->next = N;
    N->prev = L->cursor;
    L->length++;
}

void deleteFront(List L){
    if(L == NULL){
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling deleteFront() on an empty List\n");
        exit(1);
    }
    if(L->cursor == L->front){
        L->cursor = NULL;
        L->index = -1;
    }
    Node N = L->front;
    if(length(L) > 1){
        L->front = L->front->next;
        L->front->prev = NULL;
    }else{
        L->front = NULL;
        L->back = NULL;
    }
    L->length--;
    freeNode(&N);
}

void deleteBack(List L){
    if(L == NULL){
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling deleteBack() on an empty List\n");
        exit(1);
    }
    if(L->cursor == L->back){
        L->cursor = NULL;
        L->index = -1;
    }
    Node N = L->back;
    if(length(L) > 1){
        L->back = L->back->prev;
        L->back->next = NULL;
    }else{
        L->front = NULL;
        L->back = NULL;
    }
    L->length--;
    freeNode(&N);
}

void delete(List L){
    if(L == NULL){
        printf("List Error: calling delete() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0){
        printf("List Error: calling delete() on an empty List\n");
        exit(1);
    }
    if(index(L) < 0){
        printf("List Error: calling delete() on an undefined cursor\n");
        exit(1);
    }
    if(L->cursor == L->front){
        deleteFront(L);
    }else if(L->cursor == L->back){
        deleteBack(L);
    }else{
        Node N = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        L->cursor = NULL;
        L->index = -1;
        L->length--;
        freeNode(&N);
    }
}


void printList(FILE* out, List L){
    if(L == NULL){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
    }
    Node N = L->front;
    while(N != NULL){
        fprintf(out, "%d ", N->data);
        N = N->next;
    }
}

List copyList(List L){
    if(L == NULL){
        printf("List Error: calling copyList() on NULL List reference\n");
        exit(1);
    }
    List copy = newList();
    Node N = L->front;
    while(N != NULL){
        append(copy, N->data);
        N = N->next;
    }
    return copy;
}

Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return N;
}

void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}