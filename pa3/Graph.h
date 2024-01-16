/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA3
* Graph.h
* Contains function prototypes and type definitions for the Graph ADT used by the FindComponents program.
***/

#ifndef CSE101_GRAPH_H
#define CSE101_GRAPH_H

#include "List.h"

#define INF -1
#define NIL 0
#define WHITE 1
#define GRAY 2
#define BLACK 3
#define UNDEF -1


typedef struct GraphObj *Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);

void freeGraph(Graph *pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

/*** Manipulation procedures ***/
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);

#endif //CSE101_GRAPH_H
