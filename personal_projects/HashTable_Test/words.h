#pragma once

#include <iostream>
#include <string>

using std::string;

class words{
    string word;
    int length;
public:
    words() : word(NULL), length(0) {}
    words(const string& word) : word(word), length(word.size()) {}

    string getWord() const{ return word; }
    int getLength() const{ return word.length(); }

    bool operator==(const words& other) const{ return word == other.getWord(); }
};