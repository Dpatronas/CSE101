//-----------------------------------------------------------------------------
// Despina Patronas, Dpatrona
// 2021 Winter CSE 101 pa7
//
// ListTest.cpp
// A test client for new List ADT
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>

#include"List.h"

//function to print info on list status
void printStuff(List L, char S) {
  printf( "\n size (%c) = %ld", S, length(L));
  printf( "\n index(%c) = %ld", S, index1(L));
  printf( "\n front(%c) = %ld", S,  front(L));
  printf( "\n back (%c) = %ld", S,   back(L));
  printf( "\n get  (%c) = %ld\n", S,get(L));

  printf("\n LIST (%c): ", S); printList(stdout, L); printf("\n\n");
}

int main() {

  List A = newList();
  List B = newList();
  List C = newList();
  List D = newList();
  List E = newList();

printf("=========================================================");
printf("\n Default List Check (List A)");
printf("\n=========================================================");

  printStuff(A,'A');
  printList(stdout, A);

printf("\n=========================================================");
printf("\n Prepend Default no defined cursor (List A)");
printf("\n=========================================================");

  for (int i = 1; i <= 10; i++) {
    prepend(A, i);
  }
  printStuff(A,'A');

printf("\n\n=========================================================");
printf("\n Append Default no defined cursor (List B)");
printf("\n=========================================================");

  for (int i = 1; i <= 10; i++) {
    append(B,i);
  }
  printStuff(B,'B');

printf("\n\n=========================================================");
printf("\n Cursor Tests on List A and B");
printf("\n=========================================================");

  moveFront(A);
  printf("\nCursor movefront get(A)= %ld ", get(A));
  moveBack(B);
  printf("\nCursor moveback  get(B)= %ld ", get(B));
  moveFront(C);

  printf("\nCursor movefront (empty list) get(C)= %ld ", get(C));
  moveBack(D);
  printf("\nCursor moveback  (empty list) get(D)= %ld ", get(D));

  set(A, 131);
  printf("\n\n Set(A) 131 get(A)= %ld ", get(A));
  set(B, 99);
  printf("\n Set(B) 99  get(B)= %ld ", get(B));

  set(C, 100);
  printf("\n Set(C) 100 (undefined cursor) get(C)= %ld \n\n", get(C));

printf("=========================================================");
printf("\n MovePrev / MoveNext & InsertAfter / InsertBefore (List C)");
printf("\n=========================================================");

  append(C,9);
  moveFront(C);

  for (int i = 2; i <= 8; i+=2) {
    printf("\n LIST: "); printList(stdout, C);
    printf("\n Inserting %d after %ld", i, get(C));
    insertAfter(C, i);
    printf("\t New Cursor = %ld\n\n LIST: ", get(C));
    printList(stdout, C);

    if (i == 4 || i == 8) {
      
      printf("\n Inserting %d before %ld", i+10, get(C));
      insertBefore(C,i+10);
      printf("\t New Cursor = %ld", get(C));
      moveNext(C);
      printf("\n move Cursor next = %ld\n\n", get(C));
    }
  }
  printStuff(C,'C');

printf("=========================================================");
printf("\n Delete front and back and clear(List C)");
printf("\n=========================================================");

  printf("\nDeleting front (%ld) and back (%ld)", front(C), back(C));
  deleteFront(C);
  deleteBack(C);
  printStuff(C,'C');

  printf("\nMake C empy");
  clear(C);
  printStuff(C,'C');

printf("=========================================================");
printf("\n Set moving List out of bounds A");
printf("\n=========================================================");

  moveFront(A);
  printStuff(A, 'A');

  for (int i = 0; i < length(A)+1; i++ ) {
    printf("\nSet index %ld to %d", index1(A), i );
    set(A, i);
    printf(" \tLIST: "); printList(stdout, A);
    moveNext(A);
    printf(" \t moveNext index = %ld", index1(A) );
  }
  moveBack(A);
  printf("\n\nmoveBack index = %ld", index1(A) );

  for (int i = 0; i < length(A)+1; i++ ) {
    printf("\n Set index %ld to %d", index1(A), i );
    set(A, i);
    printf("\t LIST: "); printList(stdout, A);
    movePrev(A);
    printf("\t movePrev index = %ld", index1(A) );
  }

printf("\n\n=========================================================");
printf("\n Check Concat and Copy");
printf("\n=========================================================\n");

  printStuff(A,'A');
  printStuff(B,'B');

  printStuff(D,'D');

  printf("\n Set LIST D = A + B"); 
  D = concatList(A, B);
  printStuff(D,'D');

  printStuff(C,'C');
  printf("\n Set LIST C as Copy of List D"); 

  C = copyList(D);
  printStuff(C,'C');


printf("=========================================================");
printf("\n Check delete Cursor ");
printf("\n===========================================================");
  
  printStuff(D,'D');
  printf("Deleting front List D\n"); 

  moveFront(D);
  int len = length(D);
  for (int i = 0; i < len; i++) {
    delete(D);
    moveFront(D);
    printStuff(D,'D');
  }


  printStuff(C,'C');
  printf("Deleting back List D\n"); 

  moveBack(C);
  len = length(C);

  for (int i = 0; i < len; i++) {
    delete(C);
    moveBack(C);
    printStuff(C,'C');
  }

  clear(A);
  clear(B);
  clear(C);
  clear(D);

  delete(A);
  delete(B);
  delete(C);
  delete(D);
  delete(E);

  return (0);
}
