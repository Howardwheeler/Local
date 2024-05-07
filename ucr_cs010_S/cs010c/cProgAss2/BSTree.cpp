#include "BSTree.h"

bool BSTree::search(const string &item) const // recursively calls findNode and returns true if it exists
{
    return findNode(root, item);
}

string BSTree::largest() const // follows the right branch until it finds the biggest node
{
    if (is_empty(root)) // if the tree doesn't exist, returns blank
    {
        return "";
    }
    return largest_helper(root)->item;
}

string BSTree::smallest() const // follows the left branch until it finds the biggest node
{
    if (is_empty(root)) // if the tree doesn't exist, return blank
    {
        return "";
    }
    return smallest_helper(root)->item;
}

int BSTree::height(const string &item) const // recursively finds height
{
    nodePtr *searchNode = findNode(root, item);
    if (is_empty(searchNode)) // if the item looking for doesn't exist, it just returns -1
    {
        return -1;
    }
    else
    {
        return findHeight(searchNode); // recursive call
    }
}

void BSTree::insert(const string &item)
{
    if (is_empty(root))
    {                             // checks if tree is empty
        root = new nodePtr(item); // makes a new node at the root
    }
    else
    {
        nodePtr *selected_node = root; // declares a node starting from the root
        while (true)                   // loops until return is called
        {
            if (item == selected_node->item)
            { // already exists in the tree ...fyi i can use findNode() function to do this
                selected_node->count += 1;
                return;
            }
            else if (item < selected_node->item)
            { // cycles the left side of the list
                if (is_empty(selected_node->left_branch))
                { // if reached leaf node, insert it
                    selected_node->left_branch = new nodePtr(item);
                    return;
                }
                else
                {
                    selected_node = selected_node->left_branch; // cycles nodes
                }
            }
            else
            { // cycles through the right side of the list
                if (is_empty(selected_node->right_branch))
                { // if reached leaf node, insert it
                    selected_node->right_branch = new nodePtr(item);
                    return;
                }
                else
                {
                    selected_node = selected_node->right_branch; // cycles nodes
                }
            }
        }
    }
}

void BSTree::remove(const string &item)
{
    nodePtr *removeNode = findNode(root, item); // finds a node to remove
    if (is_empty(removeNode))
    { // empty tree
        return;
    }
    if (removeNode->count > 1)
    { // the item holds multiple count
        removeNode->count--;
        return;
    }

    if (is_empty(removeNode->left_branch) && is_empty(removeNode->right_branch)) // if the node is a leaf node
    {
        if (removeNode == root) // and if the leafnode is the root, set root to nullptr
        {
            root = nullptr;
        }
        else // otherwise find the parent node of the leaf node and then deallocate the node's memory
        {
            nodePtr *newParent = parentNode(root, removeNode);
            if (newParent->right_branch == removeNode) // checks if the node to be removed is on the left or right branch of the parent node
            {
                delete newParent->right_branch;
                newParent->right_branch = nullptr;
            }
            else
            {
                delete newParent->left_branch;
                newParent->left_branch = nullptr;
            }
        }
    }
    else if (!is_empty(removeNode->left_branch)) // if its not a leaf node, and the left branch is not null, call remove recursively
    {
        remove(removeNode, largest_helper(removeNode->left_branch));
    }
    else // if the left branch is null but right branch isn't, then call remove recursively
    {
        remove(removeNode, smallest_helper(removeNode->right_branch));
    }
}

void BSTree::preOrder() const // calls the recursive function
{
    preOrder_print(root);
}

void BSTree::inOrder() const // calls the recursive function
{
    inOrder_print(root);
}

void BSTree::postOrder() const // calls the recursive function
{
    postOrder_print(root);
}

nodePtr *BSTree::findNode(nodePtr *selected_node, const string &find_item) const
{
    if (is_empty(selected_node)) // a recursive function that iterates through nodes until it eithr finds the node with the item or not
    {
        return nullptr; // if the node doesn't exist, returns null
    }
    else if (selected_node->item == find_item)
    {
        return selected_node; // it found it! returns the node
    }
    else
    {
        if (selected_node->item > find_item)
        {
            return findNode(selected_node->left_branch, find_item); // searches the left branches
        }
        else
        {
            return findNode(selected_node->right_branch, find_item); // searches the right branches
        }
    }
}

nodePtr *BSTree::parentNode(nodePtr *selected_node, nodePtr *swapNode) const // finds parent node of selectedNode
{
    if (selected_node == nullptr)
    {
        return nullptr; // if it doesn't exist, returns null
    }
    else if (selected_node->left_branch == swapNode || selected_node->right_branch == swapNode)
    {
        return selected_node; // yay it found it! so returns that node
    }
    else
    {
        if (selected_node->item > swapNode->item)
        {
            return parentNode(selected_node->left_branch, swapNode); // otherwise, recursively iterates to the left and right branches
        }
        else
        {
            return parentNode(selected_node->right_branch, swapNode);
        }
    }

    return nullptr;
}

