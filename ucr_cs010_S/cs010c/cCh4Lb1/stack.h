#include <iostream>

using namespace std;

template<typename T> // makes a new template with typename T
class stack{
    const int MAX_SIZE = 20; //sets a variable to declare the max size of the stack array
    T data[20]; //initalizes the array with size 20
    int size; //to measure the current size of the array


public:
    stack() : size(0) {} //constructs a new stack with no size
    ~stack(){ //destructor for deleting the whole stack
        while(!empty()){
            pop();
        }
    }
    stack(const stack& copy) = delete; //copy constructor that does nothing.. for rule of 3
    stack &operator=(const stack& rhs) = delete; //copy operator that does nothing .. for rule of 3

    void push(T val){ //pushes the value T onto the stack
        if(size >= MAX_SIZE){
            throw overflow_error("Called push on full stack."); //throws overflow error if the stack is full
        }
        data[size++] = val; //adds onto the next index in the array and adds to size
    }
    void pop(){
        if(empty()){ //if the stack cant be popped, it throws a out of range error
            throw out_of_range("Called pop on empty stack.");
        }
        size--; //then subtracts the size so that the selected index moves down
    }
    void pop_two(){ 
        if(empty()){ //if the stack is empty or there is only one item is in the stack then it will throw an out of range error because it cant find an item to remove
            throw out_of_range("Called pop_two on empty stack.");
        } 
        else if(size == 1){
            throw out_of_range("Called pop_two on a stack of size 1.");
        }
        size-=2; //otherwise, subtract 2 sizes to the stack so that the index moves down twice
    }
    T top() const{ 
        if(empty()){ //if the stack is empty, it will throw a underflow error because there is no items in the stack. it will end up being 0
            throw underflow_error("Called top on empty stack.");
        }
        return data[size-1]; //otherwise, it will return the stack's top element which is size-1
    }
    bool empty() const{ //returns true if the stack is empty
        return (size == 0);
    }
};