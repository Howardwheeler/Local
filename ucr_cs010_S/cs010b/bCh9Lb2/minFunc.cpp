#include "minFunc.h"
const int * min(const int arr[], int arrSize) {
    if(arrSize == 0)
    {
        return nullptr;
    }
    else if(arrSize == 1)
    {
        return arr;
    }
    else{
        const int * mintest = min(arr+1, arrSize-1);
        if(*mintest < *arr)
        {
            return mintest;
        }
        else{
            return arr;
        }
    }
}