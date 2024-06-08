#pragma once

#include "WordEntry.h"

class HashTable{
	list<WordEntry> *hashTable;
	int size;
public:
    HashTable() : hashTable(NULL), size(0) {}
	HashTable(int size);
	~HashTable();
	HashTable(const HashTable &copy) = delete;
    HashTable& operator=(const HashTable &rhs) = delete;

	bool contains(const string &word) const;
	double getAverage(const string &word) const;
	void put(const string &word, int score); 
private:
	int computeHash(const string &size) const;
};