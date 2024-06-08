#include "hashtable.h"

void hashtable::insert(const string& word){
    words newWord(word);
    table[indexFinder(word)].insertWord(newWord);
}

void hashtable::remove(const string& word){
    words searchWord;
    if(table[indexFinder(word)].searchWord(word, searchWord)){
        table[indexFinder(word)].removeWord(searchWord);
    } else{
        throw runtime_error("word doesn't exist");
    }
}

void hashtable::printIndex(const int index) const{
    table[index].printList();
}

int hashtable::indexFinder(const string& word) const{
    return word.length() % size;
}