int BSTree::findHeight(nodePtr *selected_node) const
{
    if (is_empty(selected_node))
    {
        return -1; // base case to return -1 if the bottom of the tree is met or node doesn't exist
    }
    return std::max(findHeight(selected_node->left_branch), findHeight(selected_node->right_branch)) + 1; // finds the max amount of links and adds 1 to each iteration to find height of node
}

nodePtr *BSTree::largest_helper(nodePtr *selected_node) const
{
    if (selected_node->right_branch == nullptr) // recursively iterates through the right branch until it cant go right anymore, and returns the node
    {
        return selected_node;
    }
    else
    {
        return largest_helper(selected_node->right_branch);
    }
}

nodePtr *BSTree::smallest_helper(nodePtr *selected_node) const
{
    if (selected_node->left_branch == nullptr) // recursively iterates through the left branch until it cant go left anymore,and returns that node
    {
        return selected_node;
    }
    else
    {
        return smallest_helper(selected_node->left_branch);
    }
}

void BSTree::remove(nodePtr *selectedParent, nodePtr *selected_node)
{
    selectedParent->item = selected_node->item; // copy the predecessor/successor's item and count
    selectedParent->count = selected_node->count;
    if (is_empty(selected_node->left_branch) && is_empty(selected_node->right_branch)) // checks if predecessor/sucessor is a leaf node
    {
        if (is_empty(parentNode(selectedParent->left_branch, selected_node)) && is_empty(parentNode(selectedParent->right_branch, selected_node)))
        {                                                     // checks if selectedParent's child is selected_node,, if thats the case, deallocating the leaf node is easier
            if (selectedParent->left_branch == selected_node) // checks which branch the leaf node is on, then deallocates it
            {
                delete selectedParent->left_branch;
                selectedParent->left_branch = nullptr;
            }
            else
            {
                delete selectedParent->right_branch;
                selectedParent->right_branch = nullptr;
            }
        }
        else if (is_empty(parentNode(selectedParent->left_branch, selected_node))) // otherwise checks if the node is a predecessor
        {
            nodePtr *newParent = parentNode(selectedParent->right_branch, selected_node); // calls the parent node of the predecessor, then checks which branch its on and deallocates it
            if (newParent->right_branch == selected_node)
            {
                delete newParent->right_branch;
                newParent->right_branch = nullptr;
            }
            else
            {
                delete newParent->left_branch;
                newParent->left_branch = nullptr;
            }
        }
        else // otherwise, it must be a successor so it again finds the parent node of the leaf node and finds which branch the leaf is on, then deallocates the leaf
        {
            nodePtr *newParent = parentNode(selectedParent->left_branch, selected_node);
            if (newParent->right_branch == selected_node)
            {
                delete newParent->right_branch;
                newParent->right_branch = nullptr;
            }
            else
            {
                delete newParent->left_branch;
                newParent->left_branch = nullptr;
            }
        }
        return;
    }
    if (!is_empty(selected_node->left_branch)) // if its not a leaf node and the left branch exists, recursively calls with the predecessor node
    {
        remove(selected_node, largest_helper(selected_node->left_branch));
    }
    else // otherwise, the right branch exists so it recursively calls with the successor node
    {
        remove(selected_node, smallest_helper(selected_node->right_branch));
    }
}

void BSTree::preOrder_print(nodePtr *selected_node) const // top to bottom
{
    if (is_empty(selected_node)) // base case to finish printing
    {
        return;
    }
    cout << selected_node->item << "(" << selected_node->count << "), "; // prints the node its on currently, then recursively calls the left branches and then the right branches
    preOrder_print(selected_node->left_branch);
    preOrder_print(selected_node->right_branch);
}

void BSTree::inOrder_print(nodePtr *selected_node) const // left to right
{
    if (is_empty(selected_node)) // base case again
    {
        return;
    }
    inOrder_print(selected_node->left_branch); // it calls the left most branches first, then prints the current node, then the right branches
    cout << selected_node->item << "(" << selected_node->count << "), ";
    inOrder_print(selected_node->right_branch);
}

void BSTree::postOrder_print(nodePtr *selected_node) const // bottom to top
{
    if (is_empty(selected_node)) // base case again
    {
        return;
    }
    postOrder_print(selected_node->left_branch); // iterates through the left branches first, then the right branches, then prints out the current node.
    postOrder_print(selected_node->right_branch);
    cout << selected_node->item << "(" << selected_node->count << "), ";
}