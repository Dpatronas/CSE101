/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa2
* Graph.h
    Prototypes for Graph ADT operations
*********************************************************************************/

#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define NIL -1337   //negative int value (# < 0)
#define INF -1      //any non positive int value (# <= 0)

typedef struct GraphObj {
    //NOTE: 0 index is empty for the below

    List *adj;      // array of lists for adjacency list vertices

    //BFS sets these fields
    int * color;    // represent the color colors 1 = white, 2 = gray, 3 = black
    int * parent;   // # of parent of vertex
    int * distance; // # distance/ DEPTH from the source

    int size;       //# of edges / lines in G
    int order;      //# vertices in G
    int source;     //the source vertex (for calling bfs)

} GraphObj;

typedef GraphObj * Graph;

//-- Constructors-Destructors ----------------------------------------------------

// Returns a graph pointing to a newly created GraphObj
// default: n vertices
//          no edges (null graph)
Graph newGraph(int n);

// Frees all dynamically allocated memory corresponding to
// pointerGraph: *pG
// sets *pG to NULL
void freeGraph(Graph* pG);


//-- Access functions ------------------------------------------------------------

// Return the GraphObj field for order
int getOrder(Graph G);

// Return the GraphObj field for size
int getSize(Graph G);

// Returns source vertex most recently used in BFS()
// returns NIL if BFS() has not been called
int getSource(Graph G);

// Return parent of vertex in BFS()
// returns NIL if BFS() has not been called
// vertex: u
//
// PreCond:
//      u <= getOrder(G)
//      u >= 1
int getParent(Graph G, int u);

// Returns distance from most recently used BFS source
// returns INF if BFS() has not been called
// distance from BFS to
// vertex: u
//
// PreCond:
//      u <= getOrder(G)
//      u >= 1
int getDist(Graph G, int u);

// Appends to List L shortest path vertices or NIL if no path exists to 'u
// vertices of the shortest path in Graph from source to 'u'
// destination: u           ex: List L -> v1 v2 v3 u
//
// PreCond:
//      getSource(G) != NIL
//      BFS() must be called before getPath()
//      u <= getOrder(G)
//      u >= 1
void getPath(List L, Graph G, int u);


//--- Manipulation procedures ----------------------------------------------------


// Deletes all edges of G
// Restores G to its original (no edge) state AKA null graph
void makeNull(Graph G);


// Joins u to v
// vertex: u    added to adjacency List of v
// vertex: v    added to adjacency List of u
// Lists MUST maintain sorted order by increasing labels
//
// PreCond:
//      u <= getOrder(G) && u >= 1
//      v <= getOrder(G) && v >= 1
void addEdge(Graph G, int u, int v);

// Inserts new directed edge from u to v
// vertex v:    added to adjacency List of u
// note: List v unchanged
//
// PreCond:
//      u <= getOrder(G) && u >= 1
//      v <= getOrder(G) && v >= 1
void addArc(Graph G, int u, int v);

// Run BFS algo on graph G with
// source: s
// Sets color, distance, parent, and source fields of G
void BFS(Graph G, int s);

//--- Other operations -----------------------------------------------------------

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
