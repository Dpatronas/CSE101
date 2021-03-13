/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa7
* BigInteger.c

*********************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "List.h"
#include "BigInteger.h"

#define POWER 9           //note default p = 9
#define BASE pow(10,POWER) //note default b = 1,000,000,000

// Exported type  -------------------------------------------------------------

// BigInteger reference type
typedef struct BigIntegerObj {
  int sign;           //0 = default state w/ empty List
  List mag;           //list element is unsigned long: [0,base]

} BigIntegerObj;

// Constructors-Destructors --------------------------------------------------- 
// newBigInteger() 
// Returns a reference to a new BigInteger object in the zero state. 
BigInteger newBigInteger() {
  BigInteger B = malloc(sizeof(BigIntegerObj));
  if (!B) 
    exit(1);
  B->sign = 0;
  // List mag = newList();
  return B;
}

// freeBigInteger() 
// Frees heap memory associated with *pN, sets *pN to NULL. 
void freeBigInteger(BigInteger* pN) {
  if (pN && *pN) {
    free(*pN);
    pN = NULL;
  }
}

// Access functions ----------------------------------------------------------- 

// sign() 
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero state. 
int sign(BigInteger N) {
  return N->sign;
}

// compare() does not look at signs
// (-1) if A<B, 
// (1)  if A>B, ||  0 if A=B. 
int compare(BigInteger A, BigInteger B) {

  if (!A || !B)
    exit(1);

  //check A == B
  if (listEQ(A->mag,B->mag))
    return 0;

  //diff lengths
  if ((A->mag->length) > (B->mag->length)) 
    return 1;
  
  else if ((A->mag->length) < (B->mag->length)) 
    return -1;
  
  //same lengths
  int ret = 0;
  Node N = A->mag->front; //N = A elemnt
  Node M = B->mag->front; //M = B elemnt

  //go through list starting at the highest digits comparing values
  while (ret == 0 && N) {
    if (N->data > M->data)       //A > B
      ret = 1;

    else if (N->data < M->data)  //A < B
      ret = -1;
    N = N->next; M = M->next;
  }
  return ret;
}

// equals() 
// Return true (1) if A and B are equal, false (0) otherwise. 
int equals(BigInteger A, BigInteger B) {
  if (!A || !B)
    exit(1);

  //first check the length and sign matches
  if ( (A->mag->length != B->mag->length) || (A->sign != B->sign)) 
    return 0;
  
  //should be one now
  int ret = (A->mag->length == B->mag->length);
  Node N = A->mag->front;
  Node M = B->mag->front;

  //exit once ret becomes 0 or reach end of list
  while( ret && N) {
    ret = (N->data == M->data);
    N = N->next;
    M = M->next;
  }
  return ret;
}

// Manipulation procedures ---------------------------------------------------- 

// makeZero() 
// Re-sets N to the zero state.
void makeZero(BigInteger N) {
  if (!N)
    exit(1);
  N->sign = 0;
  clear(N->mag);  //clear the list associated with BigInteger N
}

// negate() 
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the 
// zero state. 
void negate(BigInteger N) {
  if (!N) 
    exit(1);
  N->sign *= -1;
}

// Takes in the string input to turn into a bigInt
// returns sign of number: 0 = empty || 1 = positive || -1 = non positive
// checks that all characters are valid digits
int stringData(int len, char *s, int sign) {
  
  if (strlen(s) == 0) { //check if string is empty
    printf("\nString is empty");
    return 0;
  }
  sign = 1; //default sign

  //iterate through entire string find non digit values / signs
  for (int i = 0; i < len; i++) {
    if (s[i] == 45) //- sign ascii char
      sign = -1;

    else if (s[i] == 43) //+ sign ignore this ascii char
      continue;

    else if ( s[i] < 48 || s[i] > 57 ) { //non digit/non sign ascii char
      printf("\nNot a digit number.. exiting now"); 
      exit(1);
    }
  }
  return sign;
}

// Cut string end by adding null in increments of power
// Used in stringToBigInteger reading in each element in the list
void cut_String(char *str) {
  for (int i = (int)strlen(str)-POWER; i < strlen(str); i++) {
    str[i] = '\0';
  }
}

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger() 
// Returns a reference to a new BigInteger object representing the decimal integer 
// represented in base 10 by the string s.  
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}  
// and an optional sign {+, -} prefix. 

