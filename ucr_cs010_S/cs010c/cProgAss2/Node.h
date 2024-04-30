#pragma once

#include <iostream>
#include <algorithm>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;

struct nodePtr{
    string item;
    int count;
    nodePtr *left_branch;
    nodePtr *right_branch;

    //rule of three
    nodePtr() : count(0), left_branch(nullptr), right_branch(nullptr) {}
    nodePtr(const string &item) : item(item), count(1), left_branch(nullptr), right_branch(nullptr) {}
    ~nodePtr() { delete left_branch; delete right_branch; }
    nodePtr(const nodePtr &copy) = delete;
    nodePtr &operator=(const nodePtr &rhs) = delete;
};

ostream &operator<<(ostream &out, const nodePtr &rhs);