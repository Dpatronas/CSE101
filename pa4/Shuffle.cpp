#include<iostream>
#include<fstream>
#include<string>
#include "List.h"

using namespace std;

// returns whether n has even or odd elements
// Note: if n is odd, its elements are even 
bool odd_Elem(int n) {
  if (n % 2 == 0) {
    return 1;
  }
  else return 0;
}

// returns the amount of shuffles to obtain the original deck
// from "perfect shuffling"
int shuffle (int n) {

  int shuffles = 0; //keeps track of the shuffles to get back to original list

  List O; //original deck
  List S; //second list, small # elements
  List B; //third list big # elements
  List M; //the merged list

  //populate original list 
  for (int i = 0; i <= n; i++) {
    O.insertBefore(i);
  }

  //set Merged list as original for iteration of initial list
  M = O; 


  while(1) { //keep looping until original is found

    M.moveFront();
    //SPLIT deck into 2 Lists (steps through the merged list)
    for (M.position(); M.position() <= n; M.moveNext() ) {

      //Set first half of list (Odd elements)
      if (odd_Elem(n) && M.position() < n/2) {   //n/2 is floored
        S.insertBefore( M.peekNext() );
        continue;
      }
      //Set first half of list (Even elements)
      else if (!odd_Elem(n) && M.position() <= n/2) {  
        S.insertBefore( M.peekNext() );
        continue;
      }
      //Set second half of list
      B.insertBefore (M.peekNext() );    
    }
    //Set position to front for both split lists and clear old Merged List for new values
    S.moveFront(); B.moveFront(); M.clear();                          

    //MERGE 
    // alterate between big and small split lists
    for (int i = 0; i < n/2; i++) {
      M.insertBefore(B.moveNext());
      M.insertBefore(S.moveNext());
    }
    //final card for odd deck
    if (odd_Elem(n)) {
      M.insertBefore(B.moveNext());
    }
    //final pair of cards for even deck
    if (!odd_Elem(n)) {
      M.insertBefore(B.moveNext());
      M.insertBefore(S.moveNext());
    }

    shuffles++;
    S.clear(); B.clear();     //clear split lists in all cases

    //exit condition Merged == Original list elements
    if (O.equals(M)) {
      O.clear(); M.clear();  //clear original and merged list before leaving
      return shuffles;
    }
  }
  return -1;
}

int main(int argc, char * argv[]) {

  // check command line for correct number of arguments
  if( argc != 2 ){
    cerr << "Usage: " << argv[0] << " <number n>" << endl;
    return(EXIT_FAILURE);
  }
  //grab the size of n as the argument
  int n = atoi(argv[1]);
  if (n <= 0) {
    cerr << "No deck to shuffle!";
    return(EXIT_FAILURE);
  }

  cout << "deck size       shuffle count" << endl;
  cout << "------------------------------" << endl;

  for (int i = 1; i <= n; i++ ) {
    printf(" %-15d %d\n", i, shuffle(i-1));
  }

  return(EXIT_SUCCESS);
}
