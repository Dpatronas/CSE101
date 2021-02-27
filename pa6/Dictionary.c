//-----------------------------------------------------------------------------
// Despina Patronas, Dpatrona
// 2021 Winter CSE 101 pa6

// Dictionary.c
// Implementation for Dictionary ADT for RBT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "Dictionary.h"

//macros defined to easily change the types of key / values
#define KEY_TYPE char*    //pointer to a string
#define VAL_TYPE int*     //tracks the frequency of a word (key)

#define KEY_UNDEF NULL    //default key
#define VAL_UNDEF NULL    //default ptr to word frequency

#define KEY_FORMAT "%s"   //print key values
#define VAL_FORMAT "%p"   //pointer value
#define KEY_CMP(x,y) strcmp(x,y)

#define NIL (void*)0      //value for NULL ptrs defined as tree leaves

// Constructors-Destructors ---------------------------------------------------

// Define a Node Object
typedef struct NodeObj {
  KEY_TYPE key;           //String (a line of the given text file)
  VAL_TYPE data;          //tracks frequency of s specific key
  char color;             // "r" = red || "b" = black (default color)
  struct NodeObj* parent; //ptr to a parent node
  struct NodeObj* left;   //ptr to previous node
  struct NodeObj* right;  //ptr to next node

} NodeObj;

typedef NodeObj* Node;

// Returns reference to a new NodeObj
Node newNode (KEY_TYPE key, VAL_TYPE data) {
  Node N = (Node)malloc(sizeof(NodeObj));
  if (!N) {
    exit(1);
  }
  //default fields of node
  N->parent = N->right = N->left = NIL;
  N->data = data;
  N->key  = key;
  N->color = 'b';

  return (N);
}

typedef struct DictionaryObj {
  Node nill;    //ptr to all nill ends of the tree
  Node root;    //ptr to the start of the tree
  Node cursor;  //keeps track of the current node for iterations
  int size;     //number of objects in the tree
  int unique;   //boolean value to disable or enable duplicates (0=dupes | 1=no dupes)

}DictionaryObj;

// newDictionary() Creates a new empty Dictionary
// If unique==false (0), then the Dictionary will accept duplicate keys, i.e. distinct pairs with identical keys. 
// If unique==true (1 or any non-zero value), then duplicate keys will not be accepted.
// In this case, the operation insert(D, k) will enforce the 
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique) {
  Dictionary D = (Dictionary)malloc(sizeof(DictionaryObj));
  if (!D) {
    exit(1);
  }
  //dummy node creation filled with garbage data ptr
  Node nillNode = newNode(KEY_UNDEF, VAL_UNDEF);
  nillNode->left=nillNode->right= nillNode;
  //set the fields
  D->nill = nillNode;   //set nill node as dummy node
  D->root = D->nill;   //root points to nothing to start
  D->cursor = D->nill;  //node that isnt pointing to anything to start

  D->size = 0;
  D->unique = unique;         // 0 = NO dupes | 1 = dupes
  return (D);
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD) {
  if(pD && *pD) {
    makeEmpty(*pD);
    memset(*pD, 0, sizeof(DictionaryObj));
    pD = NULL;
  }
}

// Access functions -----------------------------------------------------------

int size(Dictionary D) {
  if (!D) {
    exit(1);
  }
  return D->size;
}

int getUnique(Dictionary D) {
  if (!D) {
    exit(1);
  }
  return D->unique;
}

