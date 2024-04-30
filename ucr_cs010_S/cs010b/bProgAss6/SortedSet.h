#include <iostream>
#include "IntList.h"

#ifndef SORTEDSET_H
#define SORTEDSET_H

using namespace std;

class SortedSet : public IntList{
    public:
        SortedSet();
        SortedSet(const SortedSet &cpy);
        SortedSet(const IntList &cpy);
        ~SortedSet();
        bool in(int value1) const;
        SortedSet operator|(const SortedSet &rhs) const;
        SortedSet operator&(const SortedSet &rhs) const;
        void add(int value1);
        void push_front(int value1);
        void push_back(int value1);
        void insert_ordered(int value1);
        SortedSet & operator|=(const SortedSet &rhs);
        SortedSet & operator&=(const SortedSet &rhs);
};

#endif