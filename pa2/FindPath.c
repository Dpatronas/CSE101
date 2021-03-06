/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa1
* FindPath.c

Handles IO operations

  Part 1)
    File Input:
        n     (# vertices in graph)
        x y   (end vertices of corresponding edges)
        x2 y2 (egdges in range [1,n])
        0 0   (terminating dummy line)

    File Output:
      Print adjacency list representation of graph to outfile

  Part 2)
    File Input:
        s d   (line vertices pairs [1,n])
        s1 d1 (source destination)
        0 0   (terminating dummy line)

Perform Breadth First Search (BFS) from source vertex

    File Output:
        (using results of BFS)
        print out the distance for the lines source vertex to destination vertex
        use parent pointers to print out shortest path from s->d

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

  char u[100];      //hold a token vertex u or s
  char v[100];      //hold a token vertex u or s
  char vertex[10];  //hold the token order/ vertices n 
  int n;            //holds the int order

/*INPUT PART 1******************************************************/

  //Read input first line to get n (vertices)

    // NOTE: reads a single digit vertex input only..
    // int n = (int) getc(in) - 48;
    // printf("n = %d\n\n", n);

  //Read multiple digit vertex input
  fscanf(in, "%s\n", vertex); 
  n = atoi(vertex);
  
  //generate new graph G with n
  Graph G = NULL;
  G = newGraph(n);

  int dummy_pair = 0;

  //read edge pairs (u v)
  do {
    ( fscanf(in, "%s %s\n", u, v) ); 

    int vertex_u = atoi(u);
    int vertex_v = atoi(v);

    //stop reading when dummy pair is found
    if ( vertex_u == 0 && vertex_v == 0 ) {
      dummy_pair = 1;
      continue;
    }
    //add edge of vertex pair to Graph
    addEdge(G, vertex_u, vertex_v);

  } while ( dummy_pair == 0 );

/*OUTPUT PART 1******************************************************/
  //print adjacency list of Graph
  printGraph(out, G);

/*INPUT PART 2******************************************************/
  //reset the dummy pair
  dummy_pair = 0;

  //will hold the paths generated by BFS
  List L = newList();

  //Read the source and destination pairs (s d)
  while (fscanf(in, "%s %s\n", u, v) != EOF) {
    int source = atoi(u);
    int destin = atoi(v);

    if ( source == 0 && destin == 0) {
      dummy_pair = 1;
      continue;
    }
    //perform the BFS on the source
    BFS(G,source);

    //get the path
    getPath(L,G,destin);

/*OUTPUT PART 2 : Print Paths **************************************/

    //path is unreachable
    if (getDist(G,destin) == INF ) {
      fprintf(out,"\n\nThe distance from %d to %d is infinity", source, destin);
      fprintf(out,"\nNo %d-%d path exists", source, destin);
    }
    //else path is reachable
    else {
      fprintf(out,"\n\nThe distance from %d to %d is %d", source, destin, getDist(G,destin));
      fprintf(out,"\nA shortest %d-%d path is: ", source, destin);
      printList(out, L);
    }

    //reset the L for next path..
    clear(L);
  }

  //free all alloc memory..
  fclose(in);
  makeNull(G);
  freeGraph(&G);
  freeList(&L);

   return(0);
}
