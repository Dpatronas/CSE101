/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa7
* Arithmetic.c
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "BigInteger.h"

#define MAX_LEN 300

int main(int argc, char * argv[]) {

  int len = 0;
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

  BigInteger A; 
  BigInteger B;
  BigInteger S; 
  BigInteger P; 
  BigInteger Z;

//input the first Big Int
//=================================================

  fscanf(in, "%d\n", &len);
  char str[len+1];
  fscanf(in, "%s\n", str );
  A = stringToBigInteger(str);
  printBigInteger(out, A); fprintf(out, "\n\n");
  
//input the second Big Int
//=================================================

  fscanf(in, "%d\n", &len);
  char str2[len+1];
  fscanf(in, "%s\n", str2 );
  B = stringToBigInteger(str2);

  printBigInteger(out, B); fprintf(out, "\n\n");

// Arithmetic
//=================================================

  //A+B
  S = sum(A,B);  
  printBigInteger(out, S); fprintf(out, "\n\n");

  //B-A
  S = diff(A,B); 
  printBigInteger(out, S); fprintf(out, "\n\n");

  //A-A
  S = diff(A,A); 
  printBigInteger(out, S); fprintf(out, "\n\n");

  //scalars
  BigInteger Two   = stringToBigInteger("2");
  BigInteger Three = stringToBigInteger("3");
  // BigInteger Nine  = stringToBigInteger("9");
  // BigInteger SixT  = stringToBigInteger("16");

  P = prod(Three,A);  // 3A
  Z = prod(Two, B);   // 2B

  //3A-2B
  S = diff(P,Z);      
  printBigInteger(out, S); fprintf(out, "\n\n");

  // A*B 
  P = prod(A,B);    
  printBigInteger(out, P); fprintf(out, "\n\n");

  // Z = prod(A,A);      // A*A = A^2
  // printBigInteger(out, Z); fprintf(out, "\n\n");

  // P = prod(B,B);      // B*B = B^2
  // printBigInteger(out, P); fprintf(out, "\n\n");

  // Z = prod(Z,Z);      // A^2*A^2 = A^4
  // Z = prod(Nine,Z);   // 9A^4
  // printBigInteger(out, Z); fprintf(out, "\n\n");

  // P = prod(P,P);      //B^2*B^2 = B^4
  // P = prod(P,B);      //B^4*B   = B^5
  // S = sum(Z,P);

  freeBigInteger(&A);
  freeBigInteger(&B);
  freeBigInteger(&S);
  freeBigInteger(&P);
  freeBigInteger(&Z);
  freeBigInteger(&Two  );
  freeBigInteger(&Three);
  // freeBigInteger(&Nine );
  // freeBigInteger(&SixT );

  fclose(in);
  fclose(out);

  return 0;
}
