#pragma once

#include "hashlist.h"
#include <vector>

using std::vector;
using std::runtime_error;

class hashtable{
    vector<hashlist> table;
    int size;
public:
    hashtable(int size = 8) : table(size), size(size) {}

    void insert(const string& word);
    void remove(const string& word);
    void printIndex(const int index) const;
private:
    int indexFinder(const string& word) const;
};