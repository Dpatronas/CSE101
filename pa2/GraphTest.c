/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa1
  GraphTest.c
    tests the efficacy of Graph.c functions

*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){

  int n = 8;
  Graph G = NULL;
  G = newGraph(n);

  printf("\n=========================================================");
  printf("\nLinear Graph");
  printf("\n=========================================================");

  printf("\Empty Graph..\n");

  printGraph(stdout, G);
  printf("\nOrder = %d", getOrder(G));
  printf("\nSize = %d\n", getSize(G));

  //add edge test bidirectional
  printf("\n=========================================================");
  printf("\nAdd Edges Test (Directed Lines):: Populate Linearly (1-4)");
  printf("\n=========================================================");

  addEdge(G, 1,2);
  addEdge(G, 2,3);
  addEdge(G, 3,4);
  
  printf("\n");
  printGraph(stdout, G);
  printf("\nOrder = %d", getOrder(G));
  printf("\nSize = %d\n", getSize(G));

  printf("\n=========================================================");
  printf("\nAdd Arcs Test (Undirected Lines) :: Linear Graph (4-6)");
  printf("\n=========================================================");

  addArc(G,4,5);
  addArc(G,5,6);

  printf("\n");
  printGraph(stdout, G);
  printf("\nSize = %d\n", getSize(G));

  printf("\n=========================================================");
  printf("\nForm Disconnect :: Populate (7-8)");
  printf("\n=========================================================");

  addEdge(G,7,8);
  printf("\n");
  printGraph(stdout, G);
  printf("\nSize = %d\n", getSize(G));


  //check BFS for each vertex
  printf("\n=========================================================");
  printf("\nBFS Test");
  printf("\n=========================================================");

  printf("\nRun BFS source 1\n");
  BFS(G, 1);
  List Path1 = newList();
  getPath(Path1,G,4);
  printf("\nPrinting path from Source 1 - 4");
  printf("\n");
  printList(stdout, Path1);
  printGraph(stdout, G);

  for (int i = 1; i <= getOrder(G); i++) {
    printf("\nParent of %d = %d", i, getParent(G,i));
    printf("\nDistnc of %d = %d", i, getDist(G,i));
    printf("\nColour of %d = %d\n", i, G->color[i]);
  }

  printf("\n---------------------------------------------------------");

  printf("\nRun BFS source 4\n");
  BFS(G, 4);
  List Path4 = newList();
  getPath(Path4,G,2);
  printf("\nPrinting path from Source 4 - 2");
  printf("\n");
  printList(stdout, Path4);
  printGraph(stdout, G);

  for (int i = 1; i <= getOrder(G); i++) {
    printf("\nParent of %d = %d", i, getParent(G,i));
    printf("\nDistnc of %d = %d", i, getDist(G,i));
    printf("\nColour of %d = %d\n", i, G->color[i]);
  }

  printf("\n---------------------------------------------------------");

  printf("\nRun BFS source 8\n");
  BFS(G, 8);
  List Path8 = newList();
  getPath(Path8,G,1);
  printf("\nPrinting path from Source 8 - 1");
  printf("\n");
  printList(stdout, Path8);
  printGraph(stdout, G);

  for (int i = 1; i <= getOrder(G); i++) {
    printf("\nParent of %d = %d", i, getParent(G,i));
    printf("\nDistnc of %d = %d", i, getDist(G,i));
    printf("\nColour of %d = %d\n", i, G->color[i]);
  }

  printf("\n=========================================================");
  printf("\nPrint Paths Linear Test");
  printf("\n=========================================================");

  printf("\nPath from 1 to 4\n");
  printList(stdout, Path1);
  printf("\n");
  printf("\nPath from 4 to 2\n");
  printList(stdout, Path4);
  printf("\n");
  printf("\nPath from 8 to 1\n");
  printList(stdout, Path8);
  printf("\n");


  printf("\n=========================================================");
  printf("\nNon Linear Graph");
  printf("\n=========================================================");

  int m = 4;
  Graph R = NULL;
  R = newGraph(m);

  printf("\nNew Graph..\n");

  printGraph(stdout, R);
  printf("\nOrder = %d", getOrder(R));
  printf("\nSize = %d\n", getSize(R));

  printf("\n=========================================================");
  printf("\nPopulating graph with Edge combinations from [0,5]");
  printf("\n+Bounds Checking vertex 0 and vertex m + 1");
  printf("\n=========================================================");

  //check bounds/ graph size when adding edges
  for ( int i = 0; i < m+1; i++) {
    for (int j = 0; j < m+1; j++) {
      addEdge(R, i,j);
    }
  }

  printf("\n");
  printGraph(stdout, R);
  printf("\nOrder = %d", getOrder(R));
  printf("\nSize = %d\n", getSize(R));

  printf("\n=========================================================");
  printf("\nChecking for Dupes.. Repeating last test");
  printf("\n=========================================================");

  //check bounds/ graph size when adding edges
  for ( int i = 0; i < m+1; i++) {
    for (int j = 0; j < m+1; j++) {
      addEdge(R, i,j);
    }
  }
  printf("\n");
  printGraph(stdout, R);
  printf("\nOrder = %d", getOrder(R));
  printf("\nSize = %d\n", getSize(R));

  printf("\n=========================================================");
  printf("\nNullify Graphs ");
  printf("\n=========================================================");

  makeNull(G);
  printGraph(stdout, G);
  printf("\nOrder = %d", getOrder(G));
  printf("\nSize = %d\n", getSize(G));  
  
  makeNull(R);
  printf("\n");
  printGraph(stdout, R);
  printf("\nOrder = %d", getOrder(R));
  printf("\nSize = %d\n", getSize(R));

  printf("\n=========================================================");
  printf("\nPopulating graph with Arc combinations from [0,5]");
  printf("\n+Bounds Checking vertex 0 and vertex m + 1");
  printf("\n=========================================================");

  //check bounds/ graph size when adding arcs
  for ( int i = 0; i < m+1; i++) {
    for (int j = 0; j < m+1; j++) {
      addArc(R, i,j);
    }
  }

  printf("\n");
  printGraph(stdout, R);
  printf("\nOrder = %d", getOrder(R));
  printf("\nSize = %d\n", getSize(R));

  printf("\n=========================================================");
  printf("\nNullify & Freeing Graphs ");
  printf("\n=========================================================");

  makeNull(R);
  free(G);
  free(R);
   return(0);
}
