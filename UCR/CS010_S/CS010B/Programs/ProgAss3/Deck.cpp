#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "Deck.h"
#include "Card.h"

Deck::Deck(){
    for(unsigned i = 0; i < 4; ++i)
    {
        for(unsigned j = 13; j > 0; --j)
        {
            if(i == 0)
            {
                theDeck.push_back(Card('s', j));
            }
            if(i == 1)
            {
                theDeck.push_back(Card('h', j));
            }
            if(i == 2)
            {
                theDeck.push_back(Card('d', j));
            }
            if(i == 3)
            {
                theDeck.push_back(Card('c', j));
            }
        }
    }
}

Card Deck::dealCard(){
    Card cardSelect;
    cardSelect = theDeck.back();
    theDeck.pop_back();
    dealtCards.push_back(cardSelect);
    return cardSelect;
}

void Deck::shuffleDeck(){
    for(unsigned i = 0; i < dealtCards.size(); i++)
    {
        theDeck.push_back(dealtCards[i]);
    }
    dealtCards.clear();
    if(dealtCards.size() == 0)
    {
        random_shuffle(theDeck.begin(), theDeck.end());
    }
}

unsigned Deck::deckSize() const{
    return theDeck.size();
}