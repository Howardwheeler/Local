#pragma once

#include <iostream>
using namespace std;

struct IntNode {
    int data;
    IntNode* prev;
    IntNode* next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList{
    IntNode dummyhead;
    IntNode dummytail;
public:
    IntList();
    ~IntList();
    IntList(const IntList& cpy) = delete;
    IntList& operator=(const IntList&rhs) = delete;
    void push_front(int value);
    void pop_front();
    void push_back(int value);
    void pop_back();
    bool empty() const;
    friend ostream & operator <<(ostream &out, const IntList &rhs);
    void printReverse() const;
};