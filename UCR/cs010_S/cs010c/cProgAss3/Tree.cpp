#include "Tree.h"

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
  root = nullptr;
}

Tree::~Tree() {
  // TURD: You have to write this eventually, but you can
  // wait until remove works correctly and then just keep
  // removing the smallest key in the root until the tree
  // is empty
}

/*
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
}*/






void Tree::preOrder() const {
  preOrder(root);
  cout << endl;
}

void Tree::preOrder(const Node* thisNode) const{ //why is the node const?
  if(thisNode == nullptr){
    return;
  }
  cout << thisNode->small << ", ";
  preOrder(thisNode->left);
  cout << thisNode->large << ", ";
  preOrder(thisNode->middle);
  preOrder(thisNode->right);
}

void Tree::inOrder() const{
  inOrder(root);
  cout << endl;
}

void Tree::inOrder(const Node* thisNode) const{
  if(thisNode == nullptr){
    return;
  }
  inOrder(thisNode->left);
  cout << thisNode->small << ", ";
  inOrder(thisNode->middle);
  cout << thisNode->large << ", ";
  inOrder(thisNode->right);
}

void Tree::postOrder() const{
  postOrder(root);
  cout << endl;
}

void Tree::postOrder(const Node* thisNode) const{
  if(thisNode == nullptr){
    return;
  }
  postOrder(thisNode->left);
  postOrder(thisNode->middle);
  cout << thisNode->small << ", ";
  postOrder(thisNode->right);
  cout << thisNode->large << ", ";
}

void Tree::insert(const string &word){
  if(search(word) != nullptr){       //checks if the word already exists, then throws exception
    throw overflow_error("The Node Already Exists!");
  } else if(root == nullptr){       //checks if the root doesn't exist, then makes new root
    root = new Node(word);
  } else{             //otherwise, finds correct leaf node
    Node* thisNode = root;
    while(!noChildren(thisNode)){
      if(word < thisNode->small){
        thisNode = thisNode->left;
      } else if(word > thisNode->large){
        thisNode = thisNode->right;
      } else{
        thisNode = thisNode->middle;
      }
    }
    Node* insertNode = new Node(word);
    insert(thisNode, thisNode->parent, insertNode);
  }
}

void Tree::insert(Node* thisNode, Node* thisParent, Node* insertNode){
  if(thisNode == nullptr){
    root = insertNode;
    return;
  } else if(thisNode->small.empty() || thisNode->large.empty()){
    if(thisNode->large.empty()){
      thisNode->large = insertNode->small;
    } else{
      thisNode->small = insertNode->small;
    }
    thisNode->numData++;
    delete insertNode;
    fixOrder(thisNode);
    fixChildren(thisNode);
    return;
  } else{
    Node* thisNodeSibling;
    string middle = whichStringIsMiddle(thisNode->small, thisNode->large, insertNode->small);
    if (middle == insertNode->small){
      thisNodeSibling = new Node(thisNode->large);
      thisNode->large.clear();
      thisNode->numData--;
    } else if(middle == thisNode->large){
      thisNodeSibling = insertNode;
      insertNode = new Node(thisNode->large);
      thisNode->large.clear();
      thisNode->numData--;
    } else{
      thisNodeSibling = insertNode;
      insertNode = new Node(thisNode->small);
      thisNode->small.clear();
      fixOrder(thisNode);   //write the case for if this isnt a leaf node
      thisNode->numData--;
    }
    if(thisParent == nullptr){
      insert(thisParent, nullptr, insertNode);
      insertNode->left = thisNode;
      insertNode->middle = thisNodeSibling;
      fixChildren(insertNode);
    } else{
      if(thisNode == thisParent->left){
        thisParent->left = nullptr;
      } else if(thisNode == thisParent->middle){
        thisParent->middle = nullptr;
      } else{
        thisParent->right = nullptr;
      }
      insert(thisParent, thisParent->parent, insertNode);
      thisParent->left = thisNode;
      thisParent->middle = thisNodeSibling;
      fixChildren(thisParent);
    }
    return;
  }
}

void Tree::fixChildren(Node* thisNode) const {
  Node* placeholder;
  if(noChildren(thisNode)){
    return;
  }
  while(true) {
    if(thisNode->large.empty()){
      if(thisNode->right != nullptr && thisNode->small > thisNode->right->large) {
        placeholder = thisNode->right;
        thisNode->right = thisNode->middle;
        thisNode->middle = thisNode->left;
        thisNode->left = placeholder;
        cout << "check check4" << endl;
      } else if(thisNode->middle != nullptr && thisNode->small > thisNode->middle->large) {
        placeholder = thisNode->middle;
        thisNode->middle = thisNode->left;
        thisNode->left = placeholder;
        cout << "check check4" << endl;
      } else if(true){

      }
    } else if(!thisNode->large.empty()){
      if(thisNode->left != nullptr && thisNode->large < thisNode->left->small) {
        placeholder = thisNode->left;
        thisNode->left = thisNode->right;
        thisNode->right = thisNode->middle;
        thisNode->middle = placeholder;
        cout << "check check1" << endl;
      } else if(thisNode->middle != nullptr && thisNode->large < thisNode->middle->small) {
        placeholder = thisNode->middle;
        thisNode->middle = thisNode->right;
        thisNode->right = placeholder;
        cout << "check check2" << endl;
      }
    } else{
      break;
    }



    if(thisNode->left != nullptr && thisNode->middle != nullptr){
      if(thisNode->left->small > thisNode->middle->small){
        placeholder = thisNode->left;
        thisNode->left = thisNode->middle;
        thisNode->middle = placeholder;
      }
    } else if(thisNode->left != nullptr && thisNode->right != nullptr){
      if(thisNode->left->small > thisNode->right->small){
        placeholder = thisNode->left;
        thisNode->left = thisNode->right;
        thisNode->right = placeholder;
      }
    } else if(thisNode){
      //give up point
    }
  }
}

void Tree::fixOrder(Node* thisNode) const{
  if(thisNode->small.empty()){
    thisNode->small = thisNode->large;
    thisNode->large.clear();
    thisNode->left = thisNode->middle;
    thisNode->middle = thisNode->right;
    return;
  }
  if(thisNode->small > thisNode->large){
    string placeholder = thisNode->small;
    thisNode->small = thisNode->large;
    thisNode->large = placeholder;
  }
}

Node* Tree::search(const string& word) {
  return search(root, word);
}

Node* Tree::search(Node* thisNode, const string&word){
  if(thisNode == nullptr){
    return nullptr;
  }
  if(thisNode->small == word || thisNode->large == word){
    return thisNode;
  } else{
    if(word < thisNode->small){
      return search(thisNode->left, word);
    } else if(word > thisNode->large){
      return search(thisNode->right, word);
    } else{
      return search(thisNode->middle, word);
    }
  }
}

string Tree::whichStringIsMiddle(const string& small, const string& large, const string& word) const{
  if((small < word && word < large) || (large < word && word < small)){
    return word;
  } else if((word < small && small < large) || (large < small && small < word)){
    return small;
  } else{
    return large;
  }
}

bool Tree::noChildren(const Node* thisNode) const{
  return (thisNode->left == nullptr && thisNode->middle == nullptr && thisNode->right == nullptr);
}