BigInteger stringToBigInteger(char* s) {

  //make a home for string (if const string being passed)
  int len = strlen(s);
  char str[len+1];
  for (int i = 0; i <= len; i++) 
    str[i] = *(s+i);
  
  BigInteger B = newBigInteger();
  List L = newList();
  B->sign = stringData(len,str, 0);

  //prepend the list by elements in the power
  for (int i = (int)strlen(str); i >= 0; i-= POWER) {

    //ignore NULL chars
    if ( str[i] == '\0' )
      continue;

    //grab the element to append. Make elem positive if negative
    int long elem = atol(str + i );  
    // printf("\nelem: %ld\n", elem);
    if (elem < 0) 
      elem *= -1;
    
    cut_String(str);    //"cut" string
    prepend(L,elem);
  }

  //get the final element
  char last[strlen(str)];

  if ( strlen(str) > 0 ) {
    for (int j = 0; j < (int)strlen(str); j++)
      last[j] = str[j];

    int long elem = atol(last);
    // printf("\nlast elem: %ld\n", elem);

    if (elem < 0)
      elem *= -1;

    prepend(L,elem);
  }
  B->mag = L;
  return B;
}

// copy() 
// Returns a reference to a new BigInteger object in the same state as N. 
BigInteger copy(BigInteger N) {
  BigInteger New = newBigInteger();
  New->sign = N->sign;
  New->mag = copyList(N->mag);
  return New;
}

// function that performs Arithmetic carries
// determines the carry based on whether addition or subtraction is taking place
// returns the sign
int normalize(BigInteger N, char arithmetic) {
  
  if (N->sign == 0) 
    return 0;
  
  moveBack(N->mag);
  int carry = 0;   //keep track of carries
  int ret = 1;     //default sign
  int recurs = 0;

  //add normalization
  if (arithmetic == 'a') {
    for (int i = 0; i < N->mag->length; i++) {

      long elem = get(N->mag);      //EX: 179 
      //if there is a carry from previous, include it now
      if (carry) { 
        elem++;
        set(N->mag, elem);
      }
      //if the digit is over its range
      if ( (elem / BASE) >= 1 ) {   //EX: 179 / 10^2 = 1.79
        set(N->mag, elem - BASE);   //    179 - 10^2 = 79
        carry = 1; //a carry must be performed next iteration
      }
      else {
        carry = 0;//digit is in range, no carry needed for next iteration
      }
      movePrev(N->mag);
    }
    //if there is a carry after the addition prepend it
    if (carry) {
      prepend(N->mag, carry);
    }
  }

  //sub normalization
  else {  
    //exclude the largest # element in List
    for (int i = 0; i < N->mag->length -1; i++) {

      long elem = get(N->mag);      //EX: -11 
      //if there is a carry from previous, include it now
      if (carry) { 
        elem--;
        set(N->mag, elem);
      }
      //if the digit is negative
      if ( elem < 0 ) {             //EX: -11 < 0
        set(N->mag, elem + BASE);   //    -11 + 10^2 = 89
        carry = 1; //a carry must be performed next iteration
      }
      else {
        carry = 0;//digit is in range, no carry needed for next iteration
      }
      movePrev(N->mag);
    }

    //last item in the list
    if (carry) {
      set(N->mag, get(N->mag)-1 );
    }

    if (recurs) {
      //fix the final number to positive
      moveFront(N->mag); 
      set(N->mag,get(N->mag) * -1);
    }
      
    //if the final number is negative //inverse all signs and recall normalize
    if (get(N->mag) < 0) {
      for (int i = 0; i < N->mag->length; i++) {
        set(N->mag, get(N->mag)*-1);  
        moveNext(N->mag);
      }
      normalize(N, 's');  //Do a single recurse call on N
      recurs = 1;
      ret = -1;           //sign is -1
    }
  }
  return ret;
}

// add() 
// Places the sum of A and B in the existing BigInteger S
// overwriting S current state:  S = A + B 
void add(BigInteger S, BigInteger A, BigInteger B) {
  if (!A || !B || !S) 
    exit(1);

  if (A->sign == 0) {//A is an empty set
    S->mag = B->mag; S->sign = B->sign;
  }
  else if (B->sign == 0) {//B is an empty set
    S->mag = A->mag; S->sign = A->sign;
  }

  //Different signs
  else if ((A->sign == -1 && B->sign == 1) || (A->sign == 1 && B->sign == -1)) {
    //empty case
    if (listEQ(A->mag, B->mag)) {   // S = A - A || S = B - B
      S->sign = 0;
      S->mag = newList();
    }
    S->mag = sum(A,B)->mag;
    S->sign = sum(A,B)->sign;
    return;
  }
  //otherwise same signs
  S->mag = sum(A,B)->mag;
  S->sign = sum(A,B)->sign;
}

