#include "PrintJob.h"

PrintJob::PrintJob(int priority, int jobNumber, int numPages) : priority(priority), jobNumber(jobNumber), numPages(numPages) {}

int PrintJob::getPriority(){
    return priority;
}

int PrintJob::getJobNumber(){
    return jobNumber;
}

int PrintJob::getPages(){
    return numPages;
}