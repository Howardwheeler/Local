#include "Tree.h"

Tree::Tree() {
  root = nullptr;
}

Tree::~Tree() {
  // TURD: You have to write this eventually, but you can
  // wait until remove works correctly and then just keep
  // removing the smallest key in the root until the tree
  // is empty
}

void Tree::insert(const string &word){
  if(search(word) != nullptr){       //checks if the word already exists, then throws exception
    throw overflow_error("The Node Already Exists!");
  } else if(root == nullptr){       //checks if the root doesn't exist, then makes new root
    root = new Node(word);
  } else{             //otherwise, finds correct leaf node
    Node* thisNode = findLeaf(root, word);
    Node* insertNode = new Node(word);
    insert(thisNode, thisNode->parent, insertNode);
  }
}

void Tree::insert(Node* thisNode, Node* thisParent, Node* insertNode){
  if(thisNode == nullptr){
    root = insertNode;
  } else if(thisNode->small.empty() || thisNode->large.empty()){
    if(thisNode->large.empty()){
      thisNode->large = insertNode->small;
    } else{
      thisNode->small = insertNode->small;
    }
    thisNode->numData++;
    delete insertNode;
    fixOrder(thisNode);
  } else{
    Node* thisNodeSibling;
    int flag = 0;
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
      thisNode->parent = insertNode;
      thisNodeSibling->parent = insertNode;
    } else{
      if(thisParent != nullptr && (thisParent->small.empty() || thisParent->large.empty())){
        flag++;
      }
      insert(thisParent, thisParent->parent, insertNode);

      if(thisNode == thisParent->left){
        thisParent->left = nullptr;
      } else if(thisNode == thisParent->middle){
        thisParent->middle = nullptr;
      } else{
        thisParent->right = nullptr;
      }
      if(flag > 0){
        if(thisParent->middle != nullptr && thisParent->right == nullptr && thisParent->large < thisParent->middle->small){
          thisParent->right = thisParent->middle;
          thisParent->middle = nullptr;
        }
        if(thisNode->small > thisNodeSibling->small){
          Node* placeholder = thisNode;
          thisNode = thisNodeSibling;
          thisNodeSibling = placeholder;
        }
        if(thisParent->left != nullptr){
          thisParent->middle = thisNode;
          thisParent->right = thisNodeSibling;
        } else if(thisParent->middle != nullptr){
          thisParent->left = thisNode;
          thisParent->right =thisNodeSibling;
        } else{
          thisParent->left = thisNode;
          thisParent->middle = thisNodeSibling;
        }
        thisNode->parent = thisParent;
        thisNodeSibling->parent = thisParent;
      } else{
        if(thisParent->parent == insertNode){
          insertNode = insertNode->middle;
          insertNode->left = thisNode;
          insertNode->middle = thisParent->right;
          thisParent->right = nullptr;
          thisParent->middle = thisNodeSibling;
          thisNodeSibling->parent = thisParent;
          thisNode->parent = insertNode;
          insertNode->middle->parent = insertNode;
          return;
        } else{
          thisNode->parent->middle = thisNodeSibling;
          thisNode->parent->parent->middle->left = thisNode;
          thisNode->parent->parent->middle->middle = thisNode->parent->right;
          thisNode->parent->right = nullptr;
          return;




          // insertNode->left = thisNode;
          // insertNode->middle = thisNodeSibling;
          // thisNode->parent = insertNode;
          // thisNodeSibling->parent = insertNode;
        }
      }
    }
  }
  return;
}

