#include "Heap.h"

void Heap::enqueue(PrintJob* job){
    if(numItems >= MAX_HEAP_SIZE){ //checks if the size of the array is too big
        return; // if its too big, it will just return
    }
    arr[numItems] = job; //otherwise, add a new job into the array
    int i = numItems;
    while(i != 0 && arr[(i -1) /2]->getPriority() < arr[i]->getPriority()){ //then trickle up the array until the nodes are in the correct order,, this checks if the parent priority is bigger than the newly inserted priorirty
        swap(arr[i], arr[(i-1) /2]); //then swap it and iterate again
        i = (i-1)/2;
    }
    numItems++; //then add to size
}

void Heap::dequeue(){ 
    if(numItems == 0){    //checks if the size is 0, then do nothing
        return;
    }
    trickleDown(numItems); //otherwise call trickle down (fyi i removed the node in the helper function)
    numItems--; //then subtract to size
}

PrintJob* Heap::highest(){ //checks for the top node which is at the first index of the array
    if(numItems == 0){ //if the array is empty, return nullptr
        return nullptr;
    }
    return arr[0]; //returns first index of array
}

void Heap::print(){ //prints out the first index of the array's priority and job number and pages since the first index has the highest priority in the queue
    cout << "Priority: " << arr[0]->getPriority() << ", ";
    cout << "Job Number: " << arr[0]->getJobNumber() << ", ";
    cout << "Number of Pages: " << arr[0]->getPages() << endl;
}

void Heap::trickleDown(int numItems){
    int i = 0;
    arr[0] = arr[numItems-1]; //sets the highest job aka first index to the last index item
    int child = 1;
    while(child < numItems){ //then compares throughout the array 
        int max = i;
        for(int i = 0; i < 2 && i + child < numItems; i++){ //this loop trickles down the array to find the max. 
            if(arr[i + child]->getPriority() > arr[max]->getPriority()){
                max = i + child;
            }
        }
        if(max == i){
            return; //if the max is at the correct location, return 
        }
        else{
            swap(arr[i], arr[max]); //otherwise, swap the child and parent so that the orientation is correct
            i = max;
            child = 2*i + 1; //this equation helps to find the correct child nodes
        }
    }
}