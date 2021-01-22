/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa1
* Graph.c
	Implementation for Graph ADT operations

*********************************************************************************/

#include "Graph.h"

//-- Constructors-Destructors ----------------------------------------------------

// Returns a graph pointing to a newly created GraphObj
// default: n vertices
// 			no edges (null graph)
Graph newGraph(int n) {

	Graph G = (Graph)malloc(sizeof(Graph));
  if (!G) {
    printf("Bad alloc of graph!");
    exit(1);
  }

	G->order = n;
	G->size = n;
	//remains NIL until BFS is called
	G->source = NIL;

	//align each vertex to an index element
	//NOTE: 0 index will not be filled!
  int color[n]; int parent[n]; int distance[n];
	G->color = color;
	G->parent = parent;
	G->distance = distance;

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

// Return the GraphObj field for order
// value init during the construction
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
// value init during the construction
int getSize(Graph G) {
	if (G) {
		return G->order;
	}
	else {
		printf("No graph defined.."); 
		exit(1);
	}
}

// Returns source vertex most recently used in BFS()
// returns NIL if BFS() has not been called
int getSource(Graph G) {
	if (!G->source) {
    printf("BFS hasnt been called.. no source");
		return NIL;
	}
	return G->source;
}

// Return parent of vertex in BFS()
// returns NIL if BFS() has not been called
// vertex: u
//
// PreCond:
//		u <= getOrder(G)
//		u >= 1
int getParent(Graph G, int u) {
  if (!G->source) {
    printf("BFS hasnt been called.. no source");
		return NIL;
	}
  if (u <= getOrder(G) && u >= 1) {
	  return G->parent[u];
  }
  //if precondition not met
  printf("out of bounds vertex.. cannot access parent");
  return NIL;
}

// Returns DEPTH / distance from most recently used BFS source
// returns INF if BFS() has not been called
// 
// distance from BFS to vertex: u
//
// PreCond:
//		u <= getOrder(G)
//		u >= 1
int getDist(Graph G, int u) {
	if (!G->source) {
		return NIL;
	}
	//make sure the parent index will be valid
	if ( u <= getOrder(G) && u >= 1) {
		return G->distance[u];
	}
  return NIL;
}

// Appends to List L shortest path vertices or NIL if no path exists to 'u'
// vertices of the shortest path in Graph from source to 'u'
// destination: u 			ex: List L -> v1 v2 v3 u
//     PreCond:
//		getSource(G) != NIL
// 		BFS() must be called before getPath()
// 		u <= getOrder(G)
//		u >= 1
//
void getPath(List L, Graph G, int u) {

  //if BFS wasnt called there is no source
	if (!getSource(G)) {
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
	else if (u <= getOrder(G) && u >= 1) {
		  getPath(L, G, G->parent[u]);  //call functin on the parent of u until no parent can be called
      append(L,u);                  //start populating the List starting with parent->->..u	
	}
  else printf("\nu is out of bounds..\n");
}


//--- Manipulation procedures ----------------------------------------------------


// Deletes all edges of G
// Restores G to its original (no edge) state AKA null graph
void makeNull(Graph G) {
	if (!G) {
		return;
	}
  //clear all the adjacency lists back to default state
	for ( int i = 0; i < getSize(G); i++) {
    clear(G->adj[i]);
  }
  //set size to default
  G->size = 0;

}

// Joins u to v
// vertex: u 	added to adjacency List of v
// vertex: v 	added to adjacency List of u
// Lists MUST maintain sorted order by increasing labels
//     PreCond:
//		u <= getOrder(G) && u >= 1
//		v <= getOrder(G) && v >= 1
//
void addEdge(Graph G, int u, int v) {
  //precondition
  if ( (u <= getOrder(G)) && (u >= 1) && v <= getOrder(G) && (v >=1) ) {
    //add both directed edges
    addArc(G,u,v);
    addArc(G,v,u);
    //each egde increments size each (so decrement once)
    G->size--;
  }
}

// Inserts new directed edge from u to v
// vertex v: 	added to adjacency List of u
// note: List v unchanged
// Lists MUST maintain sorted order by increasing labels
//     PreCond:
//		u <= getOrder(G) && u >= 1
//		v <= getOrder(G) && v >= 1
//
void addArc(Graph G, int u, int v) {
  //precondtition
	if ( (u <= getOrder(G)) && (u >= 1) && v <= getOrder(G) && (v >=1) ) {
		//if the adjacency list for 'u' index is empty just append v directly
		if (length(G->adj[u]) == 0) {
			append(G->adj[u], v);
		}
		//else append / prepend at appropriate position
		else {
			sort(G, G->adj[u], v);
		}
		//in all cases increase size
		G->size++;
	}
  else {
    printf("\nArc is not in bounds! \nU: %d \nV: %d \nOrder: %d \n", u, v, getOrder(G));
  }
}

// Run BFS algo on graph G with
// source: s
// Sets color, distance, parent, and source fields of G
void BFS(Graph G, int s) {

	//sets the source once BFS is called
	G->source = s;

	for (int i = 1; i <= getOrder(G); i++) {
		G->color[i] = 1;      //white
		G->distance[i] = INF; //NDF
		G->parent[i] = NIL;   //NDF
	}
  //for source vertex
	G->color[s] = 2;        //gray
	G->distance[s] = 0;     //Depth = 0
	G->parent[s] = NIL;     //NDF

  //empty list act as FIFO queue 
  List Q = newList();
  //EnQueue source
  append(Q,s);

  //while queue is populated with a vertex
  while ( length(Q) > 0 ) {
    //peek and dequeue
    int x = front(Q);
    deleteFront(Q);

    //iterate through all vertexes within the adj list of x
    //ignore 0
    for (int i = 1; i <= length(G->adj[x]); i++) {
      //check if vertex undiscovered AKA white (1)
      if (G->color[i] == 1) {
        G->color[i] = 2;                      //discover new vertex now set to gray
        G->distance[i] = G->distance[x] + 1;  //set new vertex dist based on last vertex
        G->parent[i] = x;                     //parent of new vertex is last vertex
        append(Q,i);                          //enqueue the next vertex

      }
      G->color[x] = 3;    //set the last vertex to black now
    }
  }
}


//--- Other operations -----------------------------------------------------------

// Prints the adjacency list represenation of G
// Note the outfile template on pa2
void printGraph(FILE* out, Graph G){
    if (!G) {
      printf("no graph!");
      return;
    }
  	for (int i = 1; i <= getOrder(G); i++) {
      printf("%d: ", i);
      printList(stdout, G->adj[i]);
      printf("\n");
	}
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
			if ( (x < get(L)) ) {
				insertBefore(L,x);
				return;
			}
      //duplicate edge
      if ( get(L) == x) {
        //do nothing and decrement size since nothing will be added
        G->size--;
        return;
      }
			moveNext(L);
			}
		else  {
			append(L,x);
      return;
		}
  }
}
