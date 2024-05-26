#include "HashTable.h"

// Constructor to initialize the hash table with a given size
HashTable::HashTable(int size) {
    this->size = size;
    hashTable = new list<WordEntry>[size];
}

// Hash function to compute an index based on the word
int HashTable::computeHash(const string &word) const{
    unsigned long hash = 5381;
    for(char c : word) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

// Checks if the word is already in the hash table
bool HashTable::contains(const string &word) const{
    int index = computeHash(word);
    for(const auto &entry : hashTable[index]) {
        if(entry.getWord() == word) {
            return true;
        }
    }
    return false;
}

// Retrieves the average score for the word
double HashTable::getAverage(const string &word) {
    int index = computeHash(word);
    for(const auto &entry : hashTable[index]) {
        if(entry.getWord() == word) {
            return entry.getAverage();
        }
    }
    return 2.0;  // Default to neutral if word not found
}

// Inserts a word with its score into the hash table
void HashTable::put(const string &word, int score) {
    int index = computeHash(word);
    for(auto &entry : hashTable[index]) {
        if(entry.getWord() == word) {
            entry.addNewAppearance(score);
            return;
        }
    }
    hashTable[index].emplace_back(word, score);
}