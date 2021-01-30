/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa3
* Graph.c
    Implementation for Graph ADT operations
    (Used for DFS algorithm)
*********************************************************************************/

#include "Graph.h"

//dupe checker for handling size of Graph properly
static int DUPE = 0;

//check if bfs has been called
int PRE = 0;

//-- Constructors-Destructors ----------------------------------------------------

// Returns a graph pointing to a newly created GraphObj
Graph newGraph(int n) {

  Graph G = (Graph)malloc(sizeof(GraphObj));
  if (!G) {
    printf("Bad alloc of graph!"); exit(1);
  }
  G->order = n;     // vertices
  G->size = 0;      // size builds with adding edges

  //align each vertex to an index element
  G->color = (int*)malloc((n+1)*sizeof(int));
  G->discov = (int*)malloc((n+1)*sizeof(int));
  G->finish = (int*)malloc((n+1)*sizeof(int));
  G->parent = (int*)malloc((n+1)*sizeof(int));

  if ( (!G->color) || (!G->discov) || (!G->finish) || (!G->parent) ) {
    printf("Bad malloc for arrays!");
  }

  // alloc n+1 (for 0 index) rows for entire adj list
  // each vertex has an adjacency list of (Linked list)
  G->adj = (List *)malloc((n+1) * sizeof(List));

  //generate each adj list
  for (int i = 1; i <= getOrder(G); i++) {
    G->adj[i] = newList();
    if (!G->adj[i]) {
      printf("Bad alloc of adjacency list for: index %d", i); exit(1);
    }
    //predefine states
    G->parent[i] = NIL;
    G->discov[i] = UNDEF;
    G->finish[i] = UNDEF;
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
    printf("No graph defined.."); exit(1);
  }
}

// Return the GraphObj field for size
int getSize(Graph G) {
  if (G) {
    return G->size;
  }
  else {
    printf("No graph defined.."); exit(1);
  }
}

// Return parent of vertex u in DFS()
// returns NIL if DFS() has not been called
// PreCond: 1<=u<=getOrder(G)
int getParent(Graph G, int u) {
  return G->parent[u];
}

// returns UNDEF if DFS() has not been called
// PreCond: 1<=u<=getOrder(G)
int getDiscover(Graph G, int u) {
  return G->discov[u];
}

