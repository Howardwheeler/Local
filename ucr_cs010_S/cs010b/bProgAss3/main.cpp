#include <iostream>
#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include "Deck.h"
#include "Card.h"

// Returns true if vector of Cards passed in contains at least 2 Cards with the same rank.
bool hasPair(const vector<Card> &hand){
    bool isTrue = false;
    for(unsigned int i = 0; i < hand.size(); i++)
    {
        for(unsigned int j = i+1; j < hand.size();j++)
        {
            if(hand[i].getRank() == hand[j].getRank())
            {
                isTrue = true;
            }
        }
    }
    return isTrue;
}

// Sends to output stream a hand of Cards on a single line, 
// each Card separated by a comma.
// If the vector is empty, do not output anything.
// Example (vector size of 3): Ace of Spades, Two of Hearts, King of Clubs 
ostream & operator<<(ostream &out, const vector<Card> &hand){
    if(hand.size() == 0)
    {
        return out;
    }
    else{
        for(unsigned int i = 0; i < hand.size()-1;i++)
        {
            out << hand[i] << ", ";
        }
        out << hand[hand.size()-1];
    }
    return out;
}

int main() {
    ofstream oFS;
    srand(2222);
    string userInput;
    string fileName;
    int numHands;
    int numDeals;
    int count = 0;
    Deck deck;
    vector<Card> dealtCards;
    Deck();

    cout << "Do you want to output all hands to a file?(Yes/No)" << endl;
    cin >> userInput;
    if(userInput == "Yes")
    {
        cout << "Enter name of output file:" << endl;
        cin >> fileName;
        oFS.open(fileName);
        if(!oFS.is_open())
        {
            cout << "Error opening file." << endl;
            return 1;
        }
    }
    cout << "Enter number of cards per hand: " << endl;
    cin >> numHands;
    cout << "Enter number of deals (simulations): " << endl;
    cin >> numDeals;

    for(int i = 0; i < numDeals; i++)
    {
        deck.shuffleDeck();
        dealtCards.clear();
        for(int j = 0; j < numHands; j++)
        {
            Card cards = deck.dealCard();
            dealtCards.push_back(cards);
        }
        if(hasPair(dealtCards) == true)
        {
            ++count;
            oFS << "Found Pair!! ";
        }
        else{
            oFS << "             ";
        }
        oFS << dealtCards << endl;
    }

    cout << "Chances of receiving a pair in a hand of " << numHands << " cards is: " << (static_cast<double>(count) / numDeals) * 100 << "%" << endl;
    deck.shuffleDeck();
    oFS.close();
    return 0;
}