#pragma once

#include "Node.h"

using std::string;

class Tree {
private:
  Node* root;

public:
  Tree();
  ~Tree();
  Tree(const Tree&) = delete;
  Tree& operator=(const Tree&) = delete;
  
  void insert( const string & );
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  void remove( const string & );
  Node* search( const string & );

private:

  // MASSIVE CODE TURD
  // These helpers are suggested... the standard zybook solution used them
  // and you may find defining these useful. Some you absolutely
  // need (e.g. preOrder needs to have a helper function since it
  // MUST be done recursively to cover all nodes).   Use these as
  // a guide for planning what you might want to do.

  bool noChildren(Node* curr) const;
  void insert(Node* curr, const string& word);
  void addData(Node* addHere, const string& word);
  void preOrder(const Node* curr) const;
  void inOrder(const Node* curr) const;
  void postOrder(const Node* curr) const;
  void fix(Node* emptyNode);
  bool hasTwoChildSibling(Node* sibling) const;
  Node* search(Node* curr, const string& word);
};
