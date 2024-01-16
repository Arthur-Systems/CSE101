/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA2
* Graph.c
* Implements a Graph ADT with operations to manipulate the graph.
***/

#include "List.h"
#include "Graph.h"

typedef struct GraphObj {
    List *adjacencyList;
    int *color;           // An array for the color (white, gray, black) of each vertex
    int *parent;          // An array for the parent of each vertex
    int *distance;        // An array for the distance from the most recent source to each vertex
    int order;            // Number of vertices
    int size;             // Number of edges
    int source;           // Label of the vertex most recently used as source for BFS
} GraphObj;

// Constructors-Destructors
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    G->adjacencyList = malloc((n + 1) * sizeof(List));
    G->color = malloc((n + 1) * sizeof(int));
    G->parent = malloc((n + 1) * sizeof(int));
    G->distance = malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        G->adjacencyList[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    return G;
}

void freeGraph(Graph *pG) {
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i <= (*pG)->order; i++) {
            freeList(&((*pG)->adjacencyList[i]));
        }
        free((*pG)->adjacencyList);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}

// Access functions
int getOrder(Graph G) {
    return G->order;
}

int getSize(Graph G) {
    return G->size;
}

int getSource(Graph G) {
    return G->source;
}

int getParent(Graph G, int u) {
    return G->parent[u];
}

int getDist(Graph G, int u) {
    return G->distance[u];
}

void getPath(List L, Graph G, int u) {
    if (getSource(G) == NIL) {
        printf("Graph Error: calling getPath() before BFS()\n");
        exit(1);
    }
    if (u < 1 || u > G->order) {
        printf("Graph Error: calling getPath() with out of bounds vertex\n");
        exit(1);
    }
    if (u == G->source) {
        append(L, G->source);
    } else if (G->parent[u] == NIL) {
        append(L, NIL);
    } else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}

// Manipulation procedures
void makeNull(Graph G) {
    for (int i = 1; i <= G->order; i++) {
        clear(G->adjacencyList[i]);
    }
    G->size = 0;
}

void addEdge(Graph G, int u, int v) {
    if (u < 1 || u > G->order || v < 1 || v > G->order) {
        printf("Graph Error: calling addEdge() with out of bounds vertices\n");
        exit(1);
    }
    // Insert v into adjacency list of u in sorted order
    List adjU = G->adjacencyList[u];
    moveFront(adjU);
    while (index(adjU) != -1 && get(adjU) < v) {
        moveNext(adjU);
    }
    if (index(adjU) == -1) {
        append(adjU, v);
    } else {
        insertBefore(adjU, v);
    }

    // Insert u into adjacency list of v in sorted order
    List adjV = G->adjacencyList[v];
    moveFront(adjV);
    while (index(adjV) != -1 && get(adjV) < u) {
        moveNext(adjV);
    }
    if (index(adjV) == -1) {
        append(adjV, u);
    } else {
        insertBefore(adjV, u);
    }

    G->size++;
}


void addArc(Graph G, int u, int v) {
    if (u < 1 || u > G->order || v < 1 || v > G->order) {
        printf("Graph Error: calling addArc() with out of bounds vertices\n");
        exit(1);
    }
    append(G->adjacencyList[u], v);
    G->size++;
}

void BFS(Graph G, int s) {
    if (s < 1 || s > G->order) {
        printf("Graph Error: calling BFS() with out of bounds source\n");
        exit(1);
    }
    for (int i = 1; i <= G->order; i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->source = s;
    G->color[s] = GRAY;
    G->parent[s] = NIL;
    G->distance[s] = 0;
    List Q = newList();
    append(Q, s);
    while (length(Q) > 0) {
        int u = front(Q);
        deleteFront(Q);
        List neighbors = G->adjacencyList[u];
        for (moveFront(neighbors); index(neighbors) >= 0; moveNext(neighbors)) {
            int v = get(neighbors);
            if (G->color[v] == WHITE) {
                G->color[v] = GRAY;
                G->parent[v] = u;
                G->distance[v] = G->distance[u] + 1;
                append(Q, v);
            }
        }
        G->color[u] = BLACK;
    }
    freeList(&Q);
}

// Other operations
void printGraph(FILE *out, Graph G) {
    for (int i = 1; i <= G->order; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adjacencyList[i]);
        fprintf(out, "\n");
    }
}
