#include "WordLadder.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
  string dictFile, wordBegin, wordEnd, outFile; //declares the necessary strings for dictionary, first and last word, and output file
  cout << "Enter the name of the dictionary file: "; //takes in input for the string variables
  cin >> dictFile;
  cout << endl;
  cout << "Enter the name of the output file: ";
  cin >> outFile;
  cout << endl;
  cout << "Enter the first word: ";
  cin >> wordBegin;
  cout << endl;

  if (not cin) { //throws exception if input is invalid
    throw runtime_error("input failure");
  }

  while (wordBegin.size() != 5) { //if first and last word is not 5 letters, asks to retype it
    cout << "Word must have exactly 5 characters." << endl
         << "Please reenter the first word: ";
    if (not (cin >> wordBegin)) {
      throw runtime_error("Could not read 5 character first word");
    }
    cout << endl;
  }
  cout << "Enter the last word: ";
  if (not (cin >> wordEnd)) { //throws exception if the input is invalid
      throw runtime_error("Could not read 5 character last word");
  }
  cout << endl;
  while (wordEnd.size() != 5) { //for last word
    cout << "Word must have exactly 5 characters." << endl
         << "Please reenter the last word: ";
    cin >> wordEnd;
    if (not (cin >> wordEnd)) {
      throw runtime_error("Could not read 5 character last word");
    }
    cout << endl;
  }

  WordLadder wl(dictFile); //calls the constructor to make the dictionary list
	
  wl.outputLadder(wordBegin, wordEnd, outFile); //makes the word ladder

  return 0;
}