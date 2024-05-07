#pragma once

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::swap;

class PrintJob{
    int priority;
    int jobNumber;
    int numPages;
public:
    PrintJob(int priority, int jobNumber, int numberPages);

    int getPriority();
    int getJobNumber();
    int getPages();
};