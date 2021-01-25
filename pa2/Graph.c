/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa2
* Graph.c
  Implementation for Graph ADT operations

*********************************************************************************/

#include "Graph.h"

//dupe checker for handling size of Graph properly
static int dupe = 0;

//-- Constructors-Destructors ----------------------------------------------------

// Returns a graph pointing to a newly created GraphObj
// default: n vertices
//      no edges (null graph)
Graph newGraph(int n) {

  Graph G = (Graph)malloc(sizeof(GraphObj));
  if (!G) {
    printf("Bad alloc of graph!");
    exit(1);
  }

  G->order = n;     // vertices
  G->size = 0;      // size builds with adding edges
  G->source = NIL;  // remains NIL until BFS is called

  //align each vertex to an index element
  //NOTE: 0 index will not be filled!
  G->color = (int*)malloc((n+1)*sizeof(int));
    if (!G->color) {
      printf("Bad malloc for color array!");
    }
  G->parent = (int*)malloc((n+1)*sizeof(int));
    if (!G->parent) {
      printf("Bad malloc for parent array!");
    }
  G->distance = (int*)malloc((n+1)*sizeof(int));
    if (!G->distance) {
      printf("Bad malloc for distance array!");
    }

  //alloc n+1 (for 0 index) rows for entire adj list
  // each vertex has an adjacency list of (Linked list)
  G->adj = (List *)malloc((n+1) * sizeof(List));

  //generate each adj list
  for (int i = 1; i <= getOrder(G); i++) {
    G->adj[i] = newList();
    if (!G->adj[i]) {
      printf("Bad alloc of adjacency list for: index %d", i);
      exit(1);
    }
  }
  return G;
}

// Frees all dynamically allocated memory corresponding to
// pointerGraph: *pG
// sets *pG to NULL
void freeGraph(Graph* pG) {
  //frees the adj Lists of Graph at indexes (1,n)
  for (int i = 1; i <= getOrder(*pG); i++) {
    freeList(&(*pG)->adj[i]);
  }
  pG = NULL;
}

//-- Access functions ------------------------------------------------------------

// Return the GraphObj field for order (init during construction)
int getOrder(Graph G) {
  if (G) {
    return G->order;
  }
  else {
    printf("No graph defined.."); 
    exit(1);
  }
}

// Return the GraphObj field for size
int getSize(Graph G) {
  if (G) {
    return G->size;
  }
  else {
    printf("No graph defined.."); 
    exit(1);
  }
}

// Returns source vertex most recently used in BFS()
// returns NIL if BFS() has not been called
int getSource(Graph G) {
  if (G->source == NIL) {
    return NIL;
  }
  return G->source;
}

// Return parent of vertex u (created from BFS())
// returns NIL if BFS() has not been called
// PreCond:
//    u <= getOrder(G) && u >= 1
int getParent(Graph G, int u) {
  if (G->source == NIL) {
    return NIL;
  }
  else if ( u >= 1 && u <= getOrder(G) ) {
    return G->parent[u];
  }
  //if precondition not met
  return NIL;
}

// Returns DEPTH / distance from most recently used BFS source to u
// returns INF if BFS() has not been called
// PreCond:
//    u <= getOrder(G) && u >= 1
int getDist(Graph G, int u) {
  if (G->source == NIL) {
    return INF;
  }
  //make sure the parent index will be valid
  if ( u >= 1 && u <= getOrder(G) ) {
    return G->distance[u];
  }
  return INF;
}

// Appends to List L shortest path vertices or NIL if no path exists to 'u'
// vertices of the shortest path in Graph from source to 'u'
// destination: u
//    PreCond:
//    BFS() must be called before getPath()
//    u <= getOrder(G) && u >= 1
//
void getPath(List L, Graph G, int u) {

  //if BFS wasnt called there is no source
  if (getSource(G) == NIL) {
    return;
  }
  //trivial path
  else if (u == G->source) {
    append(L, u);
  }
  //unreachable path
  else if (G->parent[u] == NIL) {
    append(L,NIL);
  }
  //recursively find path from s-u
  else if ( u >= 1 && u <= getOrder(G) ) {
      getPath(L, G, G->parent[u]);  //call functin on the parent of u until no parent can be called
      append(L,u); //start populating the List starting with parent->->..u  
  }
}

//--- Manipulation procedures ----------------------------------------------------

// Deletes all edges of G
// Restores G to its original (no edge) state AKA null graph
void makeNull(Graph G) {
  if (!G) {
    return;
  }
  //clear all the adjacency lists back to default state
  for ( int i = 1; i <= getOrder(G); i++) {
    clear(G->adj[i]);
  }
  //set default size
  G->size = 0;
}

