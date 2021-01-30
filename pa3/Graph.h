/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa3
* Graph.h
    Prototypes for Graph ADT operations
    (Used for DFS algorithm)
*********************************************************************************/

#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define NIL -1337     //negative int value (# < 0)
#define UNDEF -1      //any non positive int value (# <= 0)

typedef struct GraphObj {

  //Graph fields
  int order;      //# vertices in G set upon construction
  int size;       //# of edges / lines in G

  //vertex fields 
  List *adj;      // array of lists for adjacency list vertices

  //DFS sets these fields
                  //      undiscovered   discovered   finished
  int * color;    // colors (white = 1) (gray = 2) (black = 3)
  int * discov;   // time to discover a vertex
  int * finish;   // time to finish a vertex
  int * parent;   // vertex parent of a vertex

} GraphObj;

//Graph is a pointer to GraphObj
typedef GraphObj * Graph;

//-- Constructors-Destructors ----------------------------------------------------

// Returns a graph pointing to a newly created GraphObj
// default: n vertices and no edges (null graph)
Graph newGraph(int n);

// Frees all dynamically allocated memory to pointerGraph: *pG
// sets *pG to NULL
void freeGraph(Graph* pG);


//-- Access functions ------------------------------------------------------------


// Return the GraphObj field for order
int getOrder(Graph G);

// Return the GraphObj field for size
int getSize(Graph G);

// Return parent of vertex u in DFS()
// returns NIL if DFS() has not been called
//
// PreCond: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u);

// returns UNDEF if DFS() has not been called
//
// PreCond: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u);

// returns UNDEF if DFS() has not been called
//
// PreCond: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u);

//--- Manipulation procedures ----------------------------------------------------

// Deletes all edges of G
// Restores G to its original (no edge) state AKA null graph
void makeNull(Graph G);

// Joins u to v
// vertex: u    added to adjacency List of v
// vertex: v    added to adjacency List of u
// Lists MUST maintain sorted order by increasing labels
//
// Pre: 1<=u<=n, 1<=v<=n
void addEdge(Graph G, int u, int v);

// Inserts new directed edge from u to v
// vertex v: added to adjacency List of u
// note: List v unchanged
// Lists MUST maintain sorted order by increasing labels
//
// Pre: 1<=u<=n, 1<=v<=n
void addArc(Graph G, int u, int v);

// Run DFS algo on graph G
// Sets color, discover, finish, and parent fields of vertex
//
// List S: defines order vertices are processed in main loop
// stores vertices by decreasing finish time at DFS completion
// List S acts as a FILO Stack
//
// Pre: length(S)==getOrder(G)
//      S List contains only [1 <= vertices <= getOrder(G)]
void DFS(Graph G, List S);

//--- Other operations -----------------------------------------------------------

// Transposes Graph G (reverse directed edges) in Graph
// Creates and returns a new GraphObj which is G^T
Graph transpose (Graph G);

// Returns a reference to a new graph that is a copy of G
// Creates a new GraphObj
Graph copyGraph(Graph G);

// Prints the adjacency list represenation of G
// Note the outfile template on pa2
void printGraph(FILE* out, Graph G);

// Decides where to put new integer into adjacency list
// Maintain ascending order of vertex adjacency list
// No duplicates are allowed
//
// G: Graph where vertex lives
// L: adjacency List of vertex
// x: integer to add to list
void sort( Graph G, List L, int x);
