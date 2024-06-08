#include "HashTable.h"

// Constructor to initialize the hash table with a given size
HashTable::HashTable(int size) : size(size) {
    hashTable = new list<WordEntry>[size];		//makes a new list of word entries with a constant size
}

// Destructor to deallocate the hash table
HashTable::~HashTable(){
	delete[] hashTable;						//deletes the array of list of wordEntry
}

// Hash function to compute an index based on the word
int HashTable::computeHash(const string &word) const{  //this function computes the hash function to find the correct "bucket" or technically index.
    unsigned long hash = 5381;							//this hash function was chatGPT'ed !!! works tho
    for(char currChar : word) {
        hash = ((hash << 5) + hash) + currChar;
    }
    return hash % size;									//returns the hash index
}

// Checks if the word is already in the hash table
bool HashTable::contains(const string &word) const{
    int index = computeHash(word);						//finds the index using the hash function
    for(const auto &selectWord : hashTable[index]) {	//iterates through the whole list of the selected index and compares the word passed in and the word in the list
        if(selectWord.getWord() == word) {				//if the 2 words match, it exists and returns true, otherwise no
            return true;
        }
    }
    return false;
}

// Retrieves the average score for the word
double HashTable::getAverage(const string &word) const{
    int index = computeHash(word);						//finds the index using the hash function
    for(const auto &selectWord : hashTable[index]) {	//iterates thruogh the whole list of the selected index and compares the word passed in and the word in the list
        if(selectWord.getWord() == word) {				//if the words match, call the get average helper from wordEntry to return the average. 
            return selectWord.getAverage();
        }
    }
    return 2.0;  										//otherwise, default to neutral sentiment if word not found
}

// Inserts a word with its score into the hash table
void HashTable::put(const string &word, int score) {
    int index = computeHash(word);						//finds index again, same thing
    for(auto &selectWord : hashTable[index]) {			//iterates thruogh the whole list and compares again
        if(selectWord.getWord() == word) {				//if the 2 words match, add the score to the appearance in wordEntry
            selectWord.addNewAppearance(score);
            return;
        }
    }
    hashTable[index].emplace_back(word, score);			//otherwise, make a new copy of the word and the score passed in, and adds it to the end of the list
}

int main() {
	// declare a few needed variables for inputing the data
	string line;    
	int score;
	string message = " ";
	
	// open input file
	ifstream myfile("movieReviews.txt");
	if (myfile.fail()) {
	    cout << "could not open file" << endl;
	    exit(1);
	}
	
	//create hash table
	HashTable table(20071);
	
	while (!myfile.eof()) {
	    myfile >> score;     // get score
	    myfile.get();        // get blank space
	    getline(myfile, line);
	    int len = line.size();
	    while(len > 0) {     // identify all individual strings
	        string sub;
	        len = line.find(" ");
	        if (len > 0) {
	            sub = line.substr(0, len);
	            line = line.substr(len + 1, line.size());
	        }
	        else {
	            sub = line.substr(0, line.size() - 1);
	        }
	        table.put(sub, score); // insert string with the score
	    }
	}
	
	// after data is entered in hash function
	// prompt user for a new movie review
	while(message.length() > 0) {
	    cout << "enter a review -- Press return to exit: " << endl;
	    getline(cin, message);
	
	    // used for calculating the average
	    double sum = 0;
	    int count = 0;
	    
	    double sentiment = 0.0;
	    
	    size_t len = message.size();
	    // get each individual word from the input
	    while(len != string::npos) {
	        string sub;
	        len = message.find(" ");
	        if (len != string::npos) {
	            sub = message.substr(0, len);
	            message = message.substr(len + 1, message.size());
	        }
	        else {
	            sub = message;
	        }
	        // calculate the score of each word
	        sum += table.getAverage(sub);
	        ++count;
	    }
	
	    if (message.size() > 0) {
	    	sentiment = sum / count;
	        cout << "The review has an average value of " << sentiment << endl;
	        if (sentiment >= 3.0) {
	        	cout << "Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 2.0) {
	        	cout << "Somewhat Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 1.0) {
	        	cout << "Somewhat Negative Sentiment" << endl;
	        }
	        else {
	        	cout << "Negative Sentiment" << endl;
	        }
	        cout << endl;
	    }
	}
	
	return 0;
}