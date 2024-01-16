/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA4
* Sparse.c
 * Contains the main function for the program.
***/
#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main(int argc, char* argv[]){
    FILE *in, *out;
    int n, a, b, i, j, k;
    double x;
    Matrix A, B, C, D, E, F, G, H, I, J;

    // Check command line for correct number of arguments
    if(argc != 3){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open files for reading and writing
    in = fopen(argv[1], "r");
    if(in == NULL){
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    out = fopen(argv[2], "w");
    if(out == NULL){
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // Read input file
    if(fscanf(in, "%d %d %d\n", &n, &a, &b) != 3){
        fprintf(stderr, "File format error: Expected matrix size and non-zero entry counts\n");
        exit(EXIT_FAILURE);
    }
    A = newMatrix(n);
    B = newMatrix(n);

    // Read matrix A
    for(i = 0; i < a; i++){
        if(fscanf(in, "%d %d %lf\n", &j, &k, &x) != 3){
            fprintf(stderr, "File format error: Expected row, column, value for matrix A\n");
            exit(EXIT_FAILURE);
        }
        if(j < 1 || j > n || k < 1 || k > n){
            fprintf(stderr, "Matrix index out of bounds: row %d, column %d\n", j, k);
            exit(EXIT_FAILURE);
        }
        changeEntry(A, j, k, x);
    }

    // Read matrix B
    for(i = 0; i < b; i++){
        if(fscanf(in, "%d %d %lf\n", &j, &k, &x) != 3){
            fprintf(stderr, "File format error: Expected row, column, value for matrix B\n");
            exit(EXIT_FAILURE);
        }
        if(j < 1 || j > n || k < 1 || k > n){
            fprintf(stderr, "Matrix index out of bounds: row %d, column %d\n", j, k);
            exit(EXIT_FAILURE);
        }
        changeEntry(B, j, k, x);
    }

    // Perform calculations and print results
    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    D = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, D);
    fprintf(out, "\n");
    freeMatrix(&D);

    E = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, E);
    fprintf(out, "\n");
    freeMatrix(&E);

    F = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, F);
    fprintf(out, "\n");
    freeMatrix(&F);

    G = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, G);
    fprintf(out, "\n");
    freeMatrix(&G);

    H = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, H);
    fprintf(out, "\n");
    freeMatrix(&H);

    I = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, I);
    fprintf(out, "\n");
    freeMatrix(&I);

    J = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, J);
    fprintf(out, "\n");
    freeMatrix(&J);

    // Free matrices A and B
    freeMatrix(&A);
    freeMatrix(&B);

    // Close files
    fclose(in);
    fclose(out);

    return(EXIT_SUCCESS);
}