// Joins u to v
// vertex: u  added to adjacency List of v
// vertex: v  added to adjacency List of u
// Lists MUST maintain sorted order by increasing labels
//     PreCond:
//    u <= getOrder(G) && u >= 1
//    v <= getOrder(G) && v >= 1
//
void addEdge(Graph G, int u, int v) {
  //precondition
  if ( (u <= getOrder(G)) && (u >= 1) && (v <= getOrder(G)) && (v >= 1) ) {

    // adjacency to itself is not defined?
    if ( u == v) {
      return;
    }

    //add both directed edges
    addArc(G,u,v);
    addArc(G,v,u);

    // Size adjusting as long as no dupe occurs
    if (!dupe) {
      G->size--;  //each egde increments size (so decrement once)  
    }
    //reset the dupe at end of add edge
    dupe = 0;
  }
}

// Inserts new directed edge from u to v
// vertex v:  added to adjacency List of u
// note: List v unchanged
// Lists MUST maintain sorted order by increasing labels
//    PreCond:
//    u <= getOrder(G) && u >= 1
//    v <= getOrder(G) && v >= 1
//
void addArc(Graph G, int u, int v) {

  //precondtition
  if ( (u <= getOrder(G)) && (u >= 1) && v <= getOrder(G) && (v >= 1) ) {

    // adjacency to itself is not defined?
    if ( u == v) {
      return;
    }

    //if the adjacency list for 'u' index is empty just append v directly
    if (length(G->adj[u]) == 0) {
      append(G->adj[u], v);
      G->size++;
    }
    //else append / prepend at appropriate position
    else {
      sort(G, G->adj[u], v);
    }
  }
}

// Run BFS algo on graph G with
// Graph G 
// source: s
// Sets color, distance, parent, and source fields of G
void BFS(Graph G, int s) {

  //sets the source once BFS is called
  G->source = s;

  //set all but source..
  for (int x = 1; x <= getOrder(G); x++) {
    if (x != s) {
      G->color[x] = 1;      //white
      G->distance[x] = INF; //NDF
      G->parent[x] = NIL;   //NDF
    }
  }
  
  //set source vertex
   G->color[s] = 2;        //gray
   G->distance[s] = 0;     //Depth = 0
   G->parent[s] = NIL;     //NDF

  //empty list act as FIFO queue 
  List Q = newList();
  //EnQueue source
  append(Q,s);

  //while queue is populated with a vertex
  while ( length(Q) > 0 ) {
    //peek and dequeue(front)
    int x = front(Q);
    deleteFront(Q);
    //get the cursor at first position
    moveFront(G->adj[x]);

    //iterate through all vertexes within the adj list of x
    for (int j = 1; j <= length(G->adj[x]); j++) {
      
      //let y be element within adj list
      int y = get(G->adj[x]);

      //check if vertex undiscovered AKA white (1)
      if (G->color[y] == 1) {
        G->color[y] = 2;                      //discover new vertex now set to gray
        G->distance[y] = G->distance[x] + 1;  //set new vertex dist based on last vertex
        G->parent[y] = x;                     //parent of new vertex is last vertex
        append(Q,y);                          //enqueue the next vertex
      }
      //move the cursor forward to next adj element
      moveNext(G->adj[x]);
    }
    //set the last vertex to black now
    G->color[x] = 3;
  }
  //Free the Queue List
  freeList(&Q);
}

//--- Other operations -----------------------------------------------------------

// Prints the adjacency list represenation of G
// Note the outfile template on pa2
void printGraph(FILE* out, Graph G){
    if (!G) {
      printf("no graph!");
      return;
    }
    for (int i = 1; i < getOrder(G); i++) {
      fprintf(out, "%d: ", i);
      printList(out, G->adj[i]);
      fprintf(out, "\n");
  }
  //last element
  fprintf(out, "%d: ", getOrder(G));
  printList(out, G->adj[getOrder(G)]);
}

// Decides where to put new integer into adjacency list
// Maintain ascending order of vertex adjacency list
//
// G: Graph where vertex lives
// L: adjacency List of vertex
// x: integer to add to list
//
void sort( Graph G, List L, int x) {

  moveFront(L);

  for ( int i = 1; i <= getOrder(G); i ++) {
    if (get(L) != -1) {

      //if value < front of adj List prepend
      if ( (x < get(L)) ) {
        insertBefore(L,x);
        G->size++;
        return;
      }
      //duplicate edge, trigger dupe variable (adjusts size in add edge)
      if ( get(L) == x) {
        dupe = 1;
        return;
      }
      //move cursor through the list
      moveNext(L);
      }
      
    //end of list. Must append
    else {
      append(L,x);
      G->size++;
      return;
    }
  }
}
