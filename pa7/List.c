/*********************************************************************************
* Despina Patronas, Dpatrona
* 2021 Winter CSE 101 pa7
* List.c
* Define the functions of a Doubly Linked List
  Cursor used for bi-directional iteration of list
  Cursor is undefined as default state
  Cursor traverses list from element 0 (front) to n-1 (back)
  Exports a List type
*********************************************************************************/

#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h> //for memset

#define LIST_ELEMENT long

// CONSTRUCTOR / DESTRUCTOR=======================================================

// Returns reference to a new NodeObj
Node newNode (LIST_ELEMENT data) {
  Node N = (Node)malloc(sizeof(NodeObj));
  if (!N) {   //may also do assert(N != NULL)
    exit(1);
  }
  N->data = data; //set data
  N->next = NULL; //set ptr to next node
  N->prev = NULL; //set ptr to prev node
  return (N);
}

// Frees heap of allocated memory pointed to by pointer Node (*pN)
// sets *pN to NULL
void freeNode(Node *pN) {
  if (pN && *pN) {
    memset(*pN, 0, sizeof(NodeObj)); //sets next and prev back to null
    free(*pN);
    *pN = NULL;
  }
}

// Creates and returns a new default empty state List.
List newList(void) {
  List L = (List)malloc (sizeof(ListObj));
  if (!L) {   //may also do assert(L)
    exit(1);
  }
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
  L->index = -1;
  return (L);
}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL) {
  //make sure the pointer is a valid pointer
  if (pL && *pL) {
    memset(*pL, 0, sizeof(ListObj));
    free(*pL);
    *pL = NULL;
  }
}

// ACCESS FUNCTIONS================================================================

// Returns the number of elements in L. 0 = empty
LIST_ELEMENT length(List L) {
  return L->length;
}

// Returns int index of cursor element. may returns -1 (undefined).
LIST_ELEMENT index(List L) {
  return L->index;
}

// Returns front element (data) of L
// Pre: length()>0
LIST_ELEMENT front(List L) {
  if ( L->length > 0 ) {
    return L->front->data;
  }
  printf("\nNo front to return empty list ");
  return -1;
}

// Returns back element (data) of L.
//Pre: length()>0
LIST_ELEMENT back(List L) {
  if ( L->length > 0 ) {
    return L->back->data;
  }
  printf("\nNo back to return empty list ");
  return -1;
}

// Returns cursor element (data) of L.
//Pre: length()>0, index()>=0 otherwise cursor is undefined
LIST_ELEMENT get(List L) {
  if ( (L->length > 0 ) && (L->index > -1) && (L->cursor) ) {
    return L->cursor->data;
  }
  //printf("Nothing to return list is empty / cursor NDF");
  return -1;
}

// MANIPULATE FUNCTIONS=============================================================

// Resets L to its original empty state.
void clear(List L) {

  Node ptr = L->front;
  //clear the nodes
  while(ptr) {
    //hold the next node
    Node temp = ptr->next;
    freeNode(&ptr);
    ptr = temp;
  }

  //return default state of the list
  memset(L, 0, sizeof(ListObj));
  L->index = -1;
}

// Overwrites the cursor element’s data with x
// Pre: length()>0, index()>=0
void set(List L, LIST_ELEMENT x) {
  if ( (L->index > -1) && (L->length > 0) && (L->cursor)) {
    L->cursor->data = x;
  }
}

// If L is non-empty, sets cursor to back element, otherwise do nothing
// note change index
void moveFront(List L) {
  if (L->length > 0) {
    L->cursor = L->front;
    L->index = 0;
  }
}

