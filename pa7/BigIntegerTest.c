/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa7
* BigIntegerTest.c

Tests the function of the ADT
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "BigInteger.h"
#include "List.h"

int main () {

  char str1[] = "123456";
  char str2[] = "12345";
  char str3[] = "98765";

  printf("\n\n=========================================================");
  printf("\n Populate Big Integer A & Big Integer B");
  printf("\n=========================================================");

  BigInteger A = newBigInteger();
  printf("\nDefault A->sign = %d", sign(A));
  // printBigInteger(stdout, A); //exit(1)
  A = stringToBigInteger(str1);
  printf("\nA = ");
  printBigInteger(stdout, A); printf("    ->sign = %d", sign(A));
  printf("\n");

  BigInteger B = stringToBigInteger(str2);
  printf("\nB = ");
  printBigInteger(stdout, B); printf("    ->sign = %d", sign(B));
  printf("\n");

  printf("\n=========================================================");
  printf("\n Negate B");
  printf("\n=========================================================");

  negate(B);
  printf("\nB = ");
  printBigInteger(stdout, B); printf("    ->sign = %d", sign(B));
  printf("\n");

  printf("\n=========================================================");
  printf("\n (ADD A+ -B)" );
  printf("\n=========================================================");

  printf("\n  A = ");
  printBigInteger(stdout, A);
  printf("\n+ B = ");
  printBigInteger(stdout, B);

  printf("\n -----------");
  
  BigInteger C = newBigInteger();
  add(C, A, B);  
  printf("\n C = ");
  printBigInteger(stdout, C); printf("    ->sign = %d", sign(C));
  printf("\n");

  printf("\n=========================================================");
  printf("\n (ADD -A + -B)" );
  printf("\n=========================================================");

  negate(A);
  negate(C);

  printf("\n  A = ");
  printBigInteger(stdout, A);
  printf("\n+ B = ");
  printBigInteger(stdout, B);

  printf("\n -----------");

  BigInteger D = newBigInteger();
  add(D, A, B); 
  printf("\n D = ");
  printBigInteger(stdout, D); printf("    ->sign = %d", sign(D));
  printf("\n");

  printf("\n=========================================================");
  printf("\n (ADD -A + D)" );
  printf("\n=========================================================");

  printf("\n  A = ");
  printBigInteger(stdout, A);
  printf("\n+ D = ");
  printBigInteger(stdout, D);

  printf("\n -----------");

  BigInteger E = newBigInteger();
  add(E, A, D); 
  printf("\n E = ");
  printBigInteger(stdout, E); printf("    ->sign = %d", sign(E));
  printf("\n");

  printf("\n=========================================================");
  printf("\n (ADD S = +A + +A)" );
  printf("\n=========================================================");

  negate(A);
  printf("\n  A = ");
  printBigInteger(stdout, A);  
  printf("\n+ A = ");
  printBigInteger(stdout, A);
  printf("\n -----------");

  BigInteger S = newBigInteger();
  add(S, A, A); 
  printf("\n S = ");
  printBigInteger(stdout, S); printf("    ->sign = %d", sign(S));
  printf("\n");

  printf("\n=========================================================");
  printf("\n (Sum S = +F + -C) where F == C" );
  printf("\n=========================================================");

  BigInteger F = newBigInteger();
  F = stringToBigInteger("111111");

  printf("\n  F = ");
  printBigInteger(stdout, F);  
  printf("\n+ C = ");
  printBigInteger(stdout, C);
  printf("\n -----------");

  S = sum(F,C); 
  printf("\n S = ");
  printBigInteger(stdout, S); printf("    ->sign = %d", sign(S));
  printf("\n");

  printf("\n=========================================================");
  printf("\n (Sum S = +F + -C) where F == C" );
  printf("\n=========================================================");

  negate(C);

  printf("\n  F = ");
  printBigInteger(stdout, F);  
  printf("\n+ C = ");
  printBigInteger(stdout, C);
  printf("\n -----------");

  S = sum(F,C); 
  printf("\n S = ");
  printBigInteger(stdout, S); printf("    ->sign = %d", sign(S));
  printf("\n");

  printf("\n=========================================================");
  printf("\n Check Equals" );
  printf("\n=========================================================");

  printf("\nF == C is %s\n", equals(F, C)?"true":"false");
  printf("A == A is %s\n", equals(A, A)?"true":"false");
  negate(F);
  printf("-F == C is %s\n", equals(F, C)?"true":"false");

  printf("\n=========================================================");
  printf("\n Check Add on large number with carry" );
  printf("\n=========================================================");

  A = stringToBigInteger("123456789123456789");
  B = stringToBigInteger("987654321");

  printf("\n  A = ");
  printBigInteger(stdout, A);  
  printf("\n+ B = 000000000");
  printBigInteger(stdout, B);
  printf("\n ----------------------");

  S = sum(A,B);
  printf("\n S = ");
  printBigInteger(stdout, S); printf("    ->sign = %d", sign(S));

  printf("\n=========================================================");
  printf("\n (DIFF A - B) where A == B" );
  printf("\n=========================================================");

  A = stringToBigInteger("12345");
  B = stringToBigInteger("12345");

  printf("\n  A = ");
  printBigInteger(stdout, A);  
  printf("\n- B = ");
  printBigInteger(stdout, B);
  printf("\n ----------------------");

  E = diff(A, B);
  printf("\nE = ");
  printBigInteger(stdout, E);
  printf("\n");

  printf("\n=========================================================");
  printf("\n (DIFF A - -B) where A == B" );
  printf("\n=========================================================");

  negate(B);

  printf("\n  A = ");
  printBigInteger(stdout, A);  
  printf("\n- B = ");
  printBigInteger(stdout, B);
  printf("\n ----------------------");

  E = diff(A, B);
  printf("\n  E = ");
  printBigInteger(stdout, E);
  printf("\n");

    printf("\n=========================================================");
  printf("\n (DIFF -A - -B)" );
  printf("\n=========================================================");

  A = stringToBigInteger("-12345");
  B = stringToBigInteger("-12345");

  printf("\n  A = ");
  printBigInteger(stdout, A);  
  printf("\n- B = ");
  printBigInteger(stdout, B);
  printf("\n ----------------------");

  E = diff(A, B);
  printf("\nE = ");
  printBigInteger(stdout, E);
  printf("\n");

  printf("\n=========================================================");
  printf("\n Check Diff on number with carry" );
  printf("\n=========================================================");

  D = stringToBigInteger("-9999");
  A = stringToBigInteger("1000");

  printf("\n  D = ");
  printBigInteger(stdout, D);  
  printf("\n- A = ");
  printBigInteger(stdout, A);
  printf("\n ----------------------");

  S = diff(D, A);
  printf("\nS = ");
  printBigInteger(stdout, S);
  printf("\n");

  printf("\n=========================================================");
  printf("\n (SUB -A - B) " );
  printf("\n=========================================================");

  A = stringToBigInteger("-54321");
  B = stringToBigInteger("54321");

  printf("\n  A = ");
  printBigInteger(stdout, A);  
  printf("\n- B = ");
  printBigInteger(stdout, B);
  printf("\n ----------------------");

  makeZero(E);
  subtract(E,A,B);
  printf("\n  E = ");
  printBigInteger(stdout, E);
  printf("\n");

  printf("\n=========================================================");
  printf("\n (SUB -A - B) where A == B" );
  printf("\n=========================================================");

  A = stringToBigInteger("-54321");
  B = stringToBigInteger("54321");

  printf("\n  A = ");
  printBigInteger(stdout, A);  
  printf("\n- B = ");
  printBigInteger(stdout, B);
  printf("\n ----------------------");

  makeZero(E);
  subtract(E,A,B);
  printf("\n  E = ");
  printBigInteger(stdout, E);
  printf("\n");

  printf("\n=========================================================");
  printf("\n (SUB -A - B) (with a carry)" );
  printf("\n=========================================================");

  A = stringToBigInteger("-99999");
  B = stringToBigInteger("99999");

  printf("\n  A = ");
  printBigInteger(stdout, A);  
  printf("\n- B = ");
  printBigInteger(stdout, B);
  printf("\n ----------------------");

  makeZero(E);
  subtract(E,A,B);
  printf("\n  E = ");
  printBigInteger(stdout, E);
  printf("\n");

  printf("\n=========================================================");
  printf("\n Check Multiply (negative)" );
  printf("\n=========================================================");

  A = stringToBigInteger("-123");
  B = stringToBigInteger("123");

  printf("\n  A = ");
  printBigInteger(stdout, A);  
  printf("\n* B = ");
  printBigInteger(stdout, B);
  printf("\n ----------------------");

  makeZero(E);
  multiply(E,A,B);
  printf("\n  E = ");
  printBigInteger(stdout, E);
  printf("\n");

  printf("\n=========================================================");
  printf("\n Check Multiply (positive)" );
  printf("\n=========================================================");

  A = stringToBigInteger("111111456");
  B = stringToBigInteger("111111456");

  printf("\n  A = ");
  printBigInteger(stdout, A);  
  printf("\n* B = ");
  printBigInteger(stdout, B);
  printf("\n ----------------------");

  makeZero(E);
  multiply(E,A,B);
  printf("\n  E = ");
  printBigInteger(stdout, E);
  printf("\n");

  printf("\n=========================================================");
  printf("\n Check Multiply (0)" );
  printf("\n=========================================================");

  A = stringToBigInteger("0");
  B = stringToBigInteger("111111456");

  printf("\n  A = 0");
  // printBigInteger(stdout, A);
  printf("\n- B = ");
  printBigInteger(stdout, B);
  printf("\n ----------------------");

  E = stringToBigInteger("12345");
  makeZero(E);
  multiply(E,A,B);
  printf("\n  E = 0");
  // printBigInteger(stdout, E);
  printf("\n");

  printf("\n=========================================================");
  printf("\n Check Prod (0)" );
  printf("\n=========================================================");

  A = stringToBigInteger("0");
  B = stringToBigInteger("111111456");

  printf("\n  A = 0");
  // printBigInteger(stdout, A);  
  printf("\n- B = ");
  printBigInteger(stdout, B);
  printf("\n ----------------------");

  makeZero(E);
  E = prod(A,B);
  printf("\n  E = 0");
  // printBigInteger(stdout, E);
  printf("\n");


  printf("\n=========================================================");
  printf("\n Check Prod (+)" );
  printf("\n=========================================================");

  A = stringToBigInteger("7657567");
  B = stringToBigInteger("111111456");

  printf("\n  A = ");
  printBigInteger(stdout, A);  
  printf("\n* B = ");
  printBigInteger(stdout, B);
  printf("\n ----------------------");

  makeZero(E);
  E = prod(A,B);
  printf("\n  E = ");
  printBigInteger(stdout, E);
  printf("\n");

  printf("\n=========================================================");
  printf("\n Check Prod Scalar (-1)" );
  printf("\n=========================================================");

  A = stringToBigInteger("-1");
  B = stringToBigInteger("111111456");

  printf("\n  A = ");
  printBigInteger(stdout, A);  
  printf("\n* B = ");
  printBigInteger(stdout, B);
  printf("\n ----------------------");

  makeZero(E);
  E = prod(A,B);
  printf("\n  E = ");
  printBigInteger(stdout, E);
  printf("\n");

  freeBigInteger(&A);
  freeBigInteger(&B);
  freeBigInteger(&C);
  freeBigInteger(&D);
  freeBigInteger(&E);
  freeBigInteger(&F);
  freeBigInteger(&S);

}

