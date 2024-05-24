#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <vector>

#include "WordLadder.h"

using namespace std;

WordLadder::WordLadder(const string& filename){ //Constructor for WordLadder
    ifstream inFS(filename); //opens an input file with filename passed in by the function
    string words;

    if(!inFS.is_open()) //Checks if file opened correctly
    {
        throw runtime_error("Unable to open file"); //if it didn't open, it throws an exception (cout statement there for zybooks)
        //cout << "Unable to open file: " << filename << endl;
        //return;
    }
    else{
        while(inFS >> words) //otherwise, if file does open, loop through the file and put it into the string "words"
        {
            if(words.length() != 5) //if the word in the file is more than 5 characters, this throws an exception
            {
                throw runtime_error("Failed: file input"); //cout for zybooks
                //cout << "word is too long" << endl;
                //return;
            }
            dict.push_back(words); //then push back the words into the list called dict
        }
    }
    inFS.close(); //after all the words are in the list, close file
}

void WordLadder::outputLadder(const string& start, const string& end, const string& outputFile){
    int existance = 0; //a counter to check if the start and end words exist in the dictionary
    vector<string> outputStack; //a vector used to output the stack backwards (because the stack pushes the first word to the bottom)
    ofstream oFS(outputFile); //opens output file declared in the string "outputFile"
    stack<string> wordStack; //declares a new stack
    queue<stack<string>> wordQueue; //declares a new queue
    
    if(!oFS.is_open()){ //throws exception if the output file doesn't exist
        throw runtime_error("ERROR: output file doesn't exist");
        //cout << "Unable to open file: " << outputFile << endl;
        //return;
    }
    if(start == end){ //if the start word is the same as the finish word, the word ladder is just the word, so print that one word and return
        oFS << start;
        return;
    }
    wordStack.push(start); //push the start word onto the stack
    wordQueue.push(wordStack); //push that stack onto the queue
    while(!wordQueue.empty()){ //loops until the queue is empty, which basically loops forever until the return statement at line 86 is met
        wordStack = wordQueue.front(); //sets the selected stack to be the stack placed at the front of the queue
        wordQueue.pop(); //now pop that stack off the queue to iterate the queue in the while loop
        for(auto it = dict.begin(); it != dict.end();){ //for loop that iterates through the whole dictionary
            const string& x = *it; //sets X to the current dicionary word
            if(x == start || x == end){ //test case to determine if "start" and "end" exist in the dictionary
                ++existance;
            }
            if(letterChecker(wordStack.top(), x)){ //checks if the word is off by one letter
                stack<string> newStack = wordStack; //makes a copy of the initial stack
                newStack.push(x); //pushes the word onto the new stack
                wordQueue.push(newStack); //pushes the new stack onto the queue
                newStack.pop(); //remove the word inserted onto the stack so that you can try a different word in the dictionary
                it = dict.erase(it); //gets rid of the already used word in the dictionary
            }
            else{
                ++it; //if the word isn't off by one letter, just iterate through the dictionary
            }
        }
        if(existance < 1) { //if either "start" or "end" is not in the dictionary, output to the file an error message
            oFS << "Word does not exist" << endl;
            return;
        }
        if(wordStack.top() == end){ //if the latest word on the stack is the final word, iterate through the stack and push it onto the vector 
            while(!wordStack.empty()){
                outputStack.push_back(wordStack.top());
                wordStack.pop();
            }
            for(int i = outputStack.size()-1; i >= 0; --i){ //iterate through the vector backwards and then output the words onto the output file
                oFS << outputStack[i] << " ";
            }
            return;
        }
        
    }
    oFS << "No Word Ladder Found."; //if a word ladder cannot be found, print
    oFS.close(); //close the output file and done!
}

bool WordLadder::letterChecker(const string& selectedWord, const string& newWord) const{ //a helper function to figure out if the letters are off by 1
    int difference = 0; //adds a counter
    for(int n = 0; n < 5; n++){ //iterates through the words
        if(selectedWord[n] != newWord[n]){
            ++difference;
        }
    }
    return difference <= 1; //returns true if less than one letter is off
}