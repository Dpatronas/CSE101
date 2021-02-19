/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa5
* Lex.c
    IO operations
    Creates a string array populated by the lines of:
    infile input strings as its elements
    creates an empty list which is populated lexicographically by:
    using the functions within List.h
    outfile output as sorted strings
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){
  int token_count;
  int line_count =1;
  char line[MAX_LEN];
  char tokenBuffer[MAX_LEN];
  char* token;
  int i = 0;

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

  //make the empty list
  Dictionary Lex = newDictionary(1);

   for(i = 0; i < line_count-1; i++){
      insert(Lex, tok_arr[i], i);
   }
   //print the list inOrder
   printDictionary(out, Lex);
  
  makeEmpty(Lex);
  freeDictionary(&Lex);
  return(0);
}
