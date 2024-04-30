#pragma once

#include "Node.h"

class BSTree{
    nodePtr *root;
public:
    BSTree() : root(nullptr) {}
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
    nodePtr *findNode(nodePtr *selected_node, const string &find_item) const;
    nodePtr *parentNode(nodePtr *selected_node, nodePtr *childNode) const;
    int findHeight(nodePtr *selected_node) const;
    nodePtr* largest_helper(nodePtr *selected_node) const;
    nodePtr* smallest_helper(nodePtr *selected_node) const;
    bool is_empty(nodePtr *selected_node) const { return selected_node == nullptr; }
    void remove(nodePtr *selectedParent, nodePtr *selected_node);
    void preOrder_print(nodePtr *selected_node) const;
    void inOrder_print(nodePtr *selected_node) const;
    void postOrder_print(nodePtr *selected_node) const;
};