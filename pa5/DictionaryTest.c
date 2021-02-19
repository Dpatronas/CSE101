#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dictionary.h"

int main() { 

  //random words
  char* word[] = { "nulls","zebra","wick","koy","imp","cross","list","dictionary","trie","alt","enter","yin","bool","hat","vent","fan","string","mix","xor","return", "ocarina","uint_8t","ping","get","jump","querie" };

  //random words2 with some dupes
  char* word2[] = { "next","zebra","while","koy","int","calloc","lldb","do","trie","array","exception","yordle","bool","homebrew","valgrind","for","std","malloc","x86","riscv", "ocarina","unsigned","print","gdb","jump","querie" };

printf("=========================================================");
printf("\n Default Dictionary Check Unique:A | Non Unique:B");
printf("\n=========================================================");

  Dictionary A = newDictionary(1);
  Dictionary B = newDictionary(0);

  printf("\n\n\tA: No Dupes");
  printDictionary(stdout, A);
  printf("\n Size       A: %d",       size(A));
  printf("\n Unique     A: %d",  getUnique(A));
  printf("\n currentKey A: %s", currentKey(A));
  printf("\n currentVal A: %d", currentVal(A));

  printf("\n\n\tB: Duplicates Allowed");
  printDictionary(stdout, B);
  printf("\n Size       B: %d",       size(B));
  printf("\n Unique     B: %d",  getUnique(B));
  printf("\n currentKey B: %s", currentKey(B));
  printf("\n currentVal B: %d", currentVal(B));

  printf("\n\nMake empty on empty dictionary A and B: ");
  makeEmpty(A);
  makeEmpty(B);

printf("\n\n=========================================================");
printf("\n Iterate cursor on Default Dictionaries");
printf("\n=========================================================");
  
  printf("\n\n Begin Forward on A %d",beginForward(A) );
  printf("\n Begin Reverse on B %d",beginReverse(B) );
  printf("\n MoveNext on A %d", next(A) );  
  printf("\n MovePrev on B %d", prev(B) );

printf("\n\n=========================================================");
printf("\n Populate both Dictionaries with all words");
printf("\n=========================================================");
  
  for (int i = 0; i < 26; i++) {
    insert(A,word[i], i);
    insert(A,word2[i], i);
  }

  printf("\n\n\tA: NO DUPES\n\n");
  printDictionary(stdout, A);
  printf("\n Size A: %d",       size(A));

  for (int i = 0; i < 26; i++) {
    insert(B,word[i], i);
    insert(B,word2[i], i);
  }

  printf("\n\n\tB: DUPLICATES ALLOWED \n\n");
  printDictionary(stdout, B);
  printf("\n Size B: %d",       size(B));
  
printf("\n\n=========================================================");
printf("\n Lookup keys that do and dont exist");
printf("\n=========================================================");

  printf("\nA Lookup: \n'hi' %d\n'ocarina' %d", lookup(A,"hi"), lookup(A,"ocarina"));
  printf("\n\nB Lookup: \n'xor' %d\n'bye' %d", lookup(B,"xor"), lookup(B,"bye"));

printf("\n\n=========================================================");
printf("\n Start front Iteration A (including out of bounds check) ");
printf("\n=========================================================");
  
  beginForward(A);
  printf("\n\tBEGIN FORWARD\n currentKey A: %s", currentKey(A));
  printf("\n currentVal A: %d\n\n", currentVal(A));
    
  printf("\tmoving next..\n");
  for (int i = 0; i < size(A) ; i++) {
    VAL_TYPE x = next(A);
    printf("key: "KEY_FORMAT" \t\t\tvalue: "VAL_FORMAT"\n", currentKey(A), x);
  }
    
  beginForward(A);
  printf("\n\tBEGIN FORWARD\n currentKey A: %s", currentKey(A));
  printf("\n currentVal A: %d\n", currentVal(A));

  VAL_TYPE x = prev(A);
  printf("\n\tMove prev\n currentKey A: %s", currentKey(A));
  printf("\n currentVal A: %d", currentVal(A));


printf("\n\n=========================================================");
printf("\n Start back Iteration B (including out of bounds check) ");
printf("\n=========================================================");

  beginReverse(B);
  printf("\n\tBEGIN REVERSE\n currentKey B: %s", currentKey(B));
  printf("\n currentVal B: %d\n\n", currentVal(B));
    
  printf("\tmoving prev..\n");
  for (int i = 0; i < size(B) ; i++) {
    VAL_TYPE x = prev(B);
    printf("key: "KEY_FORMAT" \t\t\tvalue: "VAL_FORMAT"\n", currentKey(B), x);
  }

printf("\n\n=========================================================");
printf("\n A: Delete words in loop & delete words2 with makeEmpty ");
printf("\n=========================================================\n\n");

  printDictionary(stdout, A);
  printf("\n\tDelete words from first word list in A\n\n");
  for (int i = 0; i < 26; i++) {
    delete(A,word[i]);
  }
  printDictionary(stdout, A);
  printf("\n Size A: %d\n",       size(A));

  printf("\n\tMake A Empty..\n");
  makeEmpty(A);
  printDictionary(stdout, A);
  printf("\n Size A: %d",       size(A));
  printf("\n currentKey A: %s", currentKey(A));
  printf("\n currentVal A: %d", currentVal(A));

printf("\n\n=========================================================");
printf("\n Delete Everything using Cursor in B) ");
printf("\n=========================================================\n\n");

  printDictionary(stdout, B);

  beginForward(B);
  printf("\n\tBEGIN FORWARD\n currentKey B: %s", currentKey(B));
  printf("\n currentVal B: %d\n", currentVal(B));

  KEY_TYPE y = currentKey(B); //front key
  while(y != KEY_UNDEF) {
    delete(B,y);              //delete front
    beginForward(B);          //reset front
    y = currentKey(B);        //assign new front key
  }
  printf("\n\tDelete keys using cursor from B");
  printDictionary(stdout, B);
  printf("\n Size A: %d",       size(A));
  printf("\n currentKey A: %s", currentKey(A));
  printf("\n currentVal A: %d", currentVal(A));

  freeDictionary(&A);
  freeDictionary(&B);

  return 0;
}