// searches and compares desired key to nodes key. returns the node with the key
// Cost = Theta(height x). Worst case is degenerative BST aka linked list
// Helper for lookup operations or delete
Node TreeSearch(Node x, KEY_TYPE k) {
  //returns key rooted at x or NULL
  if( x->data == VAL_UNDEF || KEY_CMP(k,x->key) == 0 ) {
    return x;
  }
  //go down the left subtree to search for rooted node with k
  else if ( KEY_CMP(k, x->key) < 0) {
    return TreeSearch(x->left, k);
  }
  //go down right subtree to search for rooted node with k
  return TreeSearch(x->right, k);
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value ptr. 
// If D contains no such pair, then returns VAL_UNDEF aka Null ptr.
// uses TreeSearch
VAL_TYPE lookup(Dictionary D, KEY_TYPE k) {

  Node search = TreeSearch(D->root, k);
  //no pair exists
  if (search == D->nill) {
    return VAL_UNDEF;
  }
  return search->data;
}

// Helper Functions------------------------------------------------------------

// Walks: cost = Theta(n); n = #nodes------------------------------------------

// prints BST data keys in ascending order
void inOrderTreeWalk(FILE* out, Node x) {
  if (x->data != NIL) {
    inOrderTreeWalk(out, x->left);
    fprintf( out, KEY_FORMAT, x->key);
    fprintf( out, "\n");
    inOrderTreeWalk(out, x->right);
  }
}

// prints BST data keys. Starts by printing the root
// keys < root = left subtree || keys > root = right subtree
void preOrderTreeWalk(FILE* out, Node x) {
  if (x->data != NIL) {
    fprintf( out, KEY_FORMAT, x->key);
    fprintf( out, "\n");
    preOrderTreeWalk( out, x->left);
    preOrderTreeWalk( out, x->right);
  }
}

// Prints BST data keys starting at the root (post order)
void postOrderTreeWalk(FILE* out, Node x) {
  if (x->data != NIL) {
    postOrderTreeWalk( out, x->left);
    postOrderTreeWalk( out, x->right);
    fprintf( out, KEY_FORMAT, x->key);
    fprintf( out, "\n");
  }
}

// delete nodes (post order)
void postOrderDelete(Dictionary D, Node x) {
  if (x->data != NIL) {
    postOrderDelete(D,x->left);
    postOrderDelete(D,x->right);
    delete(D,x->key);
  }
}

// Queries --------------------------------------------------------------------

// Walks down the left side of the tree to the bottom
// Cost : height of x (distance from root to deepest root)
// pre: Node x != NIL (emptyset)
Node TreeMinimum(Node x) {
  if (x->data == NIL) {
    //there is nothing to querie, empty set node for rooted x
    exit(1);
  }
  //otherwise traverse the leftmost subtree of rooted x
  while (x->left->data != NIL) {
    x = x->left;
  }
  return x;
}

// Walks down the right side of the tree to the bottom
// Cost : height of x (distance from root to deepest root)
// pre: Node x != NIL (emptyset)
Node TreeMaximum(Node x) {
  if (x->data == NIL) {
    exit(1);
  }
  while(x->right->data != NIL) {
    x = x->right;
  }
  return x;
}

// Return the node after x which would appear in order BST tree walk
// Cost: Theta(height(successor x))
// Note: there may be no successor and would return NIL (root)
// case 1: x has a right child, find the minimum
// case 2: x has no right child, climb up the tree
Node TreeSuccessor(Node x) {
  // case 1
  if (x->right->data != NIL) {
    return TreeMinimum(x->right); //left most descendent of the x's right child
  }
  // case 2
  Node y = x->parent;
  //y is not the root and x is the right child of y
  while( (y->data != NIL) && (x == y->right) ) {
    x = y;
    y = y->parent;
  }
  return y; 
}

// Returns the node before x which would appear in order BST tree walk
// Cost: Theta(height(predecessor x))
// Note: leafs dont have predecessor and would return NIL
// case 1: x has a left child, find the maximum
// case 2: x has no left child, climb up the tree
Node TreePredecessor(Node x) {
  // case 1
  if (x->left->data != NIL) {
    return TreeMaximum(x->left); //right most descendent of the x's left child
  }
  // case 2
  Node y = x->parent;
  //y is not the root and x is the left child of y
  while( (y->data != NIL) && (x == y->left) ) {
    x = y;
    y = y->parent;
  }
  return y; 
}

// Manipulation procedures ----------------------------------------------------

// LeftRotate() for RBT
// Performs a transformation on the configuration of nodes in the tree about x
// Preserves the BST properties
void LeftRotate(Dictionary D, Node x) {

  Node y = x->right;      // set y
  x->right = y->left;     // turn y’s left subtree into x’s right subtree

  if (y->left != D->nill) {
    y->left->parent = x;
  }

  y->parent = x->parent;   // link x’s parent to y

  //set root
  if (x->parent == D->nill) {
    D->root = y;
  }
  // put x on y’s left
  else if (x == x->parent->left) {
    x->parent->left = y;
  }
  // put x on y right
  else {
    x->parent->right = y;
  }
  //x is y left child
  y->left = x;
  x->parent = y;
}

// RightRotate() for RBT
// Performs a transformation on the configuration of nodes in the tree about x
// Preserves the BST properties
void RightRotate(Dictionary D, Node x) {

  Node y = x->left;       // set y
  x->left = y->right;     //turn y’s right subtree into x’s left subtree
  
  if (y->right != D->nill) {
    y->right->parent = x;
  }

  y->parent = x->parent;  //link x's parent to y

  //set root
  if (x->parent == D->nill) {
    D->root = y;
  }
  // put x on y’s right
  else if ( x == x->parent->right) {
    x->parent->right = y;
  }
  // put x on y’s left
  else {
    x->parent->left = y;
  }
  //x is y right child
  y->right = x;
  x->parent = y;
}

void InsertFix(Dictionary D, Node z) {
  //two reds found
  Node y;
  while (z->parent->color == 'r') {
    if (z->parent == z->parent->parent->left) {
      y = z->parent->parent->right;

      if (y->color == 'r') {
        z->parent->color = 'b';             // case 1
        y->color = 'b';                     // case 1
        z->parent->parent->color = 'r';     // case 1
        z = z->parent->parent;              // case 1
      }
      else {
        if (z == z->parent->right) {
          z = z->parent;                    // case 2
          LeftRotate(D, z);                 // case 2
        }
        z->parent->color = 'b';             // case 3
        z->parent->parent->color = 'r';     // case 3
        RightRotate(D, z->parent->parent);  // case 3
      }
    }
    else {
       y = z->parent->parent->left;
       if (y->color == 'r') {
          z->parent->color = 'b';            // case 4
          y->color = 'b';                   // case 4
          z->parent->parent->color = 'r';    // case 4
          z = z->parent->parent;            // case 4
       }
       else {
          if (z == z->parent->left) {
             z = z->parent;                 // case 5
             RightRotate(D, z);             // case 5
          }
          z->parent->color = 'b';           // case 6
          z->parent->parent->color = 'r';   // case 6
          LeftRotate(D, z->parent->parent); // case 6
        }
      }
    }
  D->root->color = 'b';
}

// insert() for RBT
// Insert the pair (k,v) into Dictionary D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF is enforced. 
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v) {
  
  //if allows duplicates or the key doesnt exist
  if (D->unique == 0 || lookup(D,k) == VAL_UNDEF) {

    Node nn = newNode(k, v); //using pointer data  
    nn->left = nn->right = D->nill;
    
    Node y = D->nill;
    Node x = D->root;

    //traverse the tree
    while (x != D->nill) {
      y = x;
      //chose the insertion spot
      if (KEY_CMP(nn->key, x->key) < 0) {
        x = x->left;
      }
      else {
        x = x->right;
      }
    }
    nn->parent = y;

    //empty tree case //root remains black
    if (y == D->nill) {
      D->root = nn;
    }
    //place nn on the left
    else if (KEY_CMP(nn->key,y->key) < 0) {
      y->left = nn;
    }
    //Otherwise place nn on the right
    else {
      y->right = nn;
    }
    //all cases
    D->size++;
    nn->color = 'r';      //sets the nn to red 
    InsertFix(D, nn);
  }
}

// Replaces one subtree as a child of its parent with another subtree
// u parent = v parent
void Transplant(Dictionary D, Node u, Node v) {
  //u is was the root
  if (u->parent == D->nill) {
    D->root = v;
  }
  //u is on the left of its parent
  else if (u == u->parent->left) {
    u->parent->left = v;
  }
  //u is on the right of its parent
  else {
    u->parent->right = v;
  }
  //swap
  v->parent = u->parent;
}

void RB_DeleteFixUp(Dictionary D, Node x) {
  Node w;
  while ( (x != D->root) && (x->color == 'b') ) {
    if (x == x->parent->left) {
      w = x->parent->right;

        if (w->color == 'r') {
          w->color = 'b';               // case 1
          x->parent->color = 'r';       // case 1
          LeftRotate(D, x->parent);     // case 1
          w = x->parent->right;         // case 1
        }

        else if ((w->left->color == 'b') && (w->right->color == 'b')) {
          w->color = 'r';               // case 2
          x = x->parent;                // case 2
         }

        else {
          if (w->right->color == 'b') {
            w->left->color = 'b';       // case 3
            w->color = 'r';             // case 3
            RightRotate(D, w);          // case 3
            w = x->parent->right;       // case 3
          }
          w->color = x->parent->color;  // case 4
          x->parent->color = 'b';       // case 4
          w->right->color = 'b';        // case 4
          LeftRotate(D, x->parent);     // case 4
          x = D->root;                  // case 4
        }
      }

    else {
      w = x->parent->left;

      if (w->color == 'r') {
        w->color = 'b';                 // case 5
        x->parent->color = 'r';         // case 5
        RightRotate(D, x->parent);      // case 5
        w = x->parent->left;            // case 5
      }
    
      else if ((w->right->color == 'b') && (w->left->color == 'b')) {
        w->color = 'r';                 // case 6
        x = x->parent;                  // case 6
      }
      else {
        if (w->left->color == 'b') {
          w->right->color = 'b';        // case 7
          w->color = 'r';               // case 7
          LeftRotate(D, w);             // case 7
          w = x->parent->left;          // case 7
        }
        w->color = x->parent->color;    // case 8
        x->parent->color = 'b';         // case 8
        w->left->color = 'b';           // case 8
        RightRotate(D, x->parent);      // case 8
        x = D->root;                    // case 8        
      }
    }
  }
  x->color = 'b';
}

