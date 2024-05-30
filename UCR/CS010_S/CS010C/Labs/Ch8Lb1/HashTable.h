#pragma once

#include "WordEntry.h"

class HashTable{
	list<WordEntry> *hashTable;
	int size;
public:
    HashTable() : hashTable(NULL), size(0) {}
	HashTable(int size);
	bool contains(const string &word) const;
	double getAverage(const string &word) const;
	void put(const string &, int); 
private:
	int computeHash(const string &size) const;
};