// sum() Returns a reference to a new BigInteger object representing A + B. 
BigInteger sum(BigInteger A, BigInteger B) {

  moveBack(A->mag); moveBack(B->mag);
  List L = newList();  //list to return
  BigInteger newBigInt = newBigInteger();
  int first = 0; int second = 0; 
  int len = A->mag->length; //assume equal length

  //set larger length
  if (A->mag->length > B->mag->length) {
    len = A->mag->length;
  }
  else {
    len = B->mag->length;
  }

  //same sign case -A + -B || A + B
  if (A->sign == B->sign) {
    for (int i = 0; i < len; i++) {

      first = get(A->mag);
      second = get(B->mag);

      if (first == -1) 
        first = 0;
      if (second == -1)
        second = 0;

      long sum = first + second;
      prepend(L, sum);

      //if A + B = A + A (same list) movePrev only once
      if(A->mag == B->mag) {
        movePrev(A->mag); continue; 
      } 
      movePrev(A->mag); movePrev(B->mag); //otherwise move both
    }
    newBigInt->mag = L;

    //positive sign case
    if ( (A->sign == 1 && B->sign == 1) ) {
      newBigInt->sign = 1;
      normalize(newBigInt, 'a');  //normalize + vector
      return newBigInt;
    }
    //negative sign case
    else if(A->sign == -1 && B->sign == -1){
      newBigInt->sign = -1;
      normalize(newBigInt, 's');  //normalize - vector
      return newBigInt;
    }
  }

  //opposite signs case A + -B = (A - B)
  else if (A->sign == 1 && B->sign == -1) {

    if (listEQ(A->mag, B->mag)) { //equal
      newBigInt->sign = 0;
      newBigInt->mag = L;
      return newBigInt;
    }

    for (int i = 0; i < len; i++) {

      first = get(A->mag);
      second = get(B->mag);

      if (first == -1) 
        first = 0;
      if (second == -1)
        second = 0;      

      long diff = first - second;
      prepend(L,diff);

      //if A + B = A + A (same list) movePrev only once
      if(A->mag == B->mag) {
        movePrev(A->mag); continue; 
      } 
      //otherwise move each respective list once
      movePrev(A->mag); movePrev(B->mag);
    }
    if (compare(A, B) > 0) {      //+A > -B = positive
      newBigInt->sign = 1;
    }
    else if (compare(A, B) < 0) { //+A < -B = negative
      newBigInt->sign = -1;
    }
    //set the List
    newBigInt->mag = L;
    normalize(newBigInt, 's');
  }

  //opposite signs case -A + B = (B - A)
  else {
    for (int i = 0; i < len; i++) {

      first = get(A->mag);
      second = get(B->mag);

      if (first == -1) 
        first = 0;
      if (second == -1)
        second = 0;

      long diff = first - second;
      prepend(L,diff);

      //if A + B = A + A (same list) movePrev only once
      if(A->mag == B->mag) {
        movePrev(A->mag); continue; 
      } 
      //otherwise move each respective list once
      movePrev(A->mag); movePrev(B->mag);
    }
    if (compare(A, B) > 0) {      //+A < -B = negative
      newBigInt->sign = -1;
    }
    else if (compare(A, B) < 0) { //+A > -B = positive
      newBigInt->sign = 1;
    }
    //set the List
    newBigInt->mag = L;
    normalize(newBigInt, 's');
  }
  return newBigInt;
}

// subtract() 
// Places the difference of A and B in the existing BigInteger D, overwriting  
// its current state:  D = A - B 
void subtract(BigInteger S, BigInteger A, BigInteger B) {
  if (!A || !B || !S) 
    exit(1);

  if (A->sign == 0) { //A is an empty set
    S->mag = B->mag; S->sign = B->sign * -1;
  }
  else if (B->sign == 0) {  //B is an empty set
    S->mag = A->mag; S->sign = A->sign * -1;
  }

  //A--B = A+B || -A-B = -(A+B)
  else if ((A->sign == 1 && B->sign == -1) || (A->sign == -1 && B->sign == 1)) {
    if (A->sign == -1) 
      S->sign = -1;
    else if (A->sign == 1)
      S->sign = 1;
    
    S->mag = diff(A,B)->mag;
  }
  else {
    //otherwise do the math
    S->mag = diff(A,B)->mag;
    S->sign = diff(A,B)->sign;
  }
}

