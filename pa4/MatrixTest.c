/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA4
* MatrixTest.c
* Contains the testing code for the Matrix ADT.
***/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Matrix.h"

int main() {
    printf("Matrix Test\n");

    // Initialize matrices with size 10
    int matrixSize = 10; // Renamed variable to matrixSize
    Matrix A = newMatrix(matrixSize);
    Matrix B = newMatrix(matrixSize);
    assert(A != NULL && B != NULL);
    printf("Passed: Matrix creation\n");

    // Add entries to matrices A and B
    changeEntry(A, 1, 1, 1.0);
    changeEntry(A, 1, 2, 2.0);
    changeEntry(A, 2, 2, 2.0);
    changeEntry(B, 1, 1, 1.0);
    changeEntry(B, 2, 2, 2.0);
    changeEntry(B, 3, 3, 3.0);
    assert(NNZ(A) == 3 && NNZ(B) == 3);
    printf("Passed: Adding entries\n");

    // Test size function
    assert(size(A) == 10 && size(B) == 10);
    printf("Passed: Size\n");

    // Test NNZ function
    assert(NNZ(A) == 3 && NNZ(B) == 3);
    printf("Passed: Number of Non-Zero entries\n");

    // Test equals function
    assert(!equals(A, B));
    printf("Passed: Matrix equality\n");

    // Test makeZero function
    makeZero(A);
    assert(NNZ(A) == 0);
    printf("Passed: makeZero\n");

    // Test copy function
    Matrix C = copy(B);
    assert(equals(C, B));
    printf("Passed: Copy\n");

    // Test transpose function
    Matrix T = transpose(B);
    assert(T != NULL);
    printf("Passed: Transpose\n");

    // Test scalarMult function
    Matrix S = scalarMult(2.0, B);
    assert(S != NULL);
    printf("Passed: Scalar Multiplication\n");

    // Test sum function
    Matrix Sum = sum(B, B);
    assert(Sum != NULL);
    printf("Passed: Sum\n");

    // Test diff function
    Matrix Diff = diff(B, B);
    assert(Diff != NULL);
    printf("Passed: Difference\n");

    // Test product function
    Matrix Prod = product(B, B);
    assert(Prod != NULL);
    printf("Passed: Product\n");

    // Test printMatrix function
    printf("Matrix A (should be all zeros):\n");
    printMatrix(stdout, A);
    printf("Matrix B:\n");
    printMatrix(stdout, B);
    printf("Matrix C (copy of B):\n");
    printMatrix(stdout, C);
    printf("Matrix T (transpose of B):\n");
    printMatrix(stdout, T);
    printf("Matrix S (2 * B):\n");
    printMatrix(stdout, S);
    printf("Matrix Sum (B + B):\n");
    printMatrix(stdout, Sum);
    printf("Matrix Diff (B - B):\n");
    printMatrix(stdout, Diff);
    printf("Matrix Prod (B * B):\n");
    printMatrix(stdout, Prod);

    // Free matrices
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&T);
    freeMatrix(&S);
    freeMatrix(&Sum);
    freeMatrix(&Diff);
    freeMatrix(&Prod);

    printf("All Matrix tests passed!\n");

    return EXIT_SUCCESS;
}
