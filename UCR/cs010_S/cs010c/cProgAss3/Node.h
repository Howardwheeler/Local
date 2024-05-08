#pragma once

#include <string>

using std::string;

class Node {

  friend class Tree;

private:
  string small;
  string large;
  int numData;

  Node* parent;
  Node* left;
  Node* middle;
  Node* right;

public:
  Node();

  // CODE TURD:
  // We want to use the explicit keyword here so that our
  // single parameter constructor doesn't get mistaken
  // for a conversion constructor.  See
  // https://www.geeksforgeeks.org/problem-with-single-argument-constructor-in-c-and-how-to-solve-it/
  explicit Node(const string& key);

  // CODE TURD:
  // We don't need a destructor here because everything is
  // torn down in the Tree
  
};