// diff()
// Returns a reference to a new BigInteger object representing A - B. 
BigInteger diff(BigInteger A, BigInteger B) {

  List L = newList();
  BigInteger newBigInt = newBigInteger();
  moveBack(A->mag); moveBack(B->mag);
  int first = 0; int second = 0; 
  int len = A->mag->length; //assume equal length

  if (A->mag->length > B->mag->length) {  //set larger length
    len = A->mag->length;
  }
  else {
    len = B->mag->length;
  }

  // Addition A -- B || B -- A
  if ((A->sign == 1 && B->sign == -1) || (A->sign == -1 && B->sign == 1)) {
    for (int i = 0; i < len; i++) {
      
      first = get(A->mag);
      second = get(B->mag);

      if (first == -1) 
        first = 0;
      if (second == -1)
        second = 0;

      long sum = first + second;
      prepend(L, sum);

      if(A->mag == B->mag) {
        movePrev(A->mag); continue; 
      } 
      movePrev(A->mag); movePrev(B->mag); //otherwise move both
    }
    newBigInt->mag = L;           //vector addition

    // A - -B = A+B
    if ( (A->sign == 1 && B->sign == -1) ) {
      newBigInt->sign = 1;
    }
    // -A - +B = -(A+B)
    else if(A->sign == -1 && B->sign == 1){
      newBigInt->sign = -1;
    }
    normalize(newBigInt, 'a');  //normalize + vector
    return newBigInt;
  }
  
  // Subtration If +A - +B
  else if (A->sign == 1 && B->sign == 1) {

    //empty case
    if (listEQ(A->mag, B->mag)) {
      newBigInt->sign = 0;
      newBigInt->mag = L;
      return newBigInt;
    }

    for (int i = 0; i < len; i++) {

      first = get(A->mag);
      second = get(B->mag);

      if (first == -1) 
        first = 0;
      if (second == -1)
        second = 0;

      long diff = first - second;
      prepend(L,diff);

      if(A->mag == B->mag) {
        movePrev(A->mag); continue; 
      } 
      movePrev(A->mag); movePrev(B->mag);
    }
    if (compare(A, B) > 0) {
      newBigInt->sign = 1;
    }
    else if (compare(A, B) < 0) {
      newBigInt->sign = -1;
    }
    newBigInt->mag = L;
    normalize(newBigInt, 's');
    return newBigInt;
  }

  // subtraction if +B - +A = -A + B
  for (int i = 0; i < len; i++) {
    //empty case
    if (listEQ(A->mag, B->mag)) {
      newBigInt->sign = 0;
      newBigInt->mag = L;
      return newBigInt;
    }

    first = get(A->mag);
    second = get(B->mag);

    if (first == -1) 
      first = 0;
    if (second == -1)
      second = 0;

    long diff = first - second;
    prepend(L,diff);

    if(A->mag == B->mag) {
      movePrev(A->mag); continue; 
    } 
    movePrev(A->mag); movePrev(B->mag);
  }
  if (compare(A, B) > 0) {
    newBigInt->sign = -1;
  }
  else if (compare(A, B) < 0) {
    newBigInt->sign = 1;
  }
  //set the List
  newBigInt->mag = L;
  normalize(newBigInt, 's');
  return newBigInt;
}

// multiply() 
// Places the product of A and B in the existing BigInteger P, overwriting  
// its current state:  P = A*B 
void multiply(BigInteger P, BigInteger A, BigInteger B);

// prod() 
// Returns a reference to a new BigInteger object representing A*B 
BigInteger prod(BigInteger A, BigInteger B);

// Other operations ----------------------------------------------------------- 
// printBigInteger() 
// Prints a base 10 string representation of N to filestream out. 
void printBigInteger(FILE* out, BigInteger N) {

  if ( !N || !out ) {
    exit(1);
  }

  if (N->sign == 0) {
    fprintf(out,"0"); return;
  }

  //print the zero
  if (N->sign == -1) {
    fprintf(out, "-");
  }

  //get rid of trailing 0's or elements that are 0
  Node temp = N->mag->front;
  while (temp->data == 0) {
    temp = temp->next;
  }
  fprintf(out, "%ld",temp->data);
  temp = temp->next;

  while(temp) {
    fprintf(out, "%0*ld", POWER, temp->data);
    temp = temp->next;
  }
}
