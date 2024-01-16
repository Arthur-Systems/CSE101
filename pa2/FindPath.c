/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA2
* FindPath.c
* Reads in a graph and a list of pairs of vertices, and runs BFS on the graph to find the shortest path between each pair of vertices.
***/
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]){
    FILE *in, *out;
    int n, u, v;
    Graph G = NULL;

    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if(in == NULL || out == NULL){
        printf("Error: Unable to open files for reading/writing\n");
        exit(1);
    }

    // Read the number of vertices
    fscanf(in, "%d", &n);
    G = newGraph(n);

    // Read edges and construct the graph
    while(fscanf(in, "%d %d", &u, &v) == 2){
        if(u == 0 && v == 0) break; // End of edge definitions
        addEdge(G, u, v);
    }

    printGraph(out, G);


    while(fscanf(in, "%d %d", &u, &v) == 2){
        if(u == 0 && v == 0) break;
        BFS(G, u);
        List L = newList();
        getPath(L, G, v);
        fprintf(out, "\nThe distance from %d to %d is ", u, v);
        if (getDist(G, v) == INF) {
            fprintf(out, "infinity\n");
            fprintf(out, "No %d-%d path exists\n", u, v);
        } else {
            fprintf(out, "%d\n", getDist(G, v));
            fprintf(out, "A shortest %d-%d path is: ", u, v);
            printList(out, L);
            fprintf(out, "\n");
        }
        freeList(&L);
    }
    // Close files
    fclose(in);
    fclose(out);

    // Free memory
    freeGraph(&G);

    return(0);
}
