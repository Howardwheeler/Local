#include <ostream>
#include <iostream>
#include "IntList.h"
#include "SortedSet.h"

using namespace std;

int main () {

    IntList alist;
    alist.push_back(3);
    alist.push_back(9);
    alist.push_back(2);
    alist.push_back(7);
    alist.push_back(7);

    IntList blist;
    blist.push_back(5);
    blist.push_back(2);
    blist.push_back(6);
    blist.push_back(1);
    blist.push_back(8);

    cout << "alist: " << alist << endl;
    cout << "blist: " << blist << endl;
cout << "---------------------------------------------------" << endl;

    // test making a sorted a list

    SortedSet slist(alist);
    cout << "slist: " << slist << endl;
    SortedSet copySList(slist);
    cout << "copySList: " << copySList << endl;
cout << "------------------------------------------------------------" << endl;
    SortedSet slist2(blist);
    cout << "slist2: " << slist2 << endl;
    SortedSet copySList2(blist);
    cout << "copySList2: " << copySList2 << endl;
cout << "-------------------------------------------------------------" << endl;
// make sure copySList is a deep copy
    copySList.pop_front();
    cout << "after modifying copySList: " << endl;
    cout << "slist: " << slist << endl;
    cout << "copySList: " << copySList << endl;
cout << "---------------------------------------------------------------" << endl;
    //test for in

    cout << "test for 2: ";
    if (slist.in(2)) {
        cout << "true" << endl;
    }
    else {
        cout << "false" << endl;
    }
    cout << "test for 5: ";
    if (slist.in(5)) {
        cout << "true" << endl;
    }
    else {
        cout << "false" << endl;
    }
cout << "--------------------------------------------------------------" << endl;
    //test for union operator
    SortedSet unionSet = slist | slist2;
    cout << "Union of slist and slist2: " << endl;
    cout << unionSet << endl;
cout << "------------------------------------------------------------" << endl;
    SortedSet interSet = slist & slist2;
    cout << "Intersection of slist and slist2: " << endl;
    cout << interSet << endl;
cout << "------------------------------------------------------------" << endl;
//test for add,pushback,push_front;

    SortedSet mySet;

    mySet.add(3);
    mySet.add(1);
    mySet.add(5);
    mySet.add(3); // Duplicates are not added
    mySet.add(2);

    // Test push_front function 
    mySet.push_front(4);
    mySet.push_front(1); // Duplicates are not added

    // Test push_back function 
    mySet.push_back(6);
    mySet.push_back(4); // Duplicates are not added

   cout << "SortedSet: " << mySet << endl;
cout << "__" << endl;
    //test union assign and intersect assign

    cout << slist << endl;
    cout << slist2 << endl;

    SortedSet intersectList(slist);

    slist|=slist2;
    cout << "Union of slist and slist2: " << endl;
    cout << slist << endl;

    intersectList &= slist2;
    cout << "Intersection of slist and slist2:" << endl;
    cout << intersectList << endl;

    return 0;
}