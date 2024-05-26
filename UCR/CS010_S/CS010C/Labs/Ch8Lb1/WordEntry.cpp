#include "WordEntry.h"

// Adds a new appearance of the word with the given score
void WordEntry::addNewAppearance(int score) {
    totalScore += score;
    numAppearances++;
}

// Returns the word
const string & WordEntry::getWord() const{
    return word;
}

// Returns the average score of the word
double WordEntry::getAverage() const{
    return static_cast<double>(totalScore) / numAppearances;
}