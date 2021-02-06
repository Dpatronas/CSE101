//-----------------------------------------------------------------------------
// Despina Patronas, Dpatrona
// 2021 Winter CSE 101 pa4
//
// List.cpp
// Header file for List ADT.
// List is a double ended queue with a vertical cursor standing between elements.
// Cursor position is always defined as int from range 0 (at front) to length of List (at back).

// An empty list consists of the vertical cursor only, with no elements
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>

#include "List.h"
using namespace std;

// Private Constructors ----------------------------------------------------

//Node constructor
List::Node::Node(int x) {
	data = x;
	next = nullptr;
	prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List() {

	//Dummys point to nodes which holds no data
  Node *F = new Node(-2);
  Node *B = new Node(-9);
	frontDummy = F;
	backDummy = B;

	//default list state front and back point to each other
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;

	//nodes before and after cursor
	beforeCursor = frontDummy;	//before cursor points to the frontDummy
	afterCursor	= backDummy;	//after cursor points to the backDummy

	pos_cursor = 0;		//cursor at 0 to start. Never undefined
	num_elements = 0;	//length is 0 elements to start
}

// Copy List constructor.
List::List(const List& L) {

  //Dummys point to nodes which holds no data
  Node *F = new Node(-2);
  Node *B = new Node(-9);

	frontDummy = F;
	backDummy = B;

	//default list state front and back point to each other
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;

	//nodes before and after cursor
	beforeCursor = frontDummy;	//before cursor points to the frontDummy
	afterCursor	= backDummy;	//after cursor points to the backDummy

	pos_cursor = 0;		//cursor at 0 to start. Never undefined
	num_elements = 0;	//length is 0 elements to start

	if (L.num_elements > 0) {
    F = L.frontDummy;
    B = L.backDummy;

    while(F->next != B ) {
      this->insertBefore(F->next->data);
      F=F->next;
    }
  }
}

// Destructor
List::~List() {
  clear();
  delete frontDummy;
  delete backDummy;
  afterCursor = nullptr;
  beforeCursor = nullptr;
}

// Access functions --------------------------------------------------------

// isEmpty()
// Returns true if this List is empty, false otherwise.
bool List::isEmpty() {
	return (num_elements == 0);
}

// size()
// Returns the size of this List.
int List::size() {
	return num_elements;
}

// position() similar to index
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int List::position() {
	return pos_cursor;
}

// Manipulation procedures -------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
	pos_cursor = 0;				    //fd || node | AC
  beforeCursor = frontDummy;
  afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position size() in this List.
void List::moveBack() {
	pos_cursor = size();	// BC | node || bd
  afterCursor = backDummy;
  beforeCursor = backDummy->prev;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
int List::peekNext() {
	if (pos_cursor < size() && !isEmpty()) {
		return afterCursor->data;
	}
	return -1;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
int List::peekPrev() {
	if (pos_cursor > 0 && !isEmpty()) {
		return beforeCursor->data;
	}
	return -1;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that was passed over.
// pre: position()<size()
int List::moveNext() {

	if (pos_cursor < size() && !isEmpty()) {

		afterCursor = afterCursor->next;
		beforeCursor = afterCursor->prev;

		pos_cursor++;	//increment position
    return beforeCursor->data;
	}
	return -1;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that was passed over.
// pre: position()>0
int List::movePrev() {

	if (pos_cursor > 0 && !isEmpty()) {

		beforeCursor = beforeCursor->prev;
		afterCursor = beforeCursor->next;

		pos_cursor--;
    return afterCursor->data;
	}
	return -1;
}

// insertAfter()
// Inserts x after cursor
void List::insertAfter(int x) {

	Node *nn = new Node(x);

	if (isEmpty()) {
		//fields of nn
		nn->prev = frontDummy;
		nn->next = backDummy; 	//front <-nn-> back
		
		//fields of List
		frontDummy->next = nn;	//front-> nn <-back
		backDummy->prev = nn;
	}

	//Cursor is at the back
	else if (afterCursor == backDummy) {
		//fields of nn
		nn->next = backDummy;
		nn->prev = beforeCursor;	// BC ||<-nn-> back

		backDummy->prev = nn;
		beforeCursor->next = nn;	// BC ||->nn
	}

	//Cursor is at the front
	else if (beforeCursor == frontDummy) {
		nn->prev = frontDummy;
		nn->next = afterCursor;

		frontDummy->next = nn;
		afterCursor->prev = nn;
	}

	//Cursor is somewhere in the middle
	else {
		nn->next = afterCursor;
		nn->prev = beforeCursor;

		beforeCursor->next = nn;
		afterCursor->prev = nn;
	}
	//All cases
	num_elements++;	  //increment size of List
	afterCursor = nn;	//set new after cursor

}

// insertBefore()
// Inserts x before cursor.
// Note: cursor position (incremenets)
void List::insertBefore(int x) {

	Node *nn = new Node(x);

	if (isEmpty()) {
		//fields of nn
		nn->prev = frontDummy;
		nn->next = backDummy; 	//front <-nn-> back
		
		//fields of List
		frontDummy->next = nn;	//front-> nn <-back
		backDummy->prev = nn;
	}

	//cursor is at the back
	else if (afterCursor == backDummy) {
		nn->next = backDummy;
		nn->prev = beforeCursor;

		backDummy->prev = nn;
		beforeCursor->next = nn;
	}

	//cursor is at the front
	else if (beforeCursor == frontDummy) {
		nn->prev = frontDummy;
		nn->next = afterCursor;

		frontDummy->next = nn;
		afterCursor->prev = nn;
	}
	//Cursor is somewhere in the middle
	else {
		nn->next = afterCursor;
		nn->prev = beforeCursor;

		beforeCursor->next = nn;
		afterCursor->prev = nn;
	}
	//all cases:
	pos_cursor++;	      //increment cursor
	num_elements++;	    //increment size of list
	beforeCursor = nn;	//set new before cursor

}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()
void List::eraseAfter() {

	if (position() < size() && size() > 0) {

		afterCursor->next->prev = beforeCursor;	//BC || AC | node
		beforeCursor->next = afterCursor->next;	// join BC and node

		afterCursor->next = nullptr;			//sever old ties
		afterCursor->prev = nullptr;
    delete afterCursor;               //delete old AC

		afterCursor = beforeCursor->next;	//set new AC
		num_elements--;
	}
	//Cannot delete backdummy	
	else {
		cerr << endl << "Out of bounds. Cannot delete node after" << endl;
		exit(EXIT_FAILURE);
	}
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()> 0
// Note: cursor changes position (decrements)
void List::eraseBefore() {
	if (position() > 0 && size() > 0) {

		beforeCursor->prev->next = afterCursor; // node | BC || AC
		afterCursor->prev = beforeCursor->prev;

		beforeCursor->prev = nullptr; //sever old ties
		beforeCursor->next = nullptr;
    delete beforeCursor;          //delete old BC

		beforeCursor = afterCursor->prev; //set new BC
		num_elements--;
		pos_cursor--;
	}
	//cannot delete front dummy
	else {
		cerr << endl << "Out of bounds. Cannot delete node before" << endl;
		exit(EXIT_FAILURE);
	}
}

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so
// eraseBefore() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1.
int List::findNext(int x) {
	//iterate starting at the cursor position towards the back
	for (position(); position() < size(); moveNext()) {
		if (afterCursor->data == x) {
			moveNext();	//place cursor after the found element
			return position();
		}
	}
	//if not found cursor will remain at the size() position
	return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so
// eraseAfter() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position 0, and
// returns -1.
int List::findPrev(int x) {
	//iterate starting at the cursor position towards the front
	for (position(); position() > 0; movePrev()) {
		if (beforeCursor->data == x) {
			movePrev();	//place cursor before the found element
			return position();
		}
	}
	//if not found cursor will remain at the 0 position
	return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other
// occurances. The cursor is not moved with respect to the retained
// elements, i.e. it lies between the same two retained elements that it
// did before cleanup() was called.
void List::cleanup() {

  //nothing to clean up in empty list
  if (isEmpty()) {
    return;
  }
	//save initial position of the cursor
	int saved = position();
  //a pointer for iteration of inner loop
  Node *ptr = frontDummy->next;

  //Outer loop: ptr steps through each element of the list
	for (int i = 1; i <= size(); i++) {
    
    moveFront(); //reset cursor
    for (int j = i; j > 0; j--) { //shift the cursor to be after the ptr
      moveNext();
    }

    //Inner Loop: cursor step through elements after ptr
    while (afterCursor != backDummy) {

      //Find duplicates and erase them
      if (afterCursor->data == ptr->data) {

        //reflect removal affect on original list cursor position
        if (position() < saved) {
          saved--;
        }
        eraseAfter();
        continue;
      }
      moveNext(); //move the cursor until it reaches the end of list
    }
    ptr = ptr->next; //move ptr to next node
  }

  //set the new cursor position for the list once cleanup is done
  moveFront();
  for (position(); position() < saved; moveNext());
}

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
  moveFront();
  while (afterCursor != backDummy) {
    eraseAfter();
  }
}

// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L) {
  List R;
  Node * N = this->frontDummy->next;
  Node * M = L.frontDummy->next;

  //the original list
  while (N->next != nullptr) {
    R.insertBefore(N->data);
    N = N->next;
  }
  //the joining list
  while (M->next != nullptr) {
    R.insertBefore(M->data);
    M = M->next;
  }
  return R;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
string List::to_string() {
  Node * nn = nullptr;
  string s = "";
  for (nn = frontDummy->next; nn != nullptr; nn=nn->next) {
    if (nn != backDummy) {
      if (nn->next == backDummy) {
        s += std::to_string(nn->data);
        break;
      }
      s += std::to_string(nn->data)+", ";   
    } 
  }
  return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) {
  bool eq = false;
  Node * nn = nullptr;
  Node * on = nullptr;

  eq = ( this->num_elements == R.num_elements);
  //set both to front element in list
  nn = this->frontDummy->next;
  on = R.frontDummy->next;
  while ( eq && nn!=nullptr) {
    eq = (nn->data == on->data);
    nn = nn->next;
    on= on->next;
  }
  return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
ostream& operator<<( std::ostream& stream, List& L ) {
  return stream << "(" << L.List::to_string() << ")";
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged are unchanged.
bool operator==( List& A, const List& B ) {
  return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
  
  //this List cannot be the parameter List
  if (this != &L ) {
    //make a copy of List
    List temp = L;

    //swap copy List fields with 'this' List fields
    std::swap(frontDummy,   temp.frontDummy);
    std::swap(backDummy,    temp.backDummy);
    std::swap(num_elements, temp.num_elements);
    std::swap(pos_cursor,   temp.pos_cursor);
    std::swap(beforeCursor, temp.beforeCursor);
    std::swap(afterCursor,  temp.afterCursor);
  }
  //return this List
  moveFront();
  return *this;
  //Note: copy is deleted upon return..
}
