//-----------------------------------------------------------------------------
// Despina Patronas, Dpatrona
// 2021 Winter CSE 101 pa4
//
// ListClient.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

void printStuff( List &X, char S) {

  cout << endl << S << " = " << X << endl;
  printf( "\n%c.size()     = %d", S, X.size());
  printf(" | %c.isEmpty()  = %s", S, (X.isEmpty()) ? "Yes":"Nope" );
  printf( "\n%c.position() = %d", S, X.position());
  printf( "\n%c.peekNext() = %d", S, X.peekNext());
  printf( "\n%c.moveNext() = %d", S, X.moveNext());

  printf( "\n%c.peekPrev() = %d", S, X.peekNext());
  printf( "\n%c.movePrev() = %d\n\n", S, X.movePrev());
}

int main() {

  List A, B, C, D, E;

printf("=========================================================");
printf("\n Default List Check (List A)");
printf("\n=========================================================");

  printStuff(A,'A');

printf("=========================================================");
printf("\n InsertBefore Default (List A)");
printf("\n=========================================================");

   for (int i = 1; i <= 10; i++) {
      A.insertBefore(i);
   }
  printStuff(A,'A');

printf("=========================================================");
printf("\n InsertAfter Default (List B)");
printf("\n=========================================================");

   for (int i = 1; i <= 10; i++) {
      B.insertAfter(i);
   }

  printStuff(B,'B');

printf("=========================================================");
printf("\n MovePrev / MoveNext & InsertAfter / InsertBefore (List C)");
printf("\n=========================================================");

  for (int i = 0; i <= 8; i+=2) {
    C.insertAfter(i);

    for (int i = 2; i <= 3; i+=1) {
      C.insertBefore(i);
      C.moveNext();
      printStuff(C,'C');
    }
  }

printf("=========================================================");
printf("\n Clean Up (List C)");
printf("\n=========================================================");
  
  C.cleanup();
  printStuff(C,'C');

printf("=========================================================");
printf("\n Peek / moving List out of bounds C");
printf("\n=========================================================");

  C.moveFront();
  cout << endl;
  for (int i = 0; i < C.size()+1; i++ ) {
    cout << " Peek: " << C.peekNext() << endl;
    cout << "moveNext " << C.moveNext() << endl;
  }
  cout << endl << "move back... " << endl;
  for (int i = 0; i < C.size()+1; i++ ) {
    cout << " Peek: " << C.peekPrev() << endl;
    cout << "movePrev " << C.movePrev() << endl;
  }

printf("=========================================================");
printf("\n Check equal and Concat (List A and List C -> List D)");
printf("\n=========================================================");

  printStuff(A,'A');
  printStuff(B,'B');

  cout << endl << "A==B is " << (A == B ? "true" : "false") << endl;
  D = A.concat(B);
  printStuff(D,'D');

printf("=========================================================");
printf("\n Check eraseAfter (List D)");
printf("\n=========================================================");

  for (int i = 0; i < 10; i++) {
    D.eraseAfter();
    printStuff(D,'D');
  }

printf("=========================================================");
printf("\n Check Equals");
printf("\n=========================================================");

  cout << endl << "A == B is " << (A == B ? "true" : "false") << endl;
  cout << endl << "A == D is " << (A == D ? "true" : "false") << endl;
  cout << endl << "B == D is " << (B == D ? "true" : "false") << endl;

  printStuff(A,'A');
  printStuff(B,'B');
  printStuff(D,'D');

printf("=========================================================");
printf("\n Find Next / erase before existing and non existing items");
printf("\n=========================================================");

  printStuff(B,'B');

  cout << "Existant B.findNext(5) = " << B.findNext(5) << endl;
  B.eraseBefore();

  cout << "Non existant B.findNext(5) = " << B.findNext(5) << endl;
  B.eraseBefore();

  printStuff(B,'B');

  for (int i = 0; i < 5; i++) {
    B.eraseBefore();
  }

  printStuff(B,'B');

printf("=========================================================");
printf("\n Find Prev and erase after existing and non existing items");
printf("\n=========================================================");

  printStuff(B,'B');

  cout << "B.findPrev(10) = " << B.findPrev(10) << endl;
  B.eraseAfter();

  cout << "B.findPrev(10) = " << B.findPrev(10) << endl;
  B.eraseAfter();

  printStuff(B,'B');

  cout << "\n\n*Note edge cases violating preconditions such as eraseBefore/After on dummy nodes cause exit_Failures..";

printf("\n\n=========================================================");
printf("\n Clear all lists");
printf("\n=========================================================");

  A.clear();
  B.clear();
  C.clear();
  D.clear();
  printStuff(A,'A');
  printStuff(B,'B');
  printStuff(C,'C');
  printStuff(D,'D');

   return (0);
}
