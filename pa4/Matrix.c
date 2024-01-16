/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA4
* Matrix.c
 * Contains function implementations for the Matrix ADT.
***/
#include "Matrix.h"

double vectorDot(List P, List Q);
int equalsList(List A, List B);

// EntryObj
typedef struct EntryObj {
    int col;
    double value;
} EntryObj;

// Entry Constructor
Entry newEntry(int col, double value) {
    Entry E = malloc(sizeof(EntryObj));
    E->col = col;
    E->value = value;
    return E;
}

// Access functions for Entry type
int getEntryCol(Entry E) {
    return E->col;
}

double getEntryValue(Entry E) {
    return E->value;
}

// MatrixObj
typedef struct MatrixObj {
    int size;
    int NNZ;
    List* rows;
} MatrixObj;

// newMatrix()
Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->NNZ = 0;
    M->rows = calloc(n, sizeof(List));
    for (int i = 0; i < n; i++) {
        M->rows[i] = newList();
    }
    return M;
}

// freeMatrix()
void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        for (int i = 0; i < (*pM)->size; i++) {
            List L = (*pM)->rows[i];
            moveFront(L);
            while (index(L) >= 0) {
                Entry E = (Entry)get(L);
                free(E);
                moveNext(L);
            }
            freeList(&((*pM)->rows[i]));
        }
        free((*pM)->rows);
        free(*pM);
        *pM = NULL;
    }
}

// size()
int size(Matrix M) {
    return M->size;
}

// NNZ()
int NNZ(Matrix M) {
    return M->NNZ;
}

// equals()
int equals(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if (A->size != B->size || A->NNZ != B->NNZ) {
        return 0; // Matrices are not equal if their sizes or number of non-zero entries are different
    }

    for (int i = 0; i < A->size; i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];

        if (!equalsList(rowA, rowB)) {
            return 0; // Rows are not equal
        }
    }

    return 1; // Matrices are equal
}

int equalsList(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "List Error: calling equalsList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(A) != length(B)) {
        return 0; // Lists are not equal if their lengths are different
    }

    moveFront(A);
    moveFront(B);

    while (index(A) >= 0 && index(B) >= 0) {
        Entry entryA = (Entry)get(A);
        Entry entryB = (Entry)get(B);

        if (getEntryCol(entryA) != getEntryCol(entryB) || getEntryValue(entryA) != getEntryValue(entryB)) {
            return 0; // Entries are not equal
        }

        moveNext(A);
        moveNext(B);
    }

    return 1; // Lists are equal
}


// makeZero()
void makeZero(Matrix M) {
    for (int i = 0; i < M->size; i++) {
        List L = M->rows[i];
        moveFront(L);
        while (index(L) >= 0) {
            Entry E = (Entry)get(L);
            free(E);
            moveNext(L);
        }
        clear(L);
    }
    M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (i < 1 || i > M->size || j < 1 || j > M->size) {
        fprintf(stderr, "Matrix Error: calling changeEntry() with invalid row or column\n");
        exit(EXIT_FAILURE);
    }

    List L = M->rows[i - 1];
    moveFront(L);

    // Traverse through the list to find the correct position or the insertion point
    while (index(L) >= 0 && getEntryCol((Entry)get(L)) < j) {
        moveNext(L);
    }

    // If we found an entry with the same column index, update or delete it
    if (index(L) >= 0 && getEntryCol((Entry)get(L)) == j) {
        if (x != 0.0) {
            ((Entry)get(L))->value = x; // Update the value
        } else {
            delete(L); // This will delete the node and free the associated memory
            M->NNZ--;
        }
    } else {
        // If x is not zero, insert a new entry at the current cursor position
        if (x != 0.0) {
            if (index(L) >= 0) {
                insertBefore(L, newEntry(j, x));
            } else {
                append(L, newEntry(j, x));
            }
            M->NNZ++;
        }
    }
}




// copy()
Matrix copy(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix B = newMatrix(A->size);
    for (int i = 0; i < A->size; i++) {
        List LA = A->rows[i];
        List LB = B->rows[i];
        moveFront(LA);
        while (index(LA) >= 0) {
            Entry E = get(LA);
            append(LB, newEntry(E->col, E->value));
            moveNext(LA);
        }
    }
    B->NNZ = A->NNZ;
    return B;
}

// transpose()
Matrix transpose(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling transpose() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix T = newMatrix(M->size);
    for (int i = 0; i < M->size; i++) {
        List row = M->rows[i];
        moveFront(row);
        while (index(row) >= 0) {
            Entry E = (Entry)get(row);
            int col = getEntryCol(E);
            double val = getEntryValue(E);
            changeEntry(T, col, i + 1, val);
            moveNext(row);
        }
    }
    return T;
}


