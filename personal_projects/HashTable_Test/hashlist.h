#pragma once

#include "words.h"
#include <list>

using std::list;

class hashlist{
    list<words> hashList;
public:
    void insertWord(const words& word){
        hashList.push_back(word);
    }

    void removeWord(const words& word){
        hashList.remove(word);
    }

    void printList() const{
        for (const auto& currWord : hashList){
            std::cout << currWord.getWord() << ", " << currWord.getLength() << " / ";
        }
        std::cout << std::endl;
    }

    bool searchWord(const string& word, words& foundWord) const{
        for (const auto& currWord : hashList){
            if (word == currWord.getWord()) {
                foundWord = currWord;
                return true;
            }
        }
        return false;
    }
};