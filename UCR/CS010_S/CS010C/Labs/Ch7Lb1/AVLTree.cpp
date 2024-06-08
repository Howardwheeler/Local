#include "AVLTree.h"
#include <iostream>

AVLTree::~AVLTree() { //calls the recursive delete function to erase the whole tree
    deleteTree(root);
}


void AVLTree::deleteTree(Node* deleteNode){ 
    if (deleteNode != nullptr) //if the node pointed to is not nullptr, recursively checks the left and right childs, then deletes the pointed node
    {
        deleteTree(deleteNode->left);
        deleteTree(deleteNode->right);
        delete deleteNode;
    }
}

void AVLTree::insert(const string& word) { //calls the recursive insert function
    insert(root, word);
}

void AVLTree::insert(Node*& selectNode, const string& word) {
    if (selectNode == nullptr) { //if the pointed node is null, that means its a leaf node, so add it there
        selectNode = new Node(word);
        return;
    }
    if (word < selectNode->data) { //recursively iterates through the nodes to find correct spot for word
        insert(selectNode->left, word);
    } else if (word > selectNode->data) {
        insert(selectNode->right, word);
    } else{ //checks if the word already exists, then throw an overflow error
        throw overflow_error("This word already exists");
    }

    int balance = balanceFactor(selectNode); //this part recursively checks for an imbalance on the tree when new word is inserted, then rotates depending on where the new node's inserted at
    if (balance > 1 && word < selectNode->left->data) { //for left left scenario
        selectNode = rotateRight(selectNode);
    } else if (balance < -1 && word > selectNode->right->data) { //for right right scenario
        selectNode = rotateLeft(selectNode);
    } else if (balance > 1 && word > selectNode->left->data) { //for left right scenario
        selectNode->left = rotateLeft(selectNode->left);
        selectNode = rotateRight(selectNode);
    } else if (balance < -1 && word < selectNode->right->data) { //for right left scenario
        selectNode->right = rotateRight(selectNode->right);
        selectNode = rotateLeft(selectNode);
    }
}

int AVLTree::height(Node* selectNode) const{ //finds the height of selectNode using MAX() recursively
    if (selectNode == nullptr) {
        return -1;
    }
    return std::max(height(selectNode->left), height(selectNode->right)) + 1;
}

int AVLTree::balanceFactor(Node* selectNode) const{ //finds the balance factor by comparing the left and right child's height, and if the node doesn't exist just return 0
    if (selectNode == nullptr) {
        return 0;
    }
    return height(selectNode->left) - height(selectNode->right);
}

Node* AVLTree::rotateRight(Node* exchangeNode) { //finds the 3 correspoding nodes that are unbalanced, and rotates it to the right, then returns the root of the shift
    Node* selectNode = exchangeNode->left;
    Node* exchangeNodeChild = selectNode->right;

    selectNode->right = exchangeNode;
    exchangeNode->left = exchangeNodeChild;

    return selectNode;
}

Node* AVLTree::rotateLeft(Node* selectNode) { //finds the 3 corresponding nodes that are unbalanced, and rotates it to the left, then returns the root of the shift
    Node* exchangeNode = selectNode->right;
    Node* exchangeNodeChild = exchangeNode->left;

    exchangeNode->left = selectNode;
    selectNode->right = exchangeNodeChild;

    return exchangeNode;
}

void AVLTree::printBalanceFactor(Node* selectNode) const{ //prints the tree and its' balance factors
    if (selectNode == nullptr) {
        return;
    }

    printBalanceFactor(selectNode->left);
    cout << selectNode->data << "(" << balanceFactor(selectNode) << "), ";
    printBalanceFactor(selectNode->right);
}

void AVLTree::printBalanceFactors() const{ //calls the recursive function to print balance factors
    printBalanceFactor(root);
    cout << endl;
}

void AVLTree::visualizeTree(const string &outputFilename) const{ //a output file function that outputs the tree into an output file (optional)
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

void AVLTree::visualizeTree(ofstream & outFS, Node *n) const{ //recurive helper for the visualizetree function (optional)
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