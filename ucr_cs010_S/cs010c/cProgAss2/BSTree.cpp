#include "BSTree.h"

bool BSTree::search(const string &item) const{
    return findNode(root, item);
}

string BSTree::largest() const{
    if(is_empty(root)){
        return "";
    }
    return largest_helper(root)->item;
}

string BSTree::smallest() const{
    if(is_empty(root)){
        return "";
    }
    return smallest_helper(root)->item;
}

int BSTree::height(const string &item) const{
    nodePtr *searchNode = findNode(root, item);
    if(is_empty(searchNode)){
        return -1;
    } else{
        return findHeight(searchNode);
    }
}

void BSTree::insert(const string &item){
    if(is_empty(root)){ //checks if tree is empty
        root = new nodePtr(item); //makes a new node at the root
    } else{
        nodePtr *selected_node = root;
        while(true){
            if(item == selected_node->item){ //already exists in the tree ...fyi i can use findNode() function to do this
                selected_node->count += 1;
                return;
            } else if(item < selected_node->item){ //cycles the left side of the list
                if(is_empty(selected_node->left_branch)){ //if reached leaf node, insert it
                    selected_node->left_branch = new nodePtr(item);
                    return;
                } else{
                    selected_node = selected_node->left_branch; //cycles nodes
                }
            } else{ //cycles through the right side of the list
                if(is_empty(selected_node->right_branch)){ //if reached leaf node, insert it
                    selected_node->right_branch = new nodePtr(item);
                    return;
                } else{
                    selected_node = selected_node->right_branch; //cycles nodes
                }
            }
        }
    }
}

void BSTree::remove(const string &item){
    nodePtr *removeNode = findNode(root, item);
    if(is_empty(removeNode)){ //empty tree
        return;
    }
    if(removeNode->count > 1){ //the item holds multiple count
        removeNode->count--;
        return;
    }
    
    if(is_empty(removeNode->left_branch) && is_empty(removeNode->right_branch)){
        if(removeNode == root){
            root = nullptr;
        } else{
            nodePtr *newParent = parentNode(root, removeNode);
            if(newParent->right_branch == removeNode){
                delete newParent->right_branch;
                newParent->right_branch = nullptr;
            } else{
                delete newParent->left_branch;
                newParent->left_branch = nullptr;
            }
        }
    } else if(!is_empty(removeNode->left_branch)){
        remove(removeNode, largest_helper(removeNode->left_branch));

    } else{
        remove(removeNode, smallest_helper(removeNode->right_branch));
    }
}

void BSTree::preOrder() const{
    preOrder_print(root);
}

void BSTree::inOrder() const{
    inOrder_print(root);
}

void BSTree::postOrder() const{
    postOrder_print(root);
}

nodePtr* BSTree::findNode(nodePtr *selected_node, const string &find_item) const{
    if(is_empty(selected_node)){
        return nullptr;
    } else if(selected_node->item == find_item){
        return selected_node;
    } else{
        if(selected_node->item > find_item){
            return findNode(selected_node->left_branch, find_item);
        } else{
            return findNode(selected_node->right_branch, find_item);
        }
    }
}

nodePtr* BSTree::parentNode(nodePtr *selected_node, nodePtr *swapNode) const{
    if(selected_node == nullptr){
        return nullptr;
    } else if(selected_node->left_branch == swapNode || selected_node->right_branch == swapNode){
        return selected_node;
    } else{
        if(selected_node->item > swapNode->item){
            return parentNode(selected_node->left_branch, swapNode);
        } else{
            return parentNode(selected_node->right_branch, swapNode);
        }
    }

    return nullptr;
}

int BSTree::findHeight(nodePtr *selected_node) const{
    if(is_empty(selected_node)){
        return -1;
    }
    return std::max(findHeight(selected_node->left_branch), findHeight(selected_node->right_branch)) + 1;
}

nodePtr* BSTree::largest_helper(nodePtr *selected_node) const{
    if(selected_node->right_branch == nullptr){
        return selected_node;
    } else{
        return largest_helper(selected_node->right_branch);
    }
}

nodePtr* BSTree::smallest_helper(nodePtr *selected_node) const{
    if(selected_node->left_branch == nullptr){
        return selected_node;
    } else{
        return smallest_helper(selected_node->left_branch);
    }
}

void BSTree::remove(nodePtr *selectedParent, nodePtr *selected_node){
    selectedParent->item = selected_node->item;
    selectedParent->count = selected_node->count;
    if(is_empty(selected_node->left_branch) && is_empty(selected_node->right_branch)){
        if(is_empty(parentNode(selectedParent->left_branch, selected_node)) && is_empty(parentNode(selectedParent->right_branch, selected_node))){
            if(selectedParent->left_branch == selected_node){
                delete selectedParent->left_branch;
                selectedParent->left_branch = nullptr;
            } else{
                delete selectedParent->right_branch;
                selectedParent->right_branch = nullptr;
            }
        } else if(is_empty(parentNode(selectedParent->left_branch, selected_node))){
            nodePtr *newParent = parentNode(selectedParent->right_branch, selected_node);
            if(newParent->right_branch == selected_node){
                delete newParent->right_branch;
                newParent->right_branch = nullptr;
            } else{
                delete newParent->left_branch;
                newParent->left_branch = nullptr;
            }
        } else{
            nodePtr *newParent = parentNode(selectedParent->left_branch, selected_node);
            if(newParent->right_branch == selected_node){
                delete newParent->right_branch;
                newParent->right_branch = nullptr;
            } else{
                delete newParent->left_branch;
                newParent->left_branch = nullptr;
            }
        }
        return;
    }
    if(!is_empty(selected_node->left_branch)){
        remove(selected_node, largest_helper(selected_node->left_branch));
    } else{
        remove(selected_node, smallest_helper(selected_node->right_branch));
    }
}

void BSTree::preOrder_print(nodePtr *selected_node) const{
    if(is_empty(selected_node)){
        return;
    }
    cout << selected_node->item << "(" << selected_node->count << "), ";
    preOrder_print(selected_node->left_branch);
    preOrder_print(selected_node->right_branch);
}

void BSTree::inOrder_print(nodePtr *selected_node) const{
    if(is_empty(selected_node)){
        return;
    }
    inOrder_print(selected_node->left_branch);
    cout << selected_node->item << "(" << selected_node->count << "), ";
    inOrder_print(selected_node->right_branch);
}

void BSTree::postOrder_print(nodePtr *selected_node) const{
    if(is_empty(selected_node)){
        return;
    }
    postOrder_print(selected_node->left_branch);
    postOrder_print(selected_node->right_branch);
    cout << selected_node->item << "(" << selected_node->count << "), ";
}