#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdexcept>

#include "IntVector.h"

using namespace std;

IntVector::IntVector(unsigned capacity, int value) : _size(capacity), _capacity(capacity) {
    if(capacity <= 0)
    {
        _data = nullptr;
    }
    else{
        _data = new int[capacity];
        for(unsigned int i = 0; i < capacity; i++)
        {
            _data[i] = value;
        }
    }

}

IntVector::~IntVector(){
    delete[] _data;
}

unsigned IntVector::size() const{
    return _size;
}

unsigned IntVector::capacity() const{
    return _capacity;
}

bool IntVector::empty() const{
    if(_size == 0)
    {
        return true;
    }
    else{
        return false;
    }
}

const int & IntVector::at(unsigned index) const{
    if(index >= _size)
    {
        throw out_of_range("IntVector::at_range_check");
    }
    return _data[index];
}

const int & IntVector::front() const{
    return _data[0];
}

const int & IntVector::back() const{
    return _data[_size-1];
}

void IntVector::insert(unsigned index, int value){
    if(index > _size)
    {
        throw out_of_range("IntVector::insert_range_check");
    }

    if(_size >= _capacity || _capacity == 0)
    {
        expand();
    }
    for(unsigned i = _size; i > index; i--)
    {
        _data[i] = _data[i-1];
    }
    _data[index] = value;
    ++_size;
}

void IntVector::erase(unsigned index){
    if(index >= _size)
    {
        throw out_of_range("IntVector::erase_range_check");
    }

    if(index < _size)
    {
        for(unsigned i = index; i < _size -1; i++)
        {
            _data[i] = _data[i+1];
        }
        _data[_size-1] = 0;
        --_size;
    }
}

void IntVector::assign(unsigned n, int value){
    if(n >= _capacity && n >= (_capacity*2))
    {
        expand(n-_capacity); 
    }
    else if(n >= _capacity && n < (_capacity*2))
    {
        expand();
    }

    _size = n;
    for(unsigned i = 0; i < _size; i++)
    {
        _data[i] = value;
    }
}

void IntVector::push_back(int value){
    if(_size >= _capacity)
    {
        expand();
    }
    ++_size;
    _data[_size-1] = value;
}

void IntVector::pop_back(){
    --_size;
}

void IntVector::clear(){
    _size = 0;
}

void IntVector::resize(unsigned n, int value){
    if(n >= _capacity && n >= (_capacity*2))
    {
        expand(n-_capacity); 
    }
    else if(n >= _capacity && n < (_capacity*2))
    {
        expand();
    }

    if(n < _size)
    {
        _size = n;
    }
    else{
        for(unsigned i = _size; i < n; i++)
        {
            _data[i] = value;
        }
        _size = n;
    }

}

void IntVector::reserve(unsigned n){
    if(_capacity <= n)
    {
        expand(n-_capacity);
    }
}

void IntVector::expand(){
    int *temp;
    _capacity = _capacity  * 2;
    if(_capacity == 0)
    {
        _capacity = 1;
    }
    temp = new int[_capacity];
    for(unsigned i = 0; i < _size; i++)
    {
        temp[i] = _data[i];
    }
    delete[] _data;
    _data = new int[_capacity];
    for(unsigned i = 0; i < _size; i++)
    {
        _data[i] = temp[i];
    }
    delete[] temp;
}

void IntVector::expand(unsigned amount){
    int *temp;
    _capacity = _capacity  + amount;
    temp = new int[_capacity];
    for(unsigned i = 0; i < _size; i++)
    {
        temp[i] = _data[i];
    }
    delete[] _data;
    _data = new int[_capacity];
    for(unsigned i = 0; i < _size; i++)
    {
        _data[i] = temp[i];
    }
    delete[] temp;
}

int & IntVector::at(unsigned index){
    if(index >= _size)
    {
        throw out_of_range("IntVector::at_range_check");
    }
    return _data[index];
}

int & IntVector::front(){
    return _data[0];
}

int & IntVector::back(){
    return _data[_size -1];
}