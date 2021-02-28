//-----------------------------------------------------------------------------
// Despina Patronas, Dpatrona
// 2021 Winter CSE 101 pa6
//
// Order.c
// Determines frequency of each word in a file.
//
// Usage: Order <input file> <output file>
//
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"Dictionary.h"

#define MAX_LEN 300


int main(int argc, char* argv[]){

  Dictionary D = newDictionary(0); // unique keys
  FILE* in = NULL;
  FILE* out = NULL;
  int token_count;
  int line_count = 1;
  char line[MAX_LEN];
  char tokenBuffer[MAX_LEN];
  char* token;
  int i = 0;


  // check command line arguments 
  if( argc != 3 ){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // open input file 
  in = fopen(argv[1], "r");
    if( in==NULL ){
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }

  // open output file
  out = fopen(argv[2], "w");
  if( out==NULL ){
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  // read the lines in input file
  do {
    int read_char = fgetc(in);
    if(read_char == '\n') {
      line_count++;
    }
  } while(!feof(in));

  //reset the file pointer
  rewind(in);

  //array to hold the strings
  char *tok_arr[line_count];

  while( fgets(line, MAX_LEN, in) != NULL)  {

    // get tokens in this line
    token_count = 0;
    tokenBuffer[0] = '\0';

    // get first token
    token = strtok(line, " \n");

    while( token!=NULL ){ // we have a token
      // update token buffer
      strcat(tokenBuffer, token);
      strcat(tokenBuffer, " ");
      token_count++;

      // get next token
      token = strtok(NULL, " \n");
    }
    //allocate space for each string as an element of the array
    tok_arr[i] = strcpy(malloc(strlen(tokenBuffer) +1),tokenBuffer);
    i++;
  }
  int p = 1;
  int *ptr = &p;

  for(i = 0; i < line_count-1; i++) {
    insert( D, tok_arr[i], ++ptr );
  }

  fprintf(out,"******************************************************");
  fprintf(out,"\nPRE-ORDER:");
  fprintf(out,"\n******************************************************\n");

  printDictionary(out, D, "pre");

  fprintf(out,"\n\n******************************************************");
  fprintf(out,"\nIN-ORDER:");
  fprintf(out,"\n******************************************************\n");

  printDictionary(out, D, "in");

  fprintf(out,"\n\n******************************************************");
  fprintf(out,"\nPOST-ORDER:");
  fprintf(out,"\n******************************************************\n");

  printDictionary(out, D, "post");

  fprintf(out, "\n\n");

  // free resources
  freeDictionary(&D);

  token = NULL;
  ptr = NULL;
  fclose(in);
  fclose(out);

  return(0);
}