// returns UNDEF if DFS() has not been called
// PreCond: 1<=u<=getOrder(G)
int getFinish(Graph G, int u) {
  return G->finish[u];
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
// vertex u: added to adjacency List of v
// vertex v: added to adjacency List of u
// Lists MUST maintain sorted order by increasing labels
// PreCond: 1<=u<=getOrder(G) && 1<=v<=getOrder(G)
void addEdge(Graph G, int u, int v) {
  //precondition
  if ( (u <= getOrder(G)) && (u >= 1) && (v <= getOrder(G)) && (v >= 1) ) {

    //add both directed edges
    addArc(G,u,v);
    addArc(G,v,u);

    // Size adjusting as long as no dupe occurs
    if (!DUPE) {
      G->size--;  //each egde increments size (so decrement once)  
    }
    //reset the dupe at end of add edge
    DUPE = 0;    
  }
}

// Inserts new directed edge from u to v
// vertex v: added to adjacency List of u
// note: List v unchanged
// Lists MUST maintain sorted order by increasing labels
// PreCond: 1<=u<=getOrder(G) && 1<=v<=getOrder(G)
void addArc(Graph G, int u, int v) {

  //precondtition
  if ( (u <= getOrder(G)) && (u >= 1) && v <= getOrder(G) && (v >= 1) ) {
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

// (if a vertex is called from Visit, it has a parent)
// u: vertex to visit   
// time: incremenets
void Visit(Graph G, int u, int *time, List *S) {

  G->discov[u] = ++(*time); //mark the time vertex was found
  G->color[u] = 2;          //grey out the vertex
  moveFront(G->adj[u]);     //set adj List cursor to the front

  //iterate through elements in 'u' adj list (increasing order)
  for ( int i = 1; i <= length( G->adj[u]); i++) {
    int v = get(G->adj[u]);

    if ( G->color[v] == 1 ) {   //undiscovered element in adj list of unchanged
      G->parent[v] = u;         //set parent of adj
      Visit(G, v, time, S);        //recursively call visit
    }
    moveNext(G->adj[u]);        //move to next element of adj[u]
  }
  G->color[u] = 3;            //black out vertex
  G->finish[u] = ++(*time);   //mark the time vertex was finished

  prepend(*S, u);
}

// (If vertex is called from DFS, it has no parent)
// Sets color, discover, finish, and parent fields of vertex
//
// List S: defines order vertices are processed in main loop
//
// stores vertices by decreasing finish time at DFS completion in List L
// List S acts as a FILO Stack
//
// Pre: length(S)==getOrder(G)
void DFS(Graph G, List S) {

  PRE = 1;

  if (length(S) != getOrder(G)) {
    return;
  }

  //initialize all vertices 'u' in G to default values
  for (int x = 1; x <= getOrder(G); x++ ) {
    G->color[x] = 1;
    G->parent[x] = NIL;
  }
  int time = 0;

  //start at the front of the list
  moveFront(S);

  // Visit Vertices in the order of List 
  for (int i = 1; i <= getOrder(G); i++ ) {

    int v = get(S);         //get item in list at cursor
    if (G->color[v] == 1) {
      Visit(G, v, &time, &S); //visit that cursors adj list
    }
    moveNext(S);            //go to the next element
  }
  //now remove the old list elements
  moveBack(S);
  for (int i = 1; i <=getOrder(G); i++) {
    deleteBack(S);
  }
}



//--- Other operations -----------------------------------------------------------

// Transposes Graph G (reverse directed edges) in Graph
// Creates and returns a new GraphObj which is G^T
Graph transpose (Graph G) {
  if (!G) {
    exit(1);
  }
  //make an empty graph size of old graph
  Graph T = newGraph( getOrder(G) );

  //iterate throught each vertex
  for (int i = 1; i <= getOrder(G); i++) {

    //set cursor to t he front
    moveFront(G->adj[i]);

    //iterate through elements in each vertexes adj list
    //if adj list is empty it wont enter
    for ( int j = 1; j <= length( G->adj[i]); j++) {

      int v = get(G->adj[i]); //grab the data in cursor
      addArc(T, v, i);        //swap  (adj[i] = v) =>> (adj[v] = i)
      moveNext(G->adj[i]);    //step to next element

    }
  }
  return T;
}

// Returns a reference to a new graph that is a copy of G
// Creates a new GraphObj
Graph copyGraph(Graph G) {

  if (!G) {
    exit(1);
  }

  Graph Copy = newGraph( getOrder(G) );

  //iterate through the vertices of G
  for (int i = 1; i <= getOrder(G); i++) {

    moveFront(G->adj[i]);     //set cursor to front

    //iterate through the elements within adj list of current vertex
    for (int j = 1; j <= length(G->adj[i]); j++) {

      int u = i;              //new vertex source  is element in current vertex adj list
      int v = get(G->adj[i]); //new vertex dest is element of current cursor

      addArc(Copy, u, v);     //add arcs from (source, dest) in new graph
      moveNext(G->adj[i]);
    }
  }
  return Copy;
}

// Prints the adjacency list represenation of G
// Note the outfile template on pa2
void printGraph(FILE* out, Graph G){
    if (!G) {
      printf("no graph!");
      return;
    }
    for (int i = 1; i <= getOrder(G); i++) {
      fprintf(out, "%d: ", i);
      printList(out, G->adj[i]);
      fprintf(out, "\n");
    }
  // last element
  // fprintf(out, "%d: ", getOrder(G));
  // printList(out, G->adj[getOrder(G)]);
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
        DUPE = 1;
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
