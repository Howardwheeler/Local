#include "AVLTree.h"
#include <iostream>

AVLTree::~AVLTree() {
    delete root;
}

int AVLTree::height(Node* selectNode) {
    if (selectNode == nullptr) {
        return 0;
    }
    return std::max(height(selectNode->left), height(selectNode->right)) + 1;
}

int AVLTree::balanceFactor(Node* selectNode) {
    if (selectNode == nullptr) {
        return 0;
    }
    return height(selectNode->left) - height(selectNode->right);
}

Node* AVLTree::rotateRight(Node* exchangeNode) {
    Node* selectNode = exchangeNode->left;
    Node* exchangeNodeChild = selectNode->right;

    selectNode->right = exchangeNode;
    exchangeNode->left = exchangeNodeChild;

    exchangeNode->height = std::max(height(exchangeNode->left), height(exchangeNode->right)) + 1;
    selectNode->height = std::max(height(selectNode->left), height(selectNode->right)) + 1;
    return selectNode;
}

Node* AVLTree::rotateLeft(Node* selectNode) {
    Node* exchangeNode = selectNode->right;
    Node* exchangeNodeChild = exchangeNode->left;

    exchangeNode->left = selectNode;
    selectNode->right = exchangeNodeChild;

    selectNode->height = std::max(height(selectNode->left), height(selectNode->right)) + 1;
    exchangeNode->height = std::max(height(exchangeNode->left), height(exchangeNode->right)) + 1;
    return exchangeNode;
}

void AVLTree::insert(Node*& selectNode, const string& data) {
    if (selectNode == nullptr) {
        selectNode = new Node(data);
        return;
    }

    if (data < selectNode->data) {
        insert(selectNode->left, data);
    } else if (data > selectNode->data) {
        insert(selectNode->right, data);
    }
    
    selectNode->height = std::max(height(selectNode->left), height(selectNode->right)) + 1;

    int balance = balanceFactor(selectNode);

    if (balance > 1 && data < selectNode->left->data) {
        selectNode = rotateRight(selectNode);
    } else if (balance < -1 && data > selectNode->right->data) {
        selectNode = rotateLeft(selectNode);
    } else if (balance > 1 && data > selectNode->left->data) {
        selectNode->left = rotateLeft(selectNode->left);
        selectNode = rotateRight(selectNode);
    } else if (balance < -1 && data < selectNode->right->data) {
        selectNode->right = rotateRight(selectNode->right);
        selectNode = rotateLeft(selectNode);
    }
}

void AVLTree::insert(const string& data) {
    insert(root, data);
}

void AVLTree::printBalanceFactor(Node* selectNode) {
    if (selectNode == nullptr) {
        return;
    }

    printBalanceFactor(selectNode->left);
    cout << selectNode->data << "(" << balanceFactor(selectNode) << "), ";
    printBalanceFactor(selectNode->right);
}

void AVLTree::printBalanceFactors() {
    printBalanceFactor(root);
    cout << endl;
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS << "digraph G {"<<endl;
    visualizeTree(outFS, root);
    outFS << "}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}