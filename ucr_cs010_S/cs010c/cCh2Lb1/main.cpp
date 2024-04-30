#include <iostream>
#include "IntList.h"

using namespace std;

int main(){
    IntList list; //creates new object list
    int number;
    cout << "Enter amount of nodes" << endl;
    cin >> number;
    int n = 0;

    while(n < number)
    {
        list.push_front(n); //adds nodes to the list n times.
        n += 1;
    }
    list.pop_back(); //removes the last node in the list
    list.pop_front(); //removes the first node in the list (checking for functions)
    list.printReverse(); //prints out nodes to see if push_back works
}