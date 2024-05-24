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
    int balanceFactor(Node* selectNode);
    void printBalanceFactors();
    void visualizeTree(const string &out);
private:
    int height(Node* selectNode);
    void deleteTree(Node* selectNode);
    void insert(Node*& selectNode, const string& word);
    Node* rotateLeft(Node* selectNode);
    Node* rotateRight(Node* selectNode);
    void printBalanceFactor(Node* selectNode);
    void visualizeTree(ofstream &out, Node* root);
};