// scalarMult()
Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling scalarMult() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix B = newMatrix(A->size);
    for (int i = 0; i < A->size; i++) {
        List LA = A->rows[i];
        List LB = B->rows[i];
        moveFront(LA);
        while (index(LA) >= 0) {
            Entry E = get(LA);
            append(LB, newEntry(E->col, x * E->value));
            moveNext(LA);
        }
    }
    B->NNZ = A->NNZ;
    return B;
}
// sum()
Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size) {
        fprintf(stderr, "Matrix Error: calling sum() with matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }

    if (A == B) {
        return scalarMult(2.0, A);
    }

    Matrix C = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List LA = A->rows[i - 1];
        List LB = B->rows[i - 1];
        List LC = C->rows[i - 1];

        moveFront(LA);
        moveFront(LB);

        while (index(LA) >= 0 || index(LB) >= 0) {
            int colA = (index(LA) >= 0) ? getEntryCol(get(LA)) : -1;
            int colB = (index(LB) >= 0) ? getEntryCol(get(LB)) : -1;

            if (colA == colB) {
                if (colA != -1) {
                    double sum = getEntryValue(get(LA)) + getEntryValue(get(LB));
                    if (sum != 0.0) {
                        append(LC, newEntry(colA, sum));
                        C->NNZ++;
                    }
                    moveNext(LA);
                    moveNext(LB);
                }
            } else if ((colA < colB && colA != -1) || colB == -1) {
                append(LC, newEntry(colA, getEntryValue(get(LA))));
                C->NNZ++;
                moveNext(LA);
            } else if ((colB < colA && colB != -1) || colA == -1) {
                append(LC, newEntry(colB, getEntryValue(get(LB))));
                C->NNZ++;
                moveNext(LB);
            }
        }
    }
    return C;
}



// diff()
Matrix diff(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling diff() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size) {
        fprintf(stderr, "Matrix Error: calling diff() with matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }

    Matrix C = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List LA = A->rows[i - 1];
        List LB = B->rows[i - 1];
        List LC = C->rows[i - 1];

        moveFront(LA);
        moveFront(LB);

        while (index(LA) >= 0 || index(LB) >= 0) {
            int colA = (index(LA) >= 0) ? getEntryCol(get(LA)) : -1;
            int colB = (index(LB) >= 0) ? getEntryCol(get(LB)) : -1;

            if (colA == colB) {
                if (colA != -1) {
                    double diff = getEntryValue(get(LA)) - getEntryValue(get(LB));
                    if (diff != 0.0) {
                        append(LC, newEntry(colA, diff));
                        C->NNZ++;
                    }
                    moveNext(LA);
                    moveNext(LB);
                }
            } else if ((colA < colB && colA != -1) || colB == -1) {
                append(LC, newEntry(colA, getEntryValue(get(LA))));
                C->NNZ++;
                moveNext(LA);
            } else if ((colB < colA && colB != -1) || colA == -1) {
                append(LC, newEntry(colB, -getEntryValue(get(LB))));
                C->NNZ++;
                moveNext(LB);
            }
        }
    }
    return C;
}



// product()
Matrix product(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling product() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size) {
        fprintf(stderr, "Matrix Error: calling product() with matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }

    Matrix C = newMatrix(A->size);
    Matrix BT = transpose(B); // Transpose B to make the dot product calculation easier

    for (int i = 1; i <= A->size; i++) {
        List rowA = A->rows[i-1];
        if (length(rowA) == 0) continue; // Skip if row is empty

        for (int j = 1; j <= BT->size; j++) {
            List rowBT = BT->rows[j-1];
            if (length(rowBT) == 0) continue; // Skip if row in.txt transposed B (column in.txt B) is empty

            double dotProduct = vectorDot(rowA, rowBT);
            if (dotProduct != 0.0) {
                changeEntry(C, i, j, dotProduct);
            }
        }
    }

    freeMatrix(&BT);
    return C;
}

double vectorDot(List A, List B) {
    moveFront(A);
    moveFront(B);
    double sum = 0.0;

    while (index(A) >= 0 && index(B) >= 0) {
        Entry entryA = (Entry)get(A);
        Entry entryB = (Entry)get(B);

        if (getEntryCol(entryA) == getEntryCol(entryB)) {
            sum += getEntryValue(entryA) * getEntryValue(entryB);
            moveNext(A);
            moveNext(B);
        } else if (getEntryCol(entryA) < getEntryCol(entryB)) {
            moveNext(A);
        } else {
            moveNext(B);
        }
    }

    return sum;
}



// printMatrix()
void printMatrix(FILE* out, Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling printMatrix() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < M->size; i++) {
        List L = M->rows[i];
        if (length(L) > 0) {
            fprintf(out, "%d: ", i + 1);
            moveFront(L);
            while (index(L) >= 0) {
                Entry E = (Entry)get(L);
                fprintf(out, "(%d, %.1f) ", getEntryCol(E), getEntryValue(E));
                moveNext(L);
            }
            fprintf(out, "\n");
        }
    }
}

void freeEntry(Entry* pE) {
    if (pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}


