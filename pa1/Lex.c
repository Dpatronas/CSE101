/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa1
* ListClient.c
* Test client for List ADT
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

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
  List lex = newList();
  append(lex, *tok_arr[0]);
  
  // //step through indices of array
  for (int i = 1; i < line_count; i++) {
    int curr_len = length(lex);
    moveFront(lex);

    //inner loop to iterate through linked list
    for (int j = 0; j < curr_len; j++) {
      
      if ( strcmp( tok_arr[i], tok_arr[index(lex)] ) < 0)  {
        
        if ( get(lex) >= *tok_arr[index(lex)]) {
            insertBefore(lex, *tok_arr[i]);
            //if prepend occurs, exit the inner loop
            j = curr_len + 1;
        }
      }

      else {
        //step to next element in cursor
        moveNext(lex);

        //if cursor becomes undefined then we are at back of list.. append
        if ( get(lex) == -1 ) {
          append(lex, *tok_arr[i]);
          continue;
        }
      }
    }
  }

  //print the final list
  front(lex);

  for (int i = 0; i < length(lex); i++) {
    fprintf(out, "%s ", tok_arr[index(lex)]);
    moveNext(lex);
  }

  //cleanup
  for (int j = 0; j < line_count; j++) {
    free(tok_arr[j]);
    tok_arr[j]=NULL;
  }
  
  *tok_arr = NULL;
  clear(lex);
  lex = NULL;

  fclose(in);
  fclose(out);

  return(0);
}
