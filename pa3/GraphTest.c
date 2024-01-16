/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA3
* GraphTest.c
* Tests the Graph ADT for correctness.
***/
#include <stdio.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"

int main() {
    printf("Testing Graph ADT...\n");

    int order = 5;
    Graph G = newGraph(order);

    // Test addEdge function
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 1);

    // Test addArc function
    addArc(G, 1, 3);
    addArc(G, 2, 4);
    addArc(G, 3, 5);

    // Test getSize and getOrder
    assert(getSize(G) == 8);
    assert(getOrder(G) == order);

    // Test printGraph function
    printf("Graph G:\n");
    printGraph(stdout, G);
    printf("\n");

    // Test DFS
    List S = newList();
    for (int i = 1; i <= order; i++) {
        append(S, i);
    }
    DFS(G, S);

    // Test getParent, getDiscover, and getFinish
    for (int i = 1; i <= order; i++) {
        printf("Vertex %d: Parent=%d, Discover=%d, Finish=%d\n", i, getParent(G, i), getDiscover(G, i), getFinish(G, i));
        assert(getParent(G, i) != UNDEF);
        assert(getDiscover(G, i) != UNDEF);
        assert(getFinish(G, i) != UNDEF);
    }

    // Test transpose function
    Graph T = transpose(G);
    printf("Transpose of G:\n");
    printGraph(stdout, T);
    printf("\n");

    // Test copyGraph function
    Graph C = copyGraph(G);
    printf("Copy of G:\n");
    printGraph(stdout, C);
    printf("\n");

    // Free memory
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);
    freeList(&S);

    printf("All Graph ADT tests passed!\n");

    return 0;
}
