#pragma once

#include "Node.h"

class BSTree
{
    nodePtr *root;

public:
    BSTree() : root(nullptr) {} // rule of 3, and a constructor that initializes with null root
    ~BSTree() { delete root; }
    BSTree(const BSTree &copy) = delete;
    BSTree &operator=(const BSTree &rhs) = delete;

    bool search(const string &item) const;
    string largest() const;
    string smallest() const;
    int height(const string &item) const;

    void insert(const string &item);
    void remove(const string &item);
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;

private:
    nodePtr *findNode(nodePtr *selected_node, const string &find_item) const;        // helper function to find node
    nodePtr *parentNode(nodePtr *selected_node, nodePtr *childNode) const;           // helper function to find parent node
    int findHeight(nodePtr *selected_node) const;                                    // recursive function to find height
    nodePtr *largest_helper(nodePtr *selected_node) const;                           // recursive function to find the biggest node
    nodePtr *smallest_helper(nodePtr *selected_node) const;                          // recursive function to find the smallest node
    bool is_empty(nodePtr *selected_node) const { return selected_node == nullptr; } // checks if the node is null or not
    void remove(nodePtr *selectedParent, nodePtr *selected_node);                    // recursive remove functin
    void preOrder_print(nodePtr *selected_node) const;                               // prints out pre, in, and post orders (recursive helper)
    void inOrder_print(nodePtr *selected_node) const;
    void postOrder_print(nodePtr *selected_node) const;
};