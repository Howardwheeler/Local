#pragma once

#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::ofstream;
using std::overflow_error;

struct Node{
    string data;
    Node* left;
    Node* right;
    int height;

    Node() : data(0), left(nullptr), right(nullptr), height(0) {}
    Node(const string &val) : data(val), left(nullptr), right(nullptr), height(0){}
};