// If L is non-empty, sets cursor to back element, otherwise do nothing
// note change index
void moveBack(List L) {
  if (L->length > 0) {
    L->cursor = L->back;
    L->index = L->length - 1;
  }
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; note decrement index
// if cursor is defined and at front, cursor becomes undefined;
// if cursor is undefined do nothing
void movePrev(List L) {
  if (L->cursor) {
    if (L->cursor != L->front) {
      L->cursor = L->cursor->prev;
      L->index--;
      return;
    }
    L->cursor = NULL;
    L->index = -1;
  }
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; note increment index
// if cursor is defined and at back, cursor becomes undefined; 
// do nothing if cursor is undefined 
void moveNext(List L) {
  if (L->cursor) {
    if (L->cursor != L->back) {
      L->cursor = L->cursor->next;
      L->index++;
      return;
    }
    //cursor = back becomes undefined
    L->cursor = NULL;
    L->index = -1;
  }
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
// note: if cursor is defined, increment index
void prepend(List L, LIST_ELEMENT x) {

  Node nn = newNode(x);

  //if L is not empty
   if (L->length > 0) {

    nn->next = L->front;  // nn -> front
    L->front->prev = nn;  // nn <- front
    L->front = nn;        // nn <-> oldfront

   }
   //default case L is empty
   else {
    L->front = L->back = nn;

   }
  //both cases
  L->length++;

  //if a cursor is defined, increment index
  if(L->cursor) {
    L->index++;
  }
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
// note: cursor and index unaffected
void append(List L, LIST_ELEMENT x) {

  Node nn = newNode(x);

  //if list is non empty
  if (L->length > 0 ) {
    L->back->next = nn;    // back -> nn
    nn->prev = L->back;    // back <- nn
    L->back = nn;          // oldback <-> nn
  }
  //default case L is empty
  else {
    L->front = L->back = nn; //default node nn is only element in list
  }
  //both cases
  L->length++;
}

// Insert new element before cursor.
// note: cursor will not change but index will increment
// Pre: length()>0, index()>=0
void insertBefore(List L, LIST_ELEMENT x) {

  //cursor should be defined
  if (L->cursor) {
    Node nn = newNode(x);

    //cursor is not at the front
    if (L->cursor != L->front) {
      nn->next = L->cursor;        // cursor->prev    nn  -> curosr
      nn->prev = L->cursor->prev;  // cursor->prev <- nn     cursor
      L->cursor->prev->next = nn;  // cursor->prev -> nn     cursor
      L->cursor->prev = nn;        // cursor->prev    nn  <- cursor
      
      L->index++;  
      L->length++;
    }
    //cursor at front of list (index 0)
    else {
      prepend(L,x);
      return;
    }
  }
  else {
    printf("The cursor is not defined");
    exit(1);
  }
}

// Insert new element after cursor.
// note: index will not change!
// Pre: length()>0, index()>=0
void insertAfter(List L, LIST_ELEMENT x) {

  //if cursor is defined
  if (L->cursor) {

    Node nn = newNode(x);

    //if cursor is not at the end of the list
    if (L->cursor != L->back) {
      nn->next = L->cursor->next;
      nn->prev = L->cursor;
      L->cursor->next->prev = nn;
      L->cursor->next = nn; 

      L->length++;
    }
    //if cursor = back then append
    else {
      append(L,x);
    }
  }
  else {
    printf("The cursor is not defined");
    exit(1);
  }
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
  if (L->front) {

    //what if there is a cursor defined?
    if(L->cursor) {
      //if cursor is defined
      if(L->cursor != L->front) {
        L->index--;
      }
      //if cursor is defined at the front
      else {
        L->cursor = NULL;
        L->index = -1; 
      }
    }
    //Manipulations
    //Length >= 2
    if (L->length > 1) {
      L->front->next->prev = NULL;  // front <-x- node
      Node temp = L->front->next;   // save new front
      
      freeNode(&L->front); 

      L->front = temp;              //set new front
      L->length--;

      return;
    }
    //only one element 
    else {
      clear(L);
      return;
    }

  }
  printf("There is no front element to delete!");
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {

    //what if there is a cursor defined at the back?
    if(L->cursor) {
      //if cursor is defined
      if(L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1; 
      }
    }

  if (L->back) {
    //length >= 2
    if (L->length > 1) {
      L->back->prev->next= NULL;    // -node -x-> back
      Node temp = L->back->prev;    // temp = -node -x-> back

      freeNode(&L->back);

      L->back = temp;               // -node
      L->length--;
      return;
    }
    //only one element
    else {
      clear(L);      
      return;
    }
  }
  printf("There is no back element to delete!");
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {

  if (L->cursor) {
    if (L->cursor == L->front) {
      deleteFront(L); //checks for case where cursor is only elemnt 
      L->cursor = NULL;
      L->index = -1;    
      return;       
    }
    else if (L->cursor == L->back) {
      deleteBack(L); //checks for case where cursor is only elemnt
      L->cursor = NULL;
      L->index = -1;
      return;
    }
    //cursor is somewhere in between
    else {
      L->cursor->next->prev = L->cursor->prev;  // node <- curXsor - node
      L->cursor->prev->next = L->cursor->next;  // node - curXsor -> node
      L->length--;
      freeNode(&L->cursor);
      L->cursor = NULL;
      L->index = -1;
      return;
    }
  }
  printf("There is no cursor defined; cannot delete NDF cursor!");
}

// EXTRA FUNCTIONS________________________________________________________________

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L) {
  if(!out) {
    return;
  }
  Node temp = L->front;
  while(temp) {
    fprintf(out, "%d ", temp->data);
    temp = temp->next;
  }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
  List new_List = newList();

  Node temp = L->front;
  while (temp) {
    append(new_List, temp->data);
    temp = temp->next;
  }
  return new_List;
}

// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B) {
  List new_List = newList();

  Node temp_A = A->front;
  Node temp_B = B->front;

  while (temp_A) {
    append(new_List, temp_A->data);
    temp_A = temp_A->next;
  }
  while (temp_B) {
    append(new_List, temp_B->data);
    temp_B = temp_B->next;
  }
  return new_List;
}
