#include <iostream>
#include "IntList.h"

using namespace std;

IntList::IntList() : head(nullptr), tail(nullptr){}

IntList::IntList(const IntList &cpy) : head(nullptr), tail(nullptr){
    int count = 0;
    IntNode* temp = cpy.head;
    while(temp != nullptr)
    {
        ++count;
        temp = temp->next;
    }
    temp = cpy.head;
    for(int i = 0; i < count; i++)
    {
        push_back(temp->value);
        temp = temp->next;
    }
}

IntList & IntList::operator=(const IntList &rhs){
    int count = 0;
    IntNode* temp = head;
    if(this != &rhs)
    {
        clear();
        temp = rhs.head;
        while(temp != nullptr)
        {
            ++count;
            temp = temp->next;
        }
        temp = rhs.head;
        for(int i = 0; i < count; i++)
        {
            push_back(temp->value);
            temp = temp->next;
        }
    }

    return *this;
}

IntList::~IntList(){
    clear();
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

bool IntList::empty() const{
    if(head == nullptr)
    {
        return true;
    }
    else{
        return false;
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

void IntList::push_back(int value){
    IntNode* value1 = new IntNode(value);
    
    if(head == nullptr)
    {
        head = value1;
        tail = value1;
    }
    else{
        tail->next = value1;
        tail = value1;
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

void IntList::selection_sort(){
    if(head == nullptr)
    {
        return;
    }

    int count = 0;
    int num;
    IntNode* temp = head;
    while(temp != nullptr)
    {
        ++count;
        temp = temp->next;
    }
    temp = head;
    for(int i = 0; i < count - 1; i++)
    {
        IntNode* tempMin = temp;
        IntNode* tempo = temp->next;
        for(int j = i + 1; j < count; j++)
        {
            if(tempo->value < tempMin->value)
            {
                tempMin = tempo;
            }
            tempo = tempo->next;
        }
        if(tempMin != temp)
        {
            num = temp->value;
            temp->value = tempMin->value;
            tempMin->value = num;
        }
        temp = temp->next;
    }
}

void IntList::insert_ordered(int value){
    IntNode* temp = head;
    IntNode* newNode = new IntNode(value);
    if(head == nullptr || head->value > newNode->value)
    {
        push_front(value);
    }
    else if(tail->value <= newNode->value)
    {
        push_back(value);
    }
    else{
        while(temp != nullptr && temp->next != nullptr)
        {
            if(temp->next->value >= newNode->value)
            {
                newNode->next = temp->next;
                temp->next = newNode;
                break;
            }
            temp = temp->next;
        }
    }
}

void IntList::remove_duplicates(){
    if(head == nullptr || head->next == nullptr)
    {
        return;
    }
    IntNode* temp = head;
    while(temp != nullptr && temp->next != nullptr)
    {
        IntNode* dupl = temp;
        while(dupl->next != nullptr)
        {
            if(dupl->next->value == temp->value)
            {
                IntNode* duplDelete = dupl->next;
                dupl->next = dupl->next->next;
                delete duplDelete;
            }
            else{
                dupl = dupl->next;
            }
        }
        temp = temp->next;
    }
}

void IntList::clear(){
    while (head != nullptr)
    {
        IntNode* temp = head;
        head = head->next;
        delete temp;
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