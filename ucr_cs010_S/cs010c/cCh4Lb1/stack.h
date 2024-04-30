#include <iostream>

using namespace std;

template<typename T>
class stack{
    const int MAX_SIZE = 20;
    T data[20];
    int size;


public:
    stack() : size(0) {}
    void push(T val){
        if(size >= MAX_SIZE){
            throw overflow_error("Called push on full stack.");
        }
        data[size++] = val;
    }
    void pop(){
        if(empty()){
            throw out_of_range("Called pop on empty stack.");
        }
        size--;
    }
    void pop_two(){
        if(empty()){
            throw out_of_range("Called pop_two on empty stack.");
        } 
        else if(size == 1){
            throw out_of_range("Called pop_two on a stack of size 1.");
        }
        size--;
        size--;
    }
    T top() const{
        if(empty()){
            throw underflow_error("Called top on empty stack.");
        }
        return data[size-1];
    }
    bool empty() const{
        return (size == 0);
    }
};