#include "Tree.h"
#include <iostream>
#include <string>

using namespace std;

/* Uncomment these out if you want to use them... the 'static' means
   that they are only available here in Tree.cpp

static const string& midStr( const string& s1, const string& s2, const string& s3 ) {
  if (( s1 < s2 && s1 > s3 ) ||( s1 < s3 && s1 > s2 ) ) 
    return s1;
  else if (( s2 < s1 && s2 > s3 ) ||( s2 < s3 && s2 > s1 ) ) 
    return s2;
  else 
    return s3;
}

static const string& minStr( const string& s1, const string& s2, const string& s3 ) {
  if ( s1 < s2 && s1 < s3 ) 
    return s1;
  else if ( s2 < s1 && s2 < s3 ) 
    return s2;
  else
    return s3;
}

static const string& maxStr( const string& s1, const string& s2, const string& s3 ) {
  if ( s1 > s2 && s1 > s3 ) 
    return s1;
  else if ( s2 > s1 && s2 > s3 ) 
    return s2;
  else
    return s3;
}
*/

Tree::Tree() {
  root = NULL;
}

Tree::~Tree() {
  // TURD: You have to write this eventually, but you can
  // wait until remove works correctly and then just keep
  // removing the smallest key in the root until the tree
  // is empty
}


bool Tree::noChildren( Node* node ) const {
  throw runtime_error("You need to write this");
}

void Tree::insert( const string& word ) {
  if ( root == nullptr ) {
    root = new Node( word );
  } else {
    insert( root, word );
  }
}

// TURD: Concentrate on the easy ones needed for test1 first
void Tree::insert( Node* curr, const string& word ) {
  throw runtime_error("You need to write this to get simple insert working");
}

// This is handy since it puts a key into the right spot (small or
// large string)
void Tree::addData( Node* addHere, const string& word ) {
  throw runtime_error("You need to write this to get simple insert working");
}

void
Tree::preOrder() const {
  preOrder( root );
  cout << endl;
}

void Tree::preOrder( const Node* curr ) const {
  throw runtime_error("You need to write this really early on");
}

void Tree::inOrder() const {
  inOrder( root );
  cout << endl;
}

void Tree::inOrder(const Node* curr) const {
  throw runtime_error("You need to write this really early on");
}

void Tree::postOrder() const {
  postOrder( root );
  cout << endl;
}

void Tree::postOrder(const Node* curr) const {
  throw runtime_error("You need to write this really early on");
}

void Tree::remove(const string& word) {
  // Nothing to do in an empty tree, just return
  if ( !root )
    return;
  
  // Find the node that holds this key.  If it does not exist, then
  // we have nothing to do.  Just return (no error)

  // Removing the a key in the root is a special case
  // If it is the last key, better set root back to nullptr!

  // if the node to remove is not a leaf, move the value to a leaf
  // TURD: (This is the easiest strategy to do a remove -- though the
  // zybook isn't really clear about it)

  // if we made an empty node (numData == 0), we have to fix it
}

void Tree::fix(Node* emptyNode) {
  // This is where the real heart of the program is at...
  // We have to deal with fusion, rotation, redistribution
  // here

  // Some cases:
  // emptyNode is nullptr, do nothing
  // emptyNode is the root, one of our children becomes the root

  // check for redistribution... Can I steal from a sibling with two keys?

  // If not, I have to do a merge
}

bool Tree::hasTwoChildSibling(Node* sib) const {
  throw runtime_error("this one will be handy");
}

// TURD: This is NOT const because we want the node* so we can
// do a remove
Node* Tree::search(const string& word) {
  return search(root, word);
}

// TURD: You should know how to do this one for the final
Node* Tree::search( Node* curr, const string& word ) {
  throw runtime_error("you will need to write the helper");
}
