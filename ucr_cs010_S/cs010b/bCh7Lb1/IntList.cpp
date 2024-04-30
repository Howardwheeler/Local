#include <iostream>
#include "IntList.h"

using namespace std;

IntList::IntList() : head(nullptr), tail(nullptr){

}

IntList::~IntList(){
    clear();
}

void IntList::clear(){
    while (head != nullptr)
    {
        IntNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void IntList::push_front(int value){
    IntNode* value1 = new IntNode(value);

    if (head == nullptr)
    {
        head = value1;
        tail = value1;
    }
    else{
        value1->next = head;
        head = value1;
    }
}

void IntList::pop_front(){
    if(head != nullptr)
    {
        IntNode* temp = head;
        head = head->next;
        delete temp;

        if(head == nullptr)
        {
            tail = nullptr;
        }
    }
}

bool IntList::empty() const{
    if(head == nullptr)
    {
        return true;
    }
    else{
        return false;
    }
}

const int & IntList::front() const{
    return head->value;
}

const int & IntList::back() const{
    if(head != nullptr)
    {
        IntNode* temp = head;
        while(temp->next != nullptr)
        {
            temp = temp->next;
        }
        return temp->value;
    }
    else{
        return tail->value;
    }
}

ostream & operator<<(ostream & out, const IntList &IntNode1){
    IntNode* temp = IntNode1.head;
    while(temp != nullptr)
    {
        out << temp->value;
        if(temp->next != nullptr)
        {
            out << " ";
        }
        temp = temp->next;
    }
    return out;
}