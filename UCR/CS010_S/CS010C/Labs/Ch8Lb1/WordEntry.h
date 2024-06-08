#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <cstdlib>

using std::string;
using std::list;
using std::ifstream;
using std::cout;
using std::endl;
using std::cin;

class WordEntry{
    string word;
	int numAppearances;
	int totalScore;
public:
    WordEntry() : word(NULL), numAppearances(1), totalScore(0) {}
	WordEntry(const string &word, int score) : word(word), numAppearances(1), totalScore(score) {}
	void addNewAppearance(int score);
	const string & getWord() const;
	double getAverage() const;
};