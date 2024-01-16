/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA2
* GraphTest.c
* Tests the Graph ADT for correctness.
***/
#include<assert.h>
#include"Graph.h"
#include"List.h"

void testGraphFunctions(Graph G) {
    printf("Testing Graph functions...\n");

    // Test getOrder and getSize
    printf("Order of G: %d\n", getOrder(G));
    printf("Size of G: %d\n", getSize(G));

    // Test getSource (should be NIL initially)
    assert(getSource(G) == NIL);
    printf("Source of G: %d\n", getSource(G));

    // Test getParent (should be NIL for all vertices initially)
    for (int i = 1; i <= getOrder(G); i++) {
        assert(getParent(G, i) == NIL);
    }

    // Test getDist (should be INF for all vertices initially)
    for (int i = 1; i <= getOrder(G); i++) {
        assert(getDist(G, i) == INF);
    }

    // Test BFS
    BFS(G, 1);
    printf("After BFS from vertex 1:\n");
    for (int i = 1; i <= getOrder(G); i++) {
        printf("Distance from 1 to %d: %d\n", i, getDist(G, i));
    }

    // Test getPath
    List L = newList();
    for (int i = 1; i <= getOrder(G); i++) {
        clear(L);
        getPath(L, G, i);
        printf("Shortest path from 1 to %d: ", i);
        printList(stdout, L);
        printf("\n");
    }
    freeList(&L);

    printf("Graph functions tested successfully!\n");
}

int main(int argc, char* argv[]){
    int i, s, max, min, d, n=35;
    List  C = newList(); // central vertices
    List  P = newList(); // peripheral vertices
    List  E = newList(); // eccentricities
    Graph G = NULL;

    // Build graph G
    G = newGraph(n);
    for(i=1; i<n; i++){
        if( i%7!=0 ) addEdge(G, i, i+1);
        if( i<=28  ) addEdge(G, i, i+7);
    }
    addEdge(G, 9, 31);
    addEdge(G, 17, 13);
    addEdge(G, 14, 33);

    // Print adjacency list representation of G
    printGraph(stdout, G);

    // Test Graph functions
    testGraphFunctions(G);

    // Calculate the eccentricity of each vertex
    for(s=1; s<=n; s++){
        BFS(G, s);
        max = getDist(G, 1);
        for(i=2; i<=n; i++){
            d = getDist(G, i);
            max = ( max<d ? d : max );
        }
        append(E, max);
    }

    // Determine the Radius and Diameter of G, as well as the Central and
    // Peripheral vertices.
    append(C, 1);
    append(P, 1);
    min = max = front(E);
    moveFront(E);
    moveNext(E);
    for(i=2; i<=n; i++){
        d = get(E);
        if( d==min ){
            append(C, i);
        }else if( d<min ){
            min = d;
            clear(C);
            append(C, i);
        }
        if( d==max ){
            append(P, i);
        }else if( d>max ){
            max = d;
            clear(P);
            append(P, i);
        }
        moveNext(E);
    }

    // Print results
    printf("\n");
    printf("Radius = %d\n", min);
    printf("Central vert%s: ", length(C)==1?"ex":"ices");
    printList(stdout, C);
    printf("\n");
    printf("Diameter = %d\n", max);
    printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
    printList(stdout, P);
    printf("\n");

    // Free objects
    freeList(&C);
    freeList(&P);
    freeList(&E);
    freeGraph(&G);

    return(0);
}
