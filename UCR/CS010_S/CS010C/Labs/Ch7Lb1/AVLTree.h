#pragma once

#include "Node.h"

class AVLTree{
    Node* root;
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree();
    AVLTree(const AVLTree &copy) = delete;
    AVLTree& operator=(const AVLTree &rhs) = delete;
    void insert(const string &word);
    int balanceFactor(Node* selectNode) const;
    void printBalanceFactors() const;
    void visualizeTree(const string &out) const;
private:
    int height(Node* selectNode) const;
    void deleteTree(Node* deleteNode);
    void insert(Node*& selectNode, const string& word);
    Node* rotateLeft(Node* selectNode);
    Node* rotateRight(Node* selectNode);
    void printBalanceFactor(Node* selectNode) const;
    void visualizeTree(ofstream &out, Node* root) const;
};