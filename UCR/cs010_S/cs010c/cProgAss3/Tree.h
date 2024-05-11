#pragma once

#include "Node.h"

class Tree {
private:
  Node* root;

public:
  Tree();
  ~Tree();
  Tree(const Tree& cpy) = delete;
  Tree& operator=(const Tree& rhs) = delete;
  
  void insert(const string &word);
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  //void remove(const string & word);
  Node* search(const string & word);

private:
  //void addData(Node* addHere, const string& word); was for insert
  //void fix(Node* emptyNode);
  //bool hasTwoChildSibling(Node* sibling) const;


  void preOrder(const Node* thisNode) const;
  void inOrder(const Node* thisNode) const;
  void postOrder(const Node* thisNode) const;
  void insert(Node* thisNode, Node* thisParent, Node* insertNode);
  void fixOrder(Node* thisNode) const;
  void fixChildren(Node* thisNode) const;

  bool noChildren(const Node* thisNode) const;
  string whichStringIsMiddle(const string& small, const string& large, const string& word) const;
  Node* search(Node* thisNode, const string& word);
};