void delete(Dictionary D, KEY_TYPE k) {

  if(lookup(D,k) == VAL_UNDEF) {
    return;
  }

  //see if the node exists
  Node z = TreeSearch(D->root, k);
  //see if cursor deleted
  if(z == D->cursor) {
    D->cursor = D->nill;
  }

  Node y; Node x;
  y = z;
  char y_original_color = y->color;

  if (z->left == D->nill) {
    x = z->right;
    Transplant(D, z, z->right);
    D->size--;
  }

  else if (z->right == D->nill) {
    x = z->left;
    Transplant(D, z, z->left);
    D->size--;
  }

  else {
    y = TreeMinimum(z->right);
    y_original_color = y->color;
    x = y->right;

    if (y->parent == z ) {
      x->parent = y;
    }
    else {
      Transplant(D, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    Transplant(D, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
    D->size--;
  }
  if (y_original_color == 'b') {
    RB_DeleteFixUp(D, x);
  }
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
// post order tree deletion
void makeEmpty(Dictionary D) {
  if (!D) {
    exit(1);
  }
  //take out all the nodes
  while(D->size > 0) {
    postOrderDelete(D,D->root);
  }
  D->cursor = D->nill;
}

// beginForward()
// Move cursor to the smallest element in the tree (follows in order)
// If D is empty, returns VAL_UNDEF.
VAL_TYPE beginForward(Dictionary D) {
  if (D->size == 0) {
    return VAL_UNDEF;
  }
  //cursor to smallest node
  D->cursor = TreeMinimum(D->root);
  return D->cursor->data;
}

// beginReverse()
// Move cursor to the largest element in the tree (follows in order)
// If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D) {
    if (D->size == 0) {
    return VAL_UNDEF;
  }
  //cursor to largest node
  D->cursor = TreeMaximum(D->root);
  return D->cursor->data;
}

// currentKey()
// returns current cursors key. (follows in order)
// If cursor is undefined, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D) {
    if(D->cursor == D->nill) {
    return KEY_UNDEF;
  }
  return D->cursor->key;
}

// currentVal()
// returns current cursors value. (follows in order)
// If cursor is undefined, returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D) {
  if(D->cursor == D->nill) {
    return VAL_UNDEF;
  }
  return D->cursor->data;
}

// next() returns the new cursors data value
// Move cursor to the next element in the BST (follows in order)
// If cursor is not undefined returns VAL_UNDEF.
// If cursor reaches an end pair returns VAL_UNDEF. 
VAL_TYPE next(Dictionary D) {
  //no cursor defined
  if (D->cursor == D->nill) {
    return VAL_UNDEF;
  }
  //reached root
  if(TreeSuccessor(D->cursor) == D->nill) {
    D->cursor = D->nill;
    return VAL_UNDEF;
  }
  D->cursor = TreeSuccessor(D->cursor);
  return D->cursor->data;
}

// prev() returns the new cursors data value
// Move cursor to the prev element in the BST (follows in order) 
// If cursor is not undefined returns VAL_UNDEF.
// If cursor reaches an end pair returns VAL_UNDEF. 
VAL_TYPE prev(Dictionary D) {
  //no cursor defined
  if (D->cursor == D->nill) {
    return VAL_UNDEF;
  }
  //reached leaf
  if(TreePredecessor(D->cursor) == D->nill) {
    D->cursor = D->nill; 
    return VAL_UNDEF;
  }
  D->cursor = TreePredecessor(D->cursor);
  return D->cursor->data;
}

// Other operations -----------------------------------------------------------


// printDictionary()
// Prints the keys (only) of D in an order determined by the parameter ord.
// If ord is "pre", "in" or "post", executes the corresponding tree traversal
// on the underlying RBT, printing keys only (no values).  If ord is some
// other string, prints nothing.
void printDictionary(FILE* out, Dictionary D, const char * ord) {
  if(!D) {
    exit(1);
  }
  if (strcmp(ord,"pre") == 0) {
    preOrderTreeWalk(out, D->root);
  }
  else if (strcmp(ord, "post") == 0) {
    postOrderTreeWalk(out, D->root);
  }
  else if ( strcmp(ord,"in") == 0) {
    inOrderTreeWalk(out, D->root);
  }
  //else do nothing
}
