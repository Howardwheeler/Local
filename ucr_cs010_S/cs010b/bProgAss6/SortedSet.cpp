#include <iostream>

#include "SortedSet.h"

using namespace std;

SortedSet::SortedSet() : IntList(){}

SortedSet::SortedSet(const SortedSet &cpy) : IntList(cpy){
    selection_sort();
}

SortedSet::SortedSet(const IntList &cpy) : IntList(cpy){
    remove_duplicates();
    selection_sort();
}

SortedSet::~SortedSet(){}

bool SortedSet::in(int value1) const{
    IntNode* temp = head;
    while(temp != nullptr)
    {
        if(temp->value == value1)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

SortedSet SortedSet::operator|(const SortedSet &rhs) const{
    SortedSet set;
    IntNode* temp = head;
    IntNode* rhstemp = rhs.head;
    while(temp != nullptr || rhstemp != nullptr)
    {
        if(temp == nullptr)
        {
            set.add(rhstemp->value);
            rhstemp = rhstemp->next;
        }
        else if(rhstemp == nullptr)
        {
            set.add(temp->value);
            temp = temp->next;
        }
        else{
            if(!in(rhstemp->value))
            {
                set.add(rhstemp->value);
                rhstemp = rhstemp->next;
            }
            else{
                rhstemp = rhstemp->next;
            }
            if(!in(temp->value))
            {
                set.add(temp->value);
                temp = temp->next;
            }
            else{
                set.add(temp->value);
                temp = temp->next;
            }
        }
    }
    return set;
}

SortedSet SortedSet::operator&(const SortedSet &rhs) const{
    SortedSet set;
    IntNode* rhstemp = rhs.head;
    IntNode* temp = head;
    while(temp != nullptr && rhstemp != nullptr)
    {
        if(!in(temp->value))
        {
            temp = temp->next;
        }
        else if(!in(rhstemp->value))
        {
            rhstemp = rhstemp->next;
        }
        else{
            set.add(temp->value);
            temp = temp->next;
            rhstemp = rhstemp->next;
        }
    }
    return set;
}

void SortedSet::add(int value){
    if(!in(value))
    {
        IntList::insert_ordered(value);
        //remove_duplicates();
    }
}

void SortedSet::push_front(int value){
    add(value);
}

void SortedSet::push_back(int value){
    add(value);
}

void SortedSet::insert_ordered(int value){
    add(value);
}

SortedSet & SortedSet::operator|=(const SortedSet &rhs){
    SortedSet set;
    IntNode* rhstemp = rhs.head;
    IntNode* temp = head;
    while(temp != nullptr || rhstemp != nullptr)
    {
        if(temp == nullptr)
        {
            set.add(rhstemp->value);
            rhstemp = rhstemp->next;
        }
        else if(rhstemp == nullptr)
        {
            set.add(temp->value);
            temp = temp->next;
        }
        else{
            if(!in(rhstemp->value))
            {
                set.add(rhstemp->value);
                rhstemp = rhstemp->next;
            }
            else{
                rhstemp = rhstemp->next;
            }
            if(!in(temp->value))
            {
                set.add(temp->value);
                temp = temp->next;
            }
            else{
                set.add(temp->value);
                temp = temp->next;
            }
        }
    }
    //swap(head, set.head);
    //swap(tail, set.tail);
    *this = set;
    return *this;
}

SortedSet & SortedSet::operator&=(const SortedSet &rhs){
    SortedSet set;
    IntNode* temp = rhs.head;
    while(temp != nullptr)
    {
        if(in(temp->value))
        {
            set.add(temp->value);
        }
        temp = temp->next;
    }
    if(rhs.empty())
    {
        set.clear();
    }
    *this = set;
    return *this;
}