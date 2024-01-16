/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA3
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
    int *discover;        // An array for the discover time of each vertex
    int *finish;          // An array for the finish time of each vertex
    int order;            // Number of vertices
    int size;             // Number of edges
    int source;           // Label of the vertex most recently used as source for BFS
} GraphObj;

// Constructors-Destructors
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->adjacencyList = calloc(n + 1, sizeof(List*));
    G->color = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
    G->distance = calloc(n + 1, sizeof(int));
    G->discover = calloc(n + 1, sizeof(int));
    G->finish = calloc(n + 1, sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;

    for (int i = 1; i <= n; i++) {
        G->adjacencyList[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }

    return G;
}

void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i <= (*pG)->order; i++) {
            freeList(&((*pG)->adjacencyList[i]));
        }
        free((*pG)->adjacencyList);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free((*pG)->discover);
        free((*pG)->finish);
        free(*pG);
        *pG = NULL;
    }
}

// Access functions
int getOrder(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getSource(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
}

int getParent(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getParent() with vertex u out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

int getDiscover(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getDiscover() with vertex u out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

int getFinish(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getFinish() with vertex u out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
}

// Manipulation procedures
void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addEdge() with vertices u or v out of bounds\n");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}

void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addArc() with vertices u or v out of bounds\n");
        exit(EXIT_FAILURE);
    }
    List L = G->adjacencyList[u];
    moveFront(L);
    while (index(L) > -1 && v > get(L)) {
        moveNext(L);
    }
    if (index(L) == -1) {
        append(L, v);
        G->size++;
    } else if (get(L) != v) {
        insertBefore(L, v);
        G->size++;
    }
}


void Visit(Graph G, int u, int *time, List S);

// Depth-First Search
void DFS(Graph G, List S) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling DFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (S == NULL) {
        fprintf(stderr, "Graph Error: calling DFS() with NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(S) != getOrder(G)) {
        fprintf(stderr, "Graph Error: calling DFS() with List of incorrect length\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }

    int time = 0;
    List temp = copyList(S);
    clear(S);
    moveFront(temp);
    while (index(temp) >= 0) {
        int u = get(temp);
        if (G->color[u] == WHITE) {
            Visit(G, u, &time, S);
        }
        moveNext(temp);
    }
    freeList(&temp);
}

void Visit(Graph G, int u, int *time, List S) {
    G->color[u] = GRAY;
    G->discover[u] = (++(*time));
    List adjList = G->adjacencyList[u];
    moveFront(adjList);
    while (index(adjList) >= 0) {
        int v = get(adjList);
        if (G->color[v] == WHITE) {
            G->parent[v] = u;
            Visit(G, v, time, S);
        }
        moveNext(adjList);
    }
    G->color[u] = BLACK;
    G->finish[u] = (++(*time));
    prepend(S, u);
}

// Other operations
Graph transpose(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling transpose() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    Graph T = newGraph(getOrder(G));
    for (int u = 1; u <= getOrder(G); u++) {
        List L = G->adjacencyList[u];
        moveFront(L);
        while (index(L) >= 0) {
            int v = get(L);
            addArc(T, v, u); // Reverse the direction of the edge
            moveNext(L);
        }
    }
    return T;
}

Graph copyGraph(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling copyGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    Graph C = newGraph(getOrder(G));
    for (int u = 1; u <= getOrder(G); u++) {
        List L = G->adjacencyList[u];
        moveFront(L);
        while (index(L) >= 0) {
            int v = get(L);
            addArc(C, u, v);
            moveNext(L);
        }
    }
    return C;
}

void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    for (int u = 1; u <= getOrder(G); u++) {
        fprintf(out, "%d: ", u);
        printList(out, G->adjacencyList[u]);
        fprintf(out, "\n");
    }
}

