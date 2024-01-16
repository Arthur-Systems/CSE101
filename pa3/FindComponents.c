/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA3
* FindComponents.c
* Finds the strongly connected components of a graph.
***/
#include "Graph.h"
#include "List.h"

int main(int argc, char *argv[]) {
    // Validate command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open input and output files
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    if (in == NULL || out == NULL) {
        fprintf(stderr, "Error: Unable to open files %s and/or %s\n", argv[1], argv[2]);
        exit(EXIT_FAILURE);
    }

    // Read the number of vertices
    int order;
    if (fscanf(in, "%d", &order) != 1) {
        fprintf(stderr, "Error: Invalid input format for the number of vertices\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the graph
    Graph G = newGraph(order);

    // Read and add edges to the graph
    int u, v;
    while (fscanf(in, "%d %d", &u, &v) == 2 && u != 0 && v != 0) {
        if (u < 1 || u > order || v < 1 || v > order) {
            fprintf(stderr, "Error: Invalid vertex number (%d, %d)\n", u, v);
            exit(EXIT_FAILURE);
        }
        addArc(G, u, v);
    }

    // Print the adjacency list representation of the graph
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    // Perform DFS on G and its transpose
    List S = newList();
    for (int i = 1; i <= order; i++) {
        append(S, i);
    }
    DFS(G, S);
    Graph T = transpose(G);
    DFS(T, S);

// Find and print the strongly connected components
    int numSCC = 0;
    List stack = newList();
    List *components = calloc(order, sizeof(List));
    if (components == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    moveFront(S);
    while (index(S) >= 0) {
        int u = get(S);
        if (getParent(T, u) == NIL) {
            List component = newList();
            components[numSCC] = component;
            numSCC++;
        }
        append(components[numSCC - 1], u);  // Append to the current component
        moveNext(S);
    }

    fprintf(out, "G contains %d strongly connected components:\n", numSCC);
    for (int i = numSCC - 1; i >= 0; i--) {
        fprintf(out, "Component %d: ", numSCC - i);
        printList(out, components[i]);
        fprintf(out, "\n");
    }

// Free memory and close files
    freeList(&S);
    freeList(&stack);
    for (int i = 0; i < numSCC; i++) {
        freeList(&components[i]);
    }
    free(components);
    freeGraph(&G);
    freeGraph(&T);
    fclose(in);
    fclose(out);

    return 0;
}