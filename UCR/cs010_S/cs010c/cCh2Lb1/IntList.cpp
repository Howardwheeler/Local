#include <iostream>
#include "IntList.h"

using namespace std;

IntList::IntList() : dummyhead(0), dummytail(0){
    dummyhead.next = &dummytail; dummyhead.prev = nullptr; //constructs a dummy tail and head set with data values of 0
    dummytail.prev = &dummyhead; dummytail.next = nullptr; //have them both point to eachother initially
}

IntList::~IntList(){
    while(!empty()) //condition is met only if list is not empty
    { 
        pop_front(); //pop_front till list is empty
    }
}

void IntList::push_front(int value){
    IntNode* newNode = new IntNode(value);
    if(empty()) //checks if list empty
    {
        newNode->prev = &dummyhead; //if list has nothing in it, the new node is placed between tail and head
        newNode->next = &dummytail; //newnode's next is pointed to dummytail and prev is pointed to dummyhead initially to prevent leaks
        dummyhead.next = newNode; //points dummyhead and dummytail back to newnode to officially place it in between the 2 nodes
        dummytail.prev = newNode;
    }
    else{
        newNode->prev = &dummyhead; //if list is not "empty", points newnode's prev to head and next to first node 
        newNode->next = dummyhead.next; 
        newNode->next->prev = newNode; //then it points the head and the next node back to newnode so that it snuggles between the 2 nodes
        dummyhead.next = newNode;
    }
}

void IntList::pop_front(){
    IntNode* eraseNode = dummyhead.next; //selects first node
    if(empty()) //check if list empty
    {
        return;
    }
    dummyhead.next = eraseNode->next;
    eraseNode->next->prev = &dummyhead; //deletes the first node and replaces position with dummy head... aka it basically gets rid of first node and brings dummyhead and the second node togehter
    delete eraseNode; //deletes the first node
}

void IntList::push_back(int value){
    IntNode* newNode = new IntNode(value);
    if(empty()) //check if list empty
    {
        newNode->prev = &dummyhead; //if list has nothing in it, the new node is placed between tail and head
        newNode->next = &dummytail; //newnode's next is pointed to dummytail and prev is pointed to dummyhead initially to prevent leaks
        dummyhead.next = newNode; //points dummyhead and dummytail back to newnode to officially place it in between the 2 nodes
        dummytail.prev = newNode;
    }
    else{
        newNode->prev = dummytail.prev; //if list is not "empty", points newnode's next to tail and prev to the node before tail
        newNode->next = &dummytail;
        dummytail.prev->next = newNode; //then it points the tail and the node before tail back to the newnode so that it snuggles between the 2 nodes
        dummytail.prev = newNode;
    }
}

void IntList::pop_back(){
    IntNode* eraseNode = dummytail.prev; //selects last node
    if(empty())//checks if list empty
    {
        return;
    }
    dummytail.prev = eraseNode->prev; //deletes the last node and replaces position with dummytail... aka it basically gets rid of the last node and brings dummytail and the second to last node together
    eraseNode->prev->next = &dummytail;
    delete eraseNode; //deletes last node
}

bool IntList::empty() const{
    if(dummyhead.next == &dummytail) //checks if there are no nodes between dummy head and tail
    {
        return true;
    }
    else{
        return false;
    }
}

ostream & operator<<(ostream &out, const IntList &rhs){
    IntNode* selected = rhs.dummyhead.next; //selects first node
    while(selected != &rhs.dummytail)
    {
        out << selected->data; //output data values to output file
        if(selected->next != &rhs.dummytail)//iterates till last node to add whitespace between output
        {
            out << " ";
        }
        selected = selected->next;
    }
    return out;
}

void IntList::printReverse() const{
    IntNode* currNode = dummytail.prev;
    if(empty()) //prints nothing if list is empty
    {
        return;
    }
    while(currNode != &dummyhead) //iterates through the list backwards skipping dummy tail and head
    {
        cout << currNode->data << " ";
        currNode = currNode->prev; //iterates backwards until dummyhead is reached
    }
}