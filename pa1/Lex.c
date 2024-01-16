/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA1
* Lex.c
* Reads lines from an input file, sorts them lexicographically using the List ADT, and writes the sorted lines to an output file.
***/
#include "List.h"
#include <string.h>


#define MAX_LEN 160

char *strdup(const char *s);

int main(int argc, char *argv[]) {
    FILE *in, *out;
    char line[MAX_LEN];
    int n = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // Count the number of lines in the input file
    while (fgets(line, MAX_LEN, in) != NULL) {
        n++;
    }

    char **stringArray = malloc(n * sizeof(char *));
    if (stringArray == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    rewind(in);

    for (int i = 0; i < n; i++) {
        fgets(line, MAX_LEN, in);
        stringArray[i] = strdup(line);  // Duplicate the line and store in the array
        if (stringArray[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }

    List L = newList();
    for (int i = 0; i < n; i++) {
        append(L, i);
    }
    clear(L);

    for (int i = 0; i < n; i++) {
        char *temp = stringArray[i];
        moveFront(L);
        while (index(L) >= 0 && strcmp(temp, stringArray[get(L)]) > 0) {
            moveNext(L);
        }
        if (index(L) == -1) {
            append(L, i);
        } else {
            insertBefore(L, i);
        }
    }

    // Write the sorted lines to the output file
    moveFront(L);
    while (index(L) >= 0) {
        fprintf(out, "%s", stringArray[get(L)]);
        moveNext(L);
    }

    // Free the allocated memory and close the files
    for (int i = 0; i < n; i++) {
        free(stringArray[i]);
    }
    free(stringArray);
    freeList(&L);
    fclose(in);
    fclose(out);

    return 0;
}
