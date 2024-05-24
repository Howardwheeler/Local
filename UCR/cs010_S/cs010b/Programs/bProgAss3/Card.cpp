#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

#include "Card.h"

Card::Card(){
    suit = 'c';
    rank = 2;
}

Card::Card(char suit1, int rank1){
    suit = tolower(suit1);
    rank = rank1;
    if(suit != 'c' && suit != 'd' && suit != 'h' && suit != 's')
    {
        suit = 'c';
    }
    if(rank < 1 || rank > 13)
    {
        rank = 2;
    }
}

char Card::getSuit() const{
    return suit;
}

int Card::getRank() const{
    return rank;
}

ostream & operator<<(ostream &out, const Card &hand){
    char suit = hand.suit;
    int rank = hand.rank;
    string str1;
    if(suit == 'c')
    {
        str1 = "Clubs";
    }
    if(suit == 'h')
    {
        str1 = "Hearts";
    }
    if(suit == 'd')
    {
        str1 = "Diamonds";
    }
    if(suit == 's')
    {
        str1 = "Spades";
    }

    if(rank != 1 && rank < 11)
    {
        out << rank << " of " << str1;
    }
    if(rank == 1)
    {
        out << "Ace of " << str1;
    }
    if(rank == 11)
    {
        out << "Jack of " << str1;
    }
    if(rank == 12)
    {
        out << "Queen of " << str1;
    }
    if(rank == 13)
    {
        out << "King of " << str1;
    }
    return out;
}