#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::runtime_error;
using std::overflow_error;

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
  //use explicit so that code doesnt mistake it with conversion constructor
  explicit Node(const string& word); 
};
