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

//input the first Big Int
//=================================================

  fscanf(in, "%d\n", &len);
  char str[len+1];
  fscanf(in, "%s\n", str );
  BigInteger A = stringToBigInteger(str);

  printBigInteger(out, A); fprintf(out, "\n\n");
  
//input the second Big Int
//=================================================

  fscanf(in, "%d\n", &len);
  char str2[len+1];
  fscanf(in, "%s\n", str2 );
  BigInteger B = stringToBigInteger(str2);

// Arithmetic
//=================================================

  printBigInteger(out, B); fprintf(out, "\n\n");

  BigInteger S = sum(A,B);  //A+B
  printBigInteger(out, S); fprintf(out, "\n\n");

  S = diff(A,B);            //A-B
  printBigInteger(out, S); fprintf(out, "\n\n");

  S = diff(A,A);            //A-A
  printBigInteger(out, S); fprintf(out, "\n");


  return 0;
}
