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

    Node() : data(NULL), left(nullptr), right(nullptr) {}
    Node(const string &word) : data(word), left(nullptr), right(nullptr) {}
};