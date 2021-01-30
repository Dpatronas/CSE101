/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa3
  GraphTest.c
    tests the efficacy of Graph.c functions

*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(){

  int n = 8;
  Graph G = newGraph(n);    //original graph
  Graph C = newGraph(n);    //will be copy of G
  Graph Gt = newGraph(n);   //will be transpose of G

  List S = newList();       //list to test for DFS propely
  List Asym = newList();    //list with a mismatches size
  
  //initialize lists
  for (int i = 1; i <= 3; i++) 
    append(Asym,i);

  for (int i = 1; i <= getOrder(G); i++) 
    append(S,i);
  

  printf("\nEmpty Graph G..\n");
  printGraph(stdout, G);
  printf("\nEMPTY Order = %d  // Size = %d\n", getOrder(G), getSize(G));

  printf("\n=========================================================");
  printf("\n Add Edges & Arcs Test to G");
  printf("\n=========================================================");

  addEdge(G, 1,2);
  addEdge(G, 2,3);
  addEdge(G, 3,4);
  addArc(G,4,5);
  addArc(G,5,6);
  addEdge(G,7,8);
  addArc(G,1,8);
  addArc(G,7,2);
  addArc(G,3,1);
  addArc(G,3,8);

  //Fields of G after fill
  printf("\n");
  printGraph(stdout, G);
  printf("\nG Order = %d  // Size = %d\n", getOrder(G), getSize(G));

  //check DFS
  printf("\n=========================================================");
  printf("\n DFS Test to G");
  printf("\n=========================================================");

  //list in ascending order
  printf("\nList Before DFS:\n");
  printList(stdout, S);
  printf("\n");

  DFS(G,S);

  //fields of vertices in G
  fprintf(stdout, "\n");
  fprintf(stdout, "x:   d   f   p\n\n");
  for(int i = 1; i <= getOrder(G); i++){
    fprintf(stdout, "%d: %3d %3d %3d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
  }

  //list after dfs (in descending finish time order)
  printf("\nList After DFS:\n");
  printList(stdout, S);
  printf("\n");

  printf("\n=========================================================");
  printf("\n Copy G Test && DFS of Copy");
  printf("\n=========================================================");

  C = copyGraph(G);

  //stats on copy graph
  printf("\n");
  printGraph(stdout, C);
  printf("\nCOPY Order = %d  // Size = %d\n", getOrder(C), getSize(C));
  printf("*note: copy adds edges exclusively so size is greater..\n");

  //reset list to replicate results from previous
  clear(S);
  for (int i = 1; i <= getOrder(C); i++) 
    append(S,i);
  
  //default list
  printf("\nList Before DFS:\n");
  printList(stdout, S);
  printf("\n");

  DFS(C,S);

  //vertices fields of COPY after DFS
  fprintf(stdout, "\n");
  fprintf(stdout, "x:   d   f   p\n\n");
  for(int i = 1; i <= getOrder(C); i++){
    fprintf(stdout, "%d: %3d %3d %3d\n", i, getDiscover(C, i), getFinish(C, i), getParent(C, i));
  }
  
  //list after dfs (in descending finish time order)
  printf("\nList After DFS:\n");
  printList(stdout, S);
  printf("\n");

  printf("\n=========================================================");
  printf("\n Test Transpose of G Test");
  printf("\n=========================================================");

  Gt = transpose(G);

  //default list
  clear(S);
  for (int i = 1; i <= getOrder(Gt); i++) 
    append(S,i);
  
  printf("\nBefore DFS:\n");
  printList(stdout, S);
  printf("\n");

  //stats on Transpose graph
  printf("\n");
  printGraph(stdout, Gt);
  printf("\nTRANSPOSE Order = %d  // Size = %d\n", getOrder(Gt), getSize(Gt));
  printf("*note: transpose adds edges exclusively so size is greater..\n");

  DFS(Gt,S);

  //vertices fields of Transpose after DFS
  fprintf(stdout, "\n");
  fprintf(stdout, "x:   d   f   p\n\n");
  for(int i = 1; i <= getOrder(Gt); i++){
    fprintf(stdout, "%d: %3d %3d %3d\n", i, getDiscover(Gt, i), getFinish(Gt, i), getParent(Gt, i));
  }

  //list after dfs (in descending finish time order)
  printf("\nList After DFS:\n");
  printList(stdout, S);
  printf("\n");

  printf("\n=========================================================");
  printf("\n New Graph 'R'");
  printf("\n=========================================================");

  int m = 4;
  Graph R = newGraph(m);

  printf("\nNew Graph..\n");

  printGraph(stdout, R);
  printf("\nR Order = %d  // Size = %d\n", getOrder(R), getSize(R));

  printf("\n=========================================================");
  printf("\n Bounds Checking addEdge of 'R' by adding vertices [0,m+1]");
  printf("\n=========================================================");

  //check bounds/ graph size when adding edges
  for ( int i = 0; i < m+1; i++) {
    for (int j = 0; j < m+1; j++) {
      addEdge(R, i,j);
    }
  }

  printf("\n");
  printGraph(stdout, R);
  printf("\nR Order = %d  // Size = %d\n", getOrder(R), getSize(R));

  printf("\n=========================================================");
  printf("\n Checking for Dupes.. Repeating Populating last test");
  printf("\n\n Test DFS on a List that doesnt match Graph vertices ");
  printf("\n=========================================================");

  //check bounds/ graph size when adding edges
  for ( int i = 0; i < m+1; i++) {
    for (int j = 0; j < m+1; j++) {
      addEdge(R, i,j);
    }
  }
  printf("\n");
  printGraph(stdout, R);
  printf("\nR Order = %d  // Size = %d\n", getOrder(R), getSize(R));

  DFS(R,Asym);

  printf("\n=========================================================");
  printf("\nNullify Graphs ");
  printf("\n=========================================================");

  makeNull(G);
  printf("\n(G) Order = %d  // Size = %d\n", getOrder(G), getSize(G));
  printGraph(stdout, G);
  
  makeNull(C);
  printf("\n(C) Order = %d  // Size = %d\n", getOrder(C), getSize(C));
  printGraph(stdout, C);

  makeNull(Gt);
  printf("\n(Gt) Order = %d  // Size = %d\n", getOrder(Gt), getSize(Gt));
  printGraph(stdout, Gt);

  makeNull(R);
  printf("\n(R) Order = %d  // Size = %d\n", getOrder(R), getSize(R));
  printGraph(stdout, R);

  printf("\n=========================================================");
  printf("\n Bounds Checking addArc of 'R' by adding vertices [0,m+1]");
  printf("\n=========================================================");

  //check bounds/ graph size when adding arcs
  for ( int i = 0; i < m+1; i++) {
    for (int j = 0; j < m+1; j++) {
      addArc(R, i,j);
    }
  }

  printf("\nR Order = %d  // Size = %d\n", getOrder(R), getSize(R));
  printGraph(stdout, R);

  printf("\n=========================================================");
  printf("\nNullify & Freeing Graphs ");
  printf("\n=========================================================");

  makeNull(R);
  makeNull(G);
  makeNull(Gt);
  makeNull(C);

  free(R);
  free(G);
  free(Gt);
  free(C);

   return(0);
}
