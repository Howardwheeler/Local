#include "Heap.h"

void Heap::enqueue(PrintJob* job){
    if(numItems >= MAX_HEAP_SIZE){
        return;
    }
    arr[numItems] = job;
    int i = numItems;
    while(i != 0 && arr[(i -1) /2]->getPriority() < arr[i]->getPriority()){
        swap(arr[i], arr[(i-1) /2]);
        i = (i-1)/2;
    }
    numItems++;
}

void Heap::dequeue(){
    if(numItems == 0){
        return;
    }
    trickleDown(numItems);
    numItems--;
}

PrintJob* Heap::highest(){
    if(numItems == 0){
        return nullptr;
    }
    return arr[0];
}

void Heap::print(){
    cout << "Priority: " << arr[0]->getPriority() << ", ";
    cout << "Job Number: " << arr[0]->getJobNumber() << ", ";
    cout << "Number of Pages: " << arr[0]->getPages() << endl;
}

void Heap::trickleDown(int numItems){
    int i = 0;
    arr[0] = arr[numItems-1];
    int child = 1;
    while(child < numItems){
        int max = i;
        for(int i = 0; i < 2 && i + child < numItems; i++){
            if(arr[i + child]->getPriority() > arr[max]->getPriority()){
                max = i + child;
            }
        }
        if(max == i){
            return;
        }
        else{
            swap(arr[i], arr[max]);
            i = max;
            child = 2*i + 1;
        }
    }
}