void Tree::remove(const string& word) {
  if (!root){ //checks if root is nullptr
    return;
  }
  Node* removeNode = search(word); //searches for the word in tree
  if(removeNode == nullptr){ //if the word doesn't exist, nothing happens
    return;
  }
  if(removeNode == root){ 
    if(noChildren(removeNode)){ //if removing stuff from root and root is the only node,
      if(removeNode->large.empty() || removeNode->small.empty()){ //if only one thing in the root node, set root to null
        root = nullptr;
        return;
      } else{ //otherwise, gets rid of the word, then fixes the root
        if(removeNode->large == word){
          removeNode->large.clear();
        } else{
          removeNode->small.clear();
          fixOrder(removeNode);
        }
        return;
      }
    } else{ //if the root does have children,
      if(removeNode->large.empty()){ //if only 2 children on the root
        if(removeNode->left->large.empty() && removeNode->middle->large.empty()){ //if those 2 children only have 1 string, it gets rid of the one in the root and moves the 2 strings to the root
          root = removeNode->left;
          removeNode->left->large = removeNode->middle->small;
          delete removeNode->middle;
          delete removeNode;
          return;
        } else if(!removeNode->left->large.empty()){ //otherwise, depending on the left or middle child, it will rotate
          removeNode->small = removeNode->left->large;
          removeNode->left->large.clear();
          return;
        } else{
          removeNode->small = removeNode->middle->small;
          removeNode->middle->small.clear();
          fixOrder(removeNode->middle);
          return;
        }
      }
    }
  } else if(noChildren(removeNode)){ //if the word to remove is in the leaf node, 
    if(removeNode == removeNode->parent->left){
      if(!removeNode->small.empty() && !removeNode->large.empty()){
        if(removeNode->small == word){
          removeNode->small.clear();
          fixOrder(removeNode);
        } else{
          removeNode->large.clear();
        }
        return;
      }
    }
    if(removeNode->parent->large.empty()){ //if there is only 1 sibling,
      if(removeNode->small == word){ //gets rid of the word
        removeNode->small.clear();
      } else{
        removeNode->large.clear();
      }
      if(removeNode->small.empty() && removeNode->large.empty()){  //if the node becomes empty
        if(removeNode->parent->left == removeNode){
          if(removeNode->parent->middle->large.empty()){
            removeNode->parent->large = removeNode->parent->middle->small;
            removeNode->parent->middle = nullptr;
            removeNode->parent->left = nullptr;
            return;
          } else{
            fix(removeNode);
            return;
          }
        } else if(removeNode->parent->middle == removeNode){
          if(removeNode->parent->left->large.empty()){
            removeNode->parent->large = removeNode->parent->left->small;
            fixOrder(removeNode->parent);
            removeNode->parent->left = nullptr;
            removeNode->parent->middle = nullptr;
            return;
          } else{
            fix(removeNode);
            return;
          }
        }
      }
    } else{
      if(removeNode == removeNode->parent->left){
        if(removeNode->parent->middle->large.empty()){
          removeNode->parent->middle->large = removeNode->parent->small;
          removeNode->parent->small.clear();
          fixOrder(removeNode->parent);
          fixOrder(removeNode->parent->middle);
          removeNode->parent->left = removeNode->parent->middle;
          removeNode->parent->middle = removeNode->parent->right;
          removeNode->parent->right = nullptr;
          return;
        }
      } else if(removeNode == removeNode->parent->middle){
        if(word == removeNode->small){
          removeNode->small.clear();
          fixOrder(removeNode);
        }
        if(removeNode->parent->right->large.empty()){
          if(removeNode->parent->left->large.empty()){
            removeNode->parent->left->large = removeNode->parent->small;
            removeNode->parent->small = removeNode->parent->middle->small;
            removeNode->parent->middle->small.clear();
          }
          removeNode->small = removeNode->parent->large;
          removeNode->large = removeNode->parent->right->small;
          removeNode->parent->large.clear();
          removeNode->parent->right = nullptr;
          return;
        }
      } else if(removeNode == removeNode->parent->right){
        if(removeNode->parent->middle->large.empty()){
          removeNode->parent->middle->large = removeNode->parent->large;
          removeNode->parent->large.clear();
          removeNode->parent->right = nullptr;
          delete removeNode;
          return;
        }
      }
      return;
    }
  }
}

void Tree::fix(Node* emptyNode) {
  if(emptyNode->parent->left == emptyNode){
    emptyNode->parent->small = emptyNode->small;
    emptyNode->parent->small = emptyNode->parent->middle->small;
    fixOrder(emptyNode->parent->middle);
    return;
  } else if(emptyNode->parent->middle == emptyNode){
    emptyNode->parent->small = emptyNode->small;
    emptyNode->parent->small = emptyNode->parent->left->small;
    fixOrder(emptyNode->parent->left);
    return;
  }


}

bool Tree::hasTwoChildSibling(Node* thisNode) const {
  if(thisNode->parent == nullptr){
    return false;
  } else if(!thisNode->parent->left || !thisNode->parent->middle || !thisNode->parent->right){
    return false;
  } else{
    return true;
  }
}

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
  if(!thisNode->large.empty()){
    cout << thisNode->large << ", ";
  }
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
  if(!thisNode->large.empty()){
    cout << thisNode->large << ", ";
  }
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
  if(!thisNode->large.empty()){
    cout << thisNode->large << ", ";
  }
}

Node* Tree::findLeaf(Node* thisNode, const string& word) const{
  if(noChildren(thisNode)){
    return thisNode;
  }
  if(!thisNode->small.empty() && !thisNode->large.empty()){
    if(word < thisNode->small){
      return findLeaf(thisNode->left, word);
    } else if(word < thisNode->large){
      return findLeaf(thisNode->middle, word);
    } else{
      return findLeaf(thisNode->right, word);
    }
  } else if(thisNode->large.empty()){
    if (word < thisNode->small){
      return findLeaf(thisNode->left, word);
    } else{
      return findLeaf(thisNode->middle, word);
    }
  } else{
    if(word < thisNode->large){
      return findLeaf(thisNode->middle, word);
    } else{
      return findLeaf(thisNode->right, word);
    }
  }
}

void Tree::fixOrder(Node* thisNode) const{
  if(thisNode->small.empty() && thisNode->large.empty()){
    return;
  } else if(thisNode->small.empty()){
    thisNode->small = thisNode->large;
    thisNode->large.clear();
    return;
  } else if(thisNode->large.empty()){
    return;
  } else if(thisNode->small > thisNode->large){
    string placeholder = thisNode->small;
    thisNode->small = thisNode->large;
    thisNode->large = placeholder;
    return;
  } else{
    return;
  }
}

void Tree::swap(Node* node1, Node* node2) const{
  if(node1 == nullptr || node2 == nullptr){
    return;
  }
  Node* placeholder = node1;
  node1 = node2;
  node2 = placeholder;
  return;
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
  } else if(thisNode->large.empty()){
    if(word < thisNode->small){
      return search(thisNode->left, word);
    } else{
      return search(thisNode->middle, word);
    }
  } else{
    if(word < thisNode->small){
      return search(thisNode->left, word);
    } else if(word < thisNode->large){
      return search(thisNode->middle, word);
    } else{
      return search(thisNode->right, word);
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