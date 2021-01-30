/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa1
* FindPath.c

Handles IO operations
  Part 1)
    File Input:
        n     (# vertices in graph)
        x y   (end vertices of corresponding edges)
        x2 y2 (add arcs in range [1,n])
        0 0   (terminating dummy line)

    File Output:
      Print adjacency list representation of graph to outfile

  Part 2)
  -Run DFS on G and G^T 
  -process vertices in second call by decreasing finishing times from first call
  -Determine the strong components of G

    File Output:
        print the strong components of G in toplogogically sorted order

*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

int main(int argc, char* argv[]){

  FILE *in;
  FILE *out;
  // check command line for correct number of arguments
  if( argc != 3 ){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
  // open files for reading and writing 
  in = fopen(argv[1], "r");
  if( !in ){
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  out = fopen(argv[2], "w");
  if( !out ){
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

/*PART 1******************************************************/

  char u[100];      //hold a token vertex u or s
  char v[100];      //hold a token vertex u or s
  char vertex[10];  //hold the token order/ vertices n 
  int n;            //holds the int order

  //Read input first line to get n (vertices)
  fscanf(in, "%s\n", vertex); 
  n = atoi(vertex);
  
  //generate new graph G with n
  Graph G = newGraph(n);
  int dummy_pair = 0;

  //read edge pairs (u v)
  do { ( fscanf(in, "%s %s\n", u, v) ); 

    int vertex_u = atoi(u);
    int vertex_v = atoi(v);

    //stop reading when dummy pair is found
    if ( vertex_u == 0 && vertex_v == 0 ) {
      dummy_pair = 1;
      continue;
    }
    //add edge of vertex pair to Graph
    addArc(G, vertex_u, vertex_v);

  } while ( dummy_pair == 0 );

  //print adjacency list of Graph
  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);

/*PART 2 Print SCC of G******************************************/

  //List populated with vertices.. will serve as a Stack
  List S = newList();
  for (int i = 1; i <= getOrder(G); i++) {
    append(S,i);
  }

  //1) Run DFS on G
  DFS(G,S);

  //2) Make G transpose
  Graph Gt = transpose(G);

  //3) run DFS on GT
  DFS(Gt, S);

// /*OUTPUT PART 2 : Print SCC of G **************************************/

  int scc = 0;    //count the strongly connected components
  moveBack(S);    //move cursor to the back to read scc's

  //find parents that are NIL in Stack
  for (int i = 1; i <= getOrder(G); i++) {
    if ( getParent(Gt,get(S)) == NIL ) {
      scc++;       //increment strongly connected components
    }
    movePrev(S);
  }
  // Print the SCC
  fprintf(out, "\nG contains %d strongly connected components:\n", scc);

  //if no scc, exit here
  if (scc == 0) {
    return 0;
  }

  //otherwise print the elements in the strongly connected components
  int cc = 1;             //at least one component exists
  moveBack(S);            //start from the back for Topological Order

  //iterate through list for the components & print
  while (get(S) != -1) {              //while cursor isnt at the end of list

    //if cursor of list is a parent of a component
    if ( getParent(Gt,get(S)) == NIL ) {  

      int cc_elems = 1;               //parent is a guaranteed element in component
      fprintf(out, "Component %d: %d", cc, get(S));
      moveNext(S);                    //check for offspring
      
      //Get children of the component parent
      while (get(S) != -1) {
        fprintf(out, " %d", get(S));
        cc_elems++;                   //count the children as elements in component
        moveNext(S);                  //keep looping till cursor falls off the list
      }
      for (int i= 0; i < cc_elems; i++) {
        deleteBack(S);                //remove all elements in current component
      }

      moveBack(S);                    //reset the cursor position to the back
      fprintf(out, "\n");
      cc++;                           //look for next component
    }
    //if list item is not a parent keep moving through list
    else {
      movePrev(S);                    
    }
  }

  //free all alloc memory..
  fclose(in);
  fclose(out);

  makeNull(G);
  makeNull(Gt);

  freeGraph(&G);
  freeGraph(&Gt);

  clear(S);
  freeList(&S);

   return(0);
}
