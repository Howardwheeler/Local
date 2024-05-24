#pragma once

#include "PrintJob.h"

const int MAX_HEAP_SIZE = 10;

class Heap{
    PrintJob* arr[MAX_HEAP_SIZE];
    int numItems;
public:
    Heap() : numItems(0) {}
    void enqueue(PrintJob* job);
    void dequeue();
    PrintJob* highest();
    void print();
private:
    void trickleDown(int numItems);
};