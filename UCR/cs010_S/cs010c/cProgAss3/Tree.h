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
  void remove(const string & word);
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  Node* search(const string & word);

private:
  void fix(Node* emptyNode);
  bool hasTwoChildSibling(Node* sibling) const;
  void preOrder(const Node* thisNode) const;
  void inOrder(const Node* thisNode) const;
  void postOrder(const Node* thisNode) const;
  void insert(Node* thisNode, Node* thisParent, Node* insertNode);
  void fixOrder(Node* thisNode) const;
  void fixChildren(Node* thisNode) const;
  void swap(Node* node1, Node* node2) const;

  bool noChildren(const Node* thisNode) const;
  string whichStringIsMiddle(const string& small, const string& large, const string& word) const;
  Node* findLeaf(Node* thisNode, const string& word) const;
  Node* search(Node* thisNode, const string